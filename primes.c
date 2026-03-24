/*
primes.c
Autor: Julius Kundrat FIT
Prelozene: gcc 13.3
*/

#include "bitarray.h"
#include <math.h>
#include <time.h>
#define SIZE 444000000

void Eratosthenes(bitarray_t pole){

    bitarray_fill(pole, 1);
    bitarray_setbit(pole,0,0);

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

int main(){

    clock_t start = clock();
    bitarray_alloc(arr,SIZE);
    Eratosthenes(arr);

    int count = 0;
    for(unsigned long i = SIZE-1; count < 10; i--){
        if(bitarray_getbit(arr, i) == 1){
            printf("%ld\n",i);
            count++;
        }
    }

    bitarray_free(arr);
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

    return 0;
}