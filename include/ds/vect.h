#ifndef vect_h
#define vect_h

#include "result.h"
#include <stddef.h>

typedef int (*ds_vect_cmp)(const void*, const void*);
typedef struct ds_vect ds_vect;

typedef struct ds_vect_iterator {
	int pos;

	const ds_vect* v;
} ds_vect_iterator;

// Iterator functions
void ds_vect_iterator_next(ds_vect_iterator* it);
void ds_vect_iterator_prev(ds_vect_iterator* it);
int ds_vect_iterator_is_valid(ds_vect_iterator* it);
const void* ds_vect_iterator_get(ds_vect_iterator* it);

// Vector interface
ds_vect* create_ds_vect(ds_vect_cmp cmp_func, const size_t el_size);
void delete_ds_vect(ds_vect* v);

size_t ds_vect_length(const ds_vect* v);
ds_vect_iterator ds_vect_at(const ds_vect* v, const size_t pos);
ds_vect_iterator ds_vect_begin(const ds_vect* v);
ds_vect_iterator ds_vect_end(const ds_vect* v);

int ds_vect_exists(const ds_vect* v, const void* element);
ds_result ds_vect_push_back(ds_vect* v, const void* element);
ds_result ds_vect_remove(ds_vect* v, const size_t pos);
ds_result ds_vect_set(ds_vect* v, const void* element, const size_t pos);

#endif