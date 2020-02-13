#include <stdio.h>
#include <stdlib.h>
#ifndef BOOLEAN
#define BOOLEAN
typedef enum {FALSE,TRUE} BOOL;
#endif

typedef struct fila {
  int inicio, fim, nmax;
  void** queue;
} QUEUE;


// criar fila com capacidade para n inteiros
QUEUE *mk_empty_queue(int n);
// colocar valor na fila
void enqueue(void* v,QUEUE *f);
// retirar valor na fila
void* dequeue(QUEUE *f);
// peek valor na fila
void* peek(QUEUE *f);
// verificar se a fila está vazia
BOOL queue_is_empty(QUEUE *f);
// verificar se a fila não admite mais elementos
BOOL queue_is_full(QUEUE *f);
// liberta fila
void free_queue(QUEUE *f);
// retorna comprimento
int sizequeue(QUEUE *f);
// passar queue to array
void** queuetoarray(QUEUE *f, void* (clone)(void*));
// verificar se as duas filas são iguais
BOOL equal_queues(QUEUE *f, QUEUE *f2, BOOL(*equals)(void*, void*));
// imprimir fila
void printQueue(QUEUE *f, void (print)(void*));