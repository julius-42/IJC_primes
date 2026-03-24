#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "errors.h"

#ifndef BITARRAY_H
#define BITARRAY_H

typedef unsigned long *bitarray_t;

// Gets the size of unsigned long in bits
#define ULONG_BIT (sizeof(unsigned long) * 8)
// Gets the needed amount of unsigned longs to store 'bits' amount of bits
#define calc_uls(bits) (((bits) / ULONG_BIT) + 1 + ((bits) % ULONG_BIT != 0))

// --- Macros used always as macros ---

// Creates a static bitarray of size 'size + 1'
// '+ 1' is to store the size of the bitarray
#define bitarray_create(name, size) \
    static_assert((size) > 0, "BitArray size invalid"); \
    unsigned long (name)[calc_uls(size) + 1] = {(size), 0} \

// Allocates a bitarray of size 'size + 1'
#define bitarray_alloc(name, size) \
    assert((size) > 0); \
    bitarray_t (name) = calloc(calc_uls(size) + 1, sizeof(unsigned long)); \
    if (name == NULL){ \
        error_exit("Error: bitarray_alloc - Memory allocation failed"); \
    } \
    (name)[0] = (size)


// Frees the allocated bitarray
#define bitarray_free(name) free((name))


// --- Macros used as inline functions too ---
#ifndef USE_INLINE


// Gets the size of the bitarray
#define bitarray_size(name) (name)[0]


// Fills the bitarray with 'val'
#define bitarray_fill(name, val) \
    do{ \
        unsigned long fill = (val) ? ~0UL : 0UL; \
        for(unsigned long i = 1; i < calc_uls((name)[0]); i++){ \
            (name)[i] = fill; \
        } \
    }while(0) \


// Sets a bit on index 'idx' to 'val'
#define bitarray_setbit(name, idx, val) \
    do{ \
    unsigned int ul_idx = (idx)/ULONG_BIT + 1; \
    unsigned int bit_idx = (idx)%ULONG_BIT; \
    if(val == 1){ \
        (name)[ul_idx] |= (1UL << (bit_idx)); \
    } \
    else{ \
        (name)[ul_idx] &= ~(1UL << (bit_idx)); \
    } \
    }while(0) \
    

// Gets the value of a bit on index 'idx'
#define bitarray_getbit(name, idx) \
    (((name)[((idx) / ULONG_BIT) + 1] & (1UL << ((idx) % ULONG_BIT))) != 0UL)


#else

// --- Inline functions definitions ---

inline unsigned long bitarray_size(bitarray_t name) {
    return name[0];
}

inline void bitarray_fill(bitarray_t name, int val){
    unsigned long fill = val ? ~0UL : 0UL;
    for(unsigned long i = 1; i < calc_uls(name[0]); i++){
        name[i] = fill;
    }
}

inline int bitarray_getbit(bitarray_t name, unsigned long idx) {
    return (name[(idx / ULONG_BIT) + 1] & (1UL << (idx % ULONG_BIT))) != 0UL;
}

inline void bitarray_setbit(bitarray_t name, unsigned long idx, int val){
    unsigned int ul_idx = (idx)/ULONG_BIT + 1;
    unsigned int bit_idx = (idx)%ULONG_BIT;
    if(val == 1){
        name[ul_idx] |= (1UL << bit_idx);
    }
    else{
        name[ul_idx] &= ~(1UL << bit_idx);
    }
}


#endif

#endif