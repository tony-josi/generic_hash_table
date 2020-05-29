#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inc/legacy_macros.h"
#include "inc/generic_hash_table.h"

#define BASE_SIZE                   1087
#define TEST_CASES                  400

/* static unsigned long key_arr[TEST_CASES];
static unsigned int key_arr_cntr = 0; */

typedef struct _test_struct {
    int id;
    float val;
} test_t;


int main()
{
    srand(time(0)); 
    UNUSED(RAND_GEN(100));
    g_hash_table_t ht;
    ght_ret_status_t ret_code;
    test_t temp_var;
    unsigned long temp_key;

    if(ght_init(&ht, BASE_SIZE, sizeof(test_t)) != GHT_SUCCESS) {
        printf("Init Failed\n");
    }

    for(unsigned int itr = 0 ; itr < TEST_CASES; ++itr) {
        ght_generate_key(&temp_key); 
        temp_var.id = RAND_GEN(40000);
        temp_var.val = (float) RAND_GEN(80000);
        if((ret_code = ght_insert(&ht, temp_key, &temp_var)) != GHT_SUCCESS)
            printf("Insert Error -> E_CODE: %d\n", ret_code);
        else
            printf("Insterted data: Key -> %ld, Data 1st: %d 2nd: %f\n", temp_key, temp_var.id, temp_var.val);

        temp_var.id = 0;
        temp_var.val = 0.0;

        if((ret_code = ght_get(&ht, temp_key, &temp_var)) != GHT_SUCCESS)
            printf("Insert Error -> E_CODE: %d\n", ret_code);
        else
            printf("Got data: Key -> %ld, Data 1st: %d 2nd: %f\n", temp_key, temp_var.id, temp_var.val);

        printf("\n\n\n");
    }

    if(ght_deinit(&ht) != GHT_SUCCESS) {
        printf("Init Failed\n");
    }
    
    return 0;
}


#if 0
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
#endif /* main */

#if 0 /* test main */

int main() {

    g_hash_table_t test_htable;
    test_t temp_test, temp_test_ret = {0, 0.0};
    unsigned long temp_key;
    unsigned int cntr = 0, insr_count = 0, retr_count = 0;
    ght_ret_status_t ret_code;

    clock_t begin = clock();

    if(ght_init(&test_htable, BASE_SIZE, sizeof(test_t)) != GHT_SUCCESS)
        printf("FAILED!\n");

    while(cntr < TEST_CASES) {

        temp_test.id = RAND_GEN(1000);
        temp_test.val = (float) RAND_GEN(200);

        ght_generate_key(&temp_key);
        ret_code = ght_insert(&test_htable, temp_key, (void *)&temp_test);
        if(ret_code == GHT_SUCCESS) {

            key_arr[key_arr_cntr] = temp_key;
            key_arr_cntr++;
            insr_count++;
            printf("INSERTION: ITR: %d NOS-> %d KEY-> %ld DATA: ID-> %d Val-> %f\n", \
            cntr, insr_count, temp_key, temp_test.id, temp_test.val);
        }
        else if(ret_code == GHT_KEY_ALRDY_EXISTS)
            printf("______INSERTION GHT_KEY_ALRDY_EXISTS: ITR: %d NOS-> %d KEY-> %ld DATA: ID-> %d Val-> %f\n", \
            cntr, insr_count, temp_key, temp_test.id, temp_test.val);
        else
            printf("______INSERTION GHT_FAIL: ITR: %d NOS-> %d KEY-> %ld DATA: ID-> %d Val-> %f\n", \
            cntr, insr_count, temp_key, temp_test.id, temp_test.val);

        ++cntr;

    }
    printf("KEY_ARR_SIZE: %d\n", key_arr_cntr);
    cntr = 0;
    while(cntr < key_arr_cntr) {

        ret_code = ght_get(&test_htable, key_arr[cntr], (void *)&temp_test_ret);
        if(ret_code == GHT_SUCCESS) {

            retr_count++;
            printf("RETRIEVING: CNTR-> %d NO-> %d KEY-> %ld DATA: ID-> %d Val-> %f\n", \
            cntr, retr_count, key_arr[cntr], temp_test_ret.id, temp_test_ret.val);

        }
        else if(ret_code == GHT_FAIL)
            printf("______RETRIEVING GHT_FAIL: CNTR-> %d NO-> %d KEY-> %ld DATA: ID-> %d Val-> %f\n", \
            cntr, retr_count, key_arr[cntr], temp_test_ret.id, temp_test_ret.val);

        cntr++;

    }

    if(ght_deinit(&test_htable)!= GHT_SUCCESS) {
        printf("DE INIT FAILED!\n");
        return EXIT_FAILURE;
    }
    else {
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("DE INIT SUCCESS!\n");
        printf("Execution time: %f\n", time_spent);
        return EXIT_SUCCESS;
    }
    

    return 0;

}


#endif



