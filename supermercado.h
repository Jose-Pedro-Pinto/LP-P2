#include <stdio.h>
#include <stdlib.h>
#include "caixa.h"
#include "caixaP.h"

void simula_supermercado(int afluencia, int apetencia, int n_caixasN , int n_caixasP, int ciclos);

void trata_clientes(int tempo, CAIXA caixasN[], CAIXAP caixasP[], int n_caixasN, int n_caixasP);

void processa_resultados(CAIXA caixasN[], CAIXAP caixasP[], int n_caixasN, int n_caixasP);

void mostra_caixas(CAIXA caixasN[], CAIXAP caixasP[], int n_caixasN, int n_caixasP);

BOOL existem_caixas_com_fila(CAIXA caixasN[], CAIXAP caixasP[], int n_caixasN, int n_caixasP);