// bubble_sort.c
// Bubble sort sorting algorithm.

#include "bubble_sort.h"

void bubble_sort(
    int array[], 
    size_t begin, 
    size_t end,
    policy_f should_swap)
{
    size_t size = sizeof(int);
    int i = 0;
    int j = 0;
    for (i = 0; begin + size*i <= end; i++) {
        for (j = 0; begin + size*j < end; j++) {
            if (should_swap(array[j], array[j+1])) {
                int temp1 = array[j];
                int temp2 = array[j+1];
                array[j] = temp2;
                array[j+1] = temp1;
            }
        }
    }
    return;
}
