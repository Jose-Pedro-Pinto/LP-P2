#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "priorityQueue.h"


typedef struct {

	PRIORITY_QUEUE *q;
	int numeroCaixa;
	int instantePronta;
	int numTotalClientesAtendidos;
	int numTotalProdutosProcessados;
	int numTotalEspera;
	int produtosPorTempo;

} *CAIXAP;


CAIXAP initP(int nb_cx, int numero);

void muda_info_caixaP(CAIXAP c, int valor);

void aumenta_clientes_atendidosP(CAIXAP c);

void muda_info_produtosP(CAIXAP c, int produtos);

void muda_info_t_esperaP(CAIXAP c, int t);

PRIORITY_QUEUE *fila_caixaP(CAIXAP c);

int num_caixaP(CAIXAP c);

int info_caixaP(CAIXAP c);

int clientes_atendidosP(CAIXAP c);

int info_produtosP(CAIXAP c);

int info_t_esperaP(CAIXAP c);

int produtos_processados_cicloP(CAIXAP c);

void printCaixaP(CAIXAP c);