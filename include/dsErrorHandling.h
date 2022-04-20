/**
 * @file dsErrorHandling.h
 * @version 0.3
 * @date 2022-04-19
 */
#ifndef DSERRORHANDLING_H
#define DSERRORHANDLING_H

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDBOOL_H
#define STDBOOL_H
#include <stdbool.h>
#endif

/**
 * If allocating functions fail exit
 * @param char *functionName
 * @param void *data 
 */
void allocationError(char *functionName, void *data);

/**
 * If a given arg is null return true otherwise, false
 * @param char *functionName
 * @param void *data
 * @param int narg 
 * @return true 
 * @return false 
 */
bool nullArgError(char *functionName, void *data, int narg);

/**
 * If a given value is negative return true otherwise, false
 * @param char *functionName 
 * @param int value 
 * @param int narg 
 * @return true 
 * @return false 
 */
bool negVArgError(char *functionName, int value, int narg);
/**
 * If a given function pointer is null return true otherwise, false
 * @param char *functionName 
 * @param void *func
 * @return true 
 * @return false 
 */
bool missingFunctionError(char *functionName, void *func);

/**
 * this error prints to stderr and can never return false. It only exists to print a message
 * @param char *functionName
 * @param unsigned int rBound 
 * @param unsigned int tBound 
 * @return true 
 */
bool hashChangeBoundError(char *functionName, unsigned int rBound, unsigned int tBound);



#endif