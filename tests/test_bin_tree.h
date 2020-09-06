/*
 * @file test_bin_tree.h
 * @author Valerio Bellizia
 *
 * This file contains binary tree specific tests.
 */

#ifndef test_bin_tree_h
#define test_bin_tree_h

#include "common_stuff.h"
#include "vb_test.h"

#include <stdio.h>
#include <stdlib.h>

#include <ds/bin_tree.h>

void print_bin_tree_node(ds_bin_tree_node* element) {
	vb_infoln("%d", *((int*)ds_bin_tree_node_get(element)));
}

int test_binary_tree() {
	ds_bin_tree* tree = create_ds_bin_tree(int_cmp, sizeof(int));
	ds_result res = GENERIC_ERROR;

	vb_infoln("test adding a root element on the binary tree");
	int one = 10;
	res = ds_bin_tree_insert(tree, &one);
	vb_check_equals_int("insert first element", res, SUCCESS);
	vb_check_equals_int("element should exist", ds_bin_tree_search(tree, &one), 1);
	vb_check_equals_int("size should be 1", ds_bin_tree_size(tree), 1);

	int zero = 0;
	res = ds_bin_tree_insert(tree, &zero);
	vb_check_equals_int("insert second element", res, SUCCESS);
	vb_check_equals_int("size should be 2", ds_bin_tree_size(tree), 2);

	int thirteen = 13;
	res = ds_bin_tree_insert(tree, &thirteen);
	vb_check_equals_int("insert third element", res, SUCCESS);
	vb_check_equals_int("size should be 3", ds_bin_tree_size(tree), 3);

	delete_ds_bin_tree(tree);
	return 0;
}

#endif
