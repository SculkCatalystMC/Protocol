// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/connection/encryption/JsonWebToken.hpp"
#include "../../utility/Reflection.hpp"
#include "sculk/protocol/connection/encryption/Base64Url.hpp"
#include <array>
#include <memory>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/ecdsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <vector>

namespace sculk::protocol::inline abi_v944 {

namespace {

constexpr std::size_t ES384_COORDINATE_SIZE = 48;
constexpr std::size_t ES384_SIGNATURE_SIZE  = ES384_COORDINATE_SIZE * 2;
constexpr std::size_t RS256_SIGNATURE_SIZE  = 256;

struct BioDeleter {
    void operator()(BIO* bio) const noexcept { BIO_free(bio); }
};

struct EvpPkeyDeleter {
    void operator()(EVP_PKEY* pkey) const noexcept { EVP_PKEY_free(pkey); }
};

struct EvpMdCtxDeleter {
    void operator()(EVP_MD_CTX* ctx) const noexcept { EVP_MD_CTX_free(ctx); }
};

struct BignumDeleter {
    void operator()(BIGNUM* bn) const noexcept { BN_free(bn); }
};

struct EcdsaSigDeleter {
    void operator()(ECDSA_SIG* sig) const noexcept { ECDSA_SIG_free(sig); }
};

using BioPtr      = std::unique_ptr<BIO, BioDeleter>;
using EvpPkeyPtr  = std::unique_ptr<EVP_PKEY, EvpPkeyDeleter>;
using EvpMdCtxPtr = std::unique_ptr<EVP_MD_CTX, EvpMdCtxDeleter>;
using BignumPtr   = std::unique_ptr<BIGNUM, BignumDeleter>;
using EcdsaSigPtr = std::unique_ptr<ECDSA_SIG, EcdsaSigDeleter>;

std::string getSigningInput(const JsonWebToken& token) { return token.mRawHeader + "." + token.mRawPayload; }

EvpPkeyPtr readPublicKey(std::string_view pem) {
    BioPtr bio(BIO_new_mem_buf(pem.data(), static_cast<int>(pem.size())));
    if (!bio) {
        return nullptr;
    }

    return EvpPkeyPtr(PEM_read_bio_PUBKEY(bio.get(), nullptr, nullptr, nullptr));
}

EvpPkeyPtr readPrivateKey(std::string_view pem) {
    BioPtr bio(BIO_new_mem_buf(pem.data(), static_cast<int>(pem.size())));
    if (!bio) {
        return nullptr;
    }

    return EvpPkeyPtr(PEM_read_bio_PrivateKey(bio.get(), nullptr, nullptr, nullptr));
}

std::vector<std::uint8_t> es384RawToDer(std::string_view rawSignature) {
    if (rawSignature.size() != ES384_SIGNATURE_SIZE) {
        return {};
    }

    BignumPtr r(BN_bin2bn(
        reinterpret_cast<const std::uint8_t*>(rawSignature.data()),
        static_cast<int>(ES384_COORDINATE_SIZE),
        nullptr
    ));
    BignumPtr s(BN_bin2bn(
        reinterpret_cast<const std::uint8_t*>(rawSignature.data() + ES384_COORDINATE_SIZE),
        static_cast<int>(ES384_COORDINATE_SIZE),
        nullptr
    ));
    if (!r || !s) {
        return {};
    }

    EcdsaSigPtr sig(ECDSA_SIG_new());
    if (!sig || ECDSA_SIG_set0(sig.get(), r.release(), s.release()) != 1) {
        return {};
    }

    int derLen = i2d_ECDSA_SIG(sig.get(), nullptr);
    if (derLen <= 0) {
        return {};
    }

    std::vector<std::uint8_t> der(static_cast<std::size_t>(derLen));
    std::uint8_t*             derPtr = der.data();
    if (i2d_ECDSA_SIG(sig.get(), &derPtr) != derLen) {
        return {};
    }

    return der;
}

std::string es384DerToRaw(const std::uint8_t* derData, std::size_t derSize) {
    const std::uint8_t* derPtr = derData;
    EcdsaSigPtr         sig(d2i_ECDSA_SIG(nullptr, &derPtr, static_cast<long>(derSize)));
    if (!sig) {
        return {};
    }

    const BIGNUM* r = nullptr;
    const BIGNUM* s = nullptr;
    ECDSA_SIG_get0(sig.get(), &r, &s);
    if (!r || !s) {
        return {};
    }

    std::array<std::uint8_t, ES384_SIGNATURE_SIZE> raw{};
    if (BN_bn2binpad(r, raw.data(), static_cast<int>(ES384_COORDINATE_SIZE)) != static_cast<int>(ES384_COORDINATE_SIZE)
        || BN_bn2binpad(s, raw.data() + ES384_COORDINATE_SIZE, static_cast<int>(ES384_COORDINATE_SIZE))
               != static_cast<int>(ES384_COORDINATE_SIZE)) {
        return {};
    }

    return {reinterpret_cast<const char*>(raw.data()), raw.size()};
}

} // namespace

JsonWebToken::Algorithm JsonWebToken::getAlgorithm() const { return mHeader.alg; }

bool JsonWebToken::verifyES384(std::string_view ecPublicKeyPem) const {
    if (mSignature.size() != ES384_SIGNATURE_SIZE) {
        return false;
    }

    EvpPkeyPtr pkey = readPublicKey(ecPublicKeyPem);
    if (!pkey || EVP_PKEY_base_id(pkey.get()) != EVP_PKEY_EC) {
        return false;
    }

    std::vector<std::uint8_t> derSignature = es384RawToDer(mSignature);
    if (derSignature.empty()) {
        return false;
    }

    EvpMdCtxPtr ctx(EVP_MD_CTX_new());
    if (!ctx) {
        return false;
    }

    const std::string signingInput = getSigningInput(*this);
    const bool        ok           = EVP_DigestVerifyInit(ctx.get(), nullptr, EVP_sha384(), nullptr, pkey.get()) == 1
                 && EVP_DigestVerifyUpdate(ctx.get(), signingInput.data(), signingInput.size()) == 1
                 && EVP_DigestVerifyFinal(ctx.get(), derSignature.data(), derSignature.size()) == 1;

    return ok;
}

bool JsonWebToken::verifyRS256(std::string_view rsaPublicKeyPem) const {
    if (mSignature.size() != RS256_SIGNATURE_SIZE) {
        return false;
    }

    EvpPkeyPtr pkey = readPublicKey(rsaPublicKeyPem);
    if (!pkey || EVP_PKEY_base_id(pkey.get()) != EVP_PKEY_RSA) {
        return false;
    }

    EvpMdCtxPtr ctx(EVP_MD_CTX_new());
    if (!ctx) {
        return false;
    }

    const std::string signingInput = getSigningInput(*this);
    const bool        ok =
        EVP_DigestVerifyInit(ctx.get(), nullptr, EVP_sha256(), nullptr, pkey.get()) == 1
        && EVP_DigestVerifyUpdate(ctx.get(), signingInput.data(), signingInput.size()) == 1
        && EVP_DigestVerifyFinal(ctx.get(), reinterpret_cast<const std::uint8_t*>(mSignature.data()), mSignature.size())
               == 1;

    return ok;
}

bool JsonWebToken::verify(std::string_view publicKeyPem) const {
    switch (getAlgorithm()) {
    case Algorithm::ES384:
        return verifyES384(publicKeyPem);
    case Algorithm::RS256:
        return verifyRS256(publicKeyPem);
    default:
        return false;
    }
}

std::string JsonWebToken::signES384(std::string_view eccPrivateKeyPem) {
    mHeader.alg = Algorithm::ES384;
    mSignature.clear();

    EvpPkeyPtr pkey = readPrivateKey(eccPrivateKeyPem);
    if (!pkey || EVP_PKEY_base_id(pkey.get()) != EVP_PKEY_EC) {
        return {};
    }

    EvpMdCtxPtr ctx(EVP_MD_CTX_new());
    if (!ctx) {
        return {};
    }

    const std::string signingInput = getSigningInput(*this);
    std::size_t       derSize      = 0;
    bool              ok           = EVP_DigestSignInit(ctx.get(), nullptr, EVP_sha384(), nullptr, pkey.get()) == 1
           && EVP_DigestSignUpdate(ctx.get(), signingInput.data(), signingInput.size()) == 1
           && EVP_DigestSignFinal(ctx.get(), nullptr, &derSize) == 1;

    std::vector<std::uint8_t> derSignature;
    if (ok) {
        derSignature.resize(derSize);
        ok = EVP_DigestSignFinal(ctx.get(), derSignature.data(), &derSize) == 1;
        if (ok) {
            derSignature.resize(derSize);
        }
    }

    if (!ok) {
        return {};
    }

    std::string rawSignature = es384DerToRaw(derSignature.data(), derSignature.size());
    if (rawSignature.size() != ES384_SIGNATURE_SIZE) {
        return {};
    }

    mSignature                         = rawSignature;
    const std::string encodedSignature = base64url::encode(rawSignature);
    return mRawHeader + "." + mRawPayload + "." + encodedSignature;
}

std::string JsonWebToken::signRS256(std::string_view rsaPrivateKeyPem) {
    mHeader.alg = Algorithm::RS256;
    mSignature.clear();

    EvpPkeyPtr pkey = readPrivateKey(rsaPrivateKeyPem);
    if (!pkey || EVP_PKEY_base_id(pkey.get()) != EVP_PKEY_RSA) {
        return {};
    }

    EvpMdCtxPtr ctx(EVP_MD_CTX_new());
    if (!ctx) {
        return {};
    }

    const std::string signingInput  = getSigningInput(*this);
    std::size_t       signatureSize = 0;
    bool              ok            = EVP_DigestSignInit(ctx.get(), nullptr, EVP_sha256(), nullptr, pkey.get()) == 1
           && EVP_DigestSignUpdate(ctx.get(), signingInput.data(), signingInput.size()) == 1
           && EVP_DigestSignFinal(ctx.get(), nullptr, &signatureSize) == 1;

    std::vector<std::uint8_t> signature;
    if (ok) {
        signature.resize(signatureSize);
        ok = EVP_DigestSignFinal(ctx.get(), signature.data(), &signatureSize) == 1;
        if (ok) {
            signature.resize(signatureSize);
        }
    }

    if (!ok || signature.size() != RS256_SIGNATURE_SIZE) {
        return {};
    }

    mSignature = {reinterpret_cast<const char*>(signature.data()), signature.size()};
    const std::string encodedSignature =
        base64url::encode({reinterpret_cast<const char*>(signature.data()), signature.size()});
    return mRawHeader + "." + mRawPayload + "." + encodedSignature;
}

} // namespace sculk::protocol::inline abi_v944
