// SIMD utility functions using SSE intrinsics.
// Use immintrin.h (Intel's unified intrinsics header) instead of xmmintrin.h
// to avoid Clang/GCC incompatibility where Clang treats _mm_getcsr/_mm_setcsr
// as compiler builtins, conflicting with GCC's inline function definitions.
#include <immintrin.h>

namespace simd {

unsigned int get_mxcsr() {
    return _mm_getcsr();
}

void set_mxcsr(unsigned int flags) {
    _mm_setcsr(flags);
}

// Flush denormals to zero for better SIMD performance
void enable_flush_denormals() {
    unsigned int mxcsr = _mm_getcsr();
    mxcsr |= 0x8040; // FTZ | DAZ bits
    _mm_setcsr(mxcsr);
}

} // namespace simd
