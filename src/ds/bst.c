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
	int height;
	ds_cmp cmp;
	struct ds_bst_node* parent;
	struct ds_bst_node* left;
	struct ds_bst_node* right;
};

static int max(int i1, int i2) {
	return (i1 > i2) ? i1 : i2;
}

static int node_height(ds_bst_node* node) {
	return node != NULL ? node->height : 0;
}

static int node_balance(ds_bst_node* node) {
	return node != NULL ? node_height(node->left) - node_height(node->right) : 0;
}

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

static ds_bst_node* rotate_right(ds_bst_node* node) {
	ds_bst_node* l = node->left;
	ds_bst_node* l_right = l->right;

	l->right = node;
	node->left = l_right;

	if (l_right != NULL)
		l_right->parent = node;
	l->parent = node->parent;
	node->parent = l;

	l->height = 1 + max(node_height(l->left), node_height(l->right));
	node->height = 1 + max(node_height(node->left), node_height(node->right));

	return l;
}

static ds_bst_node* rotate_left(ds_bst_node* node) {
	ds_bst_node* r = node->right;
	ds_bst_node* r_left = r->left;

	r->left = node;
	node->right = r_left;

	if (r_left != NULL)
		r_left->parent = node;
	r->parent = node->parent;
	node->parent = r;

	node->height = 1 + max(node_height(node->left), node_height(node->right));
	r->height = 1 + max(node_height(r->left), node_height(r->right));

	return r;
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

ds_bst_node* create_ds_bst_node(const void* element, ds_cmp cmp, const size_t size) {
	ds_bst_node* node = (ds_bst_node*) malloc(sizeof(ds_bst_node));
	if (node != NULL) {
		node->parent = NULL;
		node->left = NULL;
		node->right = NULL;
		node->cmp = cmp;

		node->info = malloc(size);
		if (node->info != NULL) {
			memcpy(node->info, element, size);
		}
		node->height = 1;
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

static ds_bst_node* insert_node(ds_bst* bt, ds_bst_node* parent, ds_bst_node* r, const void* element) {
	if (r == NULL) {
		ds_bst_node* n = create_ds_bst_node(element, bt->cmp, bt->element_size);
		n->parent = parent;
		return n;
	}

	int cmp = bt->cmp(element, r->info);
	if (cmp < 0) {
		ds_bst_node* n = insert_node(bt, r, r->left, element);
		if (n == NULL)
			return NULL;
		r->left = n;
	}
	else if (cmp > 0) {
		ds_bst_node* n = insert_node(bt, r, r->right, element);
		if (n == NULL)
			return NULL;
		r->right = n;
	}
	else
		return NULL;
	
	// need to update balance factor and balance the tree
	r->height = 1 + max(node_height(r->left), node_height(r->right));
	int balance = node_balance(r);

	if (balance > 1 && bt->cmp(element, r->left->info) < 0)
		return rotate_right(r);

	if (balance < -1 && bt->cmp(element, r->right->info) > 0)
		return rotate_left(r);

	// following case we have doble rotation...
	if (balance > 1 && bt->cmp(element, r->left->info) > 0) {
		r->left = rotate_left(r->left);
		return rotate_right(r);
	}

	if (balance < -1 && bt->cmp(element, r->right->info) < 0) {
		r->right = rotate_right(r->right);
		return rotate_left(r);
	}

	return r;
}

ds_result ds_bst_insert(ds_bst* bt, const void* element) {
	if (element == NULL)
		return GENERIC_ERROR;

	ds_bst_node* node = insert_node(bt, NULL, bt->root, element);
	if (node != NULL) {
		bt->root = node;
		bt->elements++;
		return SUCCESS;
	}
	
	return ELEMENT_ALREADY_EXISTS;
}

static ds_bst_node* delete_node(ds_bst_node* r, const void* element, const size_t element_size) {
	// recursively look for the node to delete... like in plain BST
	if (r == NULL)
		return NULL;
	else if (r->cmp(element, r->info) < 0)
		r->left = delete_node(r->left, element, element_size);
	else if (r->cmp(element, r->info) > 0)
		r->right = delete_node(r->right, element, element_size);
	else {
		if (r->left != NULL && r->right != NULL) {
			ds_bst_node* successor = in_order_successor(r);
			memcpy(r->info, successor->info, element_size);

			r->right = delete_node(r->right, successor->info, element_size);
		}
		else {
			ds_bst_node* node = (r->left != NULL) ? r->left : r->right;
			if (node == NULL) { // is leaf...
				node = r;
				r = NULL;
			}
			else {
				memcpy(r->info, node->info, element_size);
				r->left = node->left;
				r->right = node->right;
			}

			delete_ds_bst_node(node);
		}
	}

	if (r == NULL)
		return NULL;

	r->height = 1 + max(node_height(r->left), node_height(r->right));

	// rebalance if necessary...
	int balance = node_balance(r);
	if (balance > 1 && node_balance(r->left) >= 0)
		return rotate_right(r);

	if (balance > 1 && node_balance(r->left) < 0) {
		r->left = rotate_left(r->left);
		return rotate_right(r);
	}

	if (balance < -1 && node_balance(r->right) <= 0)
		return rotate_left(r);
	
	if (balance < -1 && node_balance(r->right) > 0) {
		r->right = rotate_right(r->right);
		return rotate_left(r);
	}

	return r;
}

ds_result ds_bst_remove(ds_bst* bt, const void* element) {
	if (bt == NULL)
		return GENERIC_ERROR;
	if (bt->root == NULL)
		return SUCCESS;

	bt->root = delete_node(bt->root, element, bt->element_size);
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
