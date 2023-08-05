// _mm_cvtss_f32, _mm_setzero_ps, __m128
#include <xmmintrin.h>

auto main()
    -> int
{
    __m128 x = {};
    //__m128 x = ::_mm_setzero_ps();

    return ::_mm_cvtss_f32(x);
}
