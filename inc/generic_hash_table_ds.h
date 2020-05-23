#ifndef _GENERIC_HT_DS_H
#define _GENERIC_HT_DS_H

#include <stddef.h> 

typedef enum {
    GHT_SUCCESS = 0,
    GHT_ITEM_NOT_FOUND,
    GHT_INVALID_PARAMS,
    GHT_FAIL
} ght_ret_status_t;

typedef struct _ght_item {

    unsigned long       id;
    void               *ptr;

} ght_item_t;

typedef struct _g_hash_table {

    size_t              base_size;
    size_t              size;
    size_t              count;
    ght_item_t         *items;

} g_hash_table_t;

#endif /* _GENERIC_HT_DS_H */

