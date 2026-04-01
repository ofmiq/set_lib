#ifndef SET_LIB_H
#define SET_LIB_H

#include <stddef.h>

/**
 * @brief Structure of an integer set.
 * @note Elements are unique and sorted.
 */
typedef struct {
  int* data;
  size_t size;
} set_of_int_t;

/**
 * @brief Creates an empty set.
 * @param n Initial capacity or number of elements in the set.
 * @return Pointer to a newly allocated empty set.
 */
set_of_int_t* set_create(int n);

/**
 * @brief Creates a set from a C-array.
 * @param arr Pointer to the array.
 * @param n Number of elements in the array.
 * @return Pointer to a newly allocated set.
 */
set_of_int_t* set_create_from_array(const int* arr, int n);

/**
 * @brief Deletes and cleans up a set.
 * @param set Pointer to the set to be deleted.
 */
void set_destroy(set_of_int_t* set);

/**
 * @brief Adds an element to a set.
 */
void set_add(set_of_int_t* set, int elem);

/**
 * @brief Prints a set.
 */
void set_print(const set_of_int_t* set);

/**
 * @brief Computes the union of two sets.
 * @param a Pointer to the first set.
 * @param b Pointer to the second set.
 * @return Pointer to a new set representing the union.
 */
set_of_int_t* set_union(const set_of_int_t* a, const set_of_int_t* b);

/**
 * @brief Computes the intersection of two sets.
 * @param a Pointer to the first set.
 * @param b Pointer to the second set.
 * @return Pointer to a new set representing the intersection.
 */
set_of_int_t* set_intersection(const set_of_int_t* a, const set_of_int_t* b);

/**
 * @brief Computes the difference between two sets.
 * @param a Pointer to the first set.
 * @param b Pointer to the second set.
 * @return Pointer to a new set representing the difference.
 */
set_of_int_t* set_difference(const set_of_int_t* a, const set_of_int_t* b);

/**
 * @brief Computes the symmetric difference between two sets.
 * @param a Pointer to the first set.
 * @param b Pointer to the second set.
 * @return Pointer to a new set representing the symmetric difference.
 */
set_of_int_t* set_sym_difference(const set_of_int_t* a, const set_of_int_t* b);

#endif