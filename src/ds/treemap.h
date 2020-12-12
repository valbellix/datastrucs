/**
 * @file treemap.h
 * @author Valerio Bellizia
 *
 * This file contains the interface to be used with ds_treemap. It implements 
 * a treemap using a ds_bst as base. It is basically a map, therefore the structure
 * contains <key, value> pairs sorted by key.
 */

#ifndef treemap_h
#define treemap_h

#include "result.h"
#include "defs.h"
#include "vect.h"

#include <stddef.h>

/**
 * This is an opaque structure that represents a treemap.
 */
typedef struct ds_treemap ds_treemap;

/**
 * This structure represents an entry of the treemap. This is basically a <key, value> pair.
 */
typedef struct ds_treemap_entry {
	void* key;
	void* value;
} ds_treemap_entry;

/**
 * This is a typedef of ds_bst_iterator as ds_bst is the struct that acts as base for this treemap implementation
 */
typedef struct ds_bst_iterator ds_treemap_iterator;

/**
 * This function will move the iterator forward.
 * 
 * @param it The iterator.
 */
void ds_treemap_iterator_next(ds_treemap_iterator* it);

/**
 * This function will move the iterator backward.
 * 
 * @param it The iterator.
 */
void ds_treemap_iterator_prev(ds_treemap_iterator* it);

/**
 * This function can be used to check if the iterator is valid.
 *
 * @param it The iterator.
 * 
 * @return it returns 1 if the iterator is valid, 0 otherwise.
 */
int ds_treemap_iterator_is_valid(ds_treemap_iterator* it);

/**
 * This function will get the element pointed by the iterator.
 *
 * @param it The iterator.
 * 
 * @return The pointer to the element stored into the current element held iterator.
 */
const ds_treemap_entry* ds_treemap_iterator_get(ds_treemap_iterator* it);

/**
 * This function will create a treemap instance.
 * 
 * @param key_cmp This is the key comparison function.
 * @param key_len This is the length of the key type.
 * @param value_len This is the length of the value type.
 * 
 * @return It returns the pointer to a new instance of ds_treemap.
 */
ds_treemap* create_ds_treemap(ds_cmp key_cmp, size_t key_len, size_t value_len);

/**
 * This function will release the memory of the treemap instance passed as argument.
 * 
 * @param map The treemap instance to release.
 */
void delete_ds_treemap(ds_treemap* map);

/**
 * This function will insert a <key, value> pair in the map.
 * 
 * @param map The treemap.
 * @param k The key.
 * @param v The value.
 * 
 * @return It returns SUCCESS if the element is inserted properly. It returns ELEMENT_ALREADY_EXISTS when adding an element whose key already exists.
 */
ds_result ds_treemap_insert(ds_treemap* map, void* k, void* v);

/**
 * This function will look for a key in the map.
 * 
 * @param map The treemap.
 * @param k The key.
 * 
 * @return It returns 1 if the element is found, 0 otherwise.
 */
int ds_treemap_search(ds_treemap* map, void* k);

/**
 * This function will return an iterator to the first element of the map.
 * 
 * @param map The treemap.
 * 
 * @return It returns an iterator to the first element of the map.
 */
ds_treemap_iterator ds_treemap_first(ds_treemap* map);

/**
 * This function will return an iterator to the last element of the map.
 * 
 * @param map The treemap.
 * 
 * @return It returns an iterator to the last element of the map.
 */
ds_treemap_iterator ds_treemap_last(ds_treemap* map);

/**
 * This function will get an element on the map based on its key.
 * 
 * @param map The treemap.
 * @param k The key.
 * 
 * @return The ds_treemap_entry pointer to the element if exists, NULL otherwise.
 */
const ds_treemap_entry* ds_treemap_get(ds_treemap* map, void* k);

/**
 * This function will remove an element whose key is provided as argument.
 * 
 * @param map The treemap.
 * @param k The key.
 * 
 * @return It returns SUCCESS if the element is removed.
 */
ds_result ds_treemap_remove(ds_treemap* map, void* k);

/**
 * This function will return a vector filled with keys in the map.
 * 
 * @param map The treemap.
 * 
 * @return It returns a ds_vect with all the keys in the map.
 */
ds_vect* ds_treemap_keys(ds_treemap* map);

/**
 * This function will return the number of elements in the map.
 * 
 * @param map The treemap.
 * 
 * @return It returns the number of elements in the map.
 */
size_t ds_treemap_size(ds_treemap* map);

#endif
