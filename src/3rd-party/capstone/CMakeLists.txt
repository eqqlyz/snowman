#
# Ugly. Is there a better way?
#

set(CAPSTONE_BUILD_DIET OFF CACHE BOOL "")
set(CAPSTONE_BUILD_STATIC ON CACHE BOOL "")
set(CAPSTONE_BUILD_SHARED OFF CACHE BOOL "")
set(CAPSTONE_BUILD_TESTS OFF CACHE BOOL "")
set(CAPSTONE_ARM_SUPPORT OFF CACHE BOOL "")
set(CAPSTONE_ARM64_SUPPORT OFF CACHE BOOL "")
set(CAPSTONE_MIPS_SUPPORT OFF CACHE BOOL "")
set(CAPSTONE_RISCV_SUPPORT ON CACHE BOOL "")
set(CAPSTONE_PPC_SUPPORT OFF CACHE BOOL "")
set(CAPSTONE_SPARC_SUPPORT OFF CACHE BOOL "")
set(CAPSTONE_SYSZ_SUPPORT OFF CACHE BOOL "")
set(CAPSTONE_XCORE_SUPPORT OFF CACHE BOOL "")
set(CAPSTONE_X86_SUPPORT ON CACHE BOOL "")
set(CAPSTONE_X86_REDUCE OFF CACHE BOOL "")
set(CAPSTONE_USE_DEFAULT_ALLOC ON CACHE BOOL "")

mark_as_advanced(
    CAPSTONE_BUILD_DIET
    CAPSTONE_BUILD_STATIC
    CAPSTONE_BUILD_SHARED
    CAPSTONE_BUILD_TESTS
    CAPSTONE_ARM_SUPPORT
    CAPSTONE_ARM64_SUPPORT
    CAPSTONE_MIPS_SUPPORT
    CAPSTONE_RISCV_SUPPORT
    CAPSTONE_PPC_SUPPORT
    CAPSTONE_SPARC_SUPPORT
    CAPSTONE_SYSZ_SUPPORT
    CAPSTONE_XCORE_SUPPORT
    CAPSTONE_X86_SUPPORT
    CAPSTONE_X86_REDUCE
    CAPSTONE_USE_DEFAULT_ALLOC
    CAPSTONE_X86_ATT_DISABLE
    CAPSTONE_BUILD_STATIC_RUNTIME
    CAPSTONE_OSXKERNEL_SUPPORT)

if(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
    add_definitions(-Wno-extra -Wno-unused-function -Wno-unknown-pragmas)
endif()

if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    add_definitions(-Wno-extra)
endif()

if(${MSVC})
    add_definitions(/wd4244)
endif()

add_subdirectory(capstone)

# vim:set et sts=4 sw=4 nospell:
