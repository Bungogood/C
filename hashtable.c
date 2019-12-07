#include <stdio.h>
#include <stdlib.h>

typedef struct hashtable {
    struct hnode** arr;
    int size;
} hashtable;

typedef struct hnode {
    struct hnode* next;
    void* key;
    void* data;
} hnode;

int hash(void* key, int n) {
    return ((int)key*2654435761) % n;
}

void add(hashtable* h, void* key, void* data) {
    int i = hash(key, h->size);
    hnode* tmp = (hnode*)malloc(sizeof(hnode));
    tmp->data = data;
    tmp->key = key;
    tmp->next = h->arr[i];
    h->arr[i] = tmp;
}

void del(hashtable* h, void* key) {
    int i = hash(&key, h->size);
    hnode* tmp = h->arr[i];
    hnode* prev = NULL;
    while (tmp->key != key && tmp->next != NULL) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp->key == key) {
        if (prev) {
            prev->next = tmp->next;
        } else {
            h->arr[i] = tmp->next;
        }
        free(tmp);
        printf("ok\n");
    }
}

void* get(hashtable* h, void* key) {
    int i = hash(&key, h->size);
    hnode* tmp = h->arr[i];
    while (tmp != NULL) {
        if (tmp->key == key) {
            return tmp->data;
        }
        tmp = tmp->next;
    }
    return NULL;
}

hashtable* create(int size) {
    hashtable* tmp = (hashtable*)malloc(sizeof(hashtable));
    tmp->arr = (hnode**)malloc(sizeof(hnode*)*size);
    for (int i=0; i<size; i++) {
        tmp->arr[i] = NULL;
    }
    tmp->size = size;
    return tmp;
}

void destory(hashtable* h) {
    for (int i=0; i<h->size; i++) {
        hnode* tmp = h->arr[i];
        hnode* del;
        while (tmp != NULL) {
            del = tmp;
            tmp = tmp->next;
            free(del);
        }
    }
    free(&h->size);
    free(h);
}

int main(int argc, char* argv[]) {
    hashtable* h = create(1);
    int a = 0;
    int b = 1;
    int c = 2;
    add(h, &a, &b);
    add(h, &b, &c);
    printf("%c: %d\n", 'a', *(int*)get(h, &a));
    printf("%c: %d\n", 'b', *(int*)get(h, &b));
    destory(h);
    printf("end");
    return 0;
}