/*
 * @file test_bin_tree.h
 * @author Valerio Bellizia
 *
 * This file contains binary tree specific tests.
 */

#ifndef test_bin_tree_h
#define test_bin_tree_h

#include "common_stuff.h"

#include <stdio.h>
#include <stdlib.h>

#include <ds/bin_tree.h>

void print_bin_tree_node(ds_bin_tree_node* element) {
	printf("%d\n", *((int*)ds_bin_tree_node_get(element)));
}

int test_binary_tree() {
	ds_bin_tree* tree = create_ds_bin_tree(int_cmp, sizeof(int));
	ds_result res = GENERIC_ERROR;

	INFOLN("test adding a root element on the binary tree")
	int rootElement = 10;
	res = ds_bin_tree_insert(tree, &rootElement);
	int exists = ds_bin_tree_search(tree, &rootElement);
	CHECK_IF("existance test", ds_bin_tree_search(tree, &rootElement))

	delete_ds_bin_tree(tree);
	return 0;
}

#endif
