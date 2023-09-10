#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "data.h"
#include "array.h"

array_t *create_array() {
    array_t *arr = malloc(sizeof(*arr));
    assert (arr);
    int size = INITIAL_ARRAY_SIZE;
    arr -> size = size;
    arr -> used = 0;
    arr -> cafes = malloc(size * sizeof(*(arr -> cafes)));
    assert(arr -> cafes);
    return arr;
}

void array_size_check(array_t *arr) {
    if (arr -> used == arr -> size) {
        int new_size = arr -> size * 2;
        arr -> size = new_size;
        arr -> cafes = realloc (arr -> cafes, new_size * sizeof(*(arr -> cafes)));
        assert(arr -> cafes);
    }
}

void insert_cafe_in_order(array_t *arr, cafe_t new_cafe) {
    array_size_check(arr);
    int i;
	for (i = arr-> used - 1; i >= 0 && trading_name_compare(new_cafe, arr->cafes[i]) == -1; i-- ) {
		arr->cafes[i + 1] = arr->cafes[i];
	}
	arr->cafes[i + 1] = new_cafe;
	arr->used++;
}

void find_and_traverse(FILE *out, array_t *arr, char *prefix, int *bytes_compared, int *strings_compared) {
    int binary_result = binary_search(arr, prefix, bytes_compared, strings_compared);
    if (binary_result != -1) {
        printf("%s --> b%d c%d s%d\n", arr -> cafes[binary_result].trading_name, (*bytes_compared)*8, *bytes_compared, *strings_compared);
        int start, end;
        range_search(arr, prefix, bytes_compared, strings_compared, &start, &end, binary_result);
        linear_search(out, arr, prefix, bytes_compared, strings_compared, start, end, binary_result);
    }
}

int binary_search(array_t *arr, char *prefix, int *bytes_compared, int *strings_compared) {
    int lo = 0;
    int hi = arr -> used - 1;
    while (lo <= hi) {
        int mid = (lo+hi)/2;
        int cmp = prefix_compare(arr -> cafes[mid], prefix, bytes_compared);
        (*strings_compared)++;
        if (cmp == -1) {
            lo = mid + 1;
        }
        else if (cmp == 1) {
            hi = mid - 1;
        }
        else {
            return mid;
        }
    }
    return -1;
}

void range_search(array_t *arr, char *prefix, int *bytes_compared, int *strings_compared, int *start, int *end, int mid) {
    (*start) = (*end) = mid;
    for (int i = mid + 1; i < arr -> used; i++) {
        (*strings_compared)++;
        if (prefix_compare(arr -> cafes[i], prefix, bytes_compared) != 0) {
            break;
        }
        else {
            (*end)++;
        }
    }
    for (int j = mid - 1; j >= 0; j--) {
        (*strings_compared)++;
        if (prefix_compare(arr -> cafes[j], prefix, bytes_compared) != 0) {
            break;
        }
        else {
            start--;
        }
    }
}

void linear_search(FILE *out, array_t *arr, char *prefix, int *bytes_compared, int *strings_compared, int start, int end, int binary_result) {
    int found[end - start + 1];
    memset(found, 0, sizeof(found));
    for (int i=start; i <= end; i++) {
        if (found[i - start]) {
            continue;
        }
        else {
            found[i - start] = 1;
            fprintf(out, "%s\n", arr -> cafes[i].trading_name);
            print_cafe_info(out, arr -> cafes[i]);
            if (i != binary_result) {
                printf("%s --> b%d c%d s%d\n", arr -> cafes[i].trading_name, (*bytes_compared)*8, *bytes_compared, *strings_compared);
            }
        }
        for (int j = i+1; j <= end; j++) {
            if (trading_name_compare(arr -> cafes[i], arr -> cafes[j]) == 0) {
                if (!found[j - start]) {
                    found[j - start] = 1;
                    print_cafe_info(out, arr -> cafes[j]);
                }
            }
        }
    }
    
}

void print_array(FILE *f, array_t *arr) {
    for (int i = 0; i < arr -> used; i++) {
        fprintf(f, "%s\n", arr -> cafes[i].trading_name);
    }
}


