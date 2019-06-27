#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

void insereNaCategoria(int id, char categoria[21]){
	FILE *arq = fopen(categoria, "ab");
	fwrite(&id, sizeof(int), 1, arq);
	fclose(arq);
}

void retiraDaCategoria(int id, char categoria[21]){
	FILE *arq = fopen(categoria, "rb+");
	int k, s, i=0;
	fseek(arq, -1, SEEK_END);
	fread(&s, sizeof(int), 1, arq);
	rewind(arq);
	fread(&k, sizeof(int), k, arq);
	while(k!=id){
		fread(&k, sizeof(int), k, arq);
		i++;
	}
	fseek(arq, i*sizeof(int), SEEK_SET);
	fwrite(&s, sizeof(int), 1, arq);
	fseek(arq, -1, SEEK_END);
	s = EOF;
	fwrite(&s, sizeof(int), 1, arq);
	fclose(arq);
}