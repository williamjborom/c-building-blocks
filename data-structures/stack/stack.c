// stack.c
// Generic stack (last in, first out) data structure.
#include <stdlib.h>
#include "stack.h"

// An individual item on the stack.
typedef struct stack_item
{
    // A pointer to the item below this on the stack.
    struct stack_item* below;
    
    // A pointer to arbitrary user-provided data.
    void* data;
} stack_item_t;

lstack_t* stack_new(void)
{
    lstack_t* my_stack = malloc(sizeof(lstack_t));
    my_stack->top = NULL;
    my_stack->count = 0;
    return my_stack;
}

bool stack_delete(lstack_t* stack)
{
    if (stack->count == 0) {
        return true;
    } else {
        return false;
    }
}

bool stack_push(lstack_t* stack, void* data)
{
    if (stack == NULL) {
        return false;
    }
    if (stack->count == 0) {
        stack_item_t* new_item = malloc(sizeof(stack_item_t));
        new_item->data = data;
        new_item->below = NULL;
        stack->top = new_item;
        stack->count = stack->count + 1;
        return true;
    } else {
        stack_item_t* new_item = malloc(sizeof(stack_item_t));
        stack_item_t* temp_top = stack->top;
        new_item->data = data;
        new_item->below = temp_top;
        stack->top = new_item;
        stack->count = stack->count + 1;
        return true;
    }
}

void* stack_pop(lstack_t* stack)
{
    if (stack == NULL) {
        return NULL;
    }
    if (stack->count == 0) {
        return NULL;
    } 
    stack_item_t* temp_top = stack->top;
    stack->top = stack->top->below;
    stack->count = stack->count - 1;
    return temp_top->data;
}

void* stack_peek(lstack_t* stack)
{
    if (stack == NULL) {
        return NULL;
    }
    if (stack->count == 0) {
        return NULL;
    } 
    return stack->top->data;
}

size_t stack_count(lstack_t* stack)
{
    if (stack == NULL) {
        return 0;
    }
    return stack->count;
}
