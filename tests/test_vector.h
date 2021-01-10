/*
 * @file test_vector.h
 * @author Valerio Bellizia
 *
 * This file contains vector specific tests.
 */

#ifndef test_vector_h
#define test_vector_h

#include "common_stuff.h"
#include "vb_test.h"

#include <stdio.h>
#include <stdlib.h>

#include <ds/vect.h>

void print_vect_element(const ds_vect_iterator* it) {
	vb_infoln("[%d] -> %d", it->pos, ds_vect_iterator_get_value(int, it));
}

int run_test_vector(ds_vect* v) {
	vb_infoln("test adding elements");
	int one = 123;
	int two = 456;
	ds_vect_push_back(v, &one);
	ds_vect_push_back(v, &two);

	ds_vect_iterator it0 = ds_vect_at(v, 0);
	ds_vect_iterator it1 = ds_vect_at(v, 1);

	vb_infoln("one -> %d", ds_vect_iterator_get_value(int, &it0));
	vb_infoln("two -> %d", ds_vect_iterator_get_value(int, &it1));

	int three = 789;
	ds_vect_push_back(v, &three);
	ds_vect_iterator it2 = ds_vect_at(v, 2);

	vb_infoln("three -> %d", ds_vect_iterator_get_value(int, &it2));

	vb_infoln("test element existence");
	int doesNotExist = 1000;
	vb_check_equals_int("check if element exists", ds_vect_exists( v, &one), 1);
	vb_check_equals_int("check if element does not exist", ds_vect_exists(v, &doesNotExist), 0);

	vb_infoln("test forward iteration");
	for (ds_vect_iterator it = ds_vect_first(v); ds_vect_iterator_is_valid(&it); ds_vect_iterator_next(&it))
		vb_infoln("[%d] -> %d", it.pos, ds_vect_iterator_get_value(int, &it));

	vb_infoln("test backward iteration");
	for (ds_vect_iterator it = ds_vect_last(v); ds_vect_iterator_is_valid(&it); ds_vect_iterator_prev(&it))
		vb_infoln("[%d] -> %d", it.pos, ds_vect_iterator_get_value(int, &it));

	vb_infoln("test insert at given position");
	int anotherValue = 555;
	ds_vect_set(v, &anotherValue, 2);
	it2 = ds_vect_at(v, 2);
	vb_infoln("[%d] -> %d", 2, ds_vect_iterator_get_value(int, &it2));

	vb_infoln("test do things forward");
	ds_vect_do(v, print_vect_element, ds_vect_first(v), ds_vect_length(v), FORWARD);

	vb_infoln("test do things backward");
	ds_vect_do(v, print_vect_element, ds_vect_last(v), ds_vect_length(v), BACKWARD);

	vb_infoln("test remove");
	ds_vect_remove(v, 1);
	ds_vect_remove(v, 1);
	for (ds_vect_iterator it = ds_vect_first(v); ds_vect_iterator_is_valid(&it); ds_vect_iterator_next(&it))
		vb_infoln("[%d] -> %d", it.pos, *((int*)ds_vect_iterator_get(&it)));

	return 0;
}

int test_vector() {
	ds_vect* v = create_ds_vect(int_cmp, sizeof(int));
	int rc = run_test_vector(v);
	delete_ds_vect(v);
	return rc;
}

#endif
