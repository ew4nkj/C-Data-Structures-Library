/**
 * @file dsUniversal.h
 * @version 0.1
 * @date 2022-04-19
 */
#ifndef DSUNIVERSAL_H
#define DSUNIVERSAL_H

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

typedef enum _type{
    ULIST,
    UQUEUE,
    USTACK,
    UHASHTABLE
}Type;

void _free(void **pptr);
#endif