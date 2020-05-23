#include <stdlib.h>

#include "../inc/generic_hash_table.h"

ght_ret_status_t ght_init(size_t base, g_hash_table_t *ht) {

    ht->base_size = base;
    ht->size = ht->base_size;
    ht->count = 0;
    if((ht->items = (ght_item_t *) calloc(sizeof(ght_item_t), ht->size)) == NULL)
        return GHT_FAIL;

    return GHT_SUCCESS;

}



