/*
 * @file treemap.c
 * @author Valerio Bellizia
 */

#include "treemap.h"
#include "bst.h"

#include <stdlib.h>
#include <string.h>

// ds_treemap struct definition...

struct ds_treemap {
	ds_bst* bst;
	size_t num_el;
	size_t key_len;
	size_t value_len;
};

ds_treemap* create_ds_treemap(ds_cmp key_cmp, size_t key_len, size_t value_len) {
	ds_treemap* map = (ds_treemap*) malloc(sizeof(ds_treemap));
	if (map == NULL)
		return map;
	
	map->num_el = 0;
	map->key_len = key_len;
	map->value_len = value_len;
	map->bst = create_ds_bst(key_cmp, sizeof(ds_treemap_entry));

	return map;
}

void delete_ds_treemap(ds_treemap* map) {
	if (map == NULL)
		return;

	delete_ds_bst(map->bst);
	free(map);
}

ds_result ds_treemap_insert(ds_treemap* map, void* k, void* v) {
	ds_treemap_entry entry;
	entry.key = k;
	entry.value = v;

	return ds_bst_insert(map->bst, &entry);
}

const ds_treemap_entry* ds_treemap_get(ds_treemap* map, void* k) {
	ds_treemap_entry aux;
	aux.key = k;
	return (const ds_treemap_entry*) ds_bst_get(map->bst, &aux);
}

int ds_treemap_search(ds_treemap* map, void* k) {
	return ds_treemap_get(map, k) != NULL;
}

ds_result ds_treemap_remove(ds_treemap* map, void* k) {
	ds_treemap_entry aux;
	aux.key = k;

	return ds_bst_remove(map->bst, &aux);
}

static void visit_bst(const void* el, void* aux) {
	ds_treemap_entry* entry = (ds_treemap_entry*) el;
	ds_vect* vect = (ds_vect*) aux;

	ds_vect_push_back(vect, entry->key);
}

ds_vect* ds_treemap_keys(ds_treemap* map) {
	ds_vect* vect = create_ds_vect(ds_bst_cmp(map->bst), map->key_len);

	ds_bst_visit(map->bst, visit_bst, vect, DFS_IN_ORDER);

	return vect;
}

ds_treemap_iterator ds_treemap_first(ds_treemap* map) {
	return ds_bst_first(map->bst);
}

ds_treemap_iterator ds_treemap_last(ds_treemap* map) {
	return ds_bst_last(map->bst);
}

void ds_treemap_iterator_next(ds_treemap_iterator* it) {
	ds_bst_iterator_next(it);
}

void ds_treemap_iterator_prev(ds_treemap_iterator* it) {
	ds_bst_iterator_prev(it);
}

int ds_treemap_iterator_is_valid(ds_treemap_iterator* it) {
	return ds_bst_iterator_is_valid(it);
}

const ds_treemap_entry* ds_treemap_iterator_get(ds_treemap_iterator* it) {
	return (const ds_treemap_entry*)ds_bst_iterator_get(it);
}

size_t ds_treemap_size(ds_treemap* map) {
	return ds_bst_size(map->bst);
}