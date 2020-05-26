/** 
 *  @file   ght_core.c
 *  @brief  Library function defintions
 *
 *  This contains the Library function defintions
 *
 *  @author Tony Josi   https://tjosi.000webhostapp.com/
 *  @bug No known bugs.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../inc/generic_hash_table.h"
#include "../inc/generic_hash_table_core_util.h"

ght_ret_status_t 
ght_init(g_hash_table_t *ht, size_t base, size_t item_sz) {

    ht->base_capacity = base;
    ht->capacity = ht->base_capacity;
    ht->item_size = item_sz;
    ht->count = 0;
    if((ht->items = \
    (ght_item_t **) calloc(ht->capacity, sizeof(ght_item_t *)))  == NULL)
        return GHT_FAIL;

    return GHT_SUCCESS;

}

ght_ret_status_t 
ght_insert(g_hash_table_t *ht, unsigned long key, void *val) {

    unsigned int ht_density = (ht->count * 100) / ht->capacity;
    if(ht_density > SCALE_UP_THRESHOLD) {
        if(__ght_core_util_scale_up(ht) != GHT_SUCCESS) 
            return GHT_FAIL;

#if PRINT_LOG
        printf("Scale Up: %ld   Prev Denisty: %d\n", ht->capacity, ht_density);
#endif /* PRINT_LOG */
    }

    size_t prev_index;
    if(ght_search(ht, key, &prev_index) == GHT_SUCCESS) {

#if PRINT_LOG
        printf("GHT_KEY_ALRDY_EXISTS Key: %ld\n", key);
#endif /* PRINT_LOG */

        return GHT_KEY_ALRDY_EXISTS;
    }

    unsigned int chain_len = 0;
    size_t index = \
    (size_t) __ght_core_util_get_hash(key, (unsigned long) ht->capacity, chain_len);

#if PRINT_LOG
    printf("Hashes: %ld", index);
#endif /* PRINT_LOG */

    while((ht->items[index]) != NULL) {
        ++chain_len;
        index = \
        (size_t) __ght_core_util_get_hash(key, (unsigned long) ht->capacity, chain_len);

#if PRINT_LOG
        printf(" %ld", index);
#endif /* PRINT_LOG */

    }

#if PRINT_LOG
    printf("\n");
#endif /* PRINT_LOG */

    if(__ght_core_util_item_init(&(ht->items[index]), key, val, ht->item_size) != GHT_SUCCESS)
        return GHT_FAIL;

    ht->count += 1;
    return GHT_SUCCESS;

}

ght_ret_status_t 
ght_search(g_hash_table_t *ht, unsigned long key, size_t *ret_ptr) {

    unsigned int chain_len = 0;
    size_t index = \
    (size_t) __ght_core_util_get_hash(key, (unsigned long) ht->capacity, chain_len);

#if PRINT_LOG
    printf("Return Hashes: %ld", index);
#endif /* PRINT_LOG */

    while(((ht->items[index]) != NULL) && (((*ht->items[index]).key) != key)) {

        if(++chain_len >= ht->capacity)
            return GHT_ITEM_NOT_FOUND;

        index = \
        (size_t) __ght_core_util_get_hash(key, (unsigned long) ht->capacity, chain_len);

#if PRINT_LOG
        printf(" %ld", index);
#endif /* PRINT_LOG */

    }

#if PRINT_LOG
    printf("\n");
#endif /* PRINT_LOG */

    if(ht->items[index] != NULL) {
        *ret_ptr = index;
        return GHT_SUCCESS;
    }

    return GHT_FAIL;

}

ght_ret_status_t 
ght_deinit(g_hash_table_t *ht) {

    if(ht->items) {
        for(size_t i = 0; i < ht->capacity; i++) {
            if(ht->items[i] != NULL) {

#if PRINT_LOG
                printf("_____________Deinit: %ld\n", i);
#endif /* PRINT_LOG */

                if(__ght_core_util_item_deinit(&(ht->items[i])) != GHT_SUCCESS)
                    return GHT_FAIL;
            }
        }
    
        free(ht->items);
        return GHT_SUCCESS;
    }

    return GHT_FAIL;
}



ght_ret_status_t 
ght_get(g_hash_table_t *ht, unsigned long key, void *ret_ptr) {

    size_t index;

    if(ght_search(ht, key, &index) != GHT_SUCCESS)
        return GHT_FAIL;

    memcpy(ret_ptr, (*(ht->items[index])).val_ptr, ht->item_size);
    return GHT_SUCCESS;
}

ght_ret_status_t 
ght_delete(g_hash_table_t *ht, unsigned long key) {

    unsigned int ht_density = (ht->count * 100) / ht->capacity;
    if((ht->capacity != ht->base_capacity) && (ht_density < SCALE_DOWN_THRESHOLD)) {
        if(__ght_core_util_scale_down(ht) != GHT_SUCCESS)
            return GHT_FAIL;

#if PRINT_LOG
        printf("Scale Down: %ld     Prev Density: %d\n", ht->capacity, ht_density);
#endif /* PRINT_LOG */
    }

    size_t index;

    if(ht->count > 0) {

        if(ght_search(ht, key, &index) != GHT_SUCCESS)
            return GHT_FAIL;

        if(__ght_core_util_item_deinit(&(ht->items[index])) != GHT_SUCCESS)
            return GHT_FAIL;
    }
    else
        return GHT_EMPTY;

#if PRINT_LOG
                printf("Deleted: %ld\n", index);
#endif /* PRINT_LOG */      

    ht->count -= 1;
    return GHT_SUCCESS;

}

ght_ret_status_t ght_generate_key(unsigned long *key) {
    struct tm * timeinfo;
    time_t now = time(0);
    timeinfo = localtime(&now);

    unsigned long min_int = (unsigned long) timeinfo->tm_min;
    unsigned long nanosec_val = get_time_in_nanosec();
    nanosec_val = nanosec_val & 0x00FFFFFFFFFFFFFF;
    nanosec_val += ((min_int & 0xFF) << 56);
    *key = nanosec_val;

    return GHT_SUCCESS;
}


