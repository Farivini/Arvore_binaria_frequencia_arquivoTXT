#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <algorithm>
#include <iostream>

// Crio uma struct para o nó interno
typedef struct no_interno dentro_no;
struct no_interno
{
	int linha;
	int freq;
	dentro_no* proximo;
};

//Criamos a arvore
struct arvore {
	char* palavra;				// seta a palavra
	int numero_linhas;			// verifica numero de linhas
	dentro_no* in_nodeptr;
	dentro_no* atual;			// verufca atual
	struct arvore* direita;		// Seta pra direita
	struct arvore* esquerda;	// Indica pra esquerda
};
typedef struct arvore* arvoreptr;

//Entrada da Arvore binaria de busca

void entrada_bst(arvoreptr* raiz,char* palavra, int linha)		// verifica entrada da arvore ,separa pra esquerda e direita conforme regra
{
	if ((*raiz) == NULL) {
		(*raiz) = (arvoreptr)malloc(sizeof(struct arvore));
		(*raiz)->palavra = (char*)malloc(50*sizeof(char));
		strcpy(((*raiz)->palavra), palavra);

		(*raiz)->numero_linhas = 1;
		(*raiz)->direita = NULL;
		(*raiz)->esquerda = NULL;
		(*raiz)->in_nodeptr = (dentro_no*)malloc(sizeof(dentro_no));
		(*raiz)->in_nodeptr->linha = linha;
		(*raiz)->in_nodeptr->freq = 1;
		(*raiz)->in_nodeptr->proximo = NULL;
		(*raiz)->atual = (*raiz)->in_nodeptr;
	}
	else {
		int checa = strcmp(((*raiz)->palavra), palavra);
		if (checa > 0)entrada_bst(&((*raiz)->esquerda), palavra, linha);
		else if (checa < 0) entrada_bst(&((*raiz)->direita), palavra, linha);
		else {
			if ((*raiz)->atual->linha == linha)(*raiz)->atual->freq++;
			else {
				(*raiz)->atual->proximo = (dentro_no*)malloc(sizeof(dentro_no));
				(*raiz)->atual->proximo->linha = linha;
				(*raiz)->atual->proximo->freq = 1;
				(*raiz)->atual->proximo->proximo = NULL;
			}
		}
	}
}



// mostra a palavra e quantas vezes ela aparece
void mostra_lista(no_interno* in_nodeptr) {
	while (in_nodeptr != NULL) {		// se no interno for diferente de nulo , significa que ate o final do arquivo
		printf("arquivo %d com frequencia %d ; ", in_nodeptr->linha, in_nodeptr->freq);
		in_nodeptr = in_nodeptr->proximo;
	}

}
//	Mostra a arvore

void mostra_arvore(arvoreptr raiz) {
	if (raiz != NULL)					// Se a raiz nao for nula 
	{
		printf("%s: ", raiz->palavra);	//printa raiz e a palavra
		mostra_lista(raiz->in_nodeptr);
		printf("\n");
		mostra_arvore(raiz->direita);
		mostra_arvore(raiz->esquerda);

	}
}



// Duas funções para livrar e liberar a memoria com a função free
void lista_livre(no_interno* in_nodeptr) {
	if (in_nodeptr != NULL) {
		free(in_nodeptr);
	}
}
void bst_livre(arvoreptr raiz) {
	if (raiz != NULL) {
		bst_livre(raiz->direita);
		bst_livre(raiz->esquerda);
		lista_livre(raiz->in_nodeptr);
		// Uso da função free para liberar a memoria faz o alocamento com malloc e free pra liberar
		free(raiz->palavra);
		free(raiz);
	}
}


//Funçao principal do programa

int main(int argc, char* argv[]) {



/* 
A partir daqui eu faço a inserção do que tem
no arquivo na minha arvore.

com laço de repetição while
letra por letra e quando for espaço ele vverifica
*/
	arvoreptr raiz = NULL;
	FILE *fp = fopen("arquivo.txt","r");
	char palavra[50], carac;
	int tamanho = 0, linhas=1;
	if (fp == NULL) {
		fprintf(stderr, "Erro de leitura do arquivo. \n");
		exit(1);
	}
	while ((carac = getc(fp)) != EOF) {
		if (carac == 'n') {
			palavra[tamanho] = '\0';
			if (tamanho > 0) entrada_bst(&raiz, palavra, linhas);
			tamanho = 0;
			linhas++;
		}
		else if (carac == ' ') {
			palavra[tamanho] = '\0';
			if (tamanho > 0) entrada_bst(&raiz, palavra, linhas);
			tamanho= 0;

		}
		else if (isalpha(carac)) {
			palavra[tamanho] = carac;
			tamanho++;

		}
	}
	if (tamanho > 0) {
		palavra[tamanho] = '\0';
		entrada_bst(&raiz, palavra, linhas);
	}

	mostra_arvore(raiz);
	
	bst_livre(raiz);
	fclose(fp);
	return 0;
		
}
