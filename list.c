#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {

  List* lista = (List*) malloc (1*sizeof(List));

  lista->head = NULL;
  lista->tail = NULL;
  lista->current = NULL;
  
     return lista;
}

void * firstList(List * list) {

  if (list != NULL && list->head != NULL){
    return list->head->data;
  }
  else{
    return NULL;
  }
}

void * nextList(List * list) {

  if (list->current != NULL && list->current->next != NULL){
    list->current = list->current->next;
    
    return list->current->data;
  }
  else{
    return NULL;
  }
}

void * lastList(List * list) {

  while(list->current->next != NULL){
    list->current = list->current->next;
  }
    return list->current->data;
}

void * prevList(List * list) {
  
  if (list->current != NULL && list->current->prev != NULL){
    list->current = list->current->prev;

    return list->current->data;
  }
  else{
    return NULL;
  }
}

void pushFront(List * list, void * data) {
  Node* nuevoNodo = createNode(data);

  if (list->head == NULL){
    list->head = nuevoNodo;
    list->tail = nuevoNodo;
  }
  else{
    nuevoNodo->next = list->head;
    list->head->prev = nuevoNodo;
    list->head = nuevoNodo;
  }
  
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node* nuevoNodo = createNode(data);

  if (list->current == NULL){
    list->current = nuevoNodo;
    list->head = nuevoNodo;
    list->tail = nuevoNodo;
  }
  else{
    list->current->next = nuevoNodo;
    nuevoNodo->prev = list->current;

    if (list->current->next->next != NULL){
      nuevoNodo->next = list->current->next->next;
      nuevoNodo->next->prev = nuevoNodo;
    }
    else{
      list->tail = nuevoNodo;
    }
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {

  if (list->current == NULL){
    return NULL;
  }
  else{
    Node* nodoEliminar = list->current;
    
    if (list->current->next != NULL){
      list->current->next->prev = list->current->prev;
    }
    else{
      list->tail = list->current->prev;
    }

    if (list->current->prev != NULL){
      list->current->prev->next = list->current->next;
    }
    else{
      list->head = list->current->next;
    }

    void* datoEliminar = nodoEliminar->data;
    free(nodoEliminar);
    return datoEliminar;
  }
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}