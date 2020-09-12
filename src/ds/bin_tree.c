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
	struct ds_bin_tree_node* parent;
	struct ds_bin_tree_node* left;
	struct ds_bin_tree_node* right;
};

// functions

static void node_visit(ds_bin_tree_node* root, void (*visit_element)(const void*), ds_visit_type type) {
	if (root == NULL)
		return;

	switch (type) {
	case DFS_PRE_ORDER:
		visit_element(root->info);
		node_visit(root->left, visit_element, type);
		node_visit(root->right, visit_element, type);
		break;
	case DFS_IN_ORDER:
		node_visit(root->left, visit_element, type);
		visit_element(root->info);
		node_visit(root->right, visit_element, type);
		break;
	case DFS_POST_ORDER:
		node_visit(root->left, visit_element, type);
		node_visit(root->right, visit_element, type);
		visit_element(root->info);
		break;
	default:
		break;
	}
}

static ds_bin_tree_node* node_search(ds_cmp cmp_func, ds_bin_tree_node* root, const void* element) {
	if (root == NULL)
		return NULL;
	else {
		int cmp_res = cmp_func(element, root->info);
		if (cmp_res == 0)
			return root;
		else if (cmp_res < 0)
			return node_search(cmp_func, root->left, element);
		else
			return node_search(cmp_func, root->right, element);
	}
}

static void free_nodes(ds_bin_tree_node* root) {
	if (root == NULL)
		return;
	else if (ds_bin_tree_node_is_leaf(root))
		free(root);
	else {
		free_nodes(root->left);
		free_nodes(root->right);
		free(root);
	}
}

static ds_bin_tree_node* get_max(ds_bin_tree_node* root) {
	if (root == NULL)
		return NULL;
	else if (ds_bin_tree_node_is_leaf(root))
		return root;
	else {
		ds_bin_tree_node* aux = root;
		while (aux->right != NULL) {
			aux = aux->right;
		}

		return aux;
	}
}

static ds_bin_tree_node* get_min(ds_bin_tree_node* root) {
	if (root == NULL)
		return NULL;
	else if (ds_bin_tree_node_is_leaf(root))
		return root;
	else {
		ds_bin_tree_node* aux = root;
		while (aux->left != NULL) {
			aux = aux->left;
		}

		return aux;
	}
}

ds_bin_tree_node* create_ds_bin_tree_node(void* element, const size_t size) {
	ds_bin_tree_node* node = (ds_bin_tree_node*) malloc(sizeof(ds_bin_tree_node));
	if (node != NULL) {
		node->parent = NULL;
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
		ds_bin_tree_node* aux = bt->root;
		ds_bin_tree_node* parent = NULL;
		int turn_left = 0; // I do not like to repeat the test after the ending of the while loop

		while (aux != NULL) {
			parent = aux;
			turn_left = bt->cmp(element, aux->info) <= 0;
			if (turn_left)
				aux = aux->left;
			else
				aux = aux->right;
		}

		if (turn_left) {
			parent->left = create_ds_bin_tree_node(element, bt->element_size);
			parent->left->parent = parent;
		}
		else {
			parent->right = create_ds_bin_tree_node(element, bt->element_size);
			parent->right->parent = parent;
		}
	}

	bt->elements++;

	return SUCCESS;
}

ds_result ds_bin_tree_remove(ds_bin_tree* bt, const void* element) {
	// The previous implementation was wrong... TBD
	if (bt == NULL)
		return GENERIC_ERROR;
	if (bt->root == NULL)
		return SUCCESS;

	ds_bin_tree_node* to_remove = node_search(bt->cmp, bt->root, element);
	if (to_remove == NULL)
		return SUCCESS;

	if (ds_bin_tree_node_is_leaf(to_remove)) {
		if (to_remove->parent != NULL) {
			if (to_remove->parent->left == to_remove)
				to_remove->parent->left = NULL;
			else
				to_remove->parent->right = NULL;
		}
	}
	else if (to_remove->left != NULL && to_remove->right == NULL) {
		// we have just one child node and it is the right one
		ds_bin_tree_node* child = to_remove->left;
		child->parent = to_remove->parent;

		if (to_remove->parent != NULL) {
			if (to_remove->parent->left == to_remove)
				to_remove->parent->left = child;
			else
				to_remove->parent->right = child;
		}
	}
	else if (to_remove->left == NULL && to_remove->right != NULL) {
		// we have just one child node and it is the right one
		ds_bin_tree_node* child = to_remove->right;
		child->parent = to_remove->parent;

		if (to_remove->parent != NULL) {
			if (to_remove->parent->left == to_remove)
				to_remove->parent->left = child;
			else
				to_remove->parent->right = child;
		}
	}
	else {
		// we have two children, so we need to swap with its successor
		// (i.e. the minimum of the right sub-tree)
		ds_bin_tree_node* successor = get_min(to_remove->right);

		// it may have just a right child
		if (successor->right != NULL) {
			if (successor->parent != NULL) {
				successor->parent->left = successor->right;
			}
			successor->right->parent = successor->parent;
		}

		successor->parent = to_remove->parent;
		successor->left = to_remove->left;
		// the right subtree of the successor should not need to be touched

		if (to_remove->parent != NULL) {
			if (to_remove->parent->left == to_remove)
				to_remove->parent->left = successor;
			else
				to_remove->parent->right = successor;
		}
	}

	delete_ds_bin_tree_node(to_remove);

	bt->elements--;
	return SUCCESS;
}

int ds_bin_tree_search(ds_bin_tree* bt, const void* element) {
	if (bt == NULL || element == NULL || bt->root == NULL)
		return 0;

	return node_search(bt->cmp, bt->root, element) != NULL;
}

void delete_ds_bin_tree(ds_bin_tree* bt) {
	if (bt == NULL)
		return;

	if (bt->root != NULL)
		free_nodes(bt->root);
	free(bt);
}

const void* ds_bin_tree_max(ds_bin_tree* bt) {
	if (bt == NULL)
		return NULL;

	ds_bin_tree_node* max = get_max(bt->root);
	if (max == NULL)
		return NULL;

	return max->info;
}

const void* ds_bin_tree_min(ds_bin_tree* bt) {
	if (bt == NULL)
		return NULL;

	ds_bin_tree_node* min = get_min(bt->root);
	if (min == NULL)
		return NULL;

	return min->info;
}

void ds_bin_tree_visit(ds_bin_tree* bt, void (*visit_element)(const void*), ds_visit_type type) {
	if (bt == NULL)
		return;

	node_visit(bt->root, visit_element, type);
}
