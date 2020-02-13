#include <stdio.h>
#include <stdlib.h>
#ifndef BOOLEAN
#define BOOLEAN

typedef enum {FALSE,TRUE} BOOL;
#endif

typedef struct filap {
  int inicioU, inicioN, fimU, fimN, nmax;
  void** urgente;
  void** normal;
} PRIORITY_QUEUE;

// criar fila com capacidade para n inteiros
PRIORITY_QUEUE *mk_empty_queueP(int n);
// colocar valor na fila
void enqueueP(void* v,PRIORITY_QUEUE *f, BOOL priority);
// retirar valor na fila
void* dequeueP(PRIORITY_QUEUE *f);
// peek valor na fila
void* peekP(PRIORITY_QUEUE *f);
// verificar se a fila está vazia
BOOL queue_is_emptyP(PRIORITY_QUEUE *f);
// verificar se a fila urgente está vazia
BOOL urgent_is_emptyP(PRIORITY_QUEUE *q);
// verificar se a fila normal está vazia
BOOL normal_is_emptyP(PRIORITY_QUEUE *q);
// verificar se a fila não admite mais elementos
BOOL queue_is_fullP(PRIORITY_QUEUE *f);
// liberta fila
void free_queueP(PRIORITY_QUEUE *f);
// retorna comprimento
int sizequeueP(PRIORITY_QUEUE *f);
// passar queue to array
void** queuetoarrayP(PRIORITY_QUEUE *f, void* (clone)(void*));
// verificar se as duas filas são iguais
BOOL equal_queuesP(PRIORITY_QUEUE *f, PRIORITY_QUEUE *f2, BOOL(*equals)(void*, void*));
// imprimir fila
void printQueueP(PRIORITY_QUEUE *f, void (print)(void*));