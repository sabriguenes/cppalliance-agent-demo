// SIMD utility functions using SSE intrinsics.
// Use <immintrin.h> for cross-compiler compatibility (Clang + GCC).
// Direct inclusion of <xmmintrin.h> causes "definition of builtin function"
// errors with Clang, which treats SSE intrinsics as compiler builtins.
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
