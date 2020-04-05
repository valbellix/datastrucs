#ifndef defs_h
#define defs_h

typedef enum ds_direction {
	FORWARD,
	BACKWARD
} ds_direction;

typedef int (*ds_cmp)(const void*, const void*);

#endif