#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../inc/generic_hash_table_ds.h"
#include "../inc/generic_hash_table_core_util.h"

ght_ret_status_t __ght_core_util_item_init
(ght_item_t *item, unsigned long key, void *val, size_t size) {

    item->key = key;
    if((item->val_ptr = malloc(size)) == NULL) {
        perror("    ERR: __ght_core_util_item_init(): malloc()");
        return GHT_FAIL;
    }
    
    if(memcpy(item->val_ptr, val, size)) {
        perror("    ERR: __ght_core_util_item_init(): memcpy()");
        return GHT_FAIL;
    }

    return GHT_SUCCESS;
}

ght_ret_status_t __ght_core_util_item_deinit
(ght_item_t *item) {
    
    if(item->val_ptr)
        free(item->val_ptr);
    else {
        perror("    ERR: __ght_core_util_item_deinit(): passing NULL to free()");
        return GHT_FAIL;
    }

    return GHT_SUCCESS;
}

