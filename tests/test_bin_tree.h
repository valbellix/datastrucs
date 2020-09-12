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

void print_int(const void* element) {
	vb_infoln("%d", *((int*)element));
}

int test_binary_tree() {
	ds_bin_tree* tree = create_ds_bin_tree(int_cmp, sizeof(int));
	ds_result res = GENERIC_ERROR;

	vb_infoln("test adding a root element on the binary tree");
	int ten = 10;
	int zero = 0;
	int five = 5;
	int twelve = 12;
	int thirteen = 13;
	int fifteen = 15;

	res = ds_bin_tree_insert(tree, &ten);
	vb_check_equals_int("insert first element", res, SUCCESS);
	vb_check_equals_int("element should exist", ds_bin_tree_search(tree, &ten), 1);
	vb_check_equals_int("size should be 1", ds_bin_tree_size(tree), 1);

	res = ds_bin_tree_insert(tree, &zero);
	vb_check_equals_int("insert second element", res, SUCCESS);
	vb_check_equals_int("size should be 2", ds_bin_tree_size(tree), 2);

	res = ds_bin_tree_insert(tree, &five);
	vb_check_equals_int("insert third element", res, SUCCESS);
	vb_check_equals_int("size should be 3", ds_bin_tree_size(tree), 3);

	res = ds_bin_tree_insert(tree, &thirteen);
	vb_check_equals_int("insert fourth element", res, SUCCESS);
	vb_check_equals_int("size should be 4", ds_bin_tree_size(tree), 4);

	res = ds_bin_tree_insert(tree, &twelve);
	vb_check_equals_int("insert fifth element", res, SUCCESS);
	vb_check_equals_int("size should be 5", ds_bin_tree_size(tree), 5);

	res = ds_bin_tree_insert(tree, &fifteen);
	vb_check_equals_int("insert sixth element", res, SUCCESS);
	vb_check_equals_int("size should be 6", ds_bin_tree_size(tree), 6);

	vb_infoln("PRE-ORDER");
	ds_bin_tree_visit(tree, print_int, DFS_PRE_ORDER);
	vb_infoln("IN-ORDER");
	ds_bin_tree_visit(tree, print_int, DFS_IN_ORDER);
	vb_infoln("POST-ORDER");
	ds_bin_tree_visit(tree, print_int, DFS_POST_ORDER);

	res = ds_bin_tree_remove(tree, &thirteen);
	vb_check_equals_int("remove should complete with success", res, SUCCESS);
	vb_check_equals_int("element should not exist anymore", ds_bin_tree_search(tree, &thirteen), 0);
	vb_check_equals_int("size should be 5", ds_bin_tree_size(tree), 5);

	delete_ds_bin_tree(tree);
	return 0;
}

#endif
