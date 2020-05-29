/** 
 *  @file   ght_core.c
 *  @brief  Library function defintions
 *
 *  This contains the Library function defintions
 *
 *  @author Tony Josi   https://tjosi.000webhostapp.com/
 *  @bug No known bugs.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include "../inc/generic_hash_table.h"
#include "../inc/generic_hash_table_core_util.h"


/**
  * @brief  Initialize the hash table data structure.
  * 
  * @param  [out] ht      Hash Table handle.
  * @param  [in]  base    Starting size of hash table.
  * @param  [in]  Hash    Size of an item in the hash table.
  * 
  * @note   This procedure initialises the #g_hash_table_t pointer variable
  *         with the base size and size of each of the item in the hash table.
  *         Also, allocates memory for each #base number of items. 
  *         
  * @retval Status:
  *             - #GHT_SUCCESS  Init success
  *             - #GHT_FAIL     Init failed
*/
ght_ret_status_t 
ght_init(g_hash_table_t *ht, size_t base, size_t item_sz) {

    ht->base_capacity = base;
    ht->capacity = ht->base_capacity;
    ht->item_size = item_sz;
    ht->count = 0;
    if((ht->items = \
    (ght_item_t *) calloc(ht->capacity, sizeof(ght_item_t)))  == NULL)
        return GHT_FAIL;

    uint8_t *alloc_mem = NULL;
    if((alloc_mem = malloc(ht->item_size * ht->capacity)) == NULL)
        return GHT_FAIL;

    for(unsigned int itr = 0; itr < ht->capacity; ++itr) {
        ht->items[itr].is_active = false;
        ht->items[itr].val_ptr = (void *) (alloc_mem + (ht->item_size * itr)); 
    }

    return GHT_SUCCESS;

}


/**
  * @brief  Inserts an item to the hash.
  * 
  * @param  [in] ht      Hash Table handle.
  * @param  [in] key     Key value of the item.
  * @param  [in] val     Pointer to the item to be inserted.
  * 
  * @note   This procedure inserts an item if and only if that
  *         key doesnt already exist in the hash table. 
  * 
  * @note   Calculates the hash table fill density to decide whether 
  *         scale the hash table size up.
  *         
  * @retval Status:
  *             - #GHT_SUCCESS              Insert success
  *             - #GHT_KEY_ALRDY_EXISTS     Key already exists insert failed
  *             - #GHT_FAIL                 Init failed
*/
ght_ret_status_t 
ght_insert(g_hash_table_t *ht, unsigned long key, void *val) {

/*     unsigned int ht_density = (ht->count * 100) / ht->capacity;
    if(ht_density > SCALE_UP_THRESHOLD) {
        if(__ght_core_util_scale_up(ht) != GHT_SUCCESS) 
            return GHT_FAIL;
 */

/* #if PRINT_LOG
        printf("Scale Up: %ld   Prev Denisty: %d\n", ht->capacity, ht_density);
#endif  *//* PRINT_LOG */
    //}

    size_t prev_index;
    if(ght_search(ht, key, &prev_index) == GHT_SUCCESS) {

#if PRINT_LOG
        printf("GHT_KEY_ALRDY_EXISTS Key: %ld\n", key);
#endif /* PRINT_LOG */

        return GHT_KEY_ALRDY_EXISTS;
    }

    unsigned int chain_len = 0;
    size_t index = \
    (size_t) __ght_core_util_get_hash(key, (unsigned long) ht->capacity, chain_len);

#if PRINT_LOG
    printf("Insert Hashes: %ld", index);
#endif /* PRINT_LOG */

    while((ht->items[index].is_active) != false) {
        ++chain_len;
        index = \
        (size_t) __ght_core_util_get_hash(key, (unsigned long) ht->capacity, chain_len);

#if PRINT_LOG
        printf("    %ld chain_len: %d", index, chain_len);
#endif /* PRINT_LOG */

    }

#if PRINT_LOG
    printf("\n");
#endif /* PRINT_LOG */

    if(__ght_core_util_item_init(&ht->items[index], key, val, ht->item_size) != GHT_SUCCESS)
        return GHT_FAIL;

    ht->count += 1;
    return GHT_SUCCESS;

}

/**
  * @brief  Searches if an item is in the hash table.
  * 
  * @param  [in]  ht      Hash Table handle.
  * @param  [in]  key     Key value of the item.
  * @param  [out] val     Index of the item in the hash table.
  * 
  * @note   This procedure searches for an item in the hash table and gives
  *         index of that item in the hash table. 
  * 
  * @retval Status:
  *             - #GHT_SUCCESS              Search success
  *             - #GHT_ITEM_NOT_FOUND       Key not found in hash table
  *             - #GHT_FAIL                 Search function failed
*/
ght_ret_status_t 
ght_search(g_hash_table_t *ht, unsigned long key, size_t *ret_ptr) {

    unsigned int chain_len = 0;
    size_t index = \
    (size_t) __ght_core_util_get_hash(key, (unsigned long) ht->capacity, chain_len);

#if PRINT_LOG
    printf("Search Hashes: %ld", index);
#endif /* PRINT_LOG */

    while((ht->items[index].is_active == true) && (ht->items[index].key != key)) {

        ++chain_len;
        if(chain_len == (ht->capacity - 1))
            return GHT_ITEM_NOT_FOUND;

        index = \
        (size_t) __ght_core_util_get_hash(key, (unsigned long) ht->capacity, chain_len);

#if PRINT_LOG
        printf("    %ld chain_len: %d", index, chain_len);
#endif /* PRINT_LOG */

    }

#if PRINT_LOG
    printf("\n");
#endif /* PRINT_LOG */

    if(ht->items[index].is_active == true) {
        *ret_ptr = index;
        return GHT_SUCCESS;
    }

    return GHT_FAIL;

}



/**
  * @brief  De-initializes the handle to the hash table.
  * 
  * @param  [in] ht      Hash Table handle.
  * 
  * @note   This procedure De-initializes the handle of hash table and frees all 
  *         allocated memory. 
  * 
  * @retval Status:
  *             - #GHT_SUCCESS              De-initialize success
  *             - #GHT_FAIL                 De-initialize function failed
*/
ght_ret_status_t 
ght_deinit(g_hash_table_t *ht) {

    if(ht->items) {

        if(ht->items[0].val_ptr) 
            free(ht->items[0].val_ptr);
    
        free(ht->items);
        return GHT_SUCCESS;
    }

    return GHT_FAIL;
}



/**
  * @brief  Gets an item from the hash table.
  * 
  * @param  [in]  ht          Hash Table handle.
  * @param  [in]  key         Key value of the item.
  * @param  [out] ret_ptr     Pointer to the location to which 
  *                           the item will be copied.
  * 
  * @note   This procedure searches for an item in the hash table and copies
  *         the item to the given pointer location if present. 
  * 
  * @retval Status:
  *             - #GHT_SUCCESS              Get success
  *             - #GHT_EMPTY                Hash Table is empty
  *             - #GHT_FAIL                 Get function failed
*/
ght_ret_status_t 
ght_get(g_hash_table_t *ht, unsigned long key, void *ret_ptr) {

    size_t index;
    ght_ret_status_t ret_code;

    if((ret_code = ght_search(ht, key, &index)) != GHT_SUCCESS)
        return ret_code;

    if(!memcpy(ret_ptr, ht->items[index].val_ptr, ht->item_size)) {
        perror("    ERR: ght_get(): memcpy()");
        return GHT_FAIL;
    }
    return GHT_SUCCESS;
}

#if 0

/**
  * @brief  Deletes an item from the hash table.
  * 
  * @param  [in]  ht          Hash Table handle.
  * @param  [in]  key         Key value of the item.
  * 
  * @note   This procedure searches for an item in the hash table and deletes
  *         the item if present. 
  * 
  * @retval Status:
  *             - #GHT_SUCCESS              Delete success
  *             - #GHT_EMPTY                Hash Table is empty
  *             - #GHT_FAIL                 Delete function failed
*/
ght_ret_status_t 
ght_delete(g_hash_table_t *ht, unsigned long key) {

    unsigned int ht_density = (ht->count * 100) / ht->capacity;
    if((ht->capacity != ht->base_capacity) && (ht_density < SCALE_DOWN_THRESHOLD)) {
        if(__ght_core_util_scale_down(ht) != GHT_SUCCESS)
            return GHT_FAIL;

#if PRINT_LOG
        printf("Scale Down: %ld     Prev Density: %d\n", ht->capacity, ht_density);
#endif /* PRINT_LOG */
    }

    size_t index;

    if(ht->count > 0) {

        if(ght_search(ht, key, &index) != GHT_SUCCESS)
            return GHT_FAIL;

        if(__ght_core_util_item_deinit(&(ht->items[index])) != GHT_SUCCESS)
            return GHT_FAIL;
    }
    else
        return GHT_EMPTY;

#if PRINT_LOG
                printf("Deleted: %ld\n", index);
#endif /* PRINT_LOG */      

    ht->count -= 1;
    return GHT_SUCCESS;

}

#endif

/**
  * @brief  Generates a unique key based on system time.
  * 
  * @param  [out]  ht          Pointer to the key location.
  * 
  * @note   This procedure generates a uinique and time based 
  *         (2 keys distinguished, on which is latest) key that can be used
  *         as the hash key, if required. 
  * 
  * @retval Status:
  *             - #GHT_SUCCESS              Delete success
*/
ght_ret_status_t 
ght_generate_key(unsigned long *key) {
    struct tm * timeinfo;
    time_t now = time(0);
    timeinfo = localtime(&now);

    unsigned long min_int = (unsigned long) timeinfo->tm_min;
    unsigned long nanosec_val = get_time_in_nanosec();
    nanosec_val = nanosec_val & 0x00FFFFFFFFFFFFFF;
    nanosec_val += ((min_int & 0xFF) << 56);
    *key = nanosec_val;

    return GHT_SUCCESS;
}


