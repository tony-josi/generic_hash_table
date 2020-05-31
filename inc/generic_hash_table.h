/** 
 *  @file   generic_hash_table.h
 *  @brief  Master Header file for Hash Table Library
 *
 *  This contains the Header file for data structure & basic funcs.
 *  defs used for the Hash Table library
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2020 Tony Josi
 *  @bug            No known bugs.
 */

#ifndef _GENERIC_HASH_TABLE_H
#define _GENERIC_HASH_TABLE_H

#include "./generic_hash_table_ds.h"

/*! \def HASH_FUNC_2_PRIME
    \brief A macro that holds constant prime number 
            used by 2nd hash function
   
*/
#define HASH_FUNC_2_PRIME                 277

/*! \def PRINT_LOG
    \brief Turn debug log info output ON(1) / OFF(0)
   
*/
#define PRINT_LOG                         0

/*! \def SCALE_UP_THRESHOLD
    \brief A macro that holds the threshold percent above 
    which hash table should scale up
   
*/
#define SCALE_UP_THRESHOLD                60

/*! \def SCALE_DOWN_THRESHOLD
    \brief A macro that holds the threshold percent below 
    which hash table should scale down
   
*/
#define SCALE_DOWN_THRESHOLD              20


/**
 * @brief Initialize the hash table
 *
 */
ght_ret_status_t ght_init(g_hash_table_t *, size_t, size_t);


/**
 * @brief Insert an item to the given hash table
 *
 */
ght_ret_status_t ght_insert(g_hash_table_t *, unsigned long, void *);


/**
 * @brief Search for an item in the hash table
 *
 */
ght_ret_status_t ght_search(g_hash_table_t *, unsigned long, size_t *);


/**
 * @brief Get a copy of an item from the hash table
 *
 */
ght_ret_status_t ght_get(g_hash_table_t *, unsigned long, void *);


/**
 * @brief Delete the given item from the hash table
 *
 */
ght_ret_status_t ght_delete(g_hash_table_t *, unsigned long);


/**
 * @brief Un initialize the given hash table
 *
 */
ght_ret_status_t ght_deinit(g_hash_table_t *);

/**
 * @brief Generate a 64 - bit unique key, can be used as keys for items
 *
 */
ght_ret_status_t ght_generate_key(unsigned long *);

#endif /* _GENERIC_HASH_TABLE_H */
