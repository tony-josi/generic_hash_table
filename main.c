#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inc/legacy_macros.h"
#include "inc/generic_hash_table.h"

#define BASE_SIZE                   40
#define TEST_CASES                  20

typedef struct _test_struct {
    int id;
    float val;
} test_t;



int main() {

    g_hash_table_t test_htable;
    test_t temp_test;
    if(ght_init(&test_htable, BASE_SIZE, sizeof(test_t)) != GHT_SUCCESS)
        printf("FAILED!\n");

    unsigned int t_case_cntr = 0;
    srand(time(0)); 
    UNUSED(RAND_GEN(100));

    while((t_case_cntr++) < (TEST_CASES)) {
        temp_test.id = RAND_GEN(1000);
        temp_test.val = (float) RAND_GEN(200);
        printf("Data: %d     %f\n", temp_test.id, temp_test.val);
        ght_insert(&test_htable, (RAND_GEN(10000)), (void *)&temp_test);
    }

    if(ght_deinit(&test_htable) != GHT_SUCCESS)
        printf("FAILED!\n");
    
    return EXIT_SUCCESS;
}
