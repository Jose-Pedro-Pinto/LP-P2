#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"


CLIENTE init(int items, int entrada) {
	CLIENTE c = (CLIENTE)malloc(sizeof(CLIENTE));
	c->numeroCompras = items;
	c->instanteEntradaFila = entrada;
	return c;
}

int artigos(CLIENTE cliente) {
	return cliente->numeroCompras;
}

int tempo_entrada(CLIENTE cliente) {
	return cliente->instanteEntradaFila;
}

void printCliente(CLIENTE cliente) {
	printf("[%d:%d] ", cliente->numeroCompras,
						    cliente->instanteEntradaFila);
}

