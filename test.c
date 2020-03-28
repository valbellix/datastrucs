#include <stdio.h>
#include <ds/vect.h>

int equalsInt(const void* e1, const void* e2) {
	const int* i1 = (int*) e1;
	const int* i2 = (int*) e2;

	return *i1 == *i2;
}

void freeInt(void* e) {
	if (e != NULL) {
		free(e);
	}
}

int main(int argc, char* argv[]) {
	ds_vect* v = create_ds_vect(equalsInt, freeInt, sizeof(int));

	int i = 123;
	ds_vect_add(v, &i);

	delete_ds_vect(v);

	return 0;
}