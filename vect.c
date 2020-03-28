#include "vect.h"

#include <stdlib.h>

#define LOAD_FACTOR 2
#define INITIAL_CAPACITY 2

struct ds_vect {
	void** elements;
	size_t capacity;
	size_t usedLength;
	size_t factor;
	size_t element_size;

	ds_vect_cmp compare;
	ds_vect_element_release element_release;
};

static ds_result expand(ds_vect* this) {
	if ((this->usedLength + 1) < this->capacity)
		return SUCCESS;

	size_t newSize = this->factor * this->capacity;
	this->elements = realloc(this->elements, newSize * sizeof(void*));
	if (this->elements = NULL)
		return GENERIC_ERROR;

	this->capacity = newSize;
	return SUCCESS;
}

ds_vect* create_ds_vect(ds_vect_cmp func, ds_vect_element_release el_rel_func, const size_t element_size) {
	ds_vect* v = (ds_vect*) malloc(sizeof(ds_vect));

	v->capacity = INITIAL_CAPACITY;
	v->usedLength = 0;
	v->factor = LOAD_FACTOR;
	v->compare = func;
	v->element_release = el_rel_func;
	v->element_size = element_size;

	v->elements = malloc(v->capacity * element_size);

	return v;
}

void delete_ds_vect(ds_vect* this) {
	if (!this)
		return;

	for (size_t i = 0; i < this->capacity; ++i) {
		this->element_release(this->elements[i]);
	}

	free(this);
}

int ds_vect_exists(const ds_vect* this, const void* element) {
	if (!this)
		return -1;

	for (size_t i = 0; i < this->usedLength; ++i) {
		if (this->compare(this->elements[i], element) == 0)
			return 1;
	}

	return 0;
}

ds_result ds_vect_at(const ds_vect* this, const size_t pos, void** out) {
	if (pos >= this->usedLength)
		return OUT_OF_BOUND;

	out = this->elements[pos];
	return SUCCESS;
}

ds_result ds_vect_add(ds_vect* this, const void* element) {
	ds_result res = expand(this);
	if (res != SUCCESS)
		return res;

	// TODO: this should be copied...
	this->elements[this->usedLength] = element;
	this->usedLength++;

	return SUCCESS;
}
