#include <stdio.h>
#include <stdlib.h>
#include "caixaP.h"

//O número da caixa;
//O instante a partir do qual a caixa está pronta para atender um cliente na fila.
//O número total de clientes que foi atendido pela caixa.
//O número total de produtos processados pela caixa.
//O tempo total de espera.
//O número de produtos que a caixa processa por unidade de tempo-


CAIXAP initP(int nb_cx, int numero) {

	CAIXAP c = (CAIXAP)malloc(sizeof(CLIENTE));;
	PRIORITY_QUEUE *q = mk_empty_queueP(10);
	c->q = q;
	c->numeroCaixa = numero;
	c->instantePronta = 0;
	c->numTotalClientesAtendidos = 0;
	c->numTotalProdutosProcessados = 0;
	c->numTotalEspera = 0;
	c->produtosPorTempo = (((double) rand() / (RAND_MAX)) * 5) + 1;
	return c;

}

void muda_info_caixaP(CAIXAP c, int valor) {
	c->instantePronta = valor;
}

void aumenta_clientes_atendidosP(CAIXAP c) {
	c->numTotalClientesAtendidos++;
}

void muda_info_produtosP(CAIXAP c, int produtos) {
	c->numTotalProdutosProcessados += produtos;
}


void muda_info_t_esperaP(CAIXAP c, int t) {
	c->numTotalEspera += t;
}

PRIORITY_QUEUE *fila_caixaP(CAIXAP c) {
	return c->q;
}

int num_caixaP(CAIXAP c) {
	return c->numeroCaixa;
}

int info_caixaP(CAIXAP c) {
	return c->instantePronta;
}

int clientes_atendidosP(CAIXAP c) {
	return c->numTotalClientesAtendidos;
}

int info_produtosP(CAIXAP c) {
	return c->numTotalProdutosProcessados;
}

int info_t_esperaP(CAIXAP c) {
	return c->numTotalEspera;
}

int produtos_processados_cicloP(CAIXAP c) {
	return c->produtosPorTempo;
}

void printCaixaP(CAIXAP c) {
	printf("Caixa prioritaria %d (%d): ", c->numeroCaixa, c->instantePronta);
	printQueueP(c->q, (void(*)(void *))printCliente);
}