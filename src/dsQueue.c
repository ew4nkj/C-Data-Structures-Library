#include "dsQueueFunctions.h"

struct _queue{
    Type type;
    void (*deleteData)(void *toBeDeleted);
    int (*compare)(const void *first,const void *second);
    void (*printData)(void *toBePrinted);
    char *(*toString)(void *toMakeString);
    enum _queueMode mode;
    int len;
    struct _queueNode *next;

};

struct _queueNode{
    int priority;
    void *data;
    struct _queueNode *next;
};


Queue *newQueue(QueueMode mode, void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second),char *(*toString)(void *toMakeString)){

    Queue *q = malloc(sizeof(Queue));
    allocationError("Queue *newQueue(QueueMode mode, void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second),char *(*toString)(void *toMakeString))",q);
    
    q->type = UQUEUE;
    q->mode = mode;
    q->len = -1;
    q->next = NULL;

    q->compare = compareFunction;
    q->deleteData = deleteFunction;
    q->printData = printFunction;
    q->toString = toString;

    return q;
}

QueueNode *newQueueNode(void *toAdd, int priority){

    QueueNode *qn = malloc(sizeof(QueueNode));
    allocationError("QueueNode *newQueueNode(void *toAdd, int priority)",qn);

    qn->data = toAdd;
    qn->priority = priority;
    qn->next = NULL;

    return qn;
}

void queuePushPriority(Queue *q, void *toAdd, int priority){

    if(nullArgError("void queuePushPriority(Queue *q, void *toAdd, int priority)",q,1)) return;
    if(nullArgError("void queuePushPriority(Queue *q, void *toAdd, int priority)",toAdd,2)) return;

    if(q->mode != PRIORITY){
        queuePushDefault(q,toAdd);
        return;
    }

    _queuePushPriority(&q->next,toAdd,priority);
    q->len = q->len + 1;
}

void _queuePushPriority(QueueNode **qn, void *toAdd, int priority){

    QueueNode *start = (*qn);
    QueueNode *tmp = newQueueNode(toAdd,priority);

    if(start == NULL){
        *qn = tmp;
        return;
    }


    if((*qn)->priority > priority){
        tmp->next = *qn;
        *qn = tmp;

    }else{
        while (start->next != NULL && start->next->priority < priority) {
            start = start->next;
        }

        tmp->next = start->next;
        start->next = tmp;
    }

}

void queuePushDefault(Queue *q, void *toAdd){

    if(nullArgError("void queuePushDefault(Queue *q, void *toAdd)",q,1)) return;
    if(nullArgError("void queuePushDefault(Queue *q, void *toAdd)",toAdd,2)) return;

    _queuePushDefault(&q->next,toAdd);
    q->len = q->len + 1;
}

void _queuePushDefault(QueueNode **qn, void *toAdd){
    
    QueueNode *last = (*qn);
    QueueNode *tmp = newQueueNode(toAdd,INT_MAX);
    
    if(*qn == NULL){
        *qn = tmp;
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }
  
    last->next = tmp;
}

void queuePush(Queue *q, void *toAdd, ...){

    if(nullArgError("void queuePush(Queue *q, void *toAdd, ...)",q,1)) return;
    if(nullArgError("void queuePush(Queue *q, void *toAdd, ...)",toAdd,2)) return;

    va_list args;
    int priority = -1;

    switch(q->mode){
        case PRIORITY:
            va_start(args,toAdd);
            priority = va_arg(args,int);
            queuePushPriority(q,toAdd,priority);
            break;
        default:
            queuePushDefault(q,toAdd);
            break;
    }
}

void *queuePeek(Queue *q){

    if(nullArgError("queuePeek(Queue **q)",q,1)) return NULL;
    if(nullArgError("queuePeek(Queue **q)",q->next,1)) return NULL;

    return q->next->data;
}

void queuePop(Queue *q){

    if(nullArgError("void queuePop(Queue **q)",q,1)) return;
    if(nullArgError("void queuePop(Queue **q)",q->next,1)) return;
    if(missingFunctionError("void queuePop(Queue **q)",q->deleteData)) return;

    _queuePop(q,&q->next);
    q->len = q->len - 1;
}

void _queuePop(Queue *q, QueueNode **qn){
    QueueNode *tmp = *qn;
    *qn = (*qn)->next;
    q->deleteData(tmp->data);
    void *v = (void *)tmp;
    _free(&v);
}

void freeQueue(Queue *q){
    
    if(nullArgError("void freeQueue(Queue *q)",q,1)) return;

    void *v = (void *)q;

    if(q->next != NULL){
        freeQueueContent(q);
        _free(&v);
    }else{
        _free(&v);
    }
}

void freeQueueContent(Queue *q){

    if(nullArgError("void freeQueueContent(Queue *q)",q,1)) return;
    if(nullArgError("void freeQueueContent(Queue *q)",q->next,1)) return;

    while(!queueIsEmpty(q)){
        queuePop(q);
    }
}

/*
 * ######################################################################################### 
 * #                          [standard and helper functions]                              #
 * #########################################################################################
 */

int queueIsEmpty(Queue *q){
    return (q == NULL || q->next == NULL) ? 1 : 0;
}

void queuePrint(Queue *q){

    if(nullArgError("void queuePrint(Queue *q)",q,1)) return;
    if(nullArgError("void queuePrint(Queue *q)",q->next,1)) return;

    QueueNode *qn = q->next;

    while(qn != NULL){
        q->printData(qn->data);
        qn = qn->next;
    }
}

int queueLength(Queue *q){
    return (q == NULL) ? 0 : q->len;
}

char *queueToString(Queue *q){

    if(nullArgError("char *queueToString(Queue *q)",q,1)) return NULL;

    char *retStr = malloc(sizeof(char)*2);
    allocationError("char *queueToString(Queue *q)",retStr);
    strcpy(retStr,"");
    
    QueueNode *qn = q->next;

    while(qn != NULL){
        char *str = q->toString(qn->data);
        int sz = strlen(retStr);
        retStr = realloc(retStr,sizeof(char)*(sz + strlen(str) + 1));
        allocationError("char *queueToString(Queue *q)",retStr);
        strcat(retStr,str);
        free(str);

        qn = qn->next;
    }
    strcat(retStr,"\0");
    return retStr;
}