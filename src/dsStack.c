#include "dsStackFunctions.h"

struct _stack{
    Type type;
    void (*deleteData)(void *toBeDeleted);
    int (*compare)(const void *first,const void *second);
    void (*printData)(void *toBePrinted);
    char *(*toString)(void *toMakeString);
    int len;
    struct _stackNode *content;

};

struct _stackNode{
    void *data;
    struct _stackNode *next;
};

Stack *newStack(void (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second),char *(*toString)(void *toMakeString)){

    Stack *stack = malloc(sizeof(Stack));
    allocationError("Stack *newStack(int size, int max, void (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second),char *(*toString)(void *toMakeString))",stack);
    
    stack->type = USTACK;
    stack->len = -1;
    stack->compare = compareFunction;
    stack->deleteData = deleteFunction;
    stack->printData = printFunction;
    stack->toString = toString;
    stack->content = NULL;

    return stack;
}

StackNode *newStackNode(void *toAdd){

    if(nullArgError("StackNode *newStackNode(void *toAdd, int priority)",toAdd,1)) return NULL;

    StackNode *node = malloc(sizeof(StackNode));
    allocationError("StackNode *newStackNode(void *toAdd, int priority)",toAdd);

    node->data = toAdd;
    node->next = NULL;

    return node;
}

void stackPush(Stack *stack, void *toAdd){
    
    if(nullArgError("void stackPushDefault(Stack *stack, void *toAdd)",stack,1)) return;
    if(nullArgError("void stackPushDefault(Stack *stack, void *toAdd)",toAdd,2)) return;

    StackNode *tmp = newStackNode(toAdd);

    if(stack->content == NULL){
        stack->content = tmp;

    }else{
        StackNode *oldNodes = stack->content;
        tmp->next = oldNodes;
        stack->content = tmp;

    }

    stack->len = stack->len + 1;
}

void stackPop(Stack *stack){

    if(nullArgError("void stackPop(Stack *stack)",stack,1)) return;
    if(nullArgError("void stackPop(Stack *stack)",stack->content,1)) return;

    StackNode *oldnodes = stack->content->next;

    stack->deleteData(stack->content->data);
    void *v = (void *)stack->content;
    _free(&v);

    stack->content = oldnodes;
    stack->len = stack->len - 1;

}

void *stackPeek(Stack *stack){

    if(nullArgError("void *stackPeek(Stack *stack)",stack,1)) return NULL;
    if(nullArgError("void *stackPeek(Stack *stack)",stack->content,1)) return NULL;

    return stack->content->data;
}

void freeStackContent(Stack *stack){

    if(nullArgError("void freeStackContent(Stack *stack)",stack,1)) return;
    if(nullArgError("void freeStackContent(Stack *stack)",stack->content,1)) return;
    if(missingFunctionError("void freeStackContent(Stack *stack)",stack->deleteData)) return;

    while(!stackIsEmpty(stack)){
        stackPop(stack);
    }

    stack->content = NULL;
    stack->len = -1;
}

void freeStack(Stack *stack){

    if(nullArgError("void freeStack(Stack *stack)",stack,1)) return;
    
    void *v = (void *)stack;

    if(stack->content == NULL){
        _free(&v);
    }else{
        freeStackContent(stack);
        _free(&v);
    }
}

/*
 * ######################################################################################### 
 * #                          [standard and helper functions]                              #
 * #########################################################################################
 */

int stackIsEmpty(Stack *stack){
    return (stack == NULL || stack->content == NULL) ? 1 : 0;
}

void stackPrint(Stack *stack){

    if(nullArgError("void stackPrint(Stack *stack)",stack,1)) return;
    if(nullArgError("void stackPrint(Stack *stack)",stack->content,1)) return;
    if(missingFunctionError("void stackPrint(Stack *stack)",stack->printData)) return;

    StackNode *tmp = stack->content;

    while(tmp != NULL){
        stack->printData(tmp->data);
        tmp = tmp->next;
    }
}

char *stackToString(Stack *stack){

    if(nullArgError("char *stackToString(Stack *stack)",stack,1)) return NULL;
    if(nullArgError("char *stackToString(Stack *stack)",stack->content,1)) return NULL;
    if(missingFunctionError("char *stackToString(Stack *stack)",stack->toString)) return NULL;

    char *retStr = malloc(sizeof(char)*2);
    allocationError("char *stackToString(Stack *stack)",retStr);
    strcpy(retStr,"");
    
    StackNode *currNode = stack->content;

    while(currNode != NULL){
        char *str = stack->toString(currNode->data);
        int sz = strlen(retStr);
        retStr = realloc(retStr,sizeof(char)*(sz + strlen(str) + 1));
        allocationError("char *stackToString(Stack *stack)",retStr);
        strcat(retStr,str);

        void *v = (void *)str;
        _free(&v);

        currNode = currNode->next;
    }
    strcat(retStr,"\0");
    return retStr;
}

int stackLength(Stack *stack){
    return (stack == NULL && stack->content == NULL) ? 0 : stack->len + 1;
}
