/*
eratosthenes.c
Autor: Julius Kundrat FIT
Prelozene: gcc 13.3
*/

#include <math.h>
#include "bitarray.h"
#include "eratosthenes.h"

void Eratosthenes(bitarray_t pole){

    bitarray_fill(pole, 1);
    bitarray_setbit(pole,0,0);
    bitarray_setbit(pole,1,0);

    for (size_t j = 4; j < pole[0]; j += 2) {
        bitarray_setbit(pole, j, 0);
    }

    for(size_t i = 3; i < sqrt(pole[0])+1; i += 2){

        if(bitarray_getbit(pole,i)){

            for(size_t j = i*i; j < pole[0]; j += 2*i){
                bitarray_setbit(pole,j,0);
            }
        }
    }
}