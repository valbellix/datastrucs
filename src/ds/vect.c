#include "vect.h"

#include <stdlib.h>
#include <string.h>

#define LOAD_FACTOR 2
#define INITIAL_CAPACITY 2

// this definition should be make things more readable, it returns the pointer to the item at position POS
#define VECT_AT(THIS, POS) THIS->store + ((POS) * THIS->element_size)

// Struct definition
struct ds_vect {
	char* store;
	size_t capacity;
	size_t size;
	size_t factor;
	size_t element_size;

	ds_vect_cmp compare;
};

// Some helpers
static ds_vect_iterator create_iterator(const ds_vect* this, const size_t pos) {
	ds_vect_iterator it;

	it.pos = pos;
	it.v = this;

	return it;
}

static ds_result expand(ds_vect* this) {
	if ((this->size + 1) <= this->capacity)
		return SUCCESS;

	size_t new_capacity = this->factor * this->capacity;
	char* data = realloc(this->store, new_capacity * this->element_size);
	if (data == NULL)
		return GENERIC_ERROR;

	this->store = data;
	this->capacity = new_capacity;

	return SUCCESS;
}

static ds_result shrink(ds_vect* this) {
	if ((this->size - 1) > this->capacity/2)
		return SUCCESS;

	size_t new_capacity = this->capacity / this->factor;
	char* data = realloc(this->store, new_capacity * this->element_size);
	if (data == NULL)
		return GENERIC_ERROR;

	this->store = data;
	this->capacity = new_capacity;

	return SUCCESS;
}

// Interface functions
void ds_vect_iterator_next(ds_vect_iterator* it) {
	if (it->pos < it->v->size)
		it->pos++;
}

void ds_vect_iterator_prev(ds_vect_iterator* it) {
	if (it->pos >= 0)
		it->pos--;
}

int ds_vect_iterator_is_valid(ds_vect_iterator* it) {
	return it->pos >= 0 && it->pos < it->v->size;
}

const void* ds_vect_iterator_get(ds_vect_iterator* it) {
	return ((const void*) VECT_AT(it->v, it->pos));
}

ds_vect* create_ds_vect(ds_vect_cmp func, const size_t element_size) {
	ds_vect* v = (ds_vect*) malloc(sizeof(ds_vect));

	v->capacity = INITIAL_CAPACITY;
	v->size = 0;
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
	for (size_t i = 0; i < this->size; ++i) {
		if (this->compare(VECT_AT(this, i), element) == 0)
			return 1;
	}

	return 0;
}

ds_vect_iterator ds_vect_at(const ds_vect* this, const size_t pos) {
	return create_iterator(this, pos);
}

ds_vect_iterator ds_vect_begin(const ds_vect* this) {
	return create_iterator(this, 0);
}

ds_vect_iterator ds_vect_end(const ds_vect* this) {
	return create_iterator(this, this->size-1);
}

ds_result ds_vect_push_back(ds_vect* this, const void* element) {
	ds_result res = expand(this);
	if (res != SUCCESS)
		return res;

	memcpy(VECT_AT(this, this->size), element, this->element_size);
	this->size++;

	return SUCCESS;
}

size_t ds_vect_length(const ds_vect* this) {
	return this->size;
}

ds_result ds_vect_set(ds_vect* this, const void* element, const size_t pos) {
	if (pos >= this->size)
		return OUT_OF_BOUND;

	memcpy(VECT_AT(this, pos), element, this->element_size);
	return SUCCESS;
}

ds_result ds_vect_remove(ds_vect* this, const size_t pos) {
	if (pos >= this->size)
		return OUT_OF_BOUND;

	if (pos != this->size - 1) {
		size_t sizeToMove = (this->capacity - pos) * this->element_size;
		memmove(VECT_AT(this, pos), VECT_AT(this, pos + 1), sizeToMove);
	}

	this->size--;

	return GENERIC_ERROR;
}
