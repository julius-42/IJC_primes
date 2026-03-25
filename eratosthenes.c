/*
eratosthenes.c
Riešenie IJC-DU1, príklad a), 25.3.2026
Autor: Julius Kundrat FIT
Preložené: gcc 13.3
Contains Eratosthenes() function that runs Eratosthenes sieve on a given bitarray
*/

#include <math.h>
#include "bitarray.h"
#include "eratosthenes.h"

void Eratosthenes(bitarray_t pole){

    bitarray_fill(pole, 1);
    bitarray_setbit(pole,0,0);
    bitarray_setbit(pole,1,0);

    // Sets all even numbers to 0
    for (size_t j = 4; j < pole[0]; j += 2) {
        bitarray_setbit(pole, j, 0);
    }

    // Loops through all numbers with value 1 (3...sqrt(N)+1)
    for(size_t i = 3; i < sqrt(pole[0])+1; i += 2){

        if(bitarray_getbit(pole,i)){
            
            // Sets number's multiples to 0, +=2*i skips even numbers
            for(size_t j = i*i; j < pole[0]; j += 2*i){
                bitarray_setbit(pole,j,0);
            }
        }
    }
}