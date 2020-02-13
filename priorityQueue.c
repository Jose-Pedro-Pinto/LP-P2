#include "priorityQueue.h"

static void queue_exit_errorP(char *msg)
{
  fprintf(stderr,"Error: %s.\n",msg);
  exit(EXIT_FAILURE);
}

// criar fila com capacidade para n inteiros
PRIORITY_QUEUE *mk_empty_queueP(int n)
{
  PRIORITY_QUEUE *q = (PRIORITY_QUEUE *) malloc(sizeof(PRIORITY_QUEUE));
  if (q == NULL)
    queue_exit_errorP("sem memoria");

  q -> urgente =  (void *) malloc(sizeof(void *)*n);
  if (q -> urgente == NULL)
    queue_exit_errorP("sem memoria");

  q -> normal =  (void *) malloc(sizeof(void *)*n);
  if (q -> normal == NULL)
    queue_exit_errorP("sem memoria");

  q -> nmax = n;
  q -> inicioU = -1;
  q -> inicioN = -1;
  q -> fimU = 0;
  q -> fimN = 0;
  return q;
}

// libertar fila
void free_queueP(PRIORITY_QUEUE *q)
{
  if (q != NULL) {
    free(q -> urgente);
    free(q -> normal);
    free(q);
  } else
    queue_exit_errorP("fila mal construida");
}

// colocar valor na fila
void enqueueP(void* v, PRIORITY_QUEUE *q,  BOOL priority)
{  
  if (queue_is_fullP(q) == TRUE)
    queue_exit_errorP("fila sem lugar");

  if (q -> urgente == NULL)
    queue_exit_errorP("fila mal construida");

  if (q -> normal == NULL)
    queue_exit_errorP("fila mal construida");

  if (priority == TRUE){
    if (urgent_is_emptyP(q)==TRUE)
      q -> inicioU = q -> fimU; // fila fica com um elemento
    q -> urgente[q->fimU] = v;
    q -> fimU = (q -> fimU+1)%(q->nmax);
  }
  else{
    if (normal_is_emptyP(q)==TRUE)
      q -> inicioN = q -> fimN; // fila fica com um elemento
    q -> normal[q->fimN] = v;
    q -> fimN = (q -> fimN+1)%(q->nmax);
  }
}

// retirar valor na fila
void* dequeueP(PRIORITY_QUEUE *q)
{  
  void* aux;
  if (queue_is_emptyP(q) == TRUE)
    queue_exit_errorP("fila sem valores");

  if (q -> urgente == NULL)
    queue_exit_errorP("fila mal construida");

  if (q -> normal == NULL)
    queue_exit_errorP("fila mal construida");

  if (urgent_is_emptyP(q) == TRUE){
    aux = q ->normal[q -> inicioN];
    q -> inicioN = (q -> inicioN+1)%(q -> nmax);
    if (q-> inicioN == q -> fimN) {  // se só tinha um elemento
      q -> inicioN = -1; q -> fimN = 0;  
    }
    return aux;
  }
  else{
    aux = q ->urgente[q -> inicioU];
    q -> inicioU = (q -> inicioU+1)%(q -> nmax);
    if (q-> inicioU == q -> fimU) {  // se só tinha um elemento
      q -> inicioU = -1; q -> fimU = 0;  
    }
    return aux;
  }
}

// peek valor na fila
void* peekP(PRIORITY_QUEUE *q)
{  
  void* aux;
  if (queue_is_emptyP(q) == TRUE)
    queue_exit_errorP("fila sem valores");

  if (q -> urgente == NULL)
    queue_exit_errorP("fila mal construida");

  if (q -> normal == NULL)
    queue_exit_errorP("fila mal construida");

  if (urgent_is_emptyP(q) == TRUE){
    aux = q ->normal[q -> inicioN];
  }
  else{
    aux = q ->urgente[q -> inicioU];
  }
  return aux;
}

// verificar se a fila está vazia
BOOL queue_is_emptyP(PRIORITY_QUEUE *q)
{
  if (q == NULL)
    queue_exit_errorP("fila mal construida");

  if (q -> inicioU == -1 && q -> inicioN == -1) return TRUE;
  return FALSE;
}

// verificar se a fila urgente está vazia
BOOL urgent_is_emptyP(PRIORITY_QUEUE *q)
{
  if (q == NULL)
    queue_exit_errorP("fila mal construida");

  if (q -> inicioU == -1) return TRUE;
  return FALSE;
}

// verificar se a fila normal está vazia
BOOL normal_is_emptyP(PRIORITY_QUEUE *q)
{
  if (q == NULL)
    queue_exit_errorP("fila mal construida");

  if (q -> inicioN == -1) return TRUE;
  return FALSE;
}

// verificar se a fila não admite mais elementos
BOOL queue_is_fullP(PRIORITY_QUEUE *q)
{
  if (q -> fimU == q -> inicioU || q -> fimN == q -> inicioN) return TRUE;
  return FALSE;
}

int sizequeueP(PRIORITY_QUEUE *q) {
  return q->fimU + q->fimN;
}

void** queuetoarrayP(PRIORITY_QUEUE *q, void* (clone)(void*)) {
  void** lst = (void**) malloc(sizeof(q->inicioU)*(q->fimU+q->fimN));
  int i= 0;
  while (i < q->fimU) {
    lst[i] = clone(q->urgente + i);
    i++;
  }
  while (i < q->fimU+q->fimN-1) {
    lst[i] = clone(q->normal + i);
    i++;
  }
  return lst;
}


BOOL equal_queuesP(PRIORITY_QUEUE *q1, PRIORITY_QUEUE *q2, BOOL (equals)(void*, void*)) {
  int i=0;
  if (q1->fimU != q2->fimU)
    return FALSE;
  if (q1->fimN != q2->fimN)
    return FALSE;
  else {
    for (i=0 ; i< q1->fimU ; i++) {
      if (equals(q1->urgente+i,q2->urgente+i) == FALSE) 
        return FALSE;
    }
    for (i=0 ; i< q1->fimN ; i++) {
      if (equals(q1->normal+i,q2->normal+i) == FALSE) 
        return FALSE;
    }
  }
  return TRUE;
}

void printQueueP(PRIORITY_QUEUE *q, void (print)(void*)) {
  int i=0;
  printf("priority: < ");
  for (i=q->inicioU ; i!=q->fimU && i!=-1 ; i++) {
    print(q->urgente[i]);
  }
  printf("> ");
  printf("normal: < ");
  for (i=q->inicioN ; i!=q->fimN && i!=-1 ; i++) {
    print(q->normal[i]);
  }
  printf(">\n");
}

void upPriorityP(PRIORITY_QUEUE *q){
  if (q == NULL)
    queue_exit_errorP("fila mal construida");

  if (normal_is_emptyP(q) == TRUE)
    queue_exit_errorP("nenhum elemento com prioridade normal");
  
  if (q -> normal == NULL)
    queue_exit_errorP("fila mal construida");

  void* aux = q ->normal[q -> inicioN];
  q -> inicioN = (q -> inicioN+1)%(q -> nmax);
  if (q-> inicioN == q -> fimN) {  // se só tinha um elemento
    q -> inicioN = -1; q -> fimN = 0;  
  }
  enqueueP(aux, q, TRUE);
}