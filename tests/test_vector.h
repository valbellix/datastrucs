/*
 * @file test_vector.h
 * @author Valerio Bellizia
 *
 * This file contains vector specific tests.
 */

#ifndef test_vector_h
#define test_vector_h

#include "common_stuff.h"

#include <stdio.h>
#include <stdlib.h>

#include <ds/vect.h>

void print_vect_element(const ds_vect_iterator* it) {
	printf("[%d] -> %d\n", it->pos, *((int*)ds_vect_iterator_get(it)));
}

int run_test_vector(ds_vect* v) {
	printf("test adding elements\n");
	int one = 123;
	int two = 456;
	ds_vect_push_back(v, &one);
	ds_vect_push_back(v, &two);

	ds_vect_iterator it0 = ds_vect_at(v, 0);
	ds_vect_iterator it1 = ds_vect_at(v, 1);

	printf("one -> %d\n", *((int*)ds_vect_iterator_get(&it0)));
	printf("two -> %d\n", *((int*)ds_vect_iterator_get(&it1)));

	int three = 789;
	ds_vect_push_back(v, &three);
	ds_vect_iterator it2 = ds_vect_at(v, 2);

	printf("three -> %d\n", *((int*)ds_vect_iterator_get(&it2)));

	INFOLN("test element existence")
	int doesNotExist = 1000;
	CHECK_IF("check if element exists", ds_vect_exists(v, &one))
	CHECK_IF_NOT("check if element does not exist", ds_vect_exists(v, &doesNotExist))

	INFOLN("test forward iteration")
	for (ds_vect_iterator it = ds_vect_first(v); ds_vect_iterator_is_valid(&it); ds_vect_iterator_next(&it)) {
		printf("[%d] -> %d\n", it.pos, *((int*)ds_vect_iterator_get(&it)));
	}

	INFOLN("test backward iteration")
	for (ds_vect_iterator it = ds_vect_last(v); ds_vect_iterator_is_valid(&it); ds_vect_iterator_prev(&it))
		printf("[%d] -> %d\n", it.pos, *((int*)ds_vect_iterator_get(&it)));

	INFOLN("test insert at given position")
	int anotherValue = 555;
	ds_vect_set(v, &anotherValue, 2);
	it2 = ds_vect_at(v, 2);
	printf("[%d] -> %d\n", 2, *((int*)ds_vect_iterator_get(&it2)));

	INFOLN("test do things forward")
	ds_vect_do(v, print_vect_element, ds_vect_first(v), ds_vect_length(v), FORWARD);

	INFOLN("test do things backward")
	ds_vect_do(v, print_vect_element, ds_vect_last(v), ds_vect_length(v), BACKWARD);

	INFOLN("test remove")
	ds_vect_remove(v, 1);
	ds_vect_remove(v, 1);
	for (ds_vect_iterator it = ds_vect_first(v); ds_vect_iterator_is_valid(&it); ds_vect_iterator_next(&it))
		printf("[%d] -> %d\n", it.pos, *((int*)ds_vect_iterator_get(&it)));

	return 0;
}

int test_vector() {
	ds_vect* v = create_ds_vect(int_cmp, sizeof(int));
	int rc = run_test_vector(v);
	delete_ds_vect(v);
	return rc;
}

#endif
