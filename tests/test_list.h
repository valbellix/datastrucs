/*
 * @file test_list.h
 * @author Valerio Bellizia
 *
 * This file contains list specific tests.
 */

#ifndef test_list_h
#define test_list_h

#include "common_stuff.h"
#include "vb_test.h"

#include <stdio.h>
#include <stdlib.h>

#include <ds/list.h>

void print_list_element(const ds_list_iterator* it) {
	vb_infoln("%d", ds_list_iterator_get_value(int, it));
}

int run_test_list(ds_list* l) {
	ds_result res = GENERIC_ERROR;

	vb_infoln("test adding elements at list front");
	int one = 123;
	int two = 456;
	int three = 789;

	res = ds_list_push_front(l, &one);
	vb_check_equals_int("test push front one", res, SUCCESS);

	res = ds_list_push_front(l, &two);
	vb_check_equals_int("test push front two", res, SUCCESS);

	res = ds_list_push_front(l, &three);
	vb_check_equals_int("test push front three", res, SUCCESS);

	vb_check_equals_int("tests existence", ds_list_exists(l, &three), 1);

	int bla = 0;
	vb_check_equals_int("non-existence test", ds_list_exists(l, &bla), 0);

	vb_infoln("test forward iteration");
	int counter = 0;
	for (ds_list_iterator it = ds_list_first(l); ds_list_iterator_is_valid(&it); ds_list_iterator_next(&it))
		vb_infoln("[%d] -> %d", counter++, ds_list_iterator_get_value(int, &it));

	vb_infoln("test do things forward");
	ds_list_do(l, print_list_element, ds_list_first(l), ds_list_length(l), FORWARD);

	vb_infoln("test do things backward");
	ds_list_do(l, print_list_element, ds_list_last(l), ds_list_length(l), BACKWARD);

	vb_infoln("test positional access");
	ds_list_iterator positional =  ds_list_at(l, 2);
	vb_check_equals_int("the element should be valid", ds_list_iterator_is_valid(&positional), 1);

	vb_infoln("Element at position 2 is %d", ds_list_iterator_get_value(int, &positional));

	ds_list_iterator non_valid = ds_list_at(l, 3);
	vb_check_equals_int("the element should not be valid", ds_list_iterator_is_valid(&non_valid), 0);

	int newElementInTheMiddle = 555;
	res = ds_list_set(l, &newElementInTheMiddle, 1);
	vb_check_equals_int("test set element in the middle", res, SUCCESS);

	positional = ds_list_at(l, 1);
	vb_check_equals_int("the element at position 1 should be valid", ds_list_iterator_is_valid(&positional), 1);

	int el = *((int*)ds_list_iterator_get(&positional));
	vb_infoln("Element at position 1 is %d", el);
	vb_check_equals_int("test if the element at position 1 is expected", el, newElementInTheMiddle);

	vb_infoln("test remove");
	res = ds_list_remove(l, 1);
	vb_infoln("print after element removal at pos 1");
	ds_list_do(l, print_list_element, ds_list_first(l), ds_list_length(l), FORWARD);

	return 0;
}

int test_list() {
	ds_list* l = create_ds_list(int_cmp, sizeof(int));
	int rc = run_test_list(l);
	delete_ds_list(l);
	return rc;
}

#endif
