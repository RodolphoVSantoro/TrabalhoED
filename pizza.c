#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "pizza.h"

Pizza *cria_pizza(int cod, float preco, char nome[51], char categoria[21]){
	Pizza *p = (Pizza*)malloc(sizeof(Pizza));
	p->cod=cod;
	setPizza(p, preco, nome, categoria);
	return p;
}

void setPizza(Pizza *p, float preco, char nome[51], char categoria[21]){
	p->preco=preco;
	strcpy(p->nome, nome);
	strcpy(p->categoria, categoria);
}

void insereNaCategoria(const char* nomeArv, int id, char categoria[21]){
	char fname[2048];
	sprintf(fname, "%s/%s", nomeArv, categoria);
	FILE *arq = fopen(fname, "rb");
	int cod=INT_MIN;
	if(arq){
		while(!feof(arq)){
			fread(&cod, sizeof(int), 1, arq);
			if(id==cod)break;
		}
		fclose(arq);
	}
	if(id==cod) return;
	arq = fopen(fname, "ab");
	fwrite(&id, sizeof(int), 1, arq);
	fclose(arq);
}

void retiraDaCategoria(const char* nomeArv, int id, char categoria[21]){
	char fname[2048];
	sprintf(fname, "%s/%s", nomeArv, categoria);
	FILE *arq = fopen(fname, "rb+");
	int k, s, i=0;
	fseek(arq, -1, SEEK_END);
	fread(&s, sizeof(int), 1, arq);
	rewind(arq);
	fread(&k, sizeof(int), k, arq);
	while(k!=id && !feof(arq)){
		fread(&k, sizeof(int), k, arq);
		i++;
	}
	if(feof(arq))return;
	fseek(arq, i*sizeof(int), SEEK_SET);
	fwrite(&s, sizeof(int), 1, arq);
	fseek(arq, -1, SEEK_END);
	s = EOF;
	fwrite(&s, sizeof(int), 1, arq);
	fclose(arq);
}

void imprimeCategoria(const char* nomeArv, char categoria[21]){
	char fname[2048];
	sprintf(fname, "%s/%s", nomeArv, categoria);
	FILE *arq = fopen(fname, "rb");
	int cod;
	if(arq){
		fread(&cod, sizeof(int), 1, arq);
		while(!feof(arq)){
			printf("%d\n", cod);
			fread(&cod, sizeof(int), 1, arq);
		}
		fclose(arq);
	}
	else printf("Nao existe a categoria %s na arvore %s\n", categoria, nomeArv);
}

void imprime_pizza(Pizza *p){
	printf("%d, %s(%s), R$: %.2f\n", p->cod, p->nome, p->categoria, p->preco);
}