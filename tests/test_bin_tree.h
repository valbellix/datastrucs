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
#include <math.h>

#include <ds/bst.h>

void print_bin_tree_node(ds_bst_node* element) {
	vb_infoln("%d", *((int*)ds_bst_node_get(element)));
}

void print_int(const void* element) {
	vb_infoln("%d", *((int*)element));
}

struct visit_test {
	int accumulator;
	int number;
};

static void reset_test(struct visit_test* test) {
	test->accumulator = 0;
	test->number = 0;
}

void visit_test(const void* element, void* func_aux) {
	int n = *((int*)element);
	struct visit_test* test = (struct visit_test*) func_aux;
	test->accumulator += pow(31, test->number) * n;
	test->number++;
}

int test_binary_tree() {
	ds_bst* tree = create_ds_bst(int_cmp, sizeof(int));
	ds_result res = GENERIC_ERROR;

	struct visit_test test = {0, 0};

	vb_infoln("test adding a root element on the binary tree");
	int ten = 10;
	int zero = 0;
	int five = 5;
	int twelve = 12;
	int thirteen = 13;
	int fifteen = 15;

	res = ds_bst_insert(tree, &ten);
	vb_check_equals_int("insert first element", res, SUCCESS);
	vb_check_equals_int("element should exist", ds_bst_search(tree, &ten), 1);
	vb_check_equals_int("size should be 1", ds_bst_size(tree), 1);

	res = ds_bst_insert(tree, &zero);
	vb_check_equals_int("insert second element", res, SUCCESS);
	vb_check_equals_int("size should be 2", ds_bst_size(tree), 2);

	res = ds_bst_insert(tree, &five);
	vb_check_equals_int("insert third element", res, SUCCESS);
	vb_check_equals_int("size should be 3", ds_bst_size(tree), 3);

	res = ds_bst_insert(tree, &thirteen);
	vb_check_equals_int("insert fourth element", res, SUCCESS);
	vb_check_equals_int("size should be 4", ds_bst_size(tree), 4);

	res = ds_bst_insert(tree, &twelve);
	vb_check_equals_int("insert fifth element", res, SUCCESS);
	vb_check_equals_int("size should be 5", ds_bst_size(tree), 5);

	res = ds_bst_insert(tree, &fifteen);
	vb_check_equals_int("insert sixth element", res, SUCCESS);
	vb_check_equals_int("size should be 6", ds_bst_size(tree), 6);

	int pre_order_expected = 10 + (pow(31, 1) * 0) + (pow(31, 2) * 5) + (pow(31, 3) * 13) + (pow(31, 4) * 12) + (pow(31, 5) * 15);
	int in_order_expected = 0 + (pow(31, 1) * 5) + (pow(31, 2) * 10) + (pow(31, 3) * 12) + (pow(31, 4) * 13) + (pow(31, 5) * 15);
	int post_order_expected = 5 + (pow(31, 1) * 0) + (pow(31, 2) * 12) + (pow(31, 3) * 15) + (pow(31, 4) * 13) + (pow(31, 5) * 10);

	vb_infoln("PRE-ORDER");
	ds_bst_visit(tree, visit_test, &test, DFS_PRE_ORDER);
	vb_check_equals_int("check the preorder visit", test.accumulator, pre_order_expected);

	vb_infoln("IN-ORDER");
	reset_test(&test);
	ds_bst_visit(tree, visit_test, &test, DFS_IN_ORDER);
	vb_check_equals_int("check the inorder visit", test.accumulator, in_order_expected);

	vb_infoln("POST-ORDER");
	reset_test(&test);
	ds_bst_visit(tree, visit_test, &test, DFS_POST_ORDER);
	vb_check_equals_int("check the post order visit", test.accumulator, post_order_expected);

	res = ds_bst_remove(tree, &thirteen);
	vb_check_equals_int("remove should complete with success", res, SUCCESS);
	vb_check_equals_int("element should not exist anymore", ds_bst_search(tree, &thirteen), 0);
	vb_check_equals_int("size should be 5", ds_bst_size(tree), 5);

	vb_check_equals_int("check if element is extracted properly", *((int*)ds_bst_get(tree, &fifteen)), fifteen);
	vb_check_equals_int("check what happens if I try to add a duplicate element", ds_bst_insert(tree, &fifteen), ELEMENT_ALREADY_EXISTS);

	delete_ds_bst(tree);
	return 0;
}

#endif
