#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../inc/generic_hash_table.h"
#include "../inc/generic_hash_table_ds.h"
#include "../inc/generic_hash_table_core_util.h"

ght_ret_status_t 
__ght_core_util_item_init(ght_item_t **item, unsigned long key, void *val, size_t size) {

    *item = malloc(sizeof(ght_item_t));
    (*item)->key = key;
    if(((*item)->val_ptr = malloc(size)) == NULL) {
        perror("    ERR: __ght_core_util_item_init(): malloc()");
        return GHT_FAIL;
    }
    
    if(!memcpy((*item)->val_ptr, val, size)) {
        perror("    ERR: __ght_core_util_item_init(): memcpy()");
        return GHT_FAIL;
    }

    return GHT_SUCCESS;
}

ght_ret_status_t 
__ght_core_util_item_deinit(ght_item_t **item) {
    
    if(*item) {
        if((*item)->val_ptr)
            free((*item)->val_ptr);
        else 
            perror("    ERR: __ght_core_util_item_deinit(): passing NULL to free(item->val_ptr)");

        free((*item));
        *item = NULL;
    }
    else {
        perror("    ERR: __ght_core_util_item_deinit(): passing NULL to free(item)");
        return GHT_FAIL;
    }

    return GHT_SUCCESS;
}

unsigned long hash_func_1(const unsigned long key, const unsigned long m) {
    
    unsigned long x = key;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    x = x ^ (x >> 31);
    return (key % m);

}

unsigned long hash_func_2(const unsigned long key) {
    
    unsigned long x = (HASH_FUNC_2_PRIME - (key % HASH_FUNC_2_PRIME));
    return x;

}

unsigned long 
get_hash(const unsigned long key, const unsigned long capacity, unsigned int chain_degreee) {

    const unsigned long first_hash = hash_func_1(key, capacity);
    const unsigned long second_hash = hash_func_2(key);
    return ((first_hash + (chain_degreee * second_hash)) % capacity);

}
