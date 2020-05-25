#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inc/legacy_macros.h"
#include "inc/generic_hash_table.h"

#define BASE_SIZE                   1087
#define TEST_CASES                  1400
#define NO_OF_DELETES               1000

static unsigned long key_arr[NO_OF_DELETES];
static unsigned int key_arr_cntr = 0;

typedef struct _test_struct {
    int id;
    float val;
} test_t;



int main() {

    g_hash_table_t test_htable;
    test_t temp_test, temp_test_ret;
    unsigned long temp_key;
    if(ght_init(&test_htable, BASE_SIZE, sizeof(test_t)) != GHT_SUCCESS)
        printf("FAILED!\n");

    unsigned int t_case_cntr = 0;
    srand(time(0)); 
    UNUSED(RAND_GEN(100));

    while((t_case_cntr++) < (TEST_CASES)) {
        temp_test.id = RAND_GEN(1000);
        temp_test.val = (float) RAND_GEN(200);
        temp_key = (RAND_GEN(10000));

        printf("Data: %d     %f\n", temp_test.id, temp_test.val);

        if(t_case_cntr == 1000) {
            printf("DELETE_BIGNS\n");
            for(unsigned int titr = 0; (titr < NO_OF_DELETES) && (titr < key_arr_cntr); ++titr) {
                if(ght_delete(&test_htable, key_arr[titr]) != GHT_SUCCESS)
                    printf("DELETE_FAIL\n");
            } 
        }
        
        if(ght_insert(&test_htable, temp_key, (void *)&temp_test) == GHT_SUCCESS) {
            if(key_arr_cntr < NO_OF_DELETES) {
                key_arr[key_arr_cntr] = temp_key;
                key_arr_cntr++;
            }
        }
    
        if(ght_get(&test_htable, temp_key, &temp_test_ret) == GHT_SUCCESS) {
            printf("Return ID: %ld, %d %f\n", temp_key, temp_test_ret.id, temp_test_ret.val);
        
/*         if(RAND_GEN(4) == 1)
            ght_delete(&test_htable, temp_key); */
        }
        
        printf("\n\n");
    }

    if(ght_deinit(&test_htable) != GHT_SUCCESS)
        printf("FAILED!\n");
    
    return EXIT_SUCCESS;
}
