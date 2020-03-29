#include "vect.h"

#include <stdlib.h>
#include <string.h>

#define LOAD_FACTOR 2
#define INITIAL_CAPACITY 2

struct ds_vect {
	char* store;
	size_t capacity;
	size_t usedLength;
	size_t factor;
	size_t element_size;

	ds_vect_cmp compare;
};

static ds_result expand(ds_vect* this) {
	if ((this->usedLength + 1) <= this->capacity)
		return SUCCESS;

	size_t newCapacity = this->factor * this->capacity;
	char* data = realloc(this->store, newCapacity * this->element_size);
	if (data == NULL)
		return GENERIC_ERROR;

	this->store = data;
	this->capacity = newCapacity;

	return SUCCESS;
}

ds_vect* create_ds_vect(ds_vect_cmp func, const size_t element_size) {
	ds_vect* v = (ds_vect*) malloc(sizeof(ds_vect));

	v->capacity = INITIAL_CAPACITY;
	v->usedLength = 0;
	v->factor = LOAD_FACTOR;
	v->compare = func;
	v->element_size = element_size;

	v->store = malloc(v->capacity * element_size);

	return v;
}

void delete_ds_vect(ds_vect* this) {
	if (!this)
		return;

	if (this->store) {
		free(this->store);
	}

	free(this);
}

int ds_vect_exists(const ds_vect* this, const void* element) {
	for (size_t i = 0; i < this->usedLength; ++i) {
		if (this->compare(this->store + (i * this->element_size), element) == 0)
			return 1;
	}

	return 0;
}

ds_result ds_vect_at(const ds_vect* this, const size_t pos, void* out) {
	if (pos >= this->usedLength)
		return OUT_OF_BOUND;

	memcpy(out, this->store + (this->element_size * pos), this->element_size);
	return SUCCESS;
}

ds_result ds_vect_add(ds_vect* this, const void* element) {
	ds_result res = expand(this);
	if (res != SUCCESS)
		return res;

	memcpy(this->store + (this->usedLength * this->element_size), element, this->element_size);
	this->usedLength++;

	return SUCCESS;
}

size_t ds_vect_length(const ds_vect* this) {
	return this->usedLength;
}

ds_result ds_vect_set(ds_vect* this, const void* element, const size_t pos) {
	if (pos >= this->usedLength) {
		return OUT_OF_BOUND;
	}

	memcpy(this->store + (pos * this->element_size), element, this->element_size);
	return SUCCESS;
}

ds_result ds_vect_remove(ds_vect* v, const void* element) {
	// TODO
	return GENERIC_ERROR;
}
