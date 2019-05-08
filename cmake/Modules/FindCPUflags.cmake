# Clang or AppleClang (see CMP0025)
if(NOT DEFINED C_CLANG AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(C_CLANG 1)
elseif(NOT DEFINED C_GCC AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(C_GCC 1)
elseif(NOT DEFINED C_MSVC AND CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(C_MSVC 1)
endif()

# Detect current compilation architecture and create standard definitions
include(CheckSymbolExists)
function(detect_architecture symbol arch)
    if (NOT DEFINED ARCHITECTURE)
        set(CMAKE_REQUIRED_QUIET 1)
        check_symbol_exists("${symbol}" "" ARCHITECTURE_${arch})
        unset(CMAKE_REQUIRED_QUIET)

        # The output variable needs to be unique across invocations otherwise
        # CMake's crazy scope rules will keep it defined
        if (ARCHITECTURE_${arch})
            set(ARCHITECTURE "${arch}" PARENT_SCOPE)
            set(ARCHITECTURE_${arch} 1 PARENT_SCOPE)
            add_definitions(-DARCHITECTURE_${arch}=1)
        endif()
    endif()
endfunction()

if (NOT ENABLE_GENERIC)
    if (C_MSVC)
        detect_architecture("_M_AMD64" x86_64)
        detect_architecture("_M_IX86" x86)
        detect_architecture("_M_ARM" ARM)
        detect_architecture("_M_ARM64" ARM64)
    else()
        detect_architecture("__x86_64__" x86_64)
        detect_architecture("__i386__" x86)
        detect_architecture("__arm__" ARM)
        detect_architecture("__aarch64__" ARM64)
    endif()
endif()
if (NOT DEFINED ARCHITECTURE)
    set(ARCHITECTURE "GENERIC")
    set(ARCHITECTURE_GENERIC 1)
    add_definitions(-DARCHITECTURE_GENERIC=1)
endif()
message(STATUS "Target architecture: ${ARCHITECTURE}")

set(TEST_DIR ${PROJECT_SOURCE_DIR}/cmake/test)

# flag that set the minimum cpu flag requirements
# used to create re-distribuitable binary
if (${ARCHITECTURE} MATCHES "x86_64|x86" AND (FORCE_SSSE3 OR FORCE_SSE41))
    if (FORCE_SSSE3)
        set(HAS_SSSE3 ON CACHE BOOL "SSSE3 SIMD enabled")
        if(C_GCC OR C_CLANG)
            set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mssse3" )
            message(STATUS "Use SSSE3 SIMD instructions")
            add_definitions(-DUSE_SSSE3)
        elseif(C_MSVC)
            set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /arch:SSSE3" )
            set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL /Ot /Ox /arch:SSSE3" )
            set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG" )
            message(STATUS "Use MSVC SSSE3 SIMD instructions")
            add_definitions (/D "_CRT_SECURE_NO_WARNINGS")
            add_definitions(-DUSE_SSSE3)
        endif()
    elseif (FORCE_SSE41)
       set(HAS_SSSE3 ON CACHE BOOL "SSSE3 SIMD enabled")
       set(HAS_SSE4_1 ON CACHE BOOL "Architecture has SSE 4.1 SIMD enabled")
       if(C_GCC OR C_CLANG)
           set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -msse4.1" )
           set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -msse4.1" )
           message(STATUS "Use SSE 4.1 SIMD instructions")
           add_definitions(-DUSE_SSSE3)
           add_definitions(-DUSE_SSE4_1)
       elseif(C_MSVC)
           set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /arch:SSE4_1" )
           set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL /Ot /Ox /arch:SSE4_1" )
           set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG" )
           add_definitions (/D "_CRT_SECURE_NO_WARNINGS")
           add_definitions(-DUSE_SSSE3)
           add_definitions(-DUSE_SSE4_1)
       endif()
    endif()
else ()
if (${ARCHITECTURE} MATCHES "x86_64|x86")
    try_run(RUN_SSE2 COMPILE_SSE2 ${CMAKE_BINARY_DIR}/tmp ${TEST_DIR}/test_x86_sse2.cxx COMPILE_DEFINITIONS -msse2 -O0)
    if(COMPILE_SSE2 AND RUN_SSE2 EQUAL 0)
       set(HAS_SSE2 ON CACHE BOOL "Architecture has SSSE2 SIMD enabled")
       if(C_GCC OR C_CLANG)
           set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2" )
           message(STATUS "Use SSE2 SIMD instructions")
           add_definitions(-DUSE_SSE2)
       elseif(C_MSVC)
           set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /arch:SSE2" )
           set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL /Ot /Ox /arch:SSE2" )
           set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG" )
           add_definitions (/D "_CRT_SECURE_NO_WARNINGS")
           add_definitions(-DUSE_SSE2)
       endif()
    else()
       set(HAS_SSE2 OFF CACHE BOOL "Architecture does not have SSSE2 SIMD enabled")
    endif()
    try_run(RUN_SSSE3 COMPILE_SSSE3 ${CMAKE_BINARY_DIR}/tmp ${TEST_DIR}/test_x86_ssse3.cxx COMPILE_DEFINITIONS -mssse3 -O0)
    if(COMPILE_SSSE3 AND RUN_SSSE3 EQUAL 0)
       set(HAS_SSSE3 ON CACHE BOOL "Architecture has SSSE3 SIMD enabled")
       if(C_GCC OR C_CLANG)
           set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mssse3" )
           message(STATUS "Use SSSE3 SIMD instructions")
           add_definitions(-DUSE_SSSE3)
       elseif(C_MSVC)
           set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /arch:SSSE3" )
           set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL /Ot /Ox /arch:SSSE3" )
           set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG" )
           message(STATUS "Use MSVC SSSE3 SIMD instructions")
           add_definitions (/D "_CRT_SECURE_NO_WARNINGS")
           add_definitions(-DUSE_SSSE3)
       endif()
    else()
       set(HAS_SSSE3 OFF CACHE BOOL "Architecture does not have SSSE3 SIMD enabled")
    endif()
    try_run(RUN_SSE4_1 COMPILE_SSE4_1 ${CMAKE_BINARY_DIR}/tmp ${TEST_DIR}/test_x86_sse41.cxx COMPILE_DEFINITIONS -msse4.1 -O0)
    if(COMPILE_SSE4_1 AND RUN_SSE4_1 EQUAL 0)
       set(HAS_SSE4_1 ON CACHE BOOL "Architecture has SSE 4.1 SIMD enabled")
       if(C_GCC OR C_CLANG)
           set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -msse4.1" )
           set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -msse4.1" )
           message(STATUS "Use SSE 4.1 SIMD instructions")
           add_definitions(-DUSE_SSE4_1)
       elseif(C_MSVC)
           set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /arch:SSE4_1" )
           set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL /Ot /Ox /arch:SSE4_1" )
           set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG" )
           add_definitions (/D "_CRT_SECURE_NO_WARNINGS")
           add_definitions(-DUSE_SSE4_1)
       endif()
    else()
       set(HAS_SSE4_1 OFF CACHE BOOL "Architecture does not have SSE 4.1 SIMD enabled")
    endif()
    try_run(RUN_SSE4_2 COMPILE_SSE4_2 ${CMAKE_BINARY_DIR}/tmp ${TEST_DIR}/test_x86_sse42.cxx COMPILE_DEFINITIONS -msse4.2 -O0)
    if(COMPILE_SSE4_2 AND RUN_SSE4_2 EQUAL 0)
       set(HAS_SSE4_2 ON CACHE BOOL "Architecture has SSE 4.2 SIMD enabled")
       if(C_GCC OR C_CLANG)
           set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -msse4.2" )
           set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -msse4.2" )
           message(STATUS "Use SSE 4.2 SIMD instructions")
           add_definitions(-DUSE_SSE4_2)
       elseif(C_MSVC)
           set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /arch:SSE4_2" )
           set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL /Ot /Ox /arch:SSE4_2" )
           set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG" )
           add_definitions (/D "_CRT_SECURE_NO_WARNINGS")
           add_definitions(-DUSE_SSE4_2)
       endif()
    else()
       set(HAS_SSE4_2 OFF CACHE BOOL "Architecture does not have SSE 4.2 SIMD enabled")
    endif()
    try_run(RUN_AVX COMPILE_AVX ${CMAKE_BINARY_DIR}/tmp ${TEST_DIR}/test_x86_avx.cxx COMPILE_DEFINITIONS -mavx -O0)
    if(COMPILE_AVX AND RUN_AVX EQUAL 0)
       set(HAS_AVX ON CACHE BOOL "Architecture has AVX SIMD enabled")
       if(C_GCC OR C_CLANG)
           set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mavx" )
           set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mavx" )
           message(STATUS "Use AVX SIMD instructions")
           add_definitions(-DUSE_AVX)
       endif()
    else()
       set(HAS_AVX OFF CACHE BOOL "Architecture does not have AVX SIMD enabled")
    endif()
    try_run(RUN_AVX2 COMPILE_AVX2 ${CMAKE_BINARY_DIR}/tmp ${TEST_DIR}/test_x86_avx2.cxx COMPILE_DEFINITIONS -mavx2 -O0)
    if(COMPILE_AVX2 AND RUN_AVX2 EQUAL 0)
       set(HAS_AVX2 ON CACHE BOOL "Architecture has AVX2 SIMD enabled")
       if(C_GCC OR C_CLANG)
           set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mavx2" )
           set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mavx2" )
           message(STATUS "Use AVX2 SIMD instructions")
           add_definitions(-DUSE_AVX2)
       endif()
    else()
       set(HAS_AVX2 OFF CACHE BOOL "Architecture does not have AVX2 SIMD enabled")
    endif()
    try_run(RUN_AVX512 COMPILE_AVX512 ${CMAKE_BINARY_DIR}/tmp ${TEST_DIR}/test_x86_avx512.cxx COMPILE_DEFINITIONS -mavx512f -O0)
    if(COMPILE_AVX512 AND RUN_AVX512 EQUAL 0)
       set(HAS_AVX512 ON CACHE BOOL "Architecture has AVX512 SIMD enabled")
       if(C_GCC OR C_CLANG)
           set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mavx512f" )
           set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mavx512f" )
           message(STATUS "Use AVX512 SIMD instructions")
           add_definitions(-DUSE_AVX512)
       endif()
    else()
       set(HAS_AVX512 OFF CACHE BOOL "Architecture does not have AVX512 SIMD enabled")
    endif()
elseif(ARCHITECTURE_ARM)
    try_run(RUN_NEON COMPILE_NEON ${CMAKE_BINARY_DIR}/tmp ${TEST_DIR}/test_arm_neon.cxx COMPILE_DEFINITIONS -mfpu=neon -O0)
    if(COMPILE_NEON AND RUN_NEON EQUAL 0)
       set(HAS_NEON ON CACHE BOOL "Architecture has NEON SIMD enabled")
       if(C_GCC OR C_CLANG)
           set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mfpu=neon" )
           set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mfpu=neon" )
           message(STATUS "Use NEON SIMD instructions")
           add_definitions(-DUSE_NEON)
       endif()
    else()
       set(HAS_NEON OFF CACHE BOOL "Architecture does not have NEON SIMD enabled")
    endif()
elseif(ARCHITECTURE_ARM64)
    # Advanced SIMD (aka NEON) is mandatory for AArch64
    set(HAS_NEON ON CACHE BOOL "Architecture has NEON SIMD enabled")
    message(STATUS "Use NEON SIMD instructions")
    add_definitions(-DUSE_NEON)
endif()
endif()

# clear binary test folder
FILE(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/tmp)
