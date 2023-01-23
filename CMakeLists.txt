cmake_minimum_required(VERSION 3.0.2)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{DEVKITPRO})
        set(DEVKITPRO $ENV{DEVKITPRO})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{DEVKITPRO}/switch.cmake" CACHE PATH "toolchain file")
    else()
        message(FATAL_ERROR "Please define DEVKITPRO to point to your SDK path!")
    endif()
endif()

project(otrh)

set(SWITCH_APP_NAME "TestHomebrew")
set(SWITCH_AUTHOR   "Otorhin")
set(SWITCH_VERSION  "1.0")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(C_FLAGS
    -D__SWITCH__
)

set(CXX_FLAGS ${C_FLAGS}
    -fno-rtti 
    -fno-exceptions
)

set(OPTIMIZATION_FLAGS
    -Ofast
)

set(SOURCES
    source/main.c
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FREETYPE2 REQUIRED IMPORTED_TARGET freetype2)
pkg_check_modules(LIBAVCODEC REQUIRED IMPORTED_TARGET libavcodec)
pkg_check_modules(LIBAVFILTER REQUIRED IMPORTED_TARGET libavfilter)
pkg_check_modules(LIBAVFORMAT REQUIRED IMPORTED_TARGET libavformat)
pkg_check_modules(LIBAVUTIL REQUIRED IMPORTED_TARGET libavutil)
pkg_check_modules(LIBPNG REQUIRED IMPORTED_TARGET libpng)
pkg_check_modules(LIBSWSCALE REQUIRED IMPORTED_TARGET libswscale)
pkg_check_modules(LIBTURBOJPEG REQUIRED IMPORTED_TARGET libturbojpeg)
pkg_check_modules(LIBWEBP REQUIRED IMPORTED_TARGET libwebp)
pkg_check_modules(OGG REQUIRED IMPORTED_TARGET ogg)
pkg_check_modules(ONIGURUMA REQUIRED IMPORTED_TARGET oniguruma)
pkg_check_modules(OPUS REQUIRED IMPORTED_TARGET opus)
pkg_check_modules(OPUSFILE REQUIRED IMPORTED_TARGET opusfile)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(VORBIS REQUIRED IMPORTED_TARGET vorbis)
pkg_check_modules(VORBISFILE REQUIRED IMPORTED_TARGET vorbisfile)
pkg_check_modules(ZLIB REQUIRED IMPORTED_TARGET zlib)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PkgConfig::FREETYPE2
    PkgConfig::LIBAVCODEC
    PkgConfig::LIBAVFILTER
    PkgConfig::LIBAVFORMAT
    PkgConfig::LIBAVUTIL
    PkgConfig::LIBPNG
    PkgConfig::LIBSWSCALE
    PkgConfig::LIBTURBOJPEG
    PkgConfig::LIBWEBP
    PkgConfig::OGG
    PkgConfig::ONIGURUMA
    PkgConfig::OPUS
    PkgConfig::OPUSFILE
    PkgConfig::SDL2
    PkgConfig::VORBIS
    PkgConfig::VORBISFILE
    PkgConfig::ZLIB
)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
target_compile_options(${PROJECT_NAME} PUBLIC $<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>)
target_compile_options(${PROJECT_NAME} PUBLIC $<$<COMPILE_LANGUAGE:CXX>:${CXX_FLAGS}>)
target_compile_options(${PROJECT_NAME} PUBLIC $<$<CONFIG:RELEASE>:${OPTIMIZATION_FLAGS}>)
target_compile_options(${PROJECT_NAME} PUBLIC $<$<CONFIG:RELWITHDEBINFO>:${OPTIMIZATION_FLAGS}>)

add_custom_target(${PROJECT_NAME}.nacp
    COMMAND ${DEVKITPRO}/tools/bin/nacptool
        --create
        ${SWITCH_APP_NAME}
        ${SWITCH_AUTHOR}
        ${SWITCH_VERSION}
        ${PROJECT_NAME}.nacp
)
add_custom_target(${PROJECT_NAME}.nro ALL
    COMMAND ${DEVKITPRO}/tools/bin/elf2nro
        ${PROJECT_NAME}
        ${PROJECT_NAME}.nro
        --icon=${CMAKE_SOURCE_DIR}/icon.jpg
        --nacp=${PROJECT_NAME}.nacp
    DEPENDS ${PROJECT_NAME}.nacp ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/icon.jpg
)

add_custom_target(${PROJECT_NAME}.nso ALL
    COMMAND ${DEVKITPRO}/tools/bin/elf2nso
        ${PROJECT_NAME}
        ${PROJECT_NAME}.nso
)