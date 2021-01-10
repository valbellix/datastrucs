/**
 * @file defs.h
 * @author Valerio Bellizia
 *
 * This file contains some common definitions shared by some of the data structures implemented in this library.
 */

#ifndef defs_h
#define defs_h

typedef enum ds_direction {
	FORWARD,
	BACKWARD
} ds_direction;

typedef int (*ds_cmp)(const void*, const void*);

// these macros are a shorthand to avoid heavy cast notation when reading stuff within collections

/**
 * This macro will extract a typed pointer from a (const) void*. The type should be specified in the way that follows:
 * ds_get_ptr(int, ptr);
 *
 * @param TYPE the type of the pointer to return.
 * @param PTR the pointer to convert.
 *
 * @return It returns the pointer casted to the given pointer type.
 */
#define ds_get_ptr(TYPE, PTR) ((TYPE*)PTR)

/**
 * This macro will extract the value from a (const) void*. The type should be specified in the way that follows_
 * ds_get_value(int, ptr);
 * 
 * @param TYPE the type of the pointer that we want to deference.
 * @param PTR the pointer to the element we want to extract.
 * 
 * @return It returns the value as deferenced pointer of the given type.
 */
#define ds_get_value(TYPE, PTR) (*(TYPE*)PTR)

#endif
