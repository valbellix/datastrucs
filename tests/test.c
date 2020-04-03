#include <stdio.h>
#include <stdlib.h>
#include <ds/vect.h>

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

int main(int argc, char* argv[]) {
	ds_vect* v = create_ds_vect(intCmp, sizeof(int));

	int one = 123;
	int two = 456;
	ds_vect_add(v, &one);
	ds_vect_add(v, &two);

	int out = 0;
	int out2 = 0;
	ds_vect_at(v, 0, &out);
	ds_vect_at(v, 1, &out2);

	printf("one -> %d\n", out);
	printf("two -> %d\n", out2);

	int three = 789;
	ds_vect_add(v, &three);

	int out3 = 0;
	ds_vect_at(v, 2, &out3);
	printf("three -> %d\n", out3);

	int doesNotExist = 1000;
	if (ds_vect_exists(v, &one))
		printf("exists!\n");
	if (!ds_vect_exists(v, &doesNotExist))
		printf("does not exist!\n");

	for (size_t i = 0; i < ds_vect_length(v); i++) {
		int val;
		ds_vect_at(v, i, &val);
		printf("[%d] -> %d\n", i, val);
	}

	int anotherValue = 555;
	ds_vect_set(v, &anotherValue, 2);

	int val;
	ds_vect_at(v, 2, &val);
	printf("%d\n", val);

	for (size_t i = 0; i < ds_vect_length(v); i++) {
		int val;
		ds_vect_at(v, i, &val);
		printf("[%d] -> %d\n", i, val);
	}

	ds_vect_remove(v, 1);
	for (size_t i = 0; i < ds_vect_length(v); i++) {
		int val;
		ds_vect_at(v, i, &val);
		printf("[%d] -> %d\n", i, val);
	}

	delete_ds_vect(v);

	return 0;
}