#ifndef list_h
#define list_h

#include "result.h"
#include "defs.h"

#include <stddef.h>

typedef struct ds_list ds_list;
typedef struct ds_list_node ds_list_node;

typedef struct ds_list_iterator {
	const ds_list* list;
	ds_list_node* curr;
} ds_list_iterator;

// Iterator functions
void ds_list_iterator_next(ds_list_iterator* it);
void ds_list_iterator_prev(ds_list_iterator* it);
int ds_list_iterator_is_valid(ds_list_iterator* it);
const void* ds_list_iterator_get(ds_list_iterator* it);

// List interface
ds_list* create_ds_list(ds_cmp cmp_func, const size_t size);
void delete_ds_list(ds_list* l);

size_t ds_list_length(const ds_list* l);
ds_list_iterator ds_list_at(const ds_list* l, const size_t pos);
ds_list_iterator ds_list_first(const ds_list* l);
ds_list_iterator ds_list_last(const ds_list* l);

int ds_list_exists(const ds_list*l, const void* element);
ds_result ds_list_push_front(ds_list* l, void* element);
ds_result ds_list_push_back(ds_list* l, void* element);
ds_result ds_list_remove(ds_list* v, const size_t pos);
ds_result ds_list_set(ds_list* v, const void* element, const size_t pos);

void ds_list_do(ds_list* l,
                void (*do_something)(const ds_list_iterator*),
                ds_list_iterator begin,
                const size_t number_of_elements,
                ds_direction direction);

#endif