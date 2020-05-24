#ifndef _GENERIC_HASH_TABLE_CORE_UTIL_H
#define _GENERIC_HASH_TABLE_CORE_UTIL_H

#include "./generic_hash_table_ds.h"

ght_ret_status_t __ght_core_util_item_init(ght_item_t *, unsigned long, void *, size_t);
ght_ret_status_t __ght_core_util_item_deinit(ght_item_t *);
unsigned long hash_func(const unsigned long, const unsigned long);
unsigned long get_hash(const unsigned long, const unsigned long, unsigned int);

#endif /* _GENERIC_HASH_TABLE_CORE_UTIL_H */
