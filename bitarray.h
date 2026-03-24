#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#ifndef BITARRAY_H
#define BITARRAY_H

typedef unsigned long *bitarray_t;

#define ULONG_BIT (sizeof(unsigned long) * 8)
#define calc_uls(bits) (((bits) / ULONG_BIT) + 1 + ((bits) % ULONG_BIT != 0))

// Maacros used always as macros
#define bitarray_create(name, size) \
    static_assert((size) > 0, "BitArray size invalid"); \
    unsigned long (name)[calc_uls(size) + 1] = {(size), 0} \


#define bitarray_alloc(name, size) \
    assert((size) > 0); \
    bitarray_t (name) = calloc(calc_uls(size) + 1, sizeof(unsigned long)); \
    if (name == NULL){ \
        fprintf(stderr, "bitarray_alloc: Chyba alokace paměti"); \
        exit(1); \
    } \
    (name)[0] = (size)


#define bitarray_free(name) free((name))


// Macros used as inline functions too
#ifndef USE_INLINE


#define bitarray_size(name) (name)[0]


#define bitarray_fill(name, val) \
    do{ \
        unsigned long fill = (val) ? ~0UL : 0UL; \
        for(unsigned long i = 1; i < calc_uls((name)[0]); i++){ \
            (name)[i] = fill; \
        } \
    }while(0) \


#define PRINT_BIN(val) do { \
    for (int i = (sizeof(unsigned long) * 8) - 1; i >= 0; i--) { \
        putchar(((val) & (1UL << i)) ? '1' : '0'); \
    } \
    putchar('\n'); \
} while(0)


#define bitarray_print(name) \
    for(unsigned long i = 1; i < calc_uls((name)[0]); i++){ \
        printf("ul %lu: ", i); \
        PRINT_BIN((name)[i]); \
    }


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
    

#define bitarray_getbit(name, idx) \
    (((name)[((idx) / ULONG_BIT) + 1] & (1UL << ((idx) % ULONG_BIT))) != 0UL)


#else

inline unsigned long bitarray_size(bitarray_t name) {
    return name[0];
}

inline void bitarray_fill(bitarray_t name, int val){
    unsigned long fill = val ? ~0UL : 0UL;
    for(unsigned long i = 1; i < calc_uls(name[0]); i++){
        name[i] = fill;
    }
}

inline void PRINT_BIN(unsigned long val){
    for (int i = (sizeof(unsigned long) * 8) - 1; i >= 0; i--) {
        putchar((val & (1UL << i)) ? '1' : '0');
    }
    putchar('\n');
}

inline void bitarray_print(bitarray_t name){
    for(unsigned long i = 1; i < calc_uls(name[0]); i++){
        printf("ul %lu: ", i);
        PRINT_BIN(name[i]);
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