/**
 * @file list.h
 * @author Valerio Bellizia
 *
 * This file contains the interface to be used with ds_list. It implements 
 * a double linked list.
 */

#ifndef list_h
#define list_h

#include "result.h"
#include "defs.h"

#include <stddef.h>

/**
 * This is an opaque structure that represents a double linked list
 */
typedef struct ds_list ds_list;

/**
 * This is an opaque structure that represents a node of a double linked list
 */
typedef struct ds_list_node ds_list_node;

/**
 * This structure is an iterator
 */
typedef struct ds_list_iterator {
	const ds_list* list;
	ds_list_node* curr;
} ds_list_iterator;

// Iterator functions

/**
 * This function will move the iterator forward.
 * 
 * @param it The iterator.
 */
void ds_list_iterator_next(ds_list_iterator* it);

/**
 * This function will move the iterator backward.
 *
 * @param it The iterator.
 */
void ds_list_iterator_prev(ds_list_iterator* it);

/**
 * This function can be used to check if the iterator is valid.
 *
 * @param it The iterator.
 * 
 * @return it returns 1 if the iterator is valid, 0 otherwise.
 */
int ds_list_iterator_is_valid(ds_list_iterator* it);

/**
 * This function will get the element pointed by the iterator as const void*.
 *
 * @param it The iterator.
 * 
 * @return The pointer to the element stored into the list.
 */
const void* ds_list_iterator_get(ds_list_iterator* it);

/**
 * This function will get the typed pointer to the element pointed by the iterator.
 *
 * @param TYPE The type we want as output.
 * @param IT The iterator.
 *
 * @return The pointer to the element stored into the list casted to the given type.
 */
#define ds_list_iterator_get_ptr(TYPE, IT) ((TYPE*)ds_list_iterator_get(IT))

/**
 * This function will get the value of the element pointed by the iterator.
 *
 * @param TYPE The type we want as output.
 * @param IT The iterator.
 *
 * @return The value to the element stored into the list casted to the given type.
 */
#define ds_list_iterator_get_value(TYPE, IT) (*(TYPE*)ds_list_iterator_get(IT))

// List interface

/**
 * This function will create an instance of ds_list
 *
 * @param cmp_func This is the pointer to a function that will be used to compare two elements
 * @param size It is the size of the element that a list node is supposed to store
 * 
 * @return It returns the pointer to a new instance of ds_list.
 */
ds_list* create_ds_list(ds_cmp cmp_func, const size_t size);

/**
 * This function will release the memory allocated to the list.
 * Elements stored in the list will be freed using 'free'.
 *
 * @param l The list.
 */
void delete_ds_list(ds_list* l);

/**
 * This function will return the length of the list, in other words, the number of elements.
 *
 * @param l The list.
 * 
 * @return the number of elements stored in the list.
 */
size_t ds_list_length(const ds_list* l);

/**
 * This function returns an iterator to the element in the given position.
 *
 * @param l The list.
 * @param pos The position of the element to get. If the position is not valid, the iterator is not valid.
 * 
 * @return An iterator to the element at the given position if valid. Otherwise it will return a non-valid iterator.
 */
ds_list_iterator ds_list_at(const ds_list* l, const size_t pos);

/**
 * This function returns an iterator to the first element.
 *
 * @param l The list.
 * 
 * @return An iterator to the first element of the list.
 */
ds_list_iterator ds_list_first(const ds_list* l);

/**
 * This function returns an iterator to the last element.
 *
 * @param l The list.
 * 
 * @return An iterator to the last element of the list.
 */
ds_list_iterator ds_list_last(const ds_list* l);

/**
 * This function returns a 'true' value if the element exists. It uses the function passed in the ds_list creation function
 * to compare two elements of the same type.
 *
 * @param l The list.
 * @param element The element we are going to look for in the list. The element should have be of the same type as the others.
 * 
 * @return It returns 1 if such element exists, 0 otherwise.
 */
int ds_list_exists(const ds_list* l, const void* element);

/**
 * This function will add an element to the front.
 *
 * @param l The list.
 * @param element Is the element to add.
 * 
 * @return It returns SUCCESS if the element is succesfully added.
 */
ds_result ds_list_push_front(ds_list* l, void* element);

/**
 * This function will add an element to the bottom.
 *
 * @param l The list.
 * @param element Is the element to add.
 * 
 * @return It returns SUCCESS if the element is succesfully added.
 */
ds_result ds_list_push_back(ds_list* l, void* element);

/**
 * This function will remove the element from a given position (if the position is valid).
 * All the elements that follow, will be shifted by one position if the position is valid.
 *
 * @param l The list. 
 * @param pos The position of the element we want to remove.
 * @return SUCCESS if it succeeds, it may return OUT_OF_BOUND if position is not valid.
 */
ds_result ds_list_remove(ds_list* l, const size_t pos);

/**
 * This function will set the element to a given position. The position should be valid.
 *
 * @param l The list.
 * @param element The element to set.
 * @param pos The position to fill with the content of the given element.
 * @return SUCCESS if it succeeds, it may return OUT_OF_BOUND if position is not valid.
 */
ds_result ds_list_set(ds_list* v, const void* element, const size_t pos);

/**
 * This function will call 'do_something' to all elements of the list starting from the
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
void ds_list_do(ds_list* l,
                void (*do_something)(const ds_list_iterator*),
                ds_list_iterator begin,
                const size_t number_of_elements,
                ds_direction direction);

#endif
