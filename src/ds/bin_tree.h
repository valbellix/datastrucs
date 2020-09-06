/**
 * @file bin_tree.h
 * @author Valerio Bellizia
 *
 * This file contains the interface to be used with ds_bin_tree. It implements 
 * a binary tree using a linked structure.
 */

#ifndef bin_tree_h
#define bin_tree_h

#include "result.h"
#include "defs.h"

#include <stddef.h>

/**
 * This is an opaque structure that represents a binary tree
 */
typedef struct ds_bin_tree ds_bin_tree;

/**
 * This is an opaque structure that represents a binary tree node.
 */
typedef struct ds_bin_tree_node ds_bin_tree_node;

/**
 * This represents the supported visiting strategies.
 */
typedef enum ds_visit_type { DFS_PRE_ORDER, DFS_IN_ORDER, DFS_POST_ORDER } ds_visit_type;

/**
 * This function will create a binary tree node by copying the element passed as argument.
 * 
 * @param element The element to store in the node.
 * @param the size of the element to store in the node.
 * @return It returns the pointer to a new instance of ds_bin_tree_node.
 */
ds_bin_tree_node* create_ds_bin_tree_node(void* element, const size_t size);

/**
 * This function will release the memory allocated to the node.
 * 
 * @param node It is the node to free.
 */
void delete_ds_bin_tree_node(ds_bin_tree_node* node);

/*
 * This function will return the pointer to the left child.
 *
 * @param node The node.
 * @return It returns a pointer to the left child.
 */
ds_bin_tree_node* ds_bin_tree_node_left(ds_bin_tree_node* node);

/*
 * This function will return the pointer to the right child.
 *
 * @param node The node.
 * @return It returns a pointer to the right child.
 */
ds_bin_tree_node* ds_bin_tree_node_right(ds_bin_tree_node* node);

/**
 * This function will return 1 if the node is a leaf (i.e. it has no children).
 *
 * @param node The node.
 * @return It returns 1 if the node has no children (i.e. it is a leaf).
 */
int ds_bin_tree_node_is_leaf(ds_bin_tree_node* node);


/**
 * This function will return a pointer to the element stored within the node.
 *
 * @param node The node.
 * @return It returns a pointer to the element store within the node.
 */
const void* ds_bin_tree_node_get(ds_bin_tree_node* node);

// Binary Tree interface

/**
 * This function will create an instance of ds_bin_tree.
 *
 * @param cmp_func This is the pointer to a function that will be used to compare two elements
 * @param size It is the size of the element that a list node is supposed to store
 * @return It returns the pointer to a new instance of ds_bin_tree
 */
ds_bin_tree* create_ds_bin_tree(ds_cmp cmp_func, const size_t size);

/**
 * This function will release the memory allocated to the binary tree.
 * Elements stored in the list will be freed using 'free'.
 *
 * @param bt the binary tree.
 */
void delete_ds_bin_tree(ds_bin_tree* bt);

/**
 * This function will return the number of elements store in the binary tree.
 *
 * @param bt The binary tree.
 * @return The number of elements stored in the binary tree.
 */
size_t ds_bin_tree_size(const ds_bin_tree* bt);

/**
 * This function will insert an element into the binary tree.
 *
 * @param bt The binary tree.
 * @param element The element.
 * @return The result of the operation.
 */
ds_result ds_bin_tree_insert(ds_bin_tree* bt, const void* element);

/**
 * This function will remove an element into the binary tree if exists.
 *
 * @param bt The binary tree.
 * @param element The element.
 * @return The result of the operation.
 */
ds_result ds_bin_tree_remove(ds_bin_tree* bt, const void* element);

/**
 * This function will look for an element into the binary tree.
 *
 * @param bt The binary tree.
 * @param element The element.
 * @return It returns 1 if the element exists, 0 otherwise.
 */
int ds_bin_tree_search(ds_bin_tree* bt, const void* element);

/**
 * This function will return the maximum value into the binary tree.
 *
 * @param bt The binary tree.
 * @return The maximum value stored in the binary tree.
 */
const void* ds_bin_tree_max(ds_bin_tree* bt);

/**
 * This function will return the minimum value into the binary tree.
 *
 * @param bt The binary tree.
 * @return The minimum value stored in the binary tree.
 */
const void* ds_bin_tree_min(ds_bin_tree* bt);

/**
 * This function will implement a custom visit on tree nodes using a specified visiting strategy.
 *
 * @param bt The binary tree.
 * @param visit_func The function that will be used to visit the element within the node.
 * @param type The type of the tree visit.
 */
void ds_bin_tree_visit(ds_bin_tree* bt, void (*visit_func)(const void*), ds_visit_type type);

#endif
