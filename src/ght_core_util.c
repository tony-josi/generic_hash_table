#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "../inc/generic_hash_table.h"
#include "../inc/generic_hash_table_ds.h"
#include "../inc/generic_hash_table_core_util.h"

static unsigned long    hash_func_1(const unsigned long, const unsigned long);
static unsigned long    hash_func_2(const unsigned long);
static unsigned int     check_if_prime(unsigned int);
static unsigned int     get_next_prime(unsigned int);

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

unsigned long 
hash_func_1(const unsigned long key, const unsigned long m) {
    
    unsigned long x = key;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    x = x ^ (x >> 31);
    return (key % m);

}

unsigned long 
hash_func_2(const unsigned long key) {
    
    unsigned long x = (HASH_FUNC_2_PRIME - (key % HASH_FUNC_2_PRIME));
    return x;

}

unsigned long 
__ght_core_util_get_hash(const unsigned long key, const unsigned long capacity, unsigned int chain_degreee) {

    const unsigned long first_hash = hash_func_1(key, capacity);
    const unsigned long second_hash = hash_func_2(key);
    return ((first_hash + (chain_degreee * second_hash) + 1) % capacity);

}

unsigned int 
check_if_prime(unsigned int num) {
    if(num < 2)
        return 1;
    if(num < 4)
        return 0;
    if((num % 2) == 0)
        return 0;

    for(unsigned int itr = 3; itr <= floor(sqrt((double) num)); itr += 2)
        if((num % itr) == 0)
            return 1;
    return 0;
}

unsigned int     
get_next_prime(unsigned int base) {

    while(check_if_prime(++base) != 0);
    return base;
}

ght_ret_status_t __ght_core_util_resize(g_hash_table_t *ht, size_t size_estimate) {

    if(size_estimate < (ht->base_capacity))
        return GHT_SUCCESS;

    g_hash_table_t new_ht;
    new_ht.base_capacity = ht->base_capacity;
    new_ht.capacity = (size_t) get_next_prime((unsigned int) size_estimate);
    new_ht.count = 0;
    new_ht.item_size = ht->item_size;
    if((new_ht.items = (ght_item_t **) calloc(new_ht.capacity, sizeof(ght_item_t *)))  == NULL)
        return GHT_FAIL;

    if(ht->items) 
        for(size_t i = 0; i < ht->capacity; i++) 
            if(ht->items[i] != NULL) {
                if(ght_insert(&new_ht, (*ht->items[i]).key, (*ht->items[i]).val_ptr) != \
                GHT_SUCCESS)
                    return GHT_FAIL;
            }

    ght_deinit(ht);
    *ht = new_ht;
    return GHT_SUCCESS;
}

ght_ret_status_t 
__ght_core_util_scale_up(g_hash_table_t *ht) {
    
    if(__ght_core_util_resize(ht, (size_t)(ht->capacity * 2)) != GHT_SUCCESS)
        return GHT_FAIL;
    
    return GHT_SUCCESS;
}


ght_ret_status_t 
__ght_core_util_scale_down(g_hash_table_t *ht) {

    if(__ght_core_util_resize(ht, (size_t)(ht->capacity / 2)) != GHT_SUCCESS) 
        return GHT_FAIL;

    return GHT_SUCCESS;
}


