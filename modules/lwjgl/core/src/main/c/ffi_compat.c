/*
 * Compatibility shim for libffi 3.5.0 API functions not present in libffi 3.4.8.
 *
 * These functions are declared in the LWJGL-bundled libffi 3.5.0 header but
 * are not exported by the system-installed libffi (3.4.8) on loongarch64.
 * They are trivial enough to implement in terms of the available API.
 */

#include "common_tools.h"

DISABLE_WARNINGS()
#define FFI_STATIC_BUILD
#include "ffi.h"
ENABLE_WARNINGS()

const char *ffi_get_version(void)
{
    return FFI_VERSION_STRING;
}

unsigned long ffi_get_version_number(void)
{
    return FFI_VERSION_NUMBER;
}

unsigned int ffi_get_default_abi(void)
{
#if !defined(FFI_DEFAULT_ABI)
    /* Older libffi headers may not define FFI_DEFAULT_ABI at all. */
#if __loongarch_grlen == 64
#if defined(__loongarch_soft_float)
    return FFI_LP64S;
#elif defined(__loongarch_single_float)
    return FFI_LP64F;
#elif defined(__loongarch_double_float)
    return FFI_LP64D;
#endif
#elif __loongarch_grlen == 32
#if defined(__loongarch_soft_float)
    return FFI_ILP32S;
#elif defined(__loongarch_single_float)
    return FFI_ILP32F;
#elif defined(__loongarch_double_float)
    return FFI_ILP32D;
#endif
#endif
#else
    return FFI_DEFAULT_ABI;
#endif
}

size_t ffi_get_closure_size(void)
{
    return sizeof(ffi_closure);
}
