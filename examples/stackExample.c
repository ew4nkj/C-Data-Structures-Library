#include "dsStackFunctions.h"
#include <string.h>

typedef struct _person{
    char *name;
    int age;
    char gender;
}Person;

char *personString(void *toMakeString){

    Person *o = (Person *)toMakeString;

    char *str = malloc(sizeof(char)*(strlen(o->name)+ 4 + sizeof(int)));

    sprintf(str,"%s %d %c",o->name,o->age,o->gender);
    return str;
}

void personToDelete(void *toBeDeleted){

    Person *o = (Person *)toBeDeleted;
    free(o->name);
    free(o);

}

int main(int argc, char *argv[]){

    Stack *dmvLine = newStack(NULL,personToDelete,NULL,personString);

    //create new structs to give to the stack
    Person *alice = malloc(sizeof(Person));
    alice->name = malloc(sizeof(char)*strlen("Alice")+1);
    strcpy(alice->name,"Alice");
    alice->age = 30;
    alice->gender = 'f';

    Person *ben = malloc(sizeof(Person));
    ben->name = malloc(sizeof(char)*strlen("Ben")+1);
    strcpy(ben->name,"Ben");
    ben->age = 20;
    ben->gender = 'm';

    Person *matt = malloc(sizeof(Person));
    matt->name = malloc(sizeof(char)*strlen("Matt")+1);
    strcpy(matt->name,"Matt");
    matt->age = 26;
    matt->gender = 'm';

    Person *deborah = malloc(sizeof(Person));
    deborah->name = malloc(sizeof(char)*strlen("Deborah")+1);
    strcpy(deborah->name,"Deborah");
    deborah->age = 91;
    deborah->gender = 'f';

    //push all structures onto the stack
    stackPush(dmvLine,alice);
    stackPush(dmvLine,ben);
    stackPush(dmvLine,matt);
    stackPush(dmvLine,deborah);

    printf("People in the dmv line\n");
    while(!stackIsEmpty(dmvLine)){
        Person *first = stackPeek(dmvLine);
        char *str = personString(first);
        printf("Next up is %s\n",str);
        free(str);
        
        //pop data off the stack so the next item can be peeked
        stackPop(dmvLine);
    }

    if(stackIsEmpty(dmvLine)){
        printf("Nobody is left\n");
    }
    freeStack(dmvLine);
    
    return EXIT_SUCCESS;
}