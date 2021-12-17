cmake_minimum_required(VERSION 3.13)
project(DString C)

set(CMAKE_C_STANDARD 11)

set(SOURCES src/dstring.c)

add_library(
    dstring SHARED
    ${SOURCES}
)

add_library(
    dstringStatic STATIC
    ${SOURCES}
)

set_target_properties(dstringStatic PROPERTIES OUTPUT_NAME dstring)

add_library(DString::DString ALIAS dstring)
add_library(DString::DString::Static ALIAS dstringStatic)

target_include_directories(
    dstring
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    #    PUBLIC include
)

target_include_directories(
    dstringStatic
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)

install(
    TARGETS dstring dstringStatic
    EXPORT DStringTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    FILES
    include/dstring.h
    TYPE INCLUDE
    COMPONENT
    Devel
)

install(
    EXPORT DStringTargets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DString
    NAMESPACE DString::
    FILE DStringTargets.cmake
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "cmake/Config.cmake.in"
    "cmake/DStringConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DString
    PATH_VARS
    CMAKE_INSTALL_LIBDIR
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/DStringConfigVersion.cmake
    VERSION 0.1.0
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/DStringConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/DStringConfigVersion.cmake"
    DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/DString"
)