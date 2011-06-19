/*
 * Copyright (C) 2010 Simon A. Berger
 *
 *  This program is free software; you may redistribute it and/or modify its
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 */


#ifndef __vec_unit_h
#define __vec_unit_h
#include <iostream>

#include <arm_neon.h>
template<class T, size_t W>
struct vector_unit {

};


template<>
struct vector_unit<short,8> {
    const static bool do_checks = false;

    typedef int16x8_t vec_t;
    typedef short T;
    const static T POS_MAX_VALUE = 0x7fff;
    const static T LARGE_VALUE = 32000;
    const static T SMALL_VALUE = -32000;
    const static T BIAS = 0;
    const static size_t W = 4;

    static inline vec_t setzero() {
        return set1(0);
    }

    static inline vec_t set1( T val ) {
        return vdupq_n_s16(val);
    }

    static inline void store( vec_t v, T *addr ) {

        vst1q_s16( addr, v );
    }

    static inline const vec_t load( T* addr ) {
        return vld1q_s16( addr );
    }

//    static inline const vec_t bit_and( const vec_t &a, const vec_t &b ) {
//        return _mm_and_si128( a, b );
//    }
//
//    static inline const vec_t bit_andnot( const vec_t &a, const vec_t &b ) {
//        return _mm_andnot_si128( a, b );
//    }

//     static inline const vec_t bit_invert( const vec_t &a ) {
//         //return _mm_andnot_pd(a, set1(0xffff));
//     }

    static inline const vec_t add( const vec_t &a, const vec_t &b ) {
        return vaddq_s16( a, b );
    }
    static inline const vec_t adds( const vec_t &a, const vec_t &b ) {
        // there is no saturating add for 32bit int. Just hope that nothing bad will happen.
        // Treat saturation as kind of 'best effort hint'
        return add( a, b );
    }

    static inline const vec_t sub( const vec_t &a, const vec_t &b ) {
        return vsubq_s16( a, b );
    }
//    static inline const vec_t cmp_zero( const vec_t &a ) {
//        return _mm_cmpeq_epi32( a, setzero() );
//    }

//    static inline const vec_t cmp_eq( const vec_t &a, const vec_t &b ) {
//        return _mm_cmpeq_epi32( a, b );
//    }
//
//    static inline const vec_t cmp_lt( const vec_t &a, const vec_t &b ) {
//
//        return _mm_cmplt_epi32( a, b );
//    }

    static inline const vec_t min( const vec_t &a, const vec_t &b ) {
    	return vminq_s16( a, b );

    }

    static inline const vec_t max( const vec_t &a, const vec_t &b ) {
    	return vmaxq_s16( a, b );
    }

    static inline const vec_t abs_diff( const vec_t &a, const vec_t &b ) {
        return vabsq_s16(sub(a,b));
    }

};

template<>
struct vector_unit<int,4> {
    const static bool do_checks = false;

    typedef int32x4_t vec_t;
    typedef int T;
    const static T POS_MAX_VALUE = 0x7fffffff;
    const static T LARGE_VALUE = 2100000000;
    const static T SMALL_VALUE = -2100000000;
    const static T BIAS = 0;
    const static size_t W = 4;

    static inline vec_t setzero() {
        return set1(0);
    }

    static inline vec_t set1( T val ) {
        return vdupq_n_s32(val);
    }

    static inline void store( vec_t v, T *addr ) {

        vst1q_s32( addr, v );
    }

    static inline const vec_t load( T* addr ) {
        return vld1q_s32( addr );
    }

//    static inline const vec_t bit_and( const vec_t &a, const vec_t &b ) {
//        return _mm_and_si128( a, b );
//    }
//
//    static inline const vec_t bit_andnot( const vec_t &a, const vec_t &b ) {
//        return _mm_andnot_si128( a, b );
//    }

//     static inline const vec_t bit_invert( const vec_t &a ) {
//         //return _mm_andnot_pd(a, set1(0xffff));
//     }

    static inline const vec_t add( const vec_t &a, const vec_t &b ) {
        return vaddq_s32( a, b );
    }
    static inline const vec_t adds( const vec_t &a, const vec_t &b ) {
        // there is no saturating add for 32bit int. Just hope that nothing bad will happen.
        // Treat saturation as kind of 'best effort hint'
        return add( a, b );
    }

    static inline const vec_t sub( const vec_t &a, const vec_t &b ) {
        return vsubq_s32( a, b );
    }
//    static inline const vec_t cmp_zero( const vec_t &a ) {
//        return _mm_cmpeq_epi32( a, setzero() );
//    }

//    static inline const vec_t cmp_eq( const vec_t &a, const vec_t &b ) {
//        return _mm_cmpeq_epi32( a, b );
//    }
//
//    static inline const vec_t cmp_lt( const vec_t &a, const vec_t &b ) {
//
//        return _mm_cmplt_epi32( a, b );
//    }

    static inline const vec_t min( const vec_t &a, const vec_t &b ) {
    	return vminq_s32( a, b );

    }

    static inline const vec_t max( const vec_t &a, const vec_t &b ) {
    	return vmaxq_s32( a, b );
    }

    static inline const vec_t abs_diff( const vec_t &a, const vec_t &b ) {
        return vabsq_s32(sub(a,b));
    }

};

template<>
struct vector_unit<float,4> {
    const static bool do_checks = false;

    typedef float32x4_t vec_t;
    typedef float T;

    const static T LARGE_VALUE = 1e8;
    const static T SMALL_VALUE = -1e8;
    const static T BIAS = 0;
    const static size_t W = 4;

    static inline vec_t setzero() {
        return set1(0);
    }

    static inline vec_t set1( T val ) {
        return vdupq_n_f32(val);
    }

    static inline void store( vec_t v, T *addr ) {

        vst1q_f32( (float32_t*)addr, v );
    }

    static inline const vec_t load( T* addr ) {
        return vld1q_f32( (float32_t*)addr );
    }

//    static inline const vec_t bit_and( const vec_t &a, const vec_t &b ) {
//        return _mm_and_si128( a, b );
//    }
//
//    static inline const vec_t bit_andnot( const vec_t &a, const vec_t &b ) {
//        return _mm_andnot_si128( a, b );
//    }

//     static inline const vec_t bit_invert( const vec_t &a ) {
//         //return _mm_andnot_pd(a, set1(0xffff));
//     }

    static inline const vec_t add( const vec_t &a, const vec_t &b ) {
        return vaddq_f32( a, b );
    }
    static inline const vec_t adds( const vec_t &a, const vec_t &b ) {
        // there is no saturating add for 32bit int. Just hope that nothing bad will happen.
        // Treat saturation as kind of 'best effort hint'
        return add( a, b );
    }

    static inline const vec_t sub( const vec_t &a, const vec_t &b ) {
        return vsubq_f32( a, b );
    }
//    static inline const vec_t cmp_zero( const vec_t &a ) {
//        return _mm_cmpeq_epi32( a, setzero() );
//    }

//    static inline const vec_t cmp_eq( const vec_t &a, const vec_t &b ) {
//        return _mm_cmpeq_epi32( a, b );
//    }
//
//    static inline const vec_t cmp_lt( const vec_t &a, const vec_t &b ) {
//
//        return _mm_cmplt_epi32( a, b );
//    }

    static inline const vec_t min( const vec_t &a, const vec_t &b ) {
    	return vminq_f32( a, b );

    }

    static inline const vec_t max( const vec_t &a, const vec_t &b ) {
    	return vmaxq_f32( a, b );
    }

    static inline const vec_t abs_diff( const vec_t &a, const vec_t &b ) {
        return vabsq_f32(sub(a,b));
    }

};



#if 0
#include <immintrin.h>

#ifdef __AVX__
#define HAVE_AVX
//#include <immintrin.h>
#endif

template<class T, size_t W> 
struct vector_unit {
   
};

// vector unit specialization: SSE 8x16bit integer 

template<>
struct vector_unit<short, 8> {

    const static bool do_checks = false;
    
    typedef __m128i vec_t;
    typedef short T;

    
    const static T POS_MAX_VALUE = 0x7fff;
    const static T LARGE_VALUE = 32000;
    const static T SMALL_VALUE = -32000;
    const static T BIAS = 0;
    const static size_t W = 8;
    
    static inline vec_t setzero() {
        return set1(0);
    }
    
    static inline vec_t set1( T val ) {
        return _mm_set1_epi16( val );
    }
    
    static inline void store( const vec_t &v, T *addr ) {

        if( do_checks && addr == 0 ) {
            throw std::runtime_error( "store: addr == 0" );
        }
        //std::cout << "store to: " << addr << "\n";
        
        _mm_store_si128( (vec_t*)addr, v );
    }
    
    static inline const vec_t load( T* addr ) {
        return _mm_load_si128( (vec_t*)addr );
    }
    
    static inline const vec_t bit_and( const vec_t &a, const vec_t &b ) {
        return _mm_and_si128( a, b );
    }
    
    static inline const vec_t bit_andnot( const vec_t &a, const vec_t &b ) {
        return _mm_andnot_si128( a, b );
    }
    
//     static inline const vec_t bit_invert( const vec_t &a ) {
//         //return _mm_andnot_pd(a, set1(0xffff));
//     }
    
    static inline const vec_t add( const vec_t &a, const vec_t &b ) {
        return _mm_add_epi16( a, b );
    }
    static inline const vec_t adds( const vec_t &a, const vec_t &b ) {
        return _mm_adds_epi16( a, b );
    }
    
    static inline const vec_t sub( const vec_t &a, const vec_t &b ) {
        return _mm_sub_epi16( a, b );
    }
    static inline const vec_t cmp_zero( const vec_t &a ) {
        return _mm_cmpeq_epi16( a, setzero() );
    }
    
    static inline const vec_t cmp_eq( const vec_t &a, const vec_t &b ) {
        return _mm_cmpeq_epi16( a, b );
    }
    
    static inline const vec_t cmp_lt( const vec_t &a, const vec_t &b ) {
     
        return _mm_cmplt_epi16( a, b );
    }
    
    static inline const vec_t min( const vec_t &a, const vec_t &b ) {
        return _mm_min_epi16( a, b );
    }
    
    static inline const vec_t max( const vec_t &a, const vec_t &b ) {
        return _mm_max_epi16( a, b );
    }
    
    static inline const vec_t abs_diff( const vec_t &a, const vec_t &b ) {
        // i don't really like this function, as ideally this would just be abs(sub(a,b)), 
        // but there doesn't seem to be a fast way to implement abs on pre SSSSSSE3.
        // The max(sub(a,b),sub(b,a)) work-around seems to be the next-best thing in this special case.
        
        #ifdef __SSSE3__
        return _mm_abs_epi16(sub(a,b));
        #else
        // FIXME: is there a faster method for boring old CPUs?
        return max( sub(a,b), sub(b,a) );
//         #error missing SSSSSSSSSE3
        #endif
    }
    
};

template<>
struct vector_unit<int, 4> {

    const static bool do_checks = false;
    
    typedef __m128i vec_t;
    typedef int T;
    const static T POS_MAX_VALUE = 0x7fffffff;
    const static T LARGE_VALUE = 2100000000;
    const static T SMALL_VALUE = -2100000000;
    const static T BIAS = 0;
    const static size_t W = 4;
    
    static inline vec_t setzero() {
        return set1(0);
    }
    
    static inline vec_t set1( T val ) {
        return _mm_set1_epi32( val );
    }
    
    static inline void store( const vec_t &v, T *addr ) {

        if( do_checks && addr == 0 ) {
            throw std::runtime_error( "store: addr == 0" );
        }
        //std::cout << "store to: " << addr << "\n";
        
        _mm_store_si128( (vec_t*)addr, v );
    }
    
    static inline const vec_t load( T* addr ) {
        return _mm_load_si128( (vec_t*)addr );
    }
    
    static inline const vec_t bit_and( const vec_t &a, const vec_t &b ) {
        return _mm_and_si128( a, b );
    }
    
    static inline const vec_t bit_andnot( const vec_t &a, const vec_t &b ) {
        return _mm_andnot_si128( a, b );
    }
    
//     static inline const vec_t bit_invert( const vec_t &a ) {
//         //return _mm_andnot_pd(a, set1(0xffff));
//     }
    
    static inline const vec_t add( const vec_t &a, const vec_t &b ) {
        return _mm_add_epi32( a, b );
    }
    static inline const vec_t adds( const vec_t &a, const vec_t &b ) {
        // there is no saturating add for 32bit int. Just hope that nothing bad will happen.
        // Treat saturation as kind of 'best effort hint'
        return _mm_add_epi32( a, b );
    }
    
    static inline const vec_t sub( const vec_t &a, const vec_t &b ) {
        return _mm_sub_epi32( a, b );
    }
    static inline const vec_t cmp_zero( const vec_t &a ) {
        return _mm_cmpeq_epi32( a, setzero() );
    }
    
    static inline const vec_t cmp_eq( const vec_t &a, const vec_t &b ) {
        return _mm_cmpeq_epi32( a, b );
    }
    
    static inline const vec_t cmp_lt( const vec_t &a, const vec_t &b ) {
     
        return _mm_cmplt_epi32( a, b );
    }
    
    static inline const vec_t min( const vec_t &a, const vec_t &b ) {
        // sse 4.1, no shit! what were they smoking...
#ifdef __SSE4_1__
        return _mm_min_epi32( a, b );
#else
#error missing SSE4.1, find some workaround...
#endif
        
    }
    
    static inline const vec_t max( const vec_t &a, const vec_t &b ) {
#ifdef __SSE4_1__
        return _mm_max_epi32( a, b );
#else        
#error missing SSE4.1, find some workaround...
#endif
    }
    
    static inline const vec_t abs_diff( const vec_t &a, const vec_t &b ) {
        // i don't really like this function, as ideally this would just be abs(sub(a,b)), 
        // but there doesn't seem to be a fast way to implement abs on pre SSSSSSE3.
        // The max(sub(a,b),sub(b,a)) work-around seems to be the next-best thing in this special case.
        
        #ifdef __SSSE3__
        return _mm_abs_epi32(sub(a,b));
        #else
        // FIXME: is there a faster method for boring old CPUs?
        return max( sub(a,b), sub(b,a) );
//         #error missing SSSSSSSSSE3
        #endif
    }
    
};

template<>
struct vector_unit<float, 4> {

    const static bool do_checks = false;
    
    typedef __m128 vec_t;
    typedef float T;

    const static int SIGN_MASK_INT = 0x7FFFFFFF;
    
    const static T LARGE_VALUE = 1e8;
    const static T SMALL_VALUE = -1e8;
    const static T BIAS = 0;
    const static size_t W = 4;
    
    static inline vec_t setzero() {
        return set1(0);
    }
    
    static inline vec_t set1( T val ) {
        return _mm_set1_ps( val );
    }
    
    static inline void store( const vec_t &v, T *addr ) {

        if( do_checks && addr == 0 ) {
            throw std::runtime_error( "store: addr == 0" );
        }
        //std::cout << "store to: " << addr << "\n";
        
        _mm_store_ps( (T*)addr, v );
    }
    
    static inline const vec_t load( T* addr ) {
        return _mm_load_ps( (T*)addr );
    }
    
#if 1 
    static inline const vec_t bit_and( const vec_t &a, const vec_t &b ) {
        return _mm_and_ps( a, b );
    }
    
    static inline const vec_t bit_andnot( const vec_t &a, const vec_t &b ) {
        return _mm_andnot_ps( a, b );
    }
#endif
//     static inline const vec_t bit_invert( const vec_t &a ) {
//         //return _mm_andnot_pd(a, set1(0xffff));
//     }
    
    static inline const vec_t add( const vec_t &a, const vec_t &b ) {
        return _mm_add_ps( a, b );
    }
    static inline const vec_t adds( const vec_t &a, const vec_t &b ) {
        // float add is always saturating, kind of!?
        return _mm_add_ps( a, b );
    }
    static inline const vec_t sub( const vec_t &a, const vec_t &b ) {
        return _mm_sub_ps( a, b );
    }
    static inline const vec_t cmp_zero( const vec_t &a ) {
        return _mm_cmpeq_ps( a, setzero() );
    }
    
    static inline const vec_t cmp_eq( const vec_t &a, const vec_t &b ) {
        // TODO: think about what this really means. Maybe use something epsilon-based as a default for float?
        return _mm_cmpeq_ps( a, b );
    }
    
    static inline const vec_t cmp_lt( const vec_t &a, const vec_t &b ) {
     
        return _mm_cmplt_ps( a, b );
    }
    
    static inline const vec_t min( const vec_t &a, const vec_t &b ) {
        return _mm_min_ps( a, b );
    }
    
    static inline const vec_t max( const vec_t &a, const vec_t &b ) {
        return _mm_max_ps( a, b );
    }
    
    static inline const vec_t abs_diff( const vec_t &a, const vec_t &b ) {
        // i don't really like this function, as ideally this would just be abs(sub(a,b)), 
        // but there doesn't seem to be a fast way to implement abs on pre SSSSSSE3.
        // The max(sub(a,b),sub(b,a)) work-around seems to be the next-best thing in this special case.
        
        //unsigned int SIGN_MASK[4] = {0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF};
        //unsigned int SIGN_MASK = 0x7FFFFFFF;
        static float SIGN_MASK = *((float*)&SIGN_MASK_INT);
        return bit_and(sub(a,b), set1(SIGN_MASK) ); // TODO: could this case any alignment problems?
        //return bit_and(sub(a,b), set1(*((float*)&SIGN_MASK_INT) )); // TODO: could this case any alignment problems?
        
        //return bit_and(sub(a,b), load((float*)SIGN_MASK ));
        
    }
    
};


#ifdef HAVE_AVX
// AVX is the most pointless thin in the world, as fas as integers are concerned.
// waiting for AVX5.7

// AVX 16x16bit vector unit
template<>
struct vector_unit<short, 16> {

    const static bool do_checks = false;
    
    typedef __m256i vec_t;
    typedef short T;
    
    const static T SMALL_VALUE = -32000;
    const static T BIAS = 0;
    const static size_t W = 8;
    
    static inline vec_t setzero() {
        return _mm256_setzero_si256();
    }
    
    static inline vec_t set1( T val ) {
        return _mm256_set1_epi16( val );
    }
    
    static inline void store( const vec_t &v, T *addr ) {

        if( do_checks && addr == 0 ) {
            throw std::runtime_error( "store: addr == 0" );
        }
        //std::cout << "store to: " << addr << "\n";
        
        _mm256_store_si256( (vec_t*)addr, v );
    }
    
    static inline const vec_t load( T* addr ) {
        return _mm256_load_si256( (vec_t*)addr );
    }
    
    static inline const vec_t bit_and( const vec_t &a, const vec_t &b ) {
        __m128i lowa = _mm256_castsi256_si128(a);
        const __m128i lowb = _mm256_castsi256_si128(b);
        
        lowa = _mm_and_si128( lowa, lowb );
        
        
        __m128i higha = _mm256_extractf128_si256(a,1);
        const __m128i highb = _mm256_extractf128_si256(b,1);
        
        higha = _mm_and_si128( higha, highb );
        
        
        return _mm256_insertf128_si256( _mm256_castsi128_si256(lowa), higha, 1 );
    }
    
    static inline const vec_t bit_andnot( const vec_t &a, const vec_t &b ) {
        __m128i lowa = _mm256_castsi256_si128(a);
        const __m128i lowb = _mm256_castsi256_si128(b);
        
        lowa = _mm_andnot_si128( lowa, lowb );
        
        
        __m128i higha = _mm256_extractf128_si256(a,1);
        const __m128i highb = _mm256_extractf128_si256(b,1);
        
        higha = _mm_andnot_si128( higha, highb );
        
        
        return _mm256_insertf128_si256( _mm256_castsi128_si256(lowa), higha, 1 );
    }
    
//     static inline const vec_t bit_invert( const vec_t &a ) {
//         //return _mm_andnot_pd(a, set1(0xffff));
//     }
    
    static inline const vec_t add( const vec_t &a, const vec_t &b ) {
        const __m128i lowa = _mm256_extractf128_si256(a,0);
        const __m128i lowb = _mm256_extractf128_si256(b,0);
        
        //lowa = _mm_add_epi16( lowa, lowb );
        
        
        const __m128i higha = _mm256_extractf128_si256(a,1);
        const __m128i highb = _mm256_extractf128_si256(b,1);
        
        //higha = _mm_add_epi16( higha, highb );
        
        
        return _mm256_insertf128_si256( _mm256_castsi128_si256(_mm_add_epi16( lowa, lowb )),  _mm_add_epi16( higha, highb ), 1 );
    }
    static inline const vec_t sub( const vec_t &a, const vec_t &b ) {
        __m128i lowa = _mm256_castsi256_si128(a);
        const __m128i lowb = _mm256_castsi256_si128(b);
        
        lowa = _mm_sub_epi16( lowa, lowb );
        
        
        __m128i higha = _mm256_extractf128_si256(a,1);
        const __m128i highb = _mm256_extractf128_si256(b,1);
        
        higha = _mm_sub_epi16( higha, highb );
        
        
        return _mm256_insertf128_si256( _mm256_castsi128_si256(lowa), higha, 1 );
    }
    static inline const vec_t cmp_zero( const vec_t &a ) {
        return cmp_eq( a, setzero() );
    }
    
    static inline const vec_t cmp_eq( const vec_t &a, const vec_t &b ) {
        __m128i lowa = _mm256_castsi256_si128(a);
        const __m128i lowb = _mm256_castsi256_si128(b);
        
        lowa = _mm_cmpeq_epi16( lowa, lowb );
        
        
        __m128i higha = _mm256_extractf128_si256(a,1);
        const __m128i highb = _mm256_extractf128_si256(b,1);
        
        higha = _mm_cmpeq_epi16( higha, highb );
        
        
        return _mm256_insertf128_si256( _mm256_castsi128_si256(lowa), higha, 1 );
    }
    
    static inline const vec_t cmp_lt( const vec_t &a, const vec_t &b ) {
     
        __m128i lowa = _mm256_castsi256_si128(a);
        const __m128i lowb = _mm256_castsi256_si128(b);
        
        lowa = _mm_cmplt_epi16( lowa, lowb );
        
        
        __m128i higha = _mm256_extractf128_si256(a,1);
        const __m128i highb = _mm256_extractf128_si256(b,1);
        
        higha = _mm_cmplt_epi16( higha, highb );
        
        
        return _mm256_insertf128_si256( _mm256_castsi128_si256(lowa), higha, 1 );
    }
    
    static inline const vec_t min( const vec_t &a, const vec_t &b ) {
        __m128i lowa = _mm256_castsi256_si128(a);
        const __m128i lowb = _mm256_castsi256_si128(b);
        
        lowa = _mm_min_epi16( lowa, lowb );
        
        
        __m128i higha = _mm256_extractf128_si256(a,1);
        const __m128i highb = _mm256_extractf128_si256(b,1);
        
        higha = _mm_min_epi16( higha, highb );
        
        
        return _mm256_insertf128_si256( _mm256_castsi128_si256(lowa), higha, 1 );
    }
    
    static inline const vec_t max( const vec_t &a, const vec_t &b ) {
        __m128i lowa = _mm256_castsi256_si128(a);
        const __m128i lowb = _mm256_castsi256_si128(b);
        
        lowa = _mm_max_epi16( lowa, lowb );
        
        
        __m128i higha = _mm256_extractf128_si256(a,1);
        const __m128i highb = _mm256_extractf128_si256(b,1);
        
        higha = _mm_max_epi16( higha, highb );
        
        
        return _mm256_insertf128_si256( _mm256_castsi128_si256(lowa), higha, 1 );
    }
};

#endif


// vector unit specialization: SSE 16x8bit integer 

template<>
struct vector_unit<unsigned char, 16> {

    const static bool do_checks = false;
    
    typedef __m128i vec_t;
    typedef unsigned char T;
    
    const static size_t W = 16;
    const static T SMALL_VALUE = 32;
    const static T BIAS = 127;
    
    
    static inline vec_t setzero() {
        return set1(0);
    }
    
    static inline vec_t set1( T val ) {
        return _mm_set1_epi8( val );
    }
    
    static inline void store( const vec_t &v, T *addr ) {

        if( do_checks && addr == 0 ) {
            throw std::runtime_error( "store: addr == 0" );
        }
        //std::cout << "store to: " << addr << "\n";
        
        _mm_store_si128( (__m128i*)addr, v );
    }
    
    static inline const vec_t load( T* addr ) {
        return (vec_t)_mm_load_si128( (__m128i *) addr );
    }
    
    static inline const vec_t bit_and( const vec_t &a, const vec_t &b ) {
        return _mm_and_si128( a, b );
    }
    
    static inline const vec_t add( const vec_t &a, const vec_t &b ) {
        return _mm_add_epi8( a, b );
    }
    
    static inline const vec_t sub( const vec_t &a, const vec_t &b ) {
        return _mm_sub_epi8( a, b );
    }
    
    static inline const vec_t cmp_zero( const vec_t &a ) {
        return _mm_cmpeq_epi8( a, setzero() );
    }
    
    static inline const vec_t min( const vec_t &a, const vec_t &b ) {
        return _mm_min_epu8( a, b );
    }
    static inline const vec_t max( const vec_t &a, const vec_t &b ) {
        return _mm_max_epu8( a, b );
    }
    
    static inline void println( const vec_t &v, T *tmp ) {
        store(v, tmp);
        std::cout << "(";
        for( size_t i = 0; i < W; i++ ) {
         
            std::cout << int(tmp[i]) << ((i < W-1) ? "," : ")");
        }
        
        std::cout << std::endl;
    }
};


template<>
struct vector_unit<short, 1> {

    const static bool do_checks = false;
    
    typedef __m128i vec_t;
    typedef short T;
    
    const static size_t W = 1;
    
    static inline vec_t setzero() {
        return set1(0);
    }
    
    static inline vec_t set1( T val ) {
        return _mm_set1_epi16( val );
    }
    
    static inline void store( const vec_t &v, T *addr ) {

        if( do_checks && addr == 0 ) {
            throw std::runtime_error( "store: addr == 0" );
        }
        //std::cout << "store to: " << addr << "\n";
        
        //_mm_store_ps( (float*)addr, (__m128)v );
        
        *addr = _mm_extract_epi16( v, 0 );
    }
    
    static inline const vec_t load( T* addr ) {
        //return (vec_t)_mm_load_ps( (float *) addr );
        return set1(*addr);
    }
    
    static inline const vec_t bit_and( const vec_t &a, const vec_t &b ) {
        return _mm_and_si128( a, b );
    }
    
    static inline const vec_t add( const vec_t &a, const vec_t &b ) {
        return _mm_add_epi16( a, b );
    }
    
    static inline const vec_t cmp_zero( const vec_t &a ) {
        return _mm_cmpeq_epi16( a, setzero() );
    }
    
    static inline const vec_t min( const vec_t &a, const vec_t &b ) {
        return _mm_min_epi16( a, b );
    }
};


// vector unit specialization: SSE scalar 16bit integer 

// template<>
// struct vector_unit<short, 1> {
// 
//     const static bool do_checks = false;
//     
//     typedef short vec_t;
//     typedef short T;
//     
//     const static size_t W = 1;
//     
//     static inline vec_t setzero() {
//         return 0;
//     }
//     
//     static inline vec_t set1( T val ) {
//         return val;
//     }
//     
//     static inline void store( const vec_t &v, T *addr ) {
// 
//         if( do_checks && addr == 0 ) {
//             throw std::runtime_error( "store: addr == 0" );
//         }
//         
//         *addr = v;
//         
//     }
//     
//     static inline const vec_t load( T* addr ) {
//         return *addr;
//     }
//     
//     static inline const vec_t bit_and( const vec_t &a, const vec_t &b ) {
//         return  a & b;
//     }
//     
//     static inline const vec_t add( const vec_t &a, const vec_t &b ) {
//         return a + b;
//     }
//     
//     static inline const vec_t cmp_zero( const vec_t &a ) {
//         //return _mm_cmpeq_epi16( a, setzero() );
//         return a == 0 ? 0xffff : 0x0;
//     }
//     
//     static inline const vec_t min( const vec_t &a, const vec_t &b ) {
//         return std::min( a, b );
//     }
// };

#endif
#endif
