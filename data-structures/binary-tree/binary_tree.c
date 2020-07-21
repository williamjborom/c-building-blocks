// binary_tree.c
// Generic binary search tree data structure.

#include <stdlib.h>
#include "binary_tree.h"

//Defining Tree Node Structure
typedef struct treenode {
	struct treenode* PARENT;
	struct treenode* LEFT;
	struct treenode* RIGHT;
	void* key;
	int* value;
} tree_node_t;

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
	return my_tree;
}
//---------------------------------------------------------------------------------------------------

//TREE DELETE----------------------------------------------------------------------------------------------------
void tree_delete_rec(deleter_f deleter, tree_node_t* node)
{
	if (node != NULL) {
		tree_delete_rec(deleter, node->LEFT);
		tree_delete_rec(deleter, node->RIGHT);
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
bool tree_insert_rec(binary_tree_t* t, comparator_f comparator, tree_node_t* node, void* key, void* value, void** out) {
	if (comparator(key, node->key) == EQUAL) {
		*out = node->value;
		node->value = value;
		return true;	
	} else if (comparator(key, node->key) == LESS && node->LEFT != NULL) {
		return (tree_insert_rec(t, comparator, node->LEFT, key, value, out));
	} else if (comparator(key, node->key) == GREATER && node->RIGHT != NULL) {
		return (tree_insert_rec(t, comparator, node->RIGHT, key, value, out));
	} else if (comparator(key, node->key) == LESS && node->LEFT == NULL) {
		tree_node_t* newtreenode = malloc(sizeof(tree_node_t));
		newtreenode->LEFT = NULL;
		newtreenode->RIGHT = NULL;
		newtreenode->key = key;
		newtreenode->value = value;
		newtreenode->PARENT = node;
		node->LEFT = newtreenode;
		t->count = t->count + 1;
		return true;
	} else if (comparator(key, node->key) == GREATER && node->RIGHT == NULL) {
		tree_node_t* newtreenode = malloc(sizeof(tree_node_t));
		newtreenode->LEFT = NULL;
		newtreenode->RIGHT = NULL;
		newtreenode->key = key;
		newtreenode->value = value;
		newtreenode->PARENT = node;
		node->RIGHT = newtreenode;
		t->count = t->count + 1;
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
	return tree_insert_rec(tree, tree->comparator, tree->root, key, value, out);
}
//----------------------------------------------------------------------------------------------------

//TREE REMOVE----------------------------------------------------------------------------------------------------

bool tree_remove_rec(binary_tree_t* t, deleter_f deleter, comparator_f comparator, tree_node_t* node, void* key) {
	if(node->LEFT != NULL && comparator(node->LEFT->key, key) == EQUAL) {
		tree_node_t* node_to_remove = node->LEFT;
		if(node_to_remove->LEFT != NULL && node_to_remove->RIGHT == NULL) {
			node->LEFT = node_to_remove->LEFT;
		} else if (node_to_remove-> LEFT == NULL && node_to_remove->RIGHT != NULL) {
			node->LEFT = node_to_remove->RIGHT;
		} else if (node_to_remove->LEFT == NULL && node_to_remove->RIGHT == NULL) {
			node->LEFT = NULL;
		} else if (node_to_remove->LEFT != NULL && node_to_remove->RIGHT != NULL) {
			node->LEFT = node_to_remove->RIGHT;
			tree_node_t* temp_to_insert = node_to_remove->LEFT;
			tree_node_t* insert_spot = node->LEFT;
			while (insert_spot->LEFT != NULL) {
				insert_spot = insert_spot->LEFT;
			}
			insert_spot->LEFT = temp_to_insert;
		}
		deleter(node_to_remove->value);
		deleter(node_to_remove->key);
		deleter(node_to_remove);
		t->count = t->count - 1;
		return true;

	} else if (node->RIGHT != NULL && comparator(node->RIGHT->key, key) == EQUAL) {
		tree_node_t* node_to_remove = node->RIGHT;
		if(node_to_remove->LEFT != NULL && node_to_remove->RIGHT == NULL) {
			node->RIGHT = node_to_remove->LEFT;
		} else if (node_to_remove-> LEFT == NULL && node_to_remove->RIGHT != NULL) {
			node->RIGHT = node_to_remove->RIGHT;
		} else if (node_to_remove->LEFT == NULL && node_to_remove->RIGHT == NULL) {
			node->RIGHT = NULL;
		} else if (node_to_remove->LEFT != NULL && node_to_remove->RIGHT != NULL) {
			node->RIGHT = node_to_remove->RIGHT;
			tree_node_t* temp_to_insert = node_to_remove->LEFT;
			tree_node_t* insert_spot = node->LEFT;
			while (insert_spot->LEFT != NULL) {
				insert_spot = insert_spot->LEFT;
			}
			insert_spot->LEFT = temp_to_insert;
		}
		deleter(node_to_remove->value);
		deleter(node_to_remove->key);
		deleter(node_to_remove);
		t->count = t->count - 1;
		return true;

	} else if (comparator(key, node->key) ==LESS && node->LEFT != NULL) {
		return (tree_remove_rec(t, deleter, comparator, node->LEFT, key));
	} else if (comparator(key, node->key) == GREATER && node->RIGHT != NULL) {
		return (tree_remove_rec(t, deleter, comparator, node->RIGHT, key));
	} else {
		return false;
	}
}

bool tree_remove(binary_tree_t* tree, void* key)
{
	return tree_remove_rec(tree, tree->deleter, tree->comparator, tree->root, key);
}
//----------------------------------------------------------------------------------------------------

//TREE FIND----------------------------------------------------------------------------------------------------
void* tree_find_rec(comparator_f comparator, tree_node_t* node, void* key) {
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
	return tree_find_rec(tree->comparator, tree->root, key);
}
//----------------------------------------------------------------------------------------------------

//TREE COUNT----------------------------------------------------------------------------------------------------
size_t tree_count(binary_tree_t* tree)
{
	return tree->count;
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
