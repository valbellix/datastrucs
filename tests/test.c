#include <ds/vect.h>
#include <ds/list.h>
#include <ds/defs.h>

#include <stdio.h>
#include <stdlib.h>

int intCmp(const void* e1, const void* e2) {
	const int* i1 = (int*) e1;
	const int* i2 = (int*) e2;

	if (*i1 < *i2)
		return -1;
	else if (*i1 == *i2)
		return 0;
	else
		return 1;
}

void print_vect_element(const ds_vect_iterator* it) {
	printf("[%d] -> %d\n", it->pos, *((int*)ds_vect_iterator_get(it)));
}

void print_list_element(const ds_list_iterator* it) {
	printf("%d\n", *((int*)ds_list_iterator_get(it)));;
}

int test_vector() {
	ds_vect* v = create_ds_vect(intCmp, sizeof(int));

	printf("test adding elements\n");
	int one = 123;
	int two = 456;
	ds_vect_push_back(v, &one);
	ds_vect_push_back(v, &two);

	ds_vect_iterator it0 = ds_vect_at(v, 0);
	ds_vect_iterator it1 = ds_vect_at(v, 1);

	printf("one -> %d\n", *((int*)ds_vect_iterator_get(&it0)));
	printf("two -> %d\n", *((int*)ds_vect_iterator_get(&it1)));

	int three = 789;
	ds_vect_push_back(v, &three);
	ds_vect_iterator it2 = ds_vect_at(v, 2);

	printf("three -> %d\n", *((int*)ds_vect_iterator_get(&it2)));

	printf("test element existence\t");
	int doesNotExist = 1000;
	if (ds_vect_exists(v, &one))
		printf("exists!\n");
	if (!ds_vect_exists(v, &doesNotExist))
		printf("does not exist!\n");

	printf("test forward iteration\n");
	for (ds_vect_iterator it = ds_vect_first(v); ds_vect_iterator_is_valid(&it); ds_vect_iterator_next(&it))
		printf("[%d] -> %d\n", it.pos, *((int*)ds_vect_iterator_get(&it)));

	printf("test backward iteration\n");
	for (ds_vect_iterator it = ds_vect_last(v); ds_vect_iterator_is_valid(&it); ds_vect_iterator_prev(&it))
		printf("[%d] -> %d\n", it.pos, *((int*)ds_vect_iterator_get(&it)));

	printf("test insert at given position\n");
	int anotherValue = 555;
	ds_vect_set(v, &anotherValue, 2);
	it2 = ds_vect_at(v, 2);
	printf("[%d] -> %d\n", 2, *((int*)ds_vect_iterator_get(&it2)));

	printf("test do things forward\n");
	ds_vect_do(v, print_vect_element, ds_vect_first(v), ds_vect_length(v), FORWARD);

	printf("test do things backward\n");
	ds_vect_do(v, print_vect_element, ds_vect_last(v), ds_vect_length(v), BACKWARD);

	printf("test remove\n");
	ds_vect_remove(v, 1);
	ds_vect_remove(v, 1);
	for (ds_vect_iterator it = ds_vect_first(v); ds_vect_iterator_is_valid(&it); ds_vect_iterator_next(&it))
		printf("[%d] -> %d\n", it.pos, *((int*)ds_vect_iterator_get(&it)));

	delete_ds_vect(v);

	return 0;
}

int test_list() {
	ds_list* l = create_ds_list(intCmp, sizeof(int));
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

	delete_ds_list(l);

	return 0;
}

int main() {
	int res = 0;
	printf("Test Vector\n");
	printf("**************\n");
	res = test_vector();

	printf("Test List\n");
	printf("**************\n");
	res = test_list();

	printf("**************\n");
	if (res == 0)
		printf("Yay! all tests succeeded\n");
	else
		printf("No... something has gone wrong\n");

	return res;
}
