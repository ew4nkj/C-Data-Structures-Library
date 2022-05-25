/**
 * @file dsListFunctions.h
 * @version 0.5
 * @date 2022-04-16
 */
#ifndef DSLISTFUNCTIONS_H
#define DSLISTFUNCTIONS_H

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

#include "dsErrorHandling.h"

//hidden types
typedef struct _list List;
typedef struct _listNode ListNode;

/*#####################################################################################
 *#                                  CREATION FUNCTIONS                               #
 *#####################################################################################
 * - List *newList(void (*printFunction)(void *toBePrinted),
 *                 void (*deleteFunction)(void *toBeDeleted),
 *                 int (*compareFunction)(const void *first,const void *second),
 *                 char *(*toString)(void *toMakeString))
 * - ListNode *newListNode(void *data, int currLen)
 * - List *listJoin(List *dest, List *src)                             
 */

/**
 * Creates a new empty list structure with all values initilized
 * @param void (*printFunction)(void *toBePrinted) 
 * @param void (*deleteFunction)(void *toBeDeleted)
 * @param int (*compareFunction)(const void *first,const void *second)
 * @param char *(*toString)(void *toMakeString)
 * @return List* 
 */
List *newList(void (*printFunction)(void *toBePrinted),
              void (*deleteFunction)(void *toBeDeleted),
              int (*compareFunction)(const void *first,const void *second),
              char *(*toString)(void *toMakeString));

/**
 * Creates a new Node for list insertion 
 * @param void *data 
 * @param int currLen 
 * @return ListNode* 
 */
ListNode *newListNode(void *data, int currLen);

/** 
 * Joins two lists but, destroys the two given
 * @param List *dest 
 * @param List *src 
 * @return List* 
 */
List *listJoin(List **dest, List **src);

/*#####################################################################################
 *#                                 INSERTION FUNCTIONS                               #
 *#####################################################################################
 * - void listInsertBack(List *list, void *toAdd);
 * - void listInsertFront(List *list, void *toAdd);
 * - void listInsertAfterPosition(List *list, int pos, void *toAdd)
 * - void listInsertAfterData(List *list, void *dataPos, void *toAdd)                             
 */

/**
 * Inserts a given pointer at the end of the list
 * @param List *list 
 * @param void *toAdd 
 */
void listInsertBack(List *list, void *toAdd);

/**
 * Inserts a given pointer at the beginning of the list 
 * @param List *list
 * @param void *toAdd
 */
void listInsertFront(List *list, void *toAdd);

/**
 * Inserts a given pointer after a given position within the list
 * @param List *list 
 * @param int pos 
 * @param void *toAdd 
 */
void listInsertAfterPosition(List *list, int pos, void *toAdd);

/**
 * Inserts a given pointer after the position of another supplied pointer
 * @param List *list 
 * @param void *dataPos
 * @param void *toAdd
 */
void listInsertAfterData(List *list, void *dataPos, void *toAdd);

/*#####################################################################################
 *#                                 RETRIEVAL FUNCTIONS                               #
 *#####################################################################################
 * - void *listGetFromFront(List *list)
 * - void *listGetFromBack(List *list)   
 * - void *listGetAtPosition(List *list, int pos)                       
 */

/**
 * Returs the pointer at the front of the list however, this function does not copy data
 * @param List *list
 * @return void* 
 */
void *listGetFromFront(List *list);

/**
 * Returs the pointer at the back of the list however, this function does not copy data
 * @param List *list 
 * @return void* 
 */
void *listGetFromBack(List *list);

/**
 * Returns a pointer at a specified position in the list however, this function does not copy data
 * @param List *list 
 * @param pos 
 * @return void* 
 */
void *listGetAtPosition(List *list, int pos);

/*#####################################################################################
 *#                                  REMOVAL FUNCTIONS                                #
 *#####################################################################################
 * - void *listRemoveAtPosition(List *list, int pos)
 * - void *listRemoveData(List *list, void *toBeDeleted)
 * - void freeListContent(List *list)
 * - void freeList(List *list)                   
 */

/** 
 * Removes a node and returns its content at a given position
 * @param List *list 
 * @param int pos
 * @return void *data
 */
void *listRemoveAtPosition(List *list, int pos);

/**
 * Removes a node from the list matching given data
 * @param List *list 
 * @param void *toBeDeleted
 * @return void *data 
 */
void *listRemoveData(List *list, void *toBeDeleted);

/**
 * Frees all node content within a given list using the user supplied delete function 
 * @param List *list 
 */
void freeListContent(List *list);

/**
 * Frees the list itself including all attached nodes
 * @param List *list 
 */
void freeList(List *list);

/*#####################################################################################
 *#                                 STD/HELPER FUNCTIONS                              #
 *#####################################################################################
 * - int listlength(List *list)
 * - int listIsEmpty(List *list)
 * - void listPrint(List *list)
 * - char *listToString(List *list)
 * - void freeList(List *list)
 * - void updateListPositions(List *list)                   
 */

/**
 * Returns a none 0 indexed length of the list
 * @param List *list 
 * @return int 
 */
int listlength(List *list);

/**
 * returns true if a given list is empty and false otherwise
 * @param List *list 
 * @return int 
 */
int listIsEmpty(List *list);
/**
 * Prints a list using the user supplied print function 
 * @param List *list 
 */
void listPrint(List *list);

/** 
 * Returns a character array representing the given list based on the supplied to string function
 * @param List *list 
 * @return char* 
 */
char *listToString(List *list);

void updateListPositions(List *list);

#endif