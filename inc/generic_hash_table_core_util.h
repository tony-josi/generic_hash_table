/** 
 *  @file   generic_hash_table_core_util.h
 *  @brief  Header file for utility functions source
 *
 *  This contains the Header file for utility functions source
 *
 *  @author Tony Josi   https://tjosi.000webhostapp.com/
 *  @bug No known bugs.
 */


#ifndef _GENERIC_HASH_TABLE_CORE_UTIL_H
#define _GENERIC_HASH_TABLE_CORE_UTIL_H

#include "./generic_hash_table_ds.h"

ght_ret_status_t __ght_core_util_item_init(ght_item_t *, unsigned long, void *, size_t);
ght_ret_status_t __ght_core_util_item_deinit(ght_item_t *);
unsigned long    __ght_core_util_get_hash(const unsigned long, const unsigned long, unsigned int);
ght_ret_status_t __ght_core_util_resize(g_hash_table_t *, size_t);
ght_ret_status_t __ght_core_util_scale_up(g_hash_table_t *);
ght_ret_status_t __ght_core_util_scale_down(g_hash_table_t *);
unsigned long    get_time_in_nanosec(void);

#endif /* _GENERIC_HASH_TABLE_CORE_UTIL_H */
