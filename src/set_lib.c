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

set_of_int_t* set_union(const set_of_int_t* a, const set_of_int_t* b) {
  if (!a || !b) {
    return NULL;
  }

  if (a->size == 0) {
    return set_create_from_array(b->data, b->size);
  }
  if (b->size == 0) {
    return set_create_from_array(a->data, a->size);
  }

  size_t a_size = a->size;
  size_t b_size = b->size;

  set_of_int_t* union_set = set_create(a_size + b_size);
  if (!union_set) {
    return NULL;
  }

  size_t l = 0;
  size_t r = 0;
  size_t k = 0;

  while (l < a_size && r < b_size) {
    if (a->data[l] < b->data[r]) {
      union_set->data[k] = a->data[l];
      ++l;
    } else if (a->data[l] > b->data[r]) {
      union_set->data[k] = b->data[r];
      ++r;
    } else {
      union_set->data[k] = a->data[l];
      ++l;
      ++r;
    }
    ++k;
  }

  while (l < a_size) {
    union_set->data[k] = a->data[l];
    ++k;
    ++l;
  }

  while (r < b_size) {
    union_set->data[k] = b->data[r];
    ++k;
    ++r;
  }

  union_set->size = k;

  return union_set;
}

set_of_int_t* set_intersection(const set_of_int_t* a, const set_of_int_t* b) {
  if (!a || !b) {
    return NULL;
  }

  size_t a_size = a->size;
  size_t b_size = b->size;

  if (a->size == 0 || b->size == 0) {
    return NULL;
  }

  set_of_int_t* intersection_set = set_create(a_size + b_size);
  if (!intersection_set) {
    return NULL;
  }

  size_t l = 0;
  size_t r = 0;
  size_t k = 0;

  while (l < a_size && r < b_size) {
    if (a->data[l] < b->data[r]) {
      ++l;
    } else if (a->data[l] > b->data[r]) {
      ++r;
    } else {
      intersection_set->data[k] = a->data[l];
      ++l;
      ++r;
      ++k;
    }
  }

  intersection_set->size = k;

  return intersection_set;
}

set_of_int_t* set_difference(const set_of_int_t* a, const set_of_int_t* b) {
  if (!a || !b) {
    return NULL;
  }

  size_t a_size = a->size;
  size_t b_size = b->size;

  if (a_size == 0) {
    return set_create(0);
  }
  if (b_size == 0) {
    return set_create_from_array(a->data, a_size);
  }

  set_of_int_t* difference_set = set_create(a_size);
  if (!difference_set) {
    return NULL;
  }

  size_t l = 0;
  size_t r = 0;
  size_t k = 0;

  while (l < a_size && r < b_size) {
    if (a->data[l] < b->data[r]) {
      difference_set->data[k] = a->data[l];
      ++k;
      ++l;
    } else if (a->data[l] > b->data[r]) {
      ++r;
    } else {
      ++l;
      ++r;
    }
  }

  while (l < a_size) {
    difference_set->data[k] = a->data[l];
    ++k;
    ++l;
  }

  difference_set->size = k;

  return difference_set;
}

set_of_int_t* set_sym_difference(const set_of_int_t* a, const set_of_int_t* b) {
  if (!a || !b) {
    return NULL;
  }

  size_t a_size = a->size;
  size_t b_size = b->size;

  if (a_size == 0) {
    return set_create_from_array(b->data, b_size);
  }
  if (b_size == 0) {
    return set_create_from_array(a->data, a_size);
  }

  set_of_int_t* sym_diff_set = set_create(a_size + b_size);
  if (!sym_diff_set) {
    return NULL;
  }

  size_t l = 0;
  size_t r = 0;
  size_t k = 0;

  while (l < a_size && r < b_size) {
    if (a->data[l] < b->data[r]) {
      sym_diff_set->data[k] = a->data[l];
      ++l;
      ++k;
    } else if (a->data[l] > b->data[r]) {
      sym_diff_set->data[k] = b->data[r];
      ++r;
      ++k;
    } else {
      ++l;
      ++r;
    }
  }

  while (l < a_size) {
    sym_diff_set->data[k] = a->data[l];
    ++l;
    ++k;
  }

  while (r < b_size) {
    sym_diff_set->data[k] = b->data[r];
    ++r;
    ++k;
  }

  sym_diff_set->size = k;

  return sym_diff_set;
}