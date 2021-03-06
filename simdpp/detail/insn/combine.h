/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_COMBINE_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_COMBINE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

#if SIMDPP_USE_AVX2
template<class V = void> SIMDPP_INL
uint8<32> i_combine(const uint8<16>& a, const uint8<16>& b)
{
    uint8<32> r;
    r = _mm256_castsi128_si256(a);
    r = _mm256_inserti128_si256(r, b, 1);
    return r;
}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_AVX2
template<class V = void> SIMDPP_INL
uint16<16> i_combine(const uint16<8>& a, const uint16<8>& b)
{
    uint16<16> r;
    r = _mm256_castsi128_si256(a);
    r = _mm256_inserti128_si256(r, b, 1);
    return r;
}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_AVX2
template<class V = void> SIMDPP_INL
uint32<8> i_combine(const uint32<4>& a, const uint32<4>& b)
{
    uint32<8> r;
    r = _mm256_castsi128_si256(a);
    r = _mm256_inserti128_si256(r, b, 1);
    return r;
}
#endif

#if SIMDPP_USE_AVX512
template<class V = void> SIMDPP_INL
uint32<16> i_combine(const uint32<8>& a, const uint32<8>& b)
{
    uint32<16> r;
    // r = _mm512_castsi256_si512(a); GCC BUG
    r = _mm512_inserti64x4(r, a, 0);
    r = _mm512_inserti64x4(r, b, 1);
    return r;
}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_AVX2
template<class V = void> SIMDPP_INL
uint64<4> i_combine(const uint64<2>& a, const uint64<2>& b)
{
    uint64<4> r;
    r = _mm256_castsi128_si256(a);
    r = _mm256_inserti128_si256(r, b, 1);
    return r;
}
#endif

#if SIMDPP_USE_AVX512
template<class V = void> SIMDPP_INL
uint64<8> i_combine(const uint64<4>& a, const uint64<4>& b)
{
    uint64<8> r;
    // r = _mm512_castsi256_si512(a); GCC BUG
    r = _mm512_inserti64x4(r, a, 0);
    r = _mm512_inserti64x4(r, b, 1);
    return r;}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_AVX
template<class V = void> SIMDPP_INL
float32<8> i_combine(const float32<4>& a, const float32<4> b)
{
    float32<8> r;
    r = _mm256_castps128_ps256(a);
    r = _mm256_insertf128_ps(r, b, 1);
    return r;
}
#endif

#if SIMDPP_USE_AVX512
template<class V = void> SIMDPP_INL
float32<16> i_combine(const float32<8>& a, const float32<8>& b)
{
    float64<8> r;
    // r = _mm512_castpd256_pd512(a); GCC BUG
    r = _mm512_insertf64x4(r, float64<4>(a), 0);
    r = _mm512_insertf64x4(r, float64<4>(b), 1);
    return float32<16>(r);
}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_AVX
template<class V = void> SIMDPP_INL
float64<4> i_combine(const float64<2>& a, const float64<2>& b)
{
    float64<4> r;
    r = _mm256_castpd128_pd256(a);
    r = _mm256_insertf128_pd(r, b, 1);
    return r;
}
#endif

#if SIMDPP_USE_AVX512
template<class V = void> SIMDPP_INL
float64<8> i_combine(const float64<4>& a, const float64<4>& b)
{
    float64<8> r;
    // r = _mm512_castpd256_pd512(a); GCC BUG
    r = _mm512_insertf64x4(r, a, 0);
    r = _mm512_insertf64x4(r, b, 1);
    return r;
}
#endif

// -----------------------------------------------------------------------------
// generic implementation
template<class V, class H> SIMDPP_INL
V i_combine(H a1, H a2)
{
    V r;
    unsigned h = H::vec_length;
    for (unsigned i = 0; i < h; ++i) { r.vec(i) = a1.vec(i); }
    for (unsigned i = 0; i < h; ++i) { r.vec(i+h) = a2.vec(i); }
    return r;
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
