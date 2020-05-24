#include <stdlib.h>

#include "../inc/generic_hash_table.h"

ght_ret_status_t ght_init(g_hash_table_t *ht, size_t base, size_t item_sz) {

    ht->base_capacity = base;
    ht->capacity = ht->base_capacity;
    ht->item_size = item_sz;
    ht->count = 0;
    if((ht->items = (ght_item_t *) calloc(sizeof(ght_item_t), ht->capacity)) == NULL)
        return GHT_FAIL;

    return GHT_SUCCESS;

}

/* ght_ret_status_t ght_insert(g_hash_table_t *ht, unsigned long key, void *val) {
    //size_t index = (size_t) //hash_func

} */

