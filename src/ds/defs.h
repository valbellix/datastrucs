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

#endif
