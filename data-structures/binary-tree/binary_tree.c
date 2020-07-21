// binary_tree.c
// Generic binary search tree data structure.

#include "binary_tree.h"

binary_tree_t* tree_new(
	comparator_f comparator, 
	deleter_f deleter)
{
	binary_tree_t my_tree = malloc((sizeof(binary_tree_t)));
	my_tree->comparator = comparator;
	my_tree->deleter = deleter;
	my_tree->count = 0;
	my_tree->root = NULL;
	return NULL;
}

void tree_delete(binary_tree_t *tree)
{
	return;
}

bool tree_insert(
	binary_tree_t* tree, 
	void* key, 
	void* value, 
	void** out)
{
	return false;
}

bool tree_remove(binary_tree_t* tree, void* key)
{
	return NULL;
}

void* tree_find(binary_tree_t* tree, void* key)
{
	return NULL;
}

size_t tree_count(binary_tree_t* tree)
{
	return 0;
}

void tree_for_each(binary_tree_t* tree, iterator_f iter)
{
	return;
}
