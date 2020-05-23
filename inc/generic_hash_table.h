#ifndef _GENERIC_HASH_TABLE_H
#define _GENERIC_HASH_TABLE_H

#include "./generic_hash_table_ds.h"

ght_ret_status_t ght_init(size_t, g_hash_table_t *);
ght_ret_status_t ght_insert(g_hash_table_t *, unsigned long, void *);
ght_ret_status_t ght_search(g_hash_table_t *, unsigned long, void **);
ght_ret_status_t ght_delete(g_hash_table_t *, unsigned long);
ght_ret_status_t ght_deinit(g_hash_table_t *);

#endif /* _GENERIC_HASH_TABLE_H */
