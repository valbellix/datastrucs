/*
 * @file bin_tree.c
 * @author Valerio Bellizia
 */

#include "bin_tree.h"

#include <stdlib.h>
#include <string.h>

// struct definitions

struct ds_bin_tree {
	ds_bin_tree_node* root;
	ds_cmp cmp;
	size_t elements;
	size_t element_size;
};

struct ds_bin_tree_node {
	void* info;
	struct ds_bin_tree_node* left;
	struct ds_bin_tree_node* right;
};

// functions

static int node_search(ds_cmp cmp_func, ds_bin_tree_node* root, const void* element) {
	if (root == NULL)
		return 0;
	else if (cmp_func(element, root->info) == 0)
		return 1;
	else if (cmp_func(element, root->info) < 0)
		return node_search(cmp_func, root->left, element);
	else
		return node_search(cmp_func, root->right, element);
}

static ds_bin_tree_node* get_parent(ds_cmp cmp_func, ds_bin_tree_node* root, const void* element) {
	if (ds_bin_tree_node_is_leaf(root))
		return root;
	else if (cmp_func(element, root->info) < 0)
		return get_parent(cmp_func, root->left, element);
	else
		return get_parent(cmp_func, root->right, element);
}

ds_bin_tree_node* create_ds_bin_tree_node(void* element, const size_t size) {
	ds_bin_tree_node* node = (ds_bin_tree_node*) malloc(sizeof(ds_bin_tree_node));
	if (node != NULL) {
		node->left = NULL;
		node->right = NULL;

		node->info = malloc(size);
		if (node->info != NULL) {
			memcpy(node->info, element, size);
		}
	}

	return node;
}

ds_bin_tree_node* ds_bin_tree_node_left(ds_bin_tree_node* node) {
	return node->left;
}


ds_bin_tree_node* ds_bin_tree_node_right(ds_bin_tree_node* node) {
	return node->right;
}

int ds_bin_tree_node_is_leaf(ds_bin_tree_node* node) {
	return (node->left == NULL) && (node->right == NULL);
}

void delete_ds_bin_tree_node(ds_bin_tree_node* node) {
	if (node != NULL) {
		if (node->info != NULL) {
			free(node->info);
		}
		free(node);
	}
}

const void* ds_bin_tree_node_get(ds_bin_tree_node* node) {
	if (node == NULL)
		return NULL;

	return node->info;
}

ds_bin_tree* create_ds_bin_tree(ds_cmp cmp_func, const size_t size) {
	ds_bin_tree* bt = (ds_bin_tree*) malloc(sizeof(ds_bin_tree));
	if (bt == NULL)
		return bt;

	bt->root = NULL;
	bt->cmp = cmp_func;
	bt->elements = 0;
	bt->element_size = size;

	return bt;
}

size_t ds_bin_tree_size(const ds_bin_tree* bt) {
	return bt->elements;
}

ds_result ds_bin_tree_insert(ds_bin_tree* bt, const void* element) {
	if (element == NULL)
		return GENERIC_ERROR;

	if (bt->root == NULL) {
		bt->root = create_ds_bin_tree_node(element, bt->element_size);
	}
	else {
		ds_bin_tree_node* parent = get_parent(bt->cmp, bt->root, element);
		// parent should not be null

		// we will insert duplicates to the left... but do we really want duplicate elements?
		if (bt->cmp(element, parent->info) <= 0)
			parent->left = create_ds_bin_tree_node(element, bt->element_size);
		else
			parent->right = create_ds_bin_tree_node(element, bt->element_size);;
	}

	bt->elements++;

	return SUCCESS;
}

ds_result ds_bin_tree_remove(ds_bin_tree* bt, const void* element) {
	if (element == NULL)
		return GENERIC_ERROR;

	if (bt->root == NULL) {
		return SUCCESS;
	}
	else {
		ds_bin_tree_node* parent = get_parent(bt->cmp, bt->root, element);
		int is_left_child = bt->cmp(element, parent->info) <= 0;

		ds_bin_tree_node* to_remove = is_left_child ? parent->left : parent->right;
		if (ds_bin_tree_node_is_leaf(to_remove)) {
			if (is_left_child)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else if (to_remove->left != NULL && to_remove->right == NULL) {
			if (is_left_child)
				parent->left = to_remove->left;
			else
				parent->right = to_remove->left;
		}
		else if (to_remove->right != NULL && to_remove->left == NULL) {
			if (is_left_child)
				parent->left = to_remove->right;
			else
				parent->right = to_remove->right;
		}
		else {
			// find the successor of the node element to remove.... i.e. the minimum of the right sub-tree
			ds_bin_tree_node* r = to_remove->right;
			while (!ds_bin_tree_node_is_leaf(r->left))
				r = r->left;

			// now 'r' is the parent of the successor of the element to remove
			r->left->left = to_remove->left;
			r->left->right = to_remove->right;
			if (is_left_child)
				parent->left = r->left;
			else
				parent->right = r->left;
		}

		to_remove->left = NULL;
		to_remove->right = NULL;
		delete_ds_bin_tree_node(to_remove);

		bt->elements--;
		return SUCCESS;
	}
}

int ds_bin_tree_search(ds_bin_tree* bt, const void* element) {
	if (bt == NULL || element == NULL || bt->root == NULL)
		return 0;

	return node_search(bt->cmp, bt->root, element);
}

void delete_ds_bin_tree(ds_bin_tree* bt) {
	// TBD
}
