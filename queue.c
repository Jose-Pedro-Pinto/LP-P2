#include "queue.h"


static void queue_exit_error(char *msg);

static void queue_exit_error(char *msg)
{
  fprintf(stderr,"Error: %s.\n",msg);
  exit(EXIT_FAILURE);
}




// criar fila com capacidade para n inteiros
QUEUE *mk_empty_queue(int n)
{
  QUEUE *q = (QUEUE *) malloc(sizeof(QUEUE));
  if (q == NULL)
    queue_exit_error("sem memoria");

  q -> queue =  (void *) malloc(sizeof(void *)*n);
  if (q -> queue == NULL)
    queue_exit_error("sem memoria");

  q -> nmax = n;
  q -> inicio = -1;
  q -> fim = 0;
  return q;
}

// libertar fila
void free_queue(QUEUE *q)
{
  if (q != NULL) {
    free(q -> queue);
    free(q);
  } else
    queue_exit_error("fila mal construida");
}



// colocar valor na fila
void enqueue(void* v,QUEUE *q)
{  
  if (queue_is_full(q) == TRUE)
    queue_exit_error("fila sem lugar");

  if (q -> queue == NULL)
    queue_exit_error("fila mal construida");

  if (queue_is_empty(q)==TRUE)
    q -> inicio = q -> fim; // fila fica com um elemento
  q -> queue[q->fim] = v;
  q -> fim = (q -> fim+1)%(q->nmax);
}

void* peek(QUEUE *q)
{  
  void* aux;
  if (queue_is_empty(q) == TRUE)
    queue_exit_error("fila sem valores");

  if (q -> queue == NULL)
    queue_exit_error("fila mal construida");

  aux = q ->queue[q -> inicio];

  return aux;
}


// retirar valor na fila
void* dequeue(QUEUE *q)
{  
  void* aux;
  if (queue_is_empty(q) == TRUE)
    queue_exit_error("fila sem valores");

  if (q -> queue == NULL)
    queue_exit_error("fila mal construida");

  aux = q ->queue[q -> inicio];
  q -> inicio = (q -> inicio+1)%(q -> nmax);
  if (q-> inicio == q -> fim) {  // se só tinha um elemento
    q -> inicio = -1; q -> fim = 0;  
  }
  return aux;
}

// verificar se a fila está vazia
BOOL queue_is_empty(QUEUE *q)
{
  if (q == NULL)
    queue_exit_error("fila mal construida");

  if (q -> inicio == -1) return TRUE;
  return FALSE;
}

// verificar se a fila não admite mais elementos
BOOL queue_is_full(QUEUE *q)
{
  if (q == NULL)
    queue_exit_error("fila mal construida");

  if (q -> fim == q -> inicio) return TRUE;
  return FALSE;
}


int sizequeue(QUEUE *q) {
  return q->fim;
}


void** queuetoarray(QUEUE *q, void* (clone)(void*)) {

  //int lst[q->fim];
  void** lst =  (void**) malloc(sizeof(q->inicio)*(q->fim));
  int i= 0;
  while (i < q->fim) {
    lst[i] = clone(q->queue + i);
    i++;
  }
  return lst;

}


BOOL equal_queues(QUEUE *q1, QUEUE *q2, BOOL (equals)(void*, void*)) {
  int i=0;
  if (q1->fim != q2->fim)
    return FALSE;
  else {
    for (i=0 ; i< q1->fim ; i++) {
      if (equals(q1->queue+i,q2->queue+i) == FALSE) 
        return FALSE;
    }
  }
  return TRUE;
}

void printQueue(QUEUE *q, void (print)(void*)) {
  int i;
  printf("< ");
  for (i=q->inicio ; i!=q->fim && i!=-1 ; i++) {
    print(q->queue[i]);
  }
  printf(">\n");
}