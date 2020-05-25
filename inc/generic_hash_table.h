#ifndef _GENERIC_HASH_TABLE_H
#define _GENERIC_HASH_TABLE_H

#include "./generic_hash_table_ds.h"

#define HASH_FUNC_2_PRIME                 67
#define PRINT_LOG                         0
#define SCALE_UP_THRESHOLD                60
#define SCALE_DOWN_THRESHOLD              20

ght_ret_status_t ght_init(g_hash_table_t *, size_t, size_t);
ght_ret_status_t ght_insert(g_hash_table_t *, unsigned long, void *);
ght_ret_status_t ght_search(g_hash_table_t *, unsigned long, size_t *);
ght_ret_status_t ght_get(g_hash_table_t *, unsigned long, void *);
ght_ret_status_t ght_delete(g_hash_table_t *, unsigned long);
ght_ret_status_t ght_deinit(g_hash_table_t *);
ght_ret_status_t ght_generate_key(unsigned long *);

#endif /* _GENERIC_HASH_TABLE_H */
