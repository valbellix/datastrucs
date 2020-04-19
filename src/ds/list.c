#include "list.h"

#include <stdlib.h>
#include <string.h>

// struct definitions

struct ds_list_node {
	char* data;

	struct ds_list_node* next;
	struct ds_list_node* prev;
};

struct ds_list {
	struct ds_list_node* root;
	size_t size;
	size_t element_size;

	ds_cmp compare;
};

static ds_list_node* create_list_node(void* element, const size_t element_size) {
	ds_list_node* node = (ds_list_node*) malloc(sizeof(ds_list_node));

	node->data = malloc(element_size);
	memcpy(node->data, element, element_size);

	node->next = NULL;
	node->prev = NULL;

	return node;
}

static ds_list_node* create_null_node() {
	ds_list_node* node = (ds_list_node*) malloc(sizeof(ds_list_node));

	node->next = NULL;
	node->prev = NULL;

	return node;
}

static void destroy_list_node(ds_list_node* node) {
	if (node == NULL)
		return;

	if (node->data != NULL)
		free(node->data);

	free(node);
}

ds_list* create_ds_list(ds_cmp cmp_func, const size_t size) {
	ds_list* list = (ds_list*) malloc(sizeof(ds_list));
	list->size = 0;
	list->element_size = size;
	list->compare = cmp_func;

	return list;
}

void delete_ds_list(ds_list* this) {
	ds_list_node* n = this->root;

	while (n != NULL) {
		ds_list_node* current = n;
		n = n->next;

		free(current);
	}

	free(this);
}

size_t ds_list_length(const ds_list* this) {
	return this->size;
}

ds_result ds_list_push_front(ds_list* this, void* element) {
	ds_list_node* n = create_list_node(element, this->element_size);

	n->next = this->root;
	this->root = n;

	this->size++;

	return SUCCESS;
}

ds_result ds_list_push_back(ds_list* this, void* element) {
	// add a fake node to simulate at least on element
	ds_list_node* aux = create_null_node();

	aux->next = this->root;
	this->root->prev = aux;

	this->root = aux;

	while (aux->next != NULL) {
		aux = aux->next;
	}

	ds_list_node* n = create_list_node(element, this->element_size);
	n->prev = aux;
	this->size++;

	// remove the fake node that is now our root
	aux = this->root;
	this->root = this->root->next;
	this->root->prev = NULL;

	// release the memory allocated to the fake node
	destroy_list_node(aux);

	return SUCCESS;
}

ds_list_iterator ds_list_at(const ds_list* this, const size_t pos) {
	ds_list_iterator iterator;
	iterator.list = this;

	if (pos >= this->size) {
		return iterator;
	}

	ds_list_node* node = this->root;
	size_t counter = 0;
	while (node != NULL) {
		if (counter == pos)
			break;

		counter++;
		node = node->next;
	}

	iterator.curr = node;
	return iterator;
}

ds_list_iterator ds_list_first(const ds_list* this) {
	ds_list_iterator iterator;
	iterator.list = this;
	iterator.curr = this->root;

	return iterator;
}

ds_list_iterator ds_list_last(const ds_list* this) {
	ds_list_iterator iterator;
	iterator.list = this;

	if (this->root == NULL)
		return iterator;

	ds_list_node* n = this->root;
	while (n->next != NULL) {
		n = n->next;
	}

	iterator.curr = n;
	return iterator;
}

void ds_list_iterator_next(ds_list_iterator* it) {
	// no need to check against nullity
	it->curr = it->curr->next;
}

void ds_list_iterator_prev(ds_list_iterator* it) {
	// no need to check against nullity
	it->curr = it->curr->prev;
}

int ds_list_iterator_is_valid(ds_list_iterator* it) {
	return it->curr != NULL;
}

const void* ds_list_iterator_get(ds_list_iterator* it) {
	return it->curr->data;
}