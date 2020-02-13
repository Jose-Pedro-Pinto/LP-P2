#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "queue.h"


typedef struct {

	QUEUE *q;
	int numeroCaixa;
	int instantePronta;
	int numTotalClientesAtendidos;
	int numTotalProdutosProcessados;
	int numTotalEspera;
	int produtosPorTempo;

} *CAIXA;


CAIXA init2(int nb_cx, int numero);

void muda_info_caixa(CAIXA c, int valor);

void aumenta_clientes_atendidos(CAIXA c);

void muda_info_produtos(CAIXA c, int produtos);

void muda_info_t_espera(CAIXA c, int t);

QUEUE *fila_caixa(CAIXA c);

int num_caixa(CAIXA c);

int info_caixa(CAIXA c);

int clientes_atendidos(CAIXA c);

int info_produtos(CAIXA c);

int info_t_espera(CAIXA c);

int produtos_processados_ciclo(CAIXA c);

void printCaixa(CAIXA c);