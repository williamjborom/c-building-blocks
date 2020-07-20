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
    size_t size = sizeof(int);
    for (i = 0; begin + size*i <= end; i++) {
        for (j = 0; begin + size*j < end; j++) {
            if (should_swap(array[begin + size*j], array[begin + size*(j+1)])) {
                int temp1 = array[begin + size*j];
                int temp2 = array[begin + size*(j+1)];
                array[begin + size*j] = temp1;
                array[begin + size*(j+1)] = temp2;
            }
        }
    }
    return;
}
