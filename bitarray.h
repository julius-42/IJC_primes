#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "errors.h"

#ifndef BITARRAY_H
#define BITARRAY_H

inline void bitarray_do_check(unsigned long size, unsigned long idx, const char *func) {
// If NO_CHECK is undefined, program will perform bounds check
#ifndef NO_CHECK
    if (idx > size) {
        error_exit("Error: %s - Index %lu out of bound 0..%lu\n", func, idx, size);
    }
// If NO_CHECK is defined, program will erase these checks
#else
    (void)size; (void)idx; (void)func;
#endif
}

#define bitarray_check(name, idx, func) bitarray_do_check((name)[0], (idx), (func))

typedef unsigned long *bitarray_t;

// Gets the size of unsigned long in bits
#define ULONG_BIT (sizeof(unsigned long) * 8)
// Gets the needed amount of unsigned longs to store 'bits' amount of bits + UL for size of bitarray
#define calc_uls(bits) (((bits) / ULONG_BIT) + 1 + ((bits) % ULONG_BIT != 0))

// --- Macros used always as macros ---


// remove afterwards
#define bitarray_print(name) \
    for(unsigned long i = 1; i < calc_uls((name)[0]); i++){ \
        printf("ul %3lu: ", i); \
        PRINT_BIN((name)[i]); \
    }

#define PRINT_BIN(val) do { \
    unsigned long _v = (val); \
    for (int _i = (sizeof(unsigned long) * 8) - 1; _i >= 0; _i--) { \
        putchar((_v & (1UL << _i)) ? '1' : '0'); \
    } \
    putchar('\n'); \
} while(0)



// Creates a static bitarray of size 'size'
#define bitarray_create(name, size) \
    static_assert((size) > 0, "Error: Invalid BitArray size\n"); \
    unsigned long (name)[calc_uls(size)] = {(size), 0} \

// Allocates a bitarray of size 'size'
#define bitarray_alloc(name, size) \
    assert((size) > 0); \
    bitarray_t (name) = calloc(calc_uls(size), sizeof(unsigned long)); \
    if (name == NULL){ \
        error_exit("Error: bitarray_alloc - Memory allocation failed\n"); \
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
    bitarray_check(name, idx, "bitarray_setbit"); \
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
    ((bitarray_check(name, idx, "bitarray_getbit")), \
    (int)(((name)[((idx) / ULONG_BIT) + 1] & (1UL << ((idx) % ULONG_BIT))) != 0UL))

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
    bitarray_check(name, idx, "bitarray_getbit");
    return (name[(idx / ULONG_BIT) + 1] & (1UL << (idx % ULONG_BIT))) != 0UL;
}

inline void bitarray_setbit(bitarray_t name, unsigned long idx, int val){
    bitarray_check(name, idx, "bitarray_setbit");
    unsigned int ul_idx = idx/ULONG_BIT + 1;
    unsigned int bit_idx = idx%ULONG_BIT;
    if(val == 1){
        name[ul_idx] |= (1UL << bit_idx);
    }
    else{
        name[ul_idx] &= ~(1UL << bit_idx);
    }
}


#endif

#endif