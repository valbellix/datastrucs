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
	printf("%d\n", *((int*)ds_list_iterator_get(it)));;
}

int test_list() {
	ds_list* l = create_ds_list(int_cmp, sizeof(int));
	ds_result res = GENERIC_ERROR;

	printf("test adding elements at list front\n");
	int one = 123;
	int two = 456;
	int three = 789;

	res = ds_list_push_front(l, &one);
	if (res != SUCCESS) {
		printf("push front failed\n");
		return 1;
	}
	res = ds_list_push_front(l, &two);
	if (res != SUCCESS) {
		printf("push front failed\n");
		return 1;
	}
	res = ds_list_push_front(l, &three);
	if (res != SUCCESS) {
		printf("push front failed\n");
		return 1;
	}

	printf("test existence\n");
	int exists = ds_list_exists(l, &three);
	if (!exists) {
		printf("existence test failed\n");
		return 1;
	}
	int bla = 0;
	exists = ds_list_exists(l, &bla);
	if (exists) {
		printf("non-existence test failed\n");
		return 1;
	}

	printf("test forward iteration\n");
	int counter = 0;
	for (ds_list_iterator it = ds_list_first(l); ds_list_iterator_is_valid(&it); ds_list_iterator_next(&it))
		printf("[%d] -> %d\n", counter++, *((int*)ds_list_iterator_get(&it)));

	printf("test do things forward\n");
	ds_list_do(l, print_list_element, ds_list_first(l), ds_list_length(l), FORWARD);

	printf("test do things backward\n");
	ds_list_do(l, print_list_element, ds_list_last(l), ds_list_length(l), BACKWARD);

	printf("test positional access\n");
	ds_list_iterator positional =  ds_list_at(l, 2);
	if (!ds_list_iterator_is_valid(&positional)) {
		printf("The element should be valid\n");
		return 1;
	}
	printf("Element at position 2 is %d\n", *((int*)ds_list_iterator_get(&positional)));

	ds_list_iterator non_valid = ds_list_at(l, 3);
	if (ds_list_iterator_is_valid(&non_valid)) {
		printf("The element should not be valid\n");
		return 1;
	}

	int newElementInTheMiddle = 555;
	res = ds_list_set(l, &newElementInTheMiddle, 1);
	if (res != SUCCESS) {
		printf("set failed\n");
		return 1;
	}
	positional = ds_list_at(l, 1);
	if (!ds_list_iterator_is_valid(&positional)) {
		printf("The element should be valid\n");
		return 1;
	}
	int el = *((int*)ds_list_iterator_get(&positional));
	printf("Element at position 1 is %d\n", el);
	if (el != newElementInTheMiddle) {
		printf("The element set at position 1 is different than expected\n");
		return 1;
	}

	printf("test remove\n");
	res = ds_list_remove(l, 1);
	printf("print after element removal at pos 1\n");
	ds_list_do(l, print_list_element, ds_list_first(l), ds_list_length(l), FORWARD);

	delete_ds_list(l);

	return 0;
}

#endif
