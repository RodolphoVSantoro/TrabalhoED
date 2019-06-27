#include <stdio.h>
#include <stdlib.h>
#include "pizza.h"

ListaPizza* cria_lista(){
	return NULL;
}

ListaPizza* insere_lista(ListaPizza *l, Pizza *p){
	ListaPizza *no = (ListaPizza*)malloc(sizeof(ListaPizza));
	no->p=p;
	no->prox=l;
	return no;
}

ListaPizza* retira_lista(ListaPizza *l, int cod){
	ListaPizza *ant=NULL, *tmp=l;
	while(tmp && l->p->cod!=cod){
		ant=tmp;
		tmp=tmp->prox;
	}
	if(tmp){
		if(ant) ant->prox=tmp->prox;
		else l=tmp->prox;
		free(tmp);
	}
	return l;
}

void imprime_lista(ListaPizza *l){
	while(l){
		Pizza *p = l->p;
		printf("%d, %s(%s), R$ %.2f\n", p->cod, p->nome, p->categoria, p->preco);
		l=l->prox;
	}
}

void libera_lista(ListaPizza *l){
	ListaPizza *tmp=l;
	while(l){
		l=l->prox;
		free(tmp);
		tmp=l;
	}
}