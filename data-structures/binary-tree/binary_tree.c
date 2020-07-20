// binary_tree.c
// Generic binary search tree data structure.

#include "binary_tree.h"

//TREE NEW----------------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------------

//TREE DELETE----------------------------------------------------------------------------------------------------
void tree_delete(binary_tree_t *tree)
{
	return;
}
//----------------------------------------------------------------------------------------------------


//TREE INSERT----------------------------------------------------------------------------------------------------
bool tree_inster_rec(tree_node_t* node, void* key, void* value, void** out) {
	if (node->key == key) {
		out = node->value;
		node->value = value;
		return true;	
	} else if (key < node->key && node->LEFT != NULL) {
		return (tree_insert_rec(node->LEFT, key));
	} else if (key > node->key && node->RIGHT != NULL) {
		return (tree_insert_rec(node->RIGHT, key));
	} else if (key < node->LEFT && node->LEFT == NULL) {
		tree_node_t* newtreenode = malloc(sizeof(tree_node_t));
		newtreenode->LEFT = NULL;
		newtreenode->RIGHT = NULL;
		newtreenode->key = key;
		newtreenode->value = value;
		newtreenode->parent = node;
		node->LEFT = newtreenode;
		return true;
	} else if (key > node->key && node->RIGHT == NULL) {
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

	return tree_insert_rec(tree->root, key, value, out);
}
//----------------------------------------------------------------------------------------------------

//TREE REMOVE----------------------------------------------------------------------------------------------------
bool tree_remove_rec(tree_node_t* node, void* key) {
	if(node->LEFT != NULL && node->LEFT->key == key) {
		tree_node_t* node_to_remove = node->LEFT;
		if(node_to_remove->LEFT != NULL) {
			node->LEFT = node_to_remove->LEFT;
		} else if (node_to_remove->RIGHT != NULL) {
			node->LEFT = node_to_remove->RIGHT;
		}
		return true;
	} else if (node->RIGHT != NULL && node->RIGHT->key == key) {
		tree_node_t* node_to_remove = node->RIGHT;
		if(node_to_remove->LEFT != NULL) {
			node->RIGHT = node_to_remove->LEFT;
		} else if (node_to_remove->RIGHT != NULL) {
			node->RIGHT = node_to_remove->RIGHT;
		}
		return true;
	} else if (key < node->key && node->LEFT != NULL) {
		return (tree_remove_rec(node->LEFT, key));
	} else if (key > node->key && node->RIGHT != NULL) {
		return (tree_remove_rec(node->RIGHT, key));
	} else {
		return false;
	}
}

bool tree_remove(binary_tree_t* tree, void* key)
{
	return tree_remove_rec(tree, key);
}
//----------------------------------------------------------------------------------------------------

//TREE FIND----------------------------------------------------------------------------------------------------
void* tree_find_rec(tree_node_t* node, void* key) {
	if (node->key == key) {
		return value;	
	} else if (node->key > key && node->LEFT != NULL) {
		return (tree_find_rec(node->LEFT, key));
	} else if (node->key < key && node->RIGHT != NULL) {
		return (tree_find_rec(node->RIGHT, key));
	} else {
		return NULL;
	}
}

void* tree_find(binary_tree_t* tree, void* key)
{
	return tree_find_rec(t->root, key);
}
//----------------------------------------------------------------------------------------------------

//TREE COUNT----------------------------------------------------------------------------------------------------
size_t tree_count(binary_tree_t* tree)
{
	return t->count;
}
//----------------------------------------------------------------------------------------------------

//TREE FOR EACH----------------------------------------------------------------------------------------------------
void tree_for_each(binary_tree_t* tree, iterator_f iter)
{
	return;
}
//----------------------------------------------------------------------------------------------------
