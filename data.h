#ifndef _DATA_H_
#define _DATA_H_

#include <stdio.h>

#define STRING_MAX_LEN 128
#define LINE_MAX_LEN 512

struct cafe {
    int census_year;
    int block_id;
    int property_id;
    int base_property_id;
    char building_address[STRING_MAX_LEN];
    char clue_small_area[STRING_MAX_LEN];
    char business_address[STRING_MAX_LEN];
    char trading_name[STRING_MAX_LEN];
    int industry_code;
    char industry_description[STRING_MAX_LEN];
    char seating_type[STRING_MAX_LEN];
    int number_of_seats;
    double longtitude;
    double latitude;
};

typedef struct cafe cafe_t;

void print_cafe_info(FILE *out, cafe_t cafe);
int prefix_compare(cafe_t cafe, char *s, int *bytes_compared);
int get_bit(char key, int n);
int trading_name_compare(cafe_t cafe1, cafe_t cafe2);
void quote_handling(char a[]);
int read(FILE *in, cafe_t *new_cafe);

#endif
