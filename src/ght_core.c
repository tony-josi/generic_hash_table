#include <stdlib.h>

#include "../inc/generic_hash_table.h"
#include "../inc/generic_hash_table_core_util.h"

ght_ret_status_t ght_init(g_hash_table_t *ht, size_t base, size_t item_sz) {

    ht->base_capacity = base;
    ht->capacity = ht->base_capacity;
    ht->item_size = item_sz;
    ht->count = 0;
    if((ht->items = (ght_item_t **) calloc(ht->capacity, sizeof(ght_item_t *)))  == NULL)
        return GHT_FAIL;

    return GHT_SUCCESS;

}

ght_ret_status_t ght_insert(g_hash_table_t *ht, unsigned long key, void *val) {

    unsigned int chain_len = 0;
    size_t index = (size_t) get_hash(key, (unsigned long) ht->capacity, chain_len);
    while((ht->items[index]) != NULL) {
        ++chain_len;
        index = (size_t) get_hash(key, (unsigned long) ht->capacity, chain_len);
    }

    if(__ght_core_util_item_init(ht->items[index], key, val, ht->item_size) != GHT_SUCCESS)
        return GHT_FAIL;

    return GHT_SUCCESS;

}

