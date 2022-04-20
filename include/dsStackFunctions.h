/**
 * @file dsStackFunctions.h
 * @version 0.5
 * @date 2022-04-16
 * 
 * FEATURES TO ADD
 * - missing all sort functionallity
 */
#ifndef DSSTACKFUNCTIONS_H
#define DSSTACKFUNCTIONS_H

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
#include "dsUniversal.h"

typedef struct _stack Stack;

typedef struct _stackNode StackNode;

/*#####################################################################################
 *#                                  CREATION FUNCTIONS                               #
 *#####################################################################################
 * - Stack *newStack(void (*printFunction)(void* toBePrinted), 
 *                   void (*deleteFunction)(void* toBeDeleted), 
 *                   int (*compareFunction)(const void* first,const void* second), 
 *                   char *(*toString)(void *toMakeString))
 * - StackNode *newStackNode(void *toAdd)
 */

/**
 * Creates a new empty stack structure with all values initilized
 * @param void (*printFunction)(void *toBePrinted) 
 * @param void (*deleteFunction)(void *toBeDeleted)
 * @param int (*compareFunction)(const void *first,const void *second)
 * @param char *(*toString)(void *toMakeString)
 * @return Stack* 
 */
Stack *newStack(void (*printFunction)(void* toBePrinted), 
                void (*deleteFunction)(void* toBeDeleted), 
                int (*compareFunction)(const void* first,const void* second), 
                char *(*toString)(void *toMakeString));

/**
 * Creates a new stack node with given data
 * @param void *toAdd
 * @return StackNode* 
 */
StackNode *newStackNode(void *toAdd);

/*#####################################################################################
 *#                                 INSERTION FUNCTIONS                               #
 *#####################################################################################
 * - void stackPush(Stack *stack, void *toAdd)
 */

/**
 * Pushes data onto a given stack
 * @param Stack *stack 
 * @param void *toAdd 
 */
void stackPush(Stack *stack, void *toAdd);

/*#####################################################################################
 *#                                 RETRIEVAL FUNCTIONS                               #
 *#####################################################################################
 * - void *stackPeek(Stack *stack)
 */

/**
 * Returns data at the top of the stack but does not remove it
 * @param Stack *stack 
 * @return void* 
 */
void *stackPeek(Stack *stack);

/*#####################################################################################
 *#                                  REMOVAL FUNCTIONS                                #
 *#####################################################################################
 * - void stackPop(Stack *stack)
 * - void freeStackContent(Stack *stack)
 * - void freeStack(Stack *stack)
 */

/**
 * Pops data off the stack, freeing it in the process
 * @param Stack *stack
 */
void stackPop(Stack *stack);

/**
 * Frees stack content but not the stack structure itself
 * @param Stack *stack
 */
void freeStackContent(Stack *stack);

/**
 * Frees the stack structure and all data within
 * @param Stack *stack 
 */
void freeStack(Stack *stack);

/*#####################################################################################
 *#                                 STD/HELPER FUNCTIONS                              #
 *#####################################################################################
 * - void stackPrint(Stack *stack)
 * - char *stackToString(Stack *stack)
 * - int stackIsEmpty(Stack *stack)
 * - int stackLength(Stack *stack)
 */

/**
 * Prints a stack using the provided print function
 * @param Stack *stack 
 */
void stackPrint(Stack *stack);

/**
 * Returns a generated string representing the given stack
 * @param Stack *stack 
 * @return char* 
 */
char *stackToString(Stack *stack);

/**
 * Determines if a stack is empty. If so return 1, otherwise 0
 * @param Stack *stack
 * @return int 
 */
int stackIsEmpty(Stack *stack);

/**
 * Returns a none 0 indexed length
 * @param Stack *stack 
 * @return int 
 */
int stackLength(Stack *stack);

#endif