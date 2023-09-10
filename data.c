#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "data.h"

void print_cafe_info(FILE *out, cafe_t cafe) {
    fprintf(out, "--> census_year: %d || block_id: %d || property_id: %d || base_property_id: %d || ", cafe.census_year, 
    cafe.block_id, cafe.property_id, cafe.base_property_id);
    fprintf(out, "building_address: %s || clue_small_area: %s || business_address: %s || trading_name: %s || ",
    cafe.building_address, cafe.clue_small_area, cafe.business_address, cafe.trading_name);
    fprintf(out, "industry_code: %d || industry_description: %s || seating_type: %s || number_of_seats: %d || longtitude: %lf || latitude: %lf ||\n",
    cafe.industry_code, cafe.industry_description, cafe.seating_type, cafe.number_of_seats,
    cafe.longtitude, cafe.latitude);
}

int prefix_compare(cafe_t cafe, char *prefix, int *bytes_compared) {
    int compare_length = strlen(prefix);
    char *name = cafe.trading_name;
    for (int i=0; i < compare_length; i++) {
        (*bytes_compared)++;
        if (prefix[i] < name[i]) {
            return 1;
        }
        else if (prefix[i] > name[i]) {
            return -1;
        }
        else {
            continue;
        }
    }
    return 0;
}

int get_bit(char key, int n) {
    if (0 <= n && n<= 7) {
        return (key >> n) & 1;
    }
    else {
        return -1;
    }
}

int trading_name_compare(cafe_t cafe1, cafe_t cafe2) {
    int cmp = strcmp(cafe1.trading_name, cafe2.trading_name);
    if (cmp < 0) {
        return -1;
    }
    else if (cmp > 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void quote_handling(char a[]){
    if (a[0] == '"'){
        int newlen = strlen(a) - 2 + 1;
        char new[newlen];
        for (int i = 1; i < newlen; i++){
            new[i - 1] = a[i];
        }
        new[newlen - 1] = '\0';
        strcpy(a, new);
    }
}

int read(FILE *in, cafe_t *new_cafe) {
    char readin[LINE_MAX_LEN];
    if (fgets(readin, LINE_MAX_LEN, in) != NULL){
        int in_quote = 0;
        for (int i=0; i < strlen(readin); i++) {
            if (readin[i] == ',' && in_quote == 0) {
                readin[i] = '#';
            }
            else if (readin[i] == '"') {
                in_quote = 1 - in_quote;
            }
        }
        
        char *token;
        char *del = "#";

        token = strtok(readin, del);
        (*new_cafe).census_year = atoi(token);

        token = strtok(NULL, del);
        (*new_cafe).block_id = atoi(token);

        token = strtok(NULL, del);
        (*new_cafe).property_id = atoi(token);

        token = strtok(NULL, del);
        (*new_cafe).base_property_id = atoi(token);

        token = strtok(NULL, del);
        quote_handling(token);
        strcpy((*new_cafe).building_address, token);

        token = strtok(NULL, del);
        quote_handling(token);
        strcpy((*new_cafe).clue_small_area, token);

        token = strtok(NULL, del);
        quote_handling(token);
        strcpy((*new_cafe).business_address, token);

        token = strtok(NULL, del);
        quote_handling(token);
        strcpy((*new_cafe).trading_name, token);

        token = strtok(NULL, del);
        (*new_cafe).industry_code = atoi(token);

        token = strtok(NULL, del);
        quote_handling(token);
        strcpy((*new_cafe).industry_description, token);

        token = strtok(NULL, del);
        quote_handling(token);
        strcpy((*new_cafe).seating_type, token);

        token = strtok(NULL, del);
        (*new_cafe).number_of_seats = atoi(token);

        token = strtok(NULL, del);
        (*new_cafe).longtitude = atof(token);

        token = strtok(NULL, del);
        (*new_cafe).latitude = atof(token);
        
        return 1;
    }
    return 0;
}







