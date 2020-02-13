#include "supermercado.h"



void trata_clientes(int tempo, CAIXA caixasN[], CAIXAP caixasP[], int n_caixasN, int n_caixasP) {
	int i;
	int nb_artigos;
	int t_atendimento;
	double artigos_prcds;
	int t_entrada;
	int t_espera;
	int t_entrada_fila;
	CAIXA cx;
	CAIXAP cxp;
	for(i=0; i<n_caixasP; i++) {
		cxp = caixasP[i];
		if (queue_is_emptyP(fila_caixaP(cxp)) == FALSE) {
			//se a fila associada à caixa não é vazia
			//verifica se o atendimento ao cliente terminou
			CLIENTE cliente = (CLIENTE)(peekP(fila_caixaP(cxp)));
			nb_artigos = artigos(cliente);
			t_atendimento = tempo - info_caixaP(cxp);
			artigos_prcds = (double)nb_artigos/(double)produtos_processados_cicloP(cxp);
			if (artigos_prcds <= t_atendimento) {
				//o cliente sai da fila da caixa
				t_entrada_fila = tempo_entrada(cliente);
				t_espera = tempo - t_entrada_fila;
				printf("--> Processado cliente com %d artigos na caixa prioritaria %d com tempo de espera %d\n", nb_artigos, num_caixaP(cxp), t_espera);
				muda_info_caixaP(cxp, tempo);
				aumenta_clientes_atendidosP(cxp);
				muda_info_produtosP(cxp, nb_artigos);
				muda_info_t_esperaP(cxp, t_espera);
				dequeueP(fila_caixaP(cxp)); //o cliente sai da fila
			}
		}
		else {
			//para as caixas vazias actualiza o tempo potencial para atendimento
			muda_info_caixaP(cxp, tempo);
		}
	}
	for(i=0; i<n_caixasN; i++) {
		cx = caixasN[i];
		if (queue_is_empty(fila_caixa(cx)) == FALSE) {
			//se a fila associada à caixa não é vazia
			//verifica se o atendimento ao cliente terminou
			CLIENTE cliente = (CLIENTE)(peek(fila_caixa(cx)));
			nb_artigos = artigos(cliente);
			t_atendimento = tempo - info_caixa(cx);
			artigos_prcds = (double)nb_artigos/(double)produtos_processados_ciclo(cx);
			if (artigos_prcds <= t_atendimento) {
				//o cliente sai da fila da caixa
				t_entrada_fila = tempo_entrada(cliente);
				t_espera = tempo - t_entrada_fila;
				printf("--> Processado cliente com %d artigos na caixa %d com tempo de espera %d\n", nb_artigos, num_caixa(cx), t_espera);
				muda_info_caixa(cx, tempo);
				aumenta_clientes_atendidos(cx);
				muda_info_produtos(cx, nb_artigos);
				muda_info_t_espera(cx, t_espera);
				dequeue(fila_caixa(cx)); //o cliente sai da fila
			}
		}
		else {
			//para as caixas vazias actualiza o tempo potencial para atendimento
			muda_info_caixa(cx, tempo);
		}
	}
}

void processa_resultados(CAIXA caixasN[], CAIXAP caixasP[], int n_caixasN, int n_caixasP) {
	int i;
	int c_t;
	CAIXA cx;
	CAIXAP cxp;	
	for (i=0; i<n_caixasP; i++) {
		cxp = caixasP[i];
		c_t = clientes_atendidosP(cxp);
		if (c_t != 0) {
			printf("\nCaixa Prioritaria %d (atendimento %d produtos por ciclo):\n", num_caixaP(cxp), produtos_processados_cicloP(cxp));
			printf("%d clientes atendidos, media produtos/cliente %d\n" , c_t, info_produtosP(cxp)/c_t);
			printf("tempo medio de espera %d \n", info_t_esperaP(cxp)/c_t);    
		}
		
		else {
			printf("\nCaixa %d nao atendeu clientes\n", num_caixaP(cxp));
		}
	}
	for (i=0; i<n_caixasN; i++) {
		cx = caixasN[i];
		c_t = clientes_atendidos(cx);
		if (c_t != 0) {
			printf("\nCaixa %d (atendimento %d produtos por ciclo):\n", num_caixa(cx), produtos_processados_ciclo(cx));
			printf("%d clientes atendidos, media produtos/cliente %d\n" , c_t, info_produtos(cx)/c_t);
			printf("tempo medio de espera %d \n", info_t_espera(cx)/c_t);    
		}
		
		else {
			printf("\nCaixa %d nao atendeu clientes\n", num_caixa(cx));
		}
	}
}

void mostra_caixas(CAIXA caixasN[], CAIXAP caixasP[], int n_caixasN, int n_caixasP) {
	int i;
	for(i=0; i<n_caixasP;i++)
		printCaixaP(caixasP[i]);
	for(i=0; i<n_caixasN;i++)
		printCaixa(caixasN[i]);
}

BOOL existem_caixas_com_fila(CAIXA caixasN[], CAIXAP caixasP[], int n_caixasN, int n_caixasP) {
	int i;
	for(i=0; i<n_caixasN; i++) {
		if(queue_is_empty(fila_caixa(caixasN[i])) == FALSE)
			return TRUE;
	}
	for(i=0; i<n_caixasP; i++) {
		if(queue_is_emptyP(fila_caixaP(caixasP[i])) == FALSE)
			return TRUE;
	}
	return FALSE;
	
}


void simula_supermercado(int afluencia, int apetencia, int n_caixasN, int n_caixasP, int ciclos) {
 	int i, j;
 	double aleatorio;
 	double limiar;
 	int num_compras;
 	CLIENTE c;
 	CAIXA cx;
	CAIXAP cxp;	
	CAIXA caixasN[n_caixasN];
	CAIXAP caixasP[n_caixasP];
	for(i=0; i<n_caixasN; i++)
		caixasN[i] = init2(n_caixasN, i);

	for(i=0; i<n_caixasP; i++)
		caixasP[i] = initP(n_caixasP, i);

	for(i=1; i<ciclos+1; i++) {

		printf("== CICLO ==  %d\n", i);

		//processa os clientes nas caixas
		trata_clientes(i, caixasN, caixasP, n_caixasN, n_caixasP);

		//decide a criação de novo cliente e número de compras
		aleatorio = ((double) rand() / (RAND_MAX));
		limiar = (double)afluencia/100;

		if(aleatorio < limiar) { //um novo cliente é criado
			num_compras = ((((double) rand() / (RAND_MAX))) * 3 * apetencia) + 1;
			printf("--> Criado cliente com %d artigos.\n", num_compras);
			c = init(num_compras, i);

			//insere o cliente na fila de uma caixa com o minimo de clientes
			int minN=sizequeue(fila_caixa(caixasN[0]));
			int np_cx=0;	
			for (j=1;j<n_caixasN;j++){
				if (minN > sizequeue(fila_caixa(caixasN[j]))){
					minN = sizequeue(fila_caixa(caixasN[j]));
					np_cx=j;
				}
			}
			int minP=sizequeueP(fila_caixaP(caixasP[0]));
			int np_cxP=0;	
			for (j=1;j<n_caixasP;j++){
				if (minP > sizequeueP(fila_caixaP(caixasP[j]))){
					minP = sizequeueP(fila_caixaP(caixasP[j]));
					np_cxP=j;
				}
			}
			if (minP <= minN){
				cxp = caixasP[np_cxP];
				BOOL priority = num_compras <= 10 ? TRUE : FALSE;
				enqueueP(c, fila_caixaP(cxp), priority);
			}
			else{
				cx = caixasN[np_cx];
				enqueue(c, fila_caixa(cx));
			}
		}
		mostra_caixas(caixasN, caixasP, n_caixasN, n_caixasP);
	}

	//processa as filas depois do fecho de entradas
	i = ciclos + 1;
	printf("Entradas fechadas\n");
	while (existem_caixas_com_fila(caixasN, caixasP, n_caixasN, n_caixasP)) {
		printf(" == CICLO == %d\n", i);
		//processa os clientes nas caixas
		trata_clientes(i, caixasN, caixasP, n_caixasN, n_caixasP);
		mostra_caixas(caixasN, caixasP, n_caixasN, n_caixasP);
		i = i+1;
	}
	processa_resultados(caixasN, caixasP, n_caixasN, n_caixasP);

}

void main() {
	int afluencia, apetencia, n_caixasN, n_caixasP, ciclos;
	printf("Valor de afluencia?\n");
	scanf("%d",&afluencia);
	printf("Valor de apetencia?\n");
	scanf("%d",&apetencia);
	printf("Numero de caixas normais?\n");
	scanf("%d",&n_caixasN);
	printf("Numero de caixas prioritarias (ate 10 produtos passa a frente)?\n");
	scanf("%d",&n_caixasP);
	printf("Numero de ciclos aberto?\n");
	scanf("%d",&ciclos);
	simula_supermercado(afluencia, apetencia, n_caixasN, n_caixasP, ciclos);
}