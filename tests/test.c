/*
 * @file test.c
 * @author Valerio Bellizia
 *
 * This file is the entry point of a program that tests the library.
 */

#include "test_list.h"
#include "test_vector.h"
#include "test_bin_tree.h"
#include "test_heap.h"

#include <stdio.h>

int main() {
	int res = 0;
	printf("Test Vector\n");
	printf("**************\n");
	res = test_vector();

	printf("Test List\n");
	printf("**************\n");
	res = test_list();

	printf("Test Binary Search Tree\n");
	printf("**************\n");
	res = test_binary_tree();

	printf("Test Heap\n");
	printf("**************\n");
	res = test_heap();

	printf("**************\n");
	if (res == 0)
		printf("Yay! all tests succeeded\n");
	else
		printf("No... something has gone wrong\n");

	return res;
}
