#ifndef _GENERIC_HASH_TABLE_H
#define _GENERIC_HASH_TABLE_H

#include "./generic_hash_table_ds.h"

ght_ret_status_t ght_init(size_t);
ght_ret_status_t ght_insert(unsigned long, void *);
ght_ret_status_t ght_search(unsigned long, void **);
ght_ret_status_t ght_delete(unsigned long);

#endif /* _GENERIC_HASH_TABLE_H */