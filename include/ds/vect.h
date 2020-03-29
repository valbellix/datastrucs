#ifndef vect_h
#define vect_h

#include "result.h"
#include <stddef.h>

typedef int (*ds_vect_cmp)(const void*, const void*);
typedef struct ds_vect ds_vect;

ds_vect* create_ds_vect(ds_vect_cmp cmp_func, const size_t el_size);
void delete_ds_vect(ds_vect* v);

size_t ds_vect_length(const ds_vect* v);
ds_result ds_vect_at(const ds_vect* v, const size_t pos, void* out);
int ds_vect_exists(const ds_vect* v, const void* element);
ds_result ds_vect_add(ds_vect* v, const void* element);
ds_result ds_vect_remove(ds_vect* v, const void* element);
ds_result ds_vect_set(ds_vect* v, const void* element, const size_t pos);

#endif