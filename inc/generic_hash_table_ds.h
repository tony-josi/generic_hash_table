/** 
 *  @file   generic_hash_table_ds.h
 *  @brief  Header file for data structure defs used for the Hash Table 
 *
 *  This contains the Header file for data structure 
 *  defs used for the Hash Table 
 *
 *  @author Tony Josi   https://tjosi.000webhostapp.com/
 *  @bug No known bugs.
 */

#ifndef _GENERIC_HT_DS_H
#define _GENERIC_HT_DS_H

#include <stddef.h> 
#include <stdbool.h>

typedef enum {
    GHT_SUCCESS = 0,        /*!< GHT Function success */
    GHT_KEY_ALRDY_EXISTS,   /*!< GHT Key Already exists */
    GHT_EMPTY,              /*!< GHT Hash table empty */
    GHT_ITEM_NOT_FOUND,     /*!< GHT Item is not present in hash table */
    GHT_INVALID_PARAMS,     /*!< GHT Invalid function params */
    GHT_FAIL                /*!< GHT Function Fail */
} ght_ret_status_t;

/**
 * @struct  ght_item_t
 * @brief   GHT basic item type
 *
 * Basic structure containing the feilds for an item in the hash table
 */
typedef struct _ght_item {

    unsigned long       key;        /*!< Key of the item */
    bool                is_active;
    void               *val_ptr;    /*!< Pointer to the item record */

} ght_item_t;

/**
 * @struct  g_hash_table_t
 * @brief   GHT handle type
 *
 * Basic structure holding all the feilds related to the specific hash table
 */
typedef struct _g_hash_table {

    size_t              base_capacity;      /*!< Base capacity of Hash Table */
    size_t              capacity;           /*!< Current capacity of Hash Table */
    size_t              item_size;          /*!< Size of an item in Hash Table */
    size_t              count;              /*!< Current count items in Hash Table */
    unsigned int        scaling_factor;     /*!< Current number of up scalings, 
                                                 decreased on scale down */
    ght_item_t         *items;              /*!< Pointer to the items memory of Hash Table */

} g_hash_table_t;

#endif /* _GENERIC_HT_DS_H */

