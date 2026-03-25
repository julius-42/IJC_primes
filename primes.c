/*
primes.c
Riešenie IJC-DU1, príklad a), 25.3.2026
Autor: Julius Kundrat FIT
Preložené: gcc 13.3
Creates a dynamic bitarray and calls Eratosthenes() with it and prints last 10 prime numbers from the BA
*/

#include <math.h>
#include <time.h>
#include "bitarray.h"
#include "eratosthenes.h"

#define SIZE 444000000

int main(){

    clock_t start = clock(); // Starts the clock to measure Eratosthenes sieve efficiency
    bitarray_alloc(arr,SIZE); // Allocates a bitarray of SIZE
    Eratosthenes(arr); // Runs the Eratosthenes sieve

    // Prints the last 10 prime numbers
    int count = 0;
    for(unsigned long i = SIZE-1; (count < 10 && i > 0); i--){
        if(bitarray_getbit(arr, i) == 1){
            printf("%ld\n",i);
            count++;
        }
    }
    
    bitarray_free(arr); // Frees the allocated bitarray
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC); // Prints the final time

    return 0;
}