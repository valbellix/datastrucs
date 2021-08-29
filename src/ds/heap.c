/*
 * @file heap.c
 * @author Valerio Bellizia
 */

#include "heap.h"
#include "vect.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

// struct definitions
struct ds_heap {
	ds_vect* v;
	size_t element_size;
	ds_heap_type type;
	size_t(*left_is_up)(ds_vect* h, int left, int right);
};

// helper functions
static int entry_cmp(const void* el1, const void* el2) {
	// it does not matter...
	return 0;
}

static int left_child_index(int index) {
	return (index * 2) + 1;
}

static int right_child_index(int index) {
	return (index * 2) + 2;
}

static int parent_index(int index) {
	if (index == 0) {
		// the root has no parent
		return -1;
	}

	return floor(((double)index - 1) / 2);
}

static size_t min_heap_cmp(ds_vect* h, int left, int right) {
	ds_vect_iterator left_it = ds_vect_at(h, left);
	ds_vect_iterator right_it = ds_vect_at(h, right);

	ds_heap_entry* left_element = ds_vect_iterator_get_ptr(ds_heap_entry, &left_it);
	ds_heap_entry* right_element = ds_vect_iterator_get_ptr(ds_heap_entry, &right_it);

	return left_element->priority < right_element->priority;
}

static size_t max_heap_cmp(ds_vect* h, int left, int right) {
	ds_vect_iterator left_it = ds_vect_at(h, left);
	ds_vect_iterator right_it = ds_vect_at(h, right);

	ds_heap_entry* left_element = ds_vect_iterator_get_ptr(ds_heap_entry, &left_it);
	ds_heap_entry* right_element = ds_vect_iterator_get_ptr(ds_heap_entry, &right_it);

	return left_element->priority > right_element->priority;
}

static void heapify(size_t (*left_is_up)(ds_vect*, int, int), ds_vect* h, int i) {
	int left_index = left_child_index(i);
	int right_index = right_child_index(i);

	size_t array_size = ds_vect_length(h);

	int upmost_index = i;
	if (left_index < array_size && left_is_up(h, left_index, upmost_index))
		upmost_index = left_index;
	if (right_index < array_size && left_is_up(h, right_index, upmost_index))
		upmost_index = right_index;
	if (upmost_index != i) {
		ds_vect_swap(h, i, upmost_index);
		heapify(left_is_up, h, upmost_index);
	}
}

// Interface functions

void delete_ds_heap_entry(ds_heap_entry* entry) {
	if (entry != NULL && entry->info != NULL)
		free(entry->info);
}

ds_heap* create_ds_heap(ds_heap_type type, const size_t element_size) {
	ds_heap* heap = (ds_heap*)malloc(sizeof(ds_heap));
	if (heap == NULL)
		return NULL;

	heap->v = create_ds_vect(entry_cmp, sizeof(ds_heap_entry));
	heap->element_size = element_size;
	heap->type = type;
	heap->left_is_up = (heap->type == MAX_HEAP) ? max_heap_cmp : min_heap_cmp;

	return heap;
}

void delete_ds_heap(ds_heap* h) {
	if (h == NULL)
		return;

	if (h->v != NULL) {
		delete_ds_vect(h->v);
	}

	free(h);
}

size_t ds_heap_size(ds_heap* h) {
	return ds_vect_length(h->v);
}

ds_heap_type ds_heap_get_type(ds_heap* h) {
	return h->type;
}

ds_result ds_heap_push(ds_heap* h, const void* element, const int priority) {
	int current = ds_vect_length(h->v);

	ds_heap_entry entry;
	entry.priority = priority;

	// We are copying the pointer here... the deep copy will be done when it will be added to te vector
	entry.info = (void*) element;

	ds_vect_push_back(h->v, &entry);

	int parent = parent_index(current);
	if (parent == -1) {
		return SUCCESS;
	}

	while (h->left_is_up(h->v, current, parent)) {
		ds_vect_swap(h->v, current, parent);

		current = parent;
		parent = parent_index(current);
		if (parent == -1)
			break;
	}

	return SUCCESS;
}

ds_heap_entry ds_heap_pop(ds_heap* h) {
	ds_vect_iterator top_it = ds_vect_at(h->v, 0);
	ds_heap_entry* el_to_pop = ds_vect_iterator_get_ptr(ds_heap_entry, &top_it);

	// We need to copy, otherwise ds_vect_remove will eventually release the memory
	ds_heap_entry entry;
	entry.priority = el_to_pop->priority;
	entry.info = malloc(h->element_size);
	memcpy(entry.info, el_to_pop->info, h->element_size);

	int array_size = ds_vect_length(h->v);

	if (array_size == 1) {
		ds_vect_remove(h->v, 0);
	}
	else {
		ds_vect_swap(h->v, 0, array_size-1);
		ds_vect_remove(h->v, array_size - 1);
		heapify(h->left_is_up, h->v, 0);
	}

	return entry;
}
