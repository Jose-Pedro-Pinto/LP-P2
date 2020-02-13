#include <stdio.h>
#include <stdlib.h>
#include "caixa.h"

//O número da caixa;
//O instante a partir do qual a caixa está pronta para atender um cliente na fila.
//O número total de clientes que foi atendido pela caixa.
//O número total de produtos processados pela caixa.
//O tempo total de espera.
//O número de produtos que a caixa processa por unidade de tempo-


CAIXA init2(int nb_cx, int numero) {

	CAIXA c = (CAIXA)malloc(sizeof(CLIENTE));;
	QUEUE *q = mk_empty_queue(10);
	c->q = q;
	c->numeroCaixa = numero;
	c->instantePronta = 0;
	c->numTotalClientesAtendidos = 0;
	c->numTotalProdutosProcessados = 0;
	c->numTotalEspera = 0;
	c->produtosPorTempo = (((double) rand() / (RAND_MAX)) * 5) + 1;
	return c;

}

void muda_info_caixa(CAIXA c, int valor) {
	c->instantePronta = valor;
}

void aumenta_clientes_atendidos(CAIXA c) {
	c->numTotalClientesAtendidos++;
}

void muda_info_produtos(CAIXA c, int produtos) {
	c->numTotalProdutosProcessados += produtos;
}


void muda_info_t_espera(CAIXA c, int t) {
	c->numTotalEspera += t;
}

QUEUE *fila_caixa(CAIXA c) {
	return c->q;
}

int num_caixa(CAIXA c) {
	return c->numeroCaixa;
}

int info_caixa(CAIXA c) {
	return c->instantePronta;
}

int clientes_atendidos(CAIXA c) {
	return c->numTotalClientesAtendidos;
}

int info_produtos(CAIXA c) {
	return c->numTotalProdutosProcessados;
}

int info_t_espera(CAIXA c) {
	return c->numTotalEspera;
}

int produtos_processados_ciclo(CAIXA c) {
	return c->produtosPorTempo;
}

void printCaixa(CAIXA c) {
	printf("Caixa %d (%d): ", c->numeroCaixa, c->instantePronta);
	printQueue(c->q, (void(*)(void *))printCliente);
}