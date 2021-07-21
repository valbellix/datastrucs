/**
 * @file vect.h
 * @author Valerio Bellizia
 *
 * This file contains the interface to be used with ds_vect. It implements 
 * a vector using an underlying array that will be resized at needs.
 */

#ifndef vect_h
#define vect_h

#include "result.h"
#include "defs.h"

#include <stddef.h>

/**
 * This is an opaque structure that represents a vector
 */
typedef struct ds_vect ds_vect;

/**
 * This structure is an iterator
 */
typedef struct ds_vect_iterator {
	int pos;

	const ds_vect* v;
} ds_vect_iterator;

// Iterator functions

/**
 * This function will move the iterator forward.
 *
 * @param it The iterator.
 */
void ds_vect_iterator_next(ds_vect_iterator* it);

/**
 * This function will move the iterator backward.
 * 
 * @param it The iterator.
 */
void ds_vect_iterator_prev(ds_vect_iterator* it);

/**
 * This function can be used to check if the iterator is valid.
 *
 * @param it The iterator.
 * 
 * @return It returns 1 if the iterator is valid, 0 otherwise.
 */
int ds_vect_iterator_is_valid(ds_vect_iterator* it);

/**
 * This function will get the element pointed by the iterator as const void*.
 *
 * @param it The iterator.
 * 
 * @return The pointer to the element stored into the vector.
 */
const void* ds_vect_iterator_get(ds_vect_iterator* it);

/**
 * This function will get the typed pointer to the element pointed by the iterator.
 * 
 * @param TYPE The type we want as output.
 * @param IT The iterator.
 * 
 * @return The pointer to the element stored into the vector casted to the given type.
 */
#define ds_vect_iterator_get_ptr(TYPE, IT) ((TYPE*)ds_vect_iterator_get(IT))

/**
 * This function will get the value of the element pointed by the iterator.
 *
 * @param TYPE The type we want as output.
 * @param IT The iterator.
 *
 * @return The value to the element stored into the vector casted to the given type.
 */
#define ds_vect_iterator_get_value(TYPE, IT) (*(TYPE*)ds_vect_iterator_get(IT))

// Vector interface

/**
 * This function will create an instance of ds_vect
 *
 * @param cmp_func This is the pointer to a function that will be used to compare two elements.
 * @param el_size It is the size of the element that the vector is supposed to store.
 * 
 * @return It returns the pointer to a new instance of ds_vect.
 */
ds_vect* create_ds_vect(ds_cmp cmp_func, const size_t el_size);

/**
 * This function will release the memory allocated to the vector.
 * Elements stored in the vector will be freed using 'free'.
 *
 * @param v The vector.
 */
void delete_ds_vect(ds_vect* v);

/**
 * This function will return the length of the vector, in other words, the number of elements.
 *
 * @param v The vector.
 * 
 * @return the number of elements stored in the vector.
 */
size_t ds_vect_length(const ds_vect* v);

/**
 * This function returns an iterator to the element in the given position.
 *
 * @param v The vector.
 * @param pos The position of the element to get. If the position is not valid, the iterator is not valid.
 * 
 * @return An iterator to the element at the given position if valid. Otherwise it will return a non-valid iterator.
 */
ds_vect_iterator ds_vect_at(const ds_vect* v, const size_t pos);

/**
 * This function returns an iterator to the first element.
 *
 * @param v The vector.
 * 
 * @return An iterator to the first element of the vector.
 */
ds_vect_iterator ds_vect_first(const ds_vect* v);

/**
 * This function returns an iterator to the last element.
 *
 * @param v The vector.
 * 
 * @return An iterator to the last element of the vector.
 */
ds_vect_iterator ds_vect_last(const ds_vect* v);

/**
 * This function returns a 'true' value if the element exists. It uses the function passed in the ds_vect creation function
 * to compare two elements of the same type.
 *
 * @param v The vector.
 * @param element The element we are going to look for in the vector. The element should have be of the same type as the others.
 * 
 * @return It returns 1 if such element exists, 0 otherwise.
 */
int ds_vect_exists(const ds_vect* v, const void* element);

/**
 * This function will add an element to the bottom.
 *
 * @param v The vector.
 * @param element Is the element to add.
 * 
 * @return It returns SUCCESS if the element is succesfully added.
 */
ds_result ds_vect_push_back(ds_vect* v, const void* element);

/**
 * This function will remove the element from a given position (if the position is valid).
 * All the elements that follow, will be shifted by one position if the position is valid.
 *
 * @param v The vector.
 * @param The position of the element we want to remove.
 * 
 * @return SUCCESS if it succeeds, it may return OUT_OF_BOUND if position is not valid.
 */
ds_result ds_vect_remove(ds_vect* v, const size_t pos);

/**
 * This function will set the element to a given position. The position should be valid.
 *
 * @param v The vector.
 * @param element The element to set.
 * @param pos The position to fill with the content of the given element.
 * 
 * @return SUCCESS if it succeeds, it may return OUT_OF_BOUND if position is not valid.
 */
ds_result ds_vect_set(ds_vect* v, const void* element, const size_t pos);

/**
* This function will swap the elements checking if positions are valid.
* 
* @param v The vector.
* @param pos_one The position of the first element to swap.
* @param pos_two The position of the second element to swap.
* 
* @return SUCCESS if it succeeds, it may return OUT_OF_BOUND if at least one of the index is not valid.
*/
ds_result ds_vect_swap(ds_vect* v, const size_t pos_one, const size_t pos_two);

/**
 * This function will call 'do_something' to all elements of the vector starting from the
 * element pointed by the 'begin' vector. It will be executed on all elements between the begin
 * to begin + number_of_elements. The iterator could be incremented or decremented according to the
 * given 'direction'.
 *
 * @param v The vector.
 * @param do_something The function to apply to the desired elements.
 * @param begin The iterator to the first element we wan to apply the function.
 * @param number_of_elements The number of times that the iterator will be moved forward/backward.
 * @param direction Indicates if the vector will be walked forward or backward.
 */
void ds_vect_do(ds_vect* v, 
                void (*do_something)(const ds_vect_iterator*),
                ds_vect_iterator begin,
                const size_t number_of_elements,
                ds_direction direction);

#endif
