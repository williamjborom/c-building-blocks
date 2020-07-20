// bubble_sort.c
// Bubble sort sorting algorithm.

#include "bubble_sort.h"

void bubble_sort(
    int array[], 
    size_t begin, 
    size_t end, 
    policy_f should_swap)
{
    int i = 0;
    int j = 0;
    for (i = 0; begin + i <= end; i++) {
        for (j = 0; begin + j < end; j++) {
            if (should_swap(array[begin + j], array[begin + (j+1)])) {
                int temp1 = array[begin + j];
                int temp2 = array[begin + (j+1)];
                array[begin + j] = temp2;
                array[begin + (j+1)] = temp1;
            }
        }
    }
    return;
}
