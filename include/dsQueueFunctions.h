/**
 * @file dsQueueFunctions.h
 * @version 0.3
 * @date 2022-04-16
 */
#ifndef DSQUEUEFUNCTIONS_H
#define DSQUEUEFUNCTIONS_H

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

#ifndef STDARG_H
#define STDARG_H
#include <stdarg.h>
#endif

#ifndef LIMITS_H
#define LIMITS_H
#include <limits.h>
#endif

#include "dsErrorHandling.h"
#include "dsUniversal.h"

typedef enum _queueMode{
    DEFAULT,
    PRIORITY
}QueueMode;

typedef struct _queue Queue;
typedef struct _queueNode QueueNode;


/*#####################################################################################
 *#                                  CREATION FUNCTIONS                               #
 *#####################################################################################
 * - Queue *newQueue(QueueMode mode, void (*printFunction)(void *toBePrinted),
 *                                   void (*deleteFunction)(void *toBeDeleted),
 *                                   int (*compareFunction)(const void *first,const void *second),
 *                                   char *(*toString)(void *toMakeString));
 * - QueueNode *newQueueNode(void *toAdd, int priority)
 */

/** 
 * Creates a new Queue structure with a given mode
 * @param QueueMode mode 
 * @param void (*printFunction)(void *toBePrinted) 
 * @param void (*deleteFunction)(void *toBeDeleted) 
 * @param int (*compareFunction)(const void *first,const void *second) 
 * @param char *(*toString)(void *toMakeString) 
 * @return Queue* 
 */
Queue *newQueue(QueueMode mode, void (*printFunction)(void *toBePrinted),
                                void (*deleteFunction)(void *toBeDeleted),
                                int (*compareFunction)(const void *first,const void *second),
                                char *(*toString)(void *toMakeString));

/**
 * Creates a new node for a queue
 * @param void *toAdd 
 * @param int priority 
 * @return QueueNode* 
 */
QueueNode *newQueueNode(void *toAdd, int priority);

/*#####################################################################################
 *#                                 INSERTION FUNCTIONS                               #
 *#####################################################################################
 * - void queuePushPriority(Queue *q, void *toAdd, int priority)
 * - void _queuePushPriority(QueueNode **qn, void *toAdd, int priority)
 * - void queuePushDefault(Queue *q, void *toAdd)
 * - void _queuePushDefault(QueueNode **qn, void *toAdd)
 * void queuePush(Queue *q, void *toAdd, ...)
 */

/**
 * A wrapper function which calls _queuePushPriority and updates values 
 * @param Queue *q 
 * @param void *toAdd 
 * @param int priority 
 */
void queuePushPriority(Queue *q, void *toAdd, int priority);

/**
 * Pushes data onto a queue at a given position
 * @param QueueNode **qn 
 * @param void *toAdd 
 * @param int priority 
 */
void _queuePushPriority(QueueNode **qn, void *toAdd, int priority);

/**
 * A wrapper function which calls _queuePushDefault and updates values 
 * @param Queue *q 
 * @param void *toAdd 
 * @param int priority 
 */
void queuePushDefault(Queue *q, void *toAdd);

/**
 * Inserts data at the end of a queue
 * @param QueueNode **qn 
 * @param void *toAdd 
 * @param int priority 
 */
void _queuePushDefault(QueueNode **qn, void *toAdd);

/**
 * Variable function for pushing onto a queue. It will call a push function based
 * on the queue structures mode and if a priority is supplied
 * @param Queue *q 
 * @param void *toAdd 
 * @param int priority <- NOT REQUIRED 
 */
void queuePush(Queue *q, void *toAdd, ...);

/*#####################################################################################
 *#                                 RETRIEVAL FUNCTIONS                               #
 *#####################################################################################
 * - void *queuePeek(Queue *q)
 */

/**
 * Returns data at the front of the queue but, does not remove it
 * @param Queue *q 
 * @return void* 
 */
void *queuePeek(Queue *q);

/*#####################################################################################
 *#                                  REMOVAL FUNCTIONS                                #
 *#####################################################################################
 * - void queuePop(Queue *q)
 * - void _queuePop(Queue *q, QueueNode **qn)
 * - void freeQueue(Queue *q)
 * - void freeQueueContent(Queue *q)
 */

/**
 * A wrapper function for void _queuePop which handles errors and updates values 
 * @param Queue *q 
 */
void queuePop(Queue *q);

/**
 * Removes data from the front of a queue
 * @param Queue *q 
 * @param QueueNode **qn 
 */
void _queuePop(Queue *q, QueueNode **qn);

/**
 * Frees a queue structure and all its content
 * @param Queue *q 
 */
void freeQueue(Queue *q);

/**
 * Frees all queue content except the structure itself
 * @param Queue *q 
 */
void freeQueueContent(Queue *q);

/*#####################################################################################
 *#                                 STD/HELPER FUNCTIONS                              #
 *#####################################################################################
 * - int queueIsEmpty(Queue *q)
 * - int queueLength(Queue *q)
 * - void queuePrint(Queue *q)
 * - char *queueToString(Queue *q)
 */

/**
 * Returns true if the qiven queue is empty and returns false otherwise
 * @param Queue *q 
 * @return int 
 */
int queueIsEmpty(Queue *q);

/**
 * Returns a none 0 indexed queue length
 * @param Queue *q 
 * @return int 
 */
int queueLength(Queue *q);

/**
 * Prints ot the queue using the provided print function
 * @param Queue *q 
 */
void queuePrint(Queue *q);

/**
 * Returns a character array representing the queue using the provided toString function
 * @param Queue *q 
 * @return char* 
 */
char *queueToString(Queue *q);

#endif