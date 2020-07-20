// accumulate.c
// Accumulate algotithm on integer arrays.

#include "accumulate.h"

int accumulate(
    int array[], 
    size_t first, 
    size_t last, 
    int start, 
    binary_op_f op)
{
    if (last <= start) {
        return 0;
    }
    int i;
    size_t size = sizeof(int);
    int accumulator = start;
    for (i = 0; first + size * i <= last; i++) {
        accumulator = op(accumulator, array[i]);
    }
    return accumulator;
}