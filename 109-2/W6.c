/* probID: W6-DoublyLinkedList */

#include<stdio.h>
#include<stdlib.h>

typedef struct nd node;
struct nd
{
    int value;
    node *NEXT, *PREV;
};

node *list_iterate(node *POS, int k){
    if(POS == NULL) return NULL;

    if(k == 0) return POS;

    if(k > 0){
        if(POS -> NEXT == NULL) return NULL;
        return list_iterate(POS -> NEXT, k - 1);
    }

    if(k < 0){
        if(POS -> PREV == NULL) return NULL;
        return list_iterate(POS -> PREV, k + 1);
    }
}

node *list_search(node *POS, int val){
    if(POS == NULL) return NULL;

    if(POS -> value == val) return POS;

    if(POS -> NEXT == NULL) return NULL;

    return list_search(POS -> NEXT, val);
}

node *list_insert_before(node *HEAD, node *POS, int val){
    node *rec;
    rec = (node*) malloc(sizeof(node));

    if(POS == NULL){
        rec -> value = val;
        rec -> PREV = NULL;
        rec -> NEXT = NULL;
        return rec;
    }

    if(POS -> PREV == NULL){
        rec -> value = val;
        rec -> PREV = NULL;
        rec -> NEXT = POS;
        POS -> PREV = rec;
        return rec;
    }

    node *prev = POS -> PREV;
    rec -> value = val;
    rec -> PREV = prev;
    rec -> NEXT = POS;
    POS -> PREV = rec;
    prev -> NEXT = rec;
    return HEAD;
}

node *list_insert_after(node *HEAD, node *POS, int val){
    node *rec;
    rec = (node*) malloc(sizeof(node));

    if(POS == NULL){
        rec -> value = val;
        rec -> PREV = NULL;
        rec -> NEXT = NULL;
        return rec;
    }

    if(POS -> NEXT == NULL){
        rec -> value = val;
        rec -> PREV = POS;
        rec -> NEXT = NULL;
        POS -> NEXT = rec;
        return HEAD;
    }
    
    node *next = POS -> NEXT;
    rec -> value = val;
    rec -> PREV = POS;
    rec -> NEXT = next;
    POS -> NEXT = rec;
    next -> PREV = rec;
    return HEAD;
}

node *list_delete(node *HEAD, node *POS){
    if(POS == NULL) return HEAD;
    if(POS -> NEXT == NULL){
        node *prev = POS -> PREV;
        prev -> NEXT = NULL;
        return HEAD;
    }

    if(POS -> PREV == NULL){
        node *next = POS -> NEXT;
        next -> PREV = NULL;
        return next;
    }

    node *next = POS -> NEXT;
    node *prev = POS -> PREV;

    prev -> NEXT = next;
    next -> PREV = prev;
    return HEAD;
}
