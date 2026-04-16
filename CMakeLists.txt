cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)
endif()

project(Protocol VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(FetchContent)

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

find_package(OpenSSL 3 REQUIRED)

set(REFLECTION_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    reflection
    GIT_REPOSITORY https://github.com/SculkCatalystMC/Reflection.git
    GIT_TAG v1.4.0
)
FetchContent_MakeAvailable(reflection)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE PROTOCOL_SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_library(Protocol STATIC ${PROTOCOL_SOURCES})
add_library(Protocol::Protocol ALIAS Protocol)

set_target_properties(Protocol PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_compile_features(Protocol PUBLIC cxx_std_23)
target_link_libraries(Protocol PRIVATE reflection::reflection OpenSSL::Crypto)

target_include_directories(Protocol PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(MSVC)
    target_compile_options(Protocol PRIVATE 
        /W4
        /utf-8
        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:RelWithDebInfo>:/O2>
    )
    target_compile_definitions(Protocol PRIVATE 
        UNICODE
        NOMINMAX
    )
else()
    target_compile_options(Protocol PRIVATE 
       -Wall
       -Wextra
       -Wpedantic
       $<$<CONFIG:Release>:-O3>
       $<$<CONFIG:RelWithDebInfo>:-O3>
    )
endif()

install(TARGETS Protocol
    EXPORT ProtocolTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/ProtocolConfig.cmake.in
    ${PROJECT_BINARY_DIR}/ProtocolConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Protocol
)

write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/ProtocolConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(EXPORT ProtocolTargets
    FILE ProtocolTargets.cmake
    NAMESPACE Protocol::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Protocol
)

install(FILES
    ${PROJECT_BINARY_DIR}/ProtocolConfig.cmake
    ${PROJECT_BINARY_DIR}/ProtocolConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Protocol
)