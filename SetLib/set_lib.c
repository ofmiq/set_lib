#include "set_lib.h"

#include <stdio.h>
#include <stdlib.h>

static int comparator(const void* a, const void* b) {
  int arg1 = *(const int*)a;
  int arg2 = *(const int*)b;
  return (arg1 > arg2) - (arg1 < arg2);
}

set_of_int_t* set_create(int n) {
  set_of_int_t* set = (set_of_int_t*)malloc(sizeof(set_of_int_t));
  if (!set) {
    return NULL;
  }

  set->data = (int*)malloc(sizeof(int) * n);
  if (!set->data) {
    free(set);
    return NULL;
  }

  set->size = n;
  return set;
}

// TODO: refactor, must work with any array (delete duplicates, sort)
set_of_int_t* set_create_from_array(const int* arr, int n) {
  if (!arr || n <= 0) {
    return NULL;
  }

  for (int i = 1; i < n; ++i) {
    if (arr[i] < arr[i - 1]) {
      return NULL;
    }
  }

  set_of_int_t* set = set_create(n);
  if (!set) {
    return NULL;
  }

  for (int i = 0; i < n; ++i) {
    set->data[i] = arr[i];
  }

  return set;
}

void set_destroy(set_of_int_t* set) {
  if (!set) {
    return;
  }
  free(set->data);
  free(set);
}

void set_print(const set_of_int_t* set) {
  if (!set || !set->data) {
    return;
  }

  for (size_t i = 0; i < set->size; ++i) {
    printf("%d ", set->data[i]);
  }
  printf("\n");
}

void set_add(set_of_int_t* set, int elem) {
  if (!set) {
    return;
  }

  for (size_t i = 0; i < set->size; i++) {
    if (set->data[i] == elem) {
      return;
    }
  }

  int new_size = set->size + 1;

  int* new_data = (int*)realloc(set->data, sizeof(int) * new_size);
  if (!new_data) {
    return;
  }

  set->data = new_data;
  set->data[set->size] = elem;
  set->size = new_size;

  qsort(set->data, set->size, sizeof(int), comparator);
}