#include <stdio.h>

#include "set_lib.h"

int main() {
  printf("set create from array\n");
  int valid_arr[] = {10, 20, 30, 40, 50};
  int n1 = sizeof(valid_arr) / sizeof(valid_arr[0]);

  set_of_int_t* set1 = set_create_from_array(valid_arr, n1);
  if (set1) {
    printf("set was created: ");
    set_print(set1);
  } else {
    printf("error\n");
  }

  printf("\nset create from array (unsorted)\n");
  int bad_arr[] = {5, 1, 3};
  int n2 = sizeof(bad_arr) / sizeof(bad_arr[0]);
  set_of_int_t* set2 = set_create_from_array(bad_arr, n2);
  if (!set2) {
    printf("planned error\n");
  }

  printf("\nset_add\n");
  if (set1) {
    printf("25 -> 60 (новое) -> 20\n");
    set_add(set1, 25);
    set_add(set1, 60);
    set_add(set1, 20);
    set_print(set1);
  }

  printf("\nset_create\n");
  set_of_int_t* set3 = set_create(0);
  if (set3) {
    printf("set 2: ");
    set_print(set3);

    set_add(set3, 50);
    printf("after adding 50: ");
    set_print(set3);
  }

  printf("\nunion of two sets\n");
  int arr_a[] = {2, 4, 6, 8};
  int arr_b[] = {1, 3, 5, 7};
  set_of_int_t* set_a = set_create_from_array(arr_a, 4);
  set_of_int_t* set_b = set_create_from_array(arr_b, 4);
  set_of_int_t* union_set = set_union(set_a, set_b);
  if (union_set) {
    printf("union set: ");
    set_print(union_set);
  }

  printf("\nmemory freeing\n");
  set_destroy(set1);
  set_destroy(set3);
  set_destroy(set_a);
  set_destroy(set_b);
  set_destroy(union_set);

  printf("all mini tests is passed\n");

  return 0;
}