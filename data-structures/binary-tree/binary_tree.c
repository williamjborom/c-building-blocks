// binary_tree.c
// Generic binary search tree data structure.

#include "binary_tree.h"

//TREE NEW----------------------------------------------------------------------------------------------------
binary_tree_t* tree_new(
	comparator_f comparator, 
	deleter_f deleter)
{
	binary_tree_t* my_tree = malloc((sizeof(binary_tree_t)));
	my_tree->comparator = comparator;
	my_tree->deleter = deleter;
	my_tree->count = 0;
	my_tree->root = NULL;
	return NULL;
}
//---------------------------------------------------------------------------------------------------

//TREE DELETE----------------------------------------------------------------------------------------------------
void tree_delete_rec(deleter_f deleter, tree_node_t* node)
{
	if (node != null) {
		tree_delete_rec(node->LEFT);
		tree_delete_rec(node->RIGHT);
		deleter(node->value);
		deleter(node);
	} 
}

void tree_delete(binary_tree_t* tree)
{
	tree_delete_rec(tree->deleter, tree->root);
}
//----------------------------------------------------------------------------------------------------


//TREE INSERT----------------------------------------------------------------------------------------------------
bool tree_insert_rec(comparator_f comparator, tree_node_t* node, void* key, void* value, void** out) {
	if (comparator(key, node->key) == EQUAL) {
		out = node->value;
		node->value = value;
		return true;	
	} else if (comparator(key, node->key) == LESS && node->LEFT != NULL) {
		return (tree_insert_rec(comparator, node->LEFT, key));
	} else if (comparator(key, node->key) == GREATER && node->RIGHT != NULL) {
		return (tree_insert_rec(comparator, node->RIGHT, key));
	} else if (comparator(key, node->key) == LESS && node->LEFT == NULL) {
		tree_node_t* newtreenode = malloc(sizeof(tree_node_t));
		newtreenode->LEFT = NULL;
		newtreenode->RIGHT = NULL;
		newtreenode->key = key;
		newtreenode->value = value;
		newtreenode->parent = node;
		node->LEFT = newtreenode;
		return true;
	} else if (comparator(key, node->key) == GREATER && node->RIGHT == NULL) {
		tree_node_t* newtreenode = malloc(sizeof(tree_node_t));
		newtreenode->LEFT = NULL;
		newtreenode->RIGHT = NULL;
		newtreenode->key = key;
		newtreenode->value = value;
		newtreenode->parent = node;
		node->RIGHT = newtreenode;
		return true;
	} else {
		return false;
	}
}

bool tree_insert(
	binary_tree_t* tree, 
	void* key, 
	void* value, 
	void** out)
{

	return tree_insert_rec(tree->comparator, tree->root, key, value, out);
}
//----------------------------------------------------------------------------------------------------

//TREE REMOVE----------------------------------------------------------------------------------------------------
bool tree_remove_rec(comparator_f comparator, tree_node_t* node, void* key) {
	if(node->LEFT != NULL && comparator(node->LEFT->key, key) == EQUAL) {
		tree_node_t* node_to_remove = node->LEFT;
		if(node_to_remove->LEFT != NULL) {
			node->LEFT = node_to_remove->LEFT;
		} else if (node_to_remove->RIGHT != NULL) {
			node->LEFT = node_to_remove->RIGHT;
		}
		return true;
	} else if (node->RIGHT != NULL && comparator(node->RIGHT->key, key) == EQUAL) {
		tree_node_t* node_to_remove = node->RIGHT;
		if(node_to_remove->LEFT != NULL) {
			node->RIGHT = node_to_remove->LEFT;
		} else if (node_to_remove->RIGHT != NULL) {
			node->RIGHT = node_to_remove->RIGHT;
		}
		return true;
	} else if (comparator(key, node->key) ==LESS && node->LEFT != NULL) {
		return (tree_remove_rec(comparator, node->LEFT, key));
	} else if (comparator(key, node->key) == GREATER && node->RIGHT != NULL) {
		return (tree_remove_rec(comparator, node->RIGHT, key));
	} else {
		return false;
	}
}

bool tree_remove(binary_tree_t* tree, void* key)
{
	return tree_remove_rec(tree->comparator, tree, key);
}
//----------------------------------------------------------------------------------------------------

//TREE FIND----------------------------------------------------------------------------------------------------
void* tree_find_rec(comaprator_f comparator, tree_node_t* node, void* key) {
	if (comparator(key, node->key) == EQUAL) {
		return node->value;	
	} else if (comparator(key, node->key) == LESS && node->LEFT != NULL) {
		return (tree_find_rec(comparator, node->LEFT, key));
	} else if (comparator(key, node->key) == GREATER && node->RIGHT != NULL) {
		return (tree_find_rec(comparator, node->RIGHT, key));
	} else {
		return NULL;
	}
}

void* tree_find(binary_tree_t* tree, void* key)
{
	return tree_find_rec(tree->comparator, t->root, key);
}
//----------------------------------------------------------------------------------------------------

//TREE COUNT----------------------------------------------------------------------------------------------------
size_t tree_count(binary_tree_t* tree)
{
	return *(t->count);
}
//----------------------------------------------------------------------------------------------------

//TREE FOR EACH----------------------------------------------------------------------------------------------------
void tree_for_each_rec(tree_node_t* node, iterator_f iter)
{
	if(node != NULL) {
		tree_for_each_rec(node->LEFT, iter);
		iter(node->key, node->value);
		tree_for_each_rec(node->RIGHT, iter);
		iter(node->key, node->value);
	}
}

void tree_for_each(binary_tree_t* tree, iterator_f iter)
{
	tree_for_each_rec(tree->root, iter);
}
//----------------------------------------------------------------------------------------------------
