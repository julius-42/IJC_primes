/*
primes.c
Autor: Julius Kundrat FIT
Prelozene: gcc 13.3
*/

#include "bitarray.h"
#include <math.h>
#include <time.h>
#define SIZE 4440000

void Eratosthenes(bitarray_t pole){

    bitarray_fill(pole, 1);
    bitarray_setbit(pole,0,0);

    for(size_t i = 2; i < sqrt(pole[0])+1; i++){

        if(bitarray_getbit(pole,i) == 1){

            for(size_t j = i+i; j < pole[0]; j+=i){
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