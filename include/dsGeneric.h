#ifndef DSGENERIC_H
#define DSGENERIC_H

#include "dsErrorHandling.h"
#include "dsHashtableFunctions.h"
#include "dsListFunctions.h"
#include "dsQueueFunctions.h"
#include "dsStackFunctions.h"
#include "dsUniversal.h"

/**
 * Wrapper for all is empty funtions 
 * @param void *dataStructure
 * @return int 
 */
int isEmpty(void *dataStructure);

/**
 * Wrapper for all print structures
 * @param void *dataStructure
 */
void toPrint(void *dataStructure);

/**
 * Wrapper for all to string functions
 * 
 * @param void *dataStructure 
 * @return char* 
 */
char *toString(void *dataStructure);

#endif