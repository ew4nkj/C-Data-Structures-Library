/**
 * @file dsHashtableFunctions.h 
 * @version 0.1
 * @date 2022-04-19
 */
#ifndef DSHASHTABLEFUNCTIONS_H
#define DSHASHTABLEFUNCTIONS_H

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef LIMITS_H
#define LIMITS_H
#include <limits.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

#include "dsErrorHandling.h"
#include "dsUniversal.h"

#define DEFAULT_HASH_SIZE 10007
#define SMALL_PRIME 31

//hidden types
typedef struct _hashTable HashTable;
typedef struct _hashNode HashNode;

/*#####################################################################################
 *#                                  CREATION FUNCTIONS                               #
 *#####################################################################################
 * - HashTable *newHashTable(void (*printFunction)(void* toBePrinted),
 *                           void (*deleteFunction)(void* toBeDeleted),
 *                           int (*compareFunction)(const void* first,const void* second),
 *                           char *(*toString)(void *toMakeString))
 * - unsigned int hash(char *key, unsigned int tableSize)
 * - void hashTableSetBound(HashTable *table, unsigned int bound)
 */

/** 
 * Creates an initilized hash table and returns it to the caller
 * @param void (*printFunction)(void* toBePrinted)
 * @param void (*deleteFunction)(void* toBeDeleted) 
 * @param int (*compareFunction)(const void* first,const void* second) 
 * @param char *(*toString)(void *toMakeString) 
 * @return HashTable* 
 */
HashTable *newHashTable(void (*printFunction)(void* toBePrinted),
                        void (*deleteFunction)(void* toBeDeleted),
                        int (*compareFunction)(const void* first,const void* second),
                        char *(*toString)(void *toMakeString));

/**
 * Computes a hash for table insertion and searching
 * @param char *key 
 * @param unsigned int tableSize 
 * @return unsigned int 
 */
unsigned int hash(char *key, unsigned int tableSize);

/**
 * Sets a new size for a given hash table however, if the table has been used this function cannot be used
 * @param HashTable *table 
 * @param unsigned int bound 
 */
void hashTableSetBound(HashTable *table, unsigned int bound);

/*#####################################################################################
 *#                                 INSERTION FUNCTIONS                               #
 *#####################################################################################
 * - void hashTableInsert(HashTable *table, char *key, void *toAdd)
 */

/**
 * Inserts data with a given key in the hash table
 * @param HashTable *table 
 * @param char *key
 * @param void *toAdd
 */
void hashTableInsert(HashTable *table, char *key, void *toAdd);

/*#####################################################################################
 *#                                 RETRIEVAL FUNCTIONS                               #
 *#####################################################################################
 * - void *hashTableSearch(HashTable *table, char *key)
 * - int hashTableSize(HashTable *table)
 */

/**
 * Searches a given hash table for a given key. If found this funtion returns its data otherwise, return null
 * @param HashTable *table
 * @param char *key
 * @return void* 
 */
void *hashTableSearch(HashTable *table, char *key);

/**
 * Returns the size of the hash table
 * @param HashTable *table 
 * @return int 
 */
int hashTableSize(HashTable *table);

/*#####################################################################################
 *#                                  REMOVAL FUNCTIONS                                #
 *#####################################################################################
 * - void *hashTableRemove(HashTable *table, char *key)
 * - void feeHashTableContent(HashTable *table)
 * - void freeHashTable(HashTable *table)
 */

/**
 * Removes data at a given key from the hashtable 
 * @param HashTable *table
 * @param char *key
 * @return void *data
 */
void *hashTableRemove(HashTable *table, char *key);

/**
 * Nulls out the entire table while freeing its content
 * @param HashTable *table
 */
void feeHashTableContent(HashTable *table);

/**
 * Frees all data associated with a hash table
 * @param HashTable *table 
 */
void freeHashTable(HashTable *table);

/*#####################################################################################
 *#                                 STD/HELPER FUNCTIONS                              #
 *#####################################################################################
 * - int hashTableUsage(HashTable *table)
 * - char *hashTableToString(HashTable *table)
 * - void hashTablePrint(HashTable *table)
 * - int hashTableIsEmpty(HashTable *table)
 */

/**
 * Returns the number of elements in a given hash table
 * 
 * @param HashTable *table 
 * @return int 
 */
int hashTableUsage(HashTable *table);

/**
 * Creates a character array representing a given hash table using the supplied to sting function 
 * @param HashTable *table 
 * @return char* 
 */
char *hashTableToString(HashTable *table);

/**
 * Prints a hash table using the suppled print function
 * @param HashTable *table) 
 */
void hashTablePrint(HashTable *table);

/**
 * Returns 1 if the hash table is empty otherwise, it returns 0
 * @param HashTable *table 
 * @return int 
 */
int hashTableIsEmpty(HashTable *table);

#endif