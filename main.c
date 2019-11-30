#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define IDSIZE 10
#define NAMESIZE 20

typedef struct {

    char last[NAMESIZE];
    char first[NAMESIZE];

}name;

typedef struct {
    char id[IDSIZE];
    name name;
    int score;
}record;

typedef struct node node;
struct node{
    record data;
    node *next;
};

typedef node *record_list;

int cmp(const record *pp, const record *qq){

    int n = qq->score - pp->score;
    if(n != 0)
        return n;
    n = strcmp(pp->name.last, qq->name.last);
    if (n != 0)
        return n;
    n = strcmp(pp->name.first,qq->name.first);
    if (n != 0)
        return n;
    return strcmp(pp->id, qq->id);
}

void list_init(record_list *plist){
    *plist = NULL;
}


void list_clear(record_list *plist){
    node *p;
    node *q;

    for(p = *plist; p != 0; p = q){
        q = p->next;
        free(p);
    }
    *plist = NULL;
}

int list_insert(record_list *plist, const record *prec){

    node **tracer;
    node *newnode = malloc(sizeof(node));

    if(newnode == 0){
        return 0;
    }

    for(tracer = plist; *tracer != 0; tracer = &(*tracer)->next){
        if(cmp(&((*tracer)->data), prec) > 0 )
            break;

    }
    newnode->data.score = prec->score;
    strcpy(newnode->data.name.last, prec->name.last);
    strcpy(newnode->data.name.first, prec->name.first);
    strcpy(newnode->data.id, prec->id);

    newnode->next = *tracer;
    *tracer = newnode;

    return 1;

}

int main(void){

    record newRecord;
    record_list rList;
    node *p;

    list_init(&rList);


    while(scanf("%s %s %s %d\n", newRecord.id, newRecord.name.last, newRecord.name.first, &newRecord.score) == 4){

        list_insert(&rList, &newRecord);
    }

    for(p = rList; p != 0; p = p->next){
        printf("%d %s %s %s\n", p->data.score, p->data.name.last, p->data.name.first, p->data.id );
    }

    list_clear(&rList);
}





