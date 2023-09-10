#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "data.h"
#include "array.h"


int main(int argc, char **argv) {
    FILE *in = fopen(argv[2], "r");
    FILE *out = fopen(argv[3], "w");

    char *header = malloc(LINE_MAX_LEN);
    fgets(header, LINE_MAX_LEN, in);

    array_t *arr = create_array();

    cafe_t *newcafe = malloc(sizeof(cafe_t));
    while (read(in, newcafe)) {
        insert_cafe_in_order(arr, *newcafe);
    }

    char *prefix = malloc(STRING_MAX_LEN);
    while (fgets(prefix, STRING_MAX_LEN, stdin)) {
        int bytes_compared = 0;
        int strings_compared = 0;
        prefix[strcspn(prefix, "\n")] = '\0';
        find_and_traverse(out, arr, prefix, &bytes_compared, &strings_compared);
    } 
    
    free(prefix);
    free(header);
    free(newcafe);
    fclose(in);
    fclose(out);
    
    return 0;
}


