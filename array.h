#ifndef _ARRAY_H
#define _ARRAY_H

#include <stdio.h>
#include "data.h"

#define INITIAL_ARRAY_SIZE 2

struct array {
    cafe_t *cafes;
    int size;
    int used;
};
typedef struct array array_t;

array_t *create_array();
void array_size_check(array_t *arr);
void insert_cafe_in_order(array_t *arr, cafe_t new_cafe);
void find_and_traverse(FILE *out, array_t *arr, char *prefix, int *bytes_compared, int *strings_compared);
int binary_search(array_t *arr, char *prefix, int *bytes_compared, int *string_compared);
void range_search(array_t *arr, char *prefix, int *bytes_compared, int *strings_compared, int *start, int *end, int mid);
void linear_search(FILE *out, array_t *arr, char *prefix, int *bytes_compared, int *strings_compared, int start, int end, int binary_result);
void print_array(FILE *f, array_t *arr);

#endif