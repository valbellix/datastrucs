/*
 * @file test_list.h
 * @author Valerio Bellizia
 *
 * This file contains list specific tests.
 */

#ifndef test_list_h
#define test_list_h

#include "common_stuff.h"

#include <stdio.h>
#include <stdlib.h>

#include <ds/list.h>

void print_list_element(const ds_list_iterator* it) {
	printf("%d\n", *((int*)ds_list_iterator_get(it)));
}

int run_test_list(ds_list* l) {
	ds_result res = GENERIC_ERROR;

	INFOLN("test adding elements at list front");
	int one = 123;
	int two = 456;
	int three = 789;

	res = ds_list_push_front(l, &one);
	CHECK_IF("test push front one", res == SUCCESS)

	res = ds_list_push_front(l, &two);
	CHECK_IF("test push front two", res == SUCCESS)

	res = ds_list_push_front(l, &three);
	CHECK_IF("test push front three", res == SUCCESS)

	CHECK_IF("tests existence", ds_list_exists(l, &three))

	int bla = 0;
	CHECK_IF_NOT("non-existence test", ds_list_exists(l, &bla));

	INFOLN("test forward iteration")
	int counter = 0;
	for (ds_list_iterator it = ds_list_first(l); ds_list_iterator_is_valid(&it); ds_list_iterator_next(&it))
		printf("[%d] -> %d\n", counter++, *((int*)ds_list_iterator_get(&it)));

	INFOLN("test do things forward")
	ds_list_do(l, print_list_element, ds_list_first(l), ds_list_length(l), FORWARD);

	INFOLN("test do things backward")
	ds_list_do(l, print_list_element, ds_list_last(l), ds_list_length(l), BACKWARD);

	INFOLN("test positional access")
	ds_list_iterator positional =  ds_list_at(l, 2);
	CHECK_IF("the element should be valid", ds_list_iterator_is_valid(&positional))

	printf("Element at position 2 is %d\n", *((int*)ds_list_iterator_get(&positional)));

	ds_list_iterator non_valid = ds_list_at(l, 3);
	CHECK_IF_NOT("the element should not be valid", ds_list_iterator_is_valid(&non_valid))

	int newElementInTheMiddle = 555;
	res = ds_list_set(l, &newElementInTheMiddle, 1);
	CHECK_IF("test set element in the middle", res == SUCCESS)

	positional = ds_list_at(l, 1);
	CHECK_IF("the element at position 1 should be valid", ds_list_iterator_is_valid(&positional))

	int el = *((int*)ds_list_iterator_get(&positional));
	printf("Element at position 1 is %d\n", el);
	CHECK_IF("test if the element at position 1 is expected", el == newElementInTheMiddle)

	INFOLN("test remove")
	res = ds_list_remove(l, 1);
	INFOLN("print after element removal at pos 1")
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
