/*
 * @file bst.c
 * @author Valerio Bellizia
 */

#include "bst.h"

#include <stdlib.h>
#include <string.h>

// struct definitions

struct ds_bst {
	ds_bst_node* root;
	ds_cmp cmp;
	size_t elements;
	size_t element_size;
};

struct ds_bst_node {
	void* info;
	struct ds_bst_node* parent;
	struct ds_bst_node* left;
	struct ds_bst_node* right;
};

static void node_visit(ds_bst_node* root, void (*visit_element)(const void*, void*), void* other_args, ds_visit_type type) {
	if (root == NULL)
		return;

	switch (type) {
	case DFS_PRE_ORDER:
		visit_element(root->info, other_args);
		node_visit(root->left, visit_element, other_args, type);
		node_visit(root->right, visit_element, other_args, type);
		break;
	case DFS_IN_ORDER:
		node_visit(root->left, visit_element, other_args, type);
		visit_element(root->info, other_args);
		node_visit(root->right, visit_element, other_args, type);
		break;
	case DFS_POST_ORDER:
		node_visit(root->left, visit_element, other_args, type);
		node_visit(root->right, visit_element, other_args, type);
		visit_element(root->info, other_args);
		break;
	default:
		break;
	}
}

static ds_bst_node* node_search(ds_cmp cmp_func, ds_bst_node* root, const void* element) {
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

static void free_nodes(ds_bst_node* root) {
	if (root == NULL)
		return;
	else if (ds_bst_node_is_leaf(root))
		free(root);
	else {
		free_nodes(root->left);
		free_nodes(root->right);
		free(root);
	}
}

static ds_bst_node* get_max(ds_bst_node* root) {
	if (root == NULL)
		return NULL;
	else if (ds_bst_node_is_leaf(root))
		return root;
	else {
		ds_bst_node* aux = root;
		while (aux->right != NULL) {
			aux = aux->right;
		}

		return aux;
	}
}

static ds_bst_node* get_min(ds_bst_node* root) {
	if (root == NULL)
		return NULL;
	else if (ds_bst_node_is_leaf(root))
		return root;
	else {
		ds_bst_node* aux = root;
		while (aux->left != NULL) {
			aux = aux->left;
		}

		return aux;
	}
}

static ds_bst_node* in_order_successor(ds_bst_node* node) {
	if (node->right != NULL)
		return get_min(node->right);
	
	ds_bst_node* parent = node->parent;
	ds_bst_node* n = node;
	while (parent != NULL && n == parent->right) {
		n = parent;
		parent = parent->parent;
	}

	return parent;
}

static ds_bst_node* in_order_predecessor(ds_bst_node* node) {
	if (node->left != NULL)
		return get_max(node->left);
	
	ds_bst_node* parent = node->parent;
	ds_bst_node* n = node;
	while (parent != NULL && n == parent->left) {
		n = parent;
		parent = parent->parent;
	}

	return parent;
}

ds_bst_iterator ds_bst_first(ds_bst* bt) {
	ds_bst_iterator it;
	it.bst = bt;
	it.current = get_min(bt->root);

	return it;
}

ds_bst_iterator ds_bst_last(ds_bst* bt) {
	ds_bst_iterator it;
	it.bst = bt;
	it.current = get_max(bt->root);

	return it;
}

void ds_bst_iterator_next(ds_bst_iterator* it) {
	ds_bst_node* successor = in_order_successor(it->current);

	// if the successor is the current itself we are at the end...
	it->current = (successor == it->current) ? NULL : successor;
}

void ds_bst_iterator_prev(ds_bst_iterator* it) {
	ds_bst_node* pred = in_order_predecessor(it->current);

	// if the prececessor is the current itself we are at the end...
	it->current = (pred == it->current) ? NULL : pred;
}

int ds_bst_iterator_is_valid(ds_bst_iterator* it) {
	return it->current != NULL;
}

const void* ds_bst_iterator_get(ds_bst_iterator* it) {
	return it->current->info;
}

ds_bst_node* create_ds_bst_node(const void* element, const size_t size) {
	ds_bst_node* node = (ds_bst_node*) malloc(sizeof(ds_bst_node));
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

ds_bst_node* ds_bst_node_left(ds_bst_node* node) {
	return node->left;
}


ds_bst_node* ds_bst_node_right(ds_bst_node* node) {
	return node->right;
}

int ds_bst_node_is_leaf(ds_bst_node* node) {
	return (node->left == NULL) && (node->right == NULL);
}

void delete_ds_bst_node(ds_bst_node* node) {
	if (node != NULL) {
		if (node->info != NULL) {
			free(node->info);
		}
		free(node);
	}
}

const void* ds_bst_node_get(ds_bst_node* node) {
	if (node == NULL)
		return NULL;

	return node->info;
}

ds_bst* create_ds_bst(ds_cmp cmp_func, const size_t size) {
	ds_bst* bt = (ds_bst*) malloc(sizeof(ds_bst));
	if (bt == NULL)
		return bt;

	bt->root = NULL;
	bt->cmp = cmp_func;
	bt->elements = 0;
	bt->element_size = size;

	return bt;
}

size_t ds_bst_size(const ds_bst* bt) {
	return bt->elements;
}

ds_result ds_bst_insert(ds_bst* bt, const void* element) {
	if (element == NULL)
		return GENERIC_ERROR;

	if (bt->root == NULL) {
		bt->root = create_ds_bst_node(element, bt->element_size);
	}
	else {
		ds_bst_node* aux = bt->root;
		ds_bst_node* parent = NULL;
		int turn_left = 0; // I do not like to repeat the test after the ending of the while loop

		while (aux != NULL) {
			parent = aux;
			int res = bt->cmp(element, aux->info);
			if (res == 0)
				return ELEMENT_ALREADY_EXISTS;

			turn_left = res <= 0;
			if (turn_left)
				aux = aux->left;
			else
				aux = aux->right;
		}

		if (turn_left) {
			parent->left = create_ds_bst_node(element, bt->element_size);
			parent->left->parent = parent;
		}
		else {
			parent->right = create_ds_bst_node(element, bt->element_size);
			parent->right->parent = parent;
		}
	}

	bt->elements++;

	return SUCCESS;
}

ds_result ds_bst_remove(ds_bst* bt, const void* element) {
	if (bt == NULL)
		return GENERIC_ERROR;
	if (bt->root == NULL)
		return SUCCESS;

	ds_bst_node* to_remove = node_search(bt->cmp, bt->root, element);
	if (to_remove == NULL)
		return SUCCESS;

	if (ds_bst_node_is_leaf(to_remove)) {
		if (to_remove->parent != NULL) {
			if (to_remove->parent->left == to_remove)
				to_remove->parent->left = NULL;
			else
				to_remove->parent->right = NULL;
		}
	}
	else if (to_remove->left != NULL && to_remove->right == NULL) {
		// we have just one child node and it is the right one
		ds_bst_node* child = to_remove->left;
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
		ds_bst_node* child = to_remove->right;
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
		ds_bst_node* successor = get_min(to_remove->right);

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

	delete_ds_bst_node(to_remove);

	bt->elements--;
	return SUCCESS;
}

int ds_bst_search(ds_bst* bt, const void* element) {
	if (bt == NULL || element == NULL || bt->root == NULL)
		return 0;

	return node_search(bt->cmp, bt->root, element) != NULL;
}

const void* ds_bst_get(ds_bst* bt, const void* element) {
	if (bt == NULL || element == NULL || bt->root == NULL)
		return NULL;

	ds_bst_node* res = node_search(bt->cmp, bt->root, element);
	if (res == NULL)
		return NULL;
	return res->info;
}

void delete_ds_bst(ds_bst* bt) {
	if (bt == NULL)
		return;

	if (bt->root != NULL)
		free_nodes(bt->root);
	free(bt);
}

ds_cmp ds_bst_cmp(ds_bst* bt) {
	return bt->cmp;
}

const void* ds_bst_max(ds_bst* bt) {
	if (bt == NULL)
		return NULL;

	ds_bst_node* max = get_max(bt->root);
	if (max == NULL)
		return NULL;

	return max->info;
}

const void* ds_bst_min(ds_bst* bt) {
	if (bt == NULL)
		return NULL;

	ds_bst_node* min = get_min(bt->root);
	if (min == NULL)
		return NULL;

	return min->info;
}

void ds_bst_visit(ds_bst* bt, void (*visit_element)(const void*, void*), void* other_args, ds_visit_type type) {
	if (bt == NULL)
		return;

	node_visit(bt->root, visit_element, other_args, type);
}
