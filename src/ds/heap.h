/**
 * @file heap.h
 * @author Valerio Bellizia
 *
 * This file contains the interface to be used with ds_heap.
 */

#ifndef heap_h
#define heap_h

#include "result.h"
#include "defs.h"

#include <stddef.h>

/**
 * This is an opaque struct that represents a heap
 */
typedef struct ds_heap ds_heap;

/**
 * This is an opaque struct that represents an element of an heap
 */
typedef struct ds_heap_entry {
	void* info;
	int priority;
} ds_heap_entry;

/**
 * This function will release the memory allocated to the entry
 * 
 * @param entry The entry.
 */
void delete_ds_heap_entry(ds_heap_entry* entry);

/**
 * This function will create an instance of ds_heap.
 * 
 * @param element_size It is the size of the element to held within the heap.
 * 
 * @return It returns an instance of the heap.
 */
ds_heap* create_ds_heap(const size_t element_size);

/**
 * This function will release the memory allocated to the heap.
 * Elements stored in the heap will be 'freed'
 * 
 * @param h The heap.
 */
void delete_ds_heap(ds_heap* h);

/**
 * This function will return the size of the heap.
 * 
 * @param h The heap.
 * 
 * @return It returns the number of elements in the heap.
 */
size_t ds_heap_size(ds_heap* h);

/**
 * This function will pop the first element of the heap. It returns and removes it.
 * 
 * @param h The heap.
 * 
 * @return It returns the first element of the heap after it has been removed.
 */
ds_heap_entry ds_heap_pop(ds_heap* h);

/**
 * This function will insert an element in the heap.
 * 
 * @param h The heap.
 * @param element The element to push into the heap.
 * @param priority The priority.
 * 
 * @return it returns SUCCESS if the element is succesfully inserted.
 */
ds_result ds_heap_push(ds_heap* h, const void* element, const int priority);

#endif
