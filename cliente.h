#include <stdio.h>
#include <stdlib.h>

#ifndef Cliente
#define Cliente
typedef struct {
	int numeroCompras;
	int instanteEntradaFila;
} *CLIENTE;


CLIENTE init(int numeroCompras, int instanteEntradaFila);


int artigos(CLIENTE cliente);

int tempo_entrada(CLIENTE cliente);

void printCliente(CLIENTE cliente);
#endif