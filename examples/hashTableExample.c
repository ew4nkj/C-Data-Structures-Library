#include "dsHashtableFunctions.h"

typedef struct _person{
    char *name;
    int age;
}Person;

char *personString(void *toMakeString){

    Person *o = (Person *)toMakeString;

    char *str = malloc(sizeof(char)*(strlen(o->name)+ 14 + sizeof(int)));

    sprintf(str,"%s is %d years old\n",o->name,o->age);
    return str;
}

void personToDelete(void *toBeDeleted){

    Person *o = (Person *)toBeDeleted;
    free(o);

}

void personToPrint(void *toBePrinted){

    Person *o = (Person *)toBePrinted;
    printf("%s is in the table\n",o->name);
}

int personToCompare(const void *first,const void *second){

    Person *o1 = (Person *)first;
    Person *o2 = (Person *)second;
    return strcmp(o1->name,o2->name);
}

int main(int argc, char *argv[]){

    HashTable *table = newHashTable(personToPrint,personToDelete,NULL,personString);
    
    Person *beck = malloc(sizeof(Person));
    beck->age = 12;
    beck->name = "beck";

    Person *john = malloc(sizeof(Person));
    john->age = 21;
    john->name = "john";

    Person *alice = malloc(sizeof(Person));
    alice->age = 30;
    alice->name = "alice";

    Person *alyssa = malloc(sizeof(Person));
    alyssa->age = 21; 
    alyssa->name = "alyssa";

    Person *lara = malloc(sizeof(Person));
    lara->age = 45;
    lara->name = "lara";

    Person *avery = malloc(sizeof(Person));
    avery->age = 80;
    avery->name = "avery";

    hashTableSetBound(table,7);

    hashTableInsert(table,"beck",beck);
    hashTableInsert(table,"alice",alice);
    hashTableInsert(table,"john",john);
    hashTableInsert(table,"alyssa",alyssa);
    hashTableInsert(table,"lara",lara);
    hashTableInsert(table,"avery",avery);

    printf("who is in my table?\n");
    hashTablePrint(table);


    char *str = hashTableToString(table);
    printf("\nhow old is everyone?\n%s",str);
    free(str);
    
    freeHashTable(table);
    return EXIT_SUCCESS;
}