/*
 * @file test_heap.h
 * @author Valerio Bellizia
 *
 * This file contains heap specific tests.
 */

#ifndef test_heap_h
#define test_heap_h

#include "common_stuff.h"
#include "vb_test.h"

#include <ds/heap.h>

int run_test_heap(ds_heap* heap) {
	int fifty = 50;
	int thousand = 1000;
	int hundred = 100;
	int five_hundred = 500;
	int seven_hundred = 700;

	int expected[] = {50, 100, 500, 700, 1000};

	ds_result res;

	res = ds_heap_push(heap, &fifty, 50);
	vb_check_equals_int("check if push succeeds", res, SUCCESS);
	ds_heap_push(heap, &thousand, 1000);
	vb_check_equals_int("check if push succeeds", res, SUCCESS);
	ds_heap_push(heap, &hundred, 100);
	vb_check_equals_int("check if push succeeds", res, SUCCESS);
	ds_heap_push(heap, &five_hundred, 500);
	vb_check_equals_int("check if push succeeds", res, SUCCESS);
	ds_heap_push(heap, &seven_hundred, 700);
	vb_check_equals_int("check if push succeeds", res, SUCCESS);

	vb_check_equals_int("check if the number of elements is expected", ds_heap_size(heap), 5);

	int i = 0;
	do {
		ds_heap_entry entry = ds_heap_pop(heap);
		vb_check_equals_int("check position", *(int*)entry.info, expected[i]);
		delete_ds_heap_entry(&entry);
		i++;
	} while (ds_heap_size(heap) != 0);

	return 0;
}

int test_heap() {
	ds_heap* heap = create_ds_heap(sizeof(int));
	int rc = run_test_heap(heap);
	delete_ds_heap(heap);
	return rc;
}

#endif