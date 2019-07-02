#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pizza.h"

int main(){
	ArvBM arvPizza;
	strcpy(arvPizza.nome, "pizzas");
	deleta_arv(arvPizza);
	arvPizza = cria_arvore("pizzas", 2);
	arvPizza = insere_arv_parametros(arvPizza, 10, 30.0, "Calabresa", "Salgada");
    printf("Inseriu 10:\n");
	imprime_prox("pizzas/pizzas0", 0);
    imprime_prox("pizzas/pizzas2", 2);
    imprime_prox("pizzas/pizzas3", 3);
    imprime_prox("pizzas/pizzas4", 4);
	arvPizza = insere_arv_parametros(arvPizza, 15, 32.0, "Bianca", "Salgada");
    printf("Inseriu 15:\n");
	imprime_prox("pizzas/pizzas0", 0);
    imprime_prox("pizzas/pizzas2", 2);
    imprime_prox("pizzas/pizzas3", 3);
    imprime_prox("pizzas/pizzas4", 4);
	arvPizza = insere_arv_parametros(arvPizza ,18, 40.0, "Estrogonoff com Cogumelos", "Especial");
    printf("Inseriu 18:\n");
	imprime_prox("pizzas/pizzas0", 0);
    imprime_prox("pizzas/pizzas2", 2);
    imprime_prox("pizzas/pizzas3", 3);
    imprime_prox("pizzas/pizzas4", 4);
	arvPizza = insere_arv_parametros(arvPizza ,25, 25.0, "Banana", "Doce");
    printf("Inseriu 25:\n");
    imprime_prox("pizzas/pizzas0", 0);
    imprime_prox("pizzas/pizzas2", 2);
    imprime_prox("pizzas/pizzas3", 3);
    imprime_prox("pizzas/pizzas4", 4);
    arvPizza = insere_arv_parametros(arvPizza ,30, 25.0, "Banana", "Doce");
    printf("Inseriu 30:\n");
    imprime_prox("pizzas/pizzas0", 0);
    imprime_prox("pizzas/pizzas2", 2);
    imprime_prox("pizzas/pizzas3", 3);
    imprime_prox("pizzas/pizzas4", 4);
    arvPizza = insere_arv_parametros(arvPizza ,27, 25.0, "Banana", "Doce");
    printf("Inseriu 27:\n");
    imprime_prox("pizzas/pizzas0", 0);
    imprime_prox("pizzas/pizzas2", 2);
    imprime_prox("pizzas/pizzas3", 3);
    imprime_prox("pizzas/pizzas4", 4);
    arvPizza = insere_arv_parametros(arvPizza ,28, 25.0, "Banana", "Doce");
    printf("Inseriu 28:\n");
    imprime_prox("pizzas/pizzas0", 0);
    imprime_prox("pizzas/pizzas2", 2);
    imprime_prox("pizzas/pizzas3", 3);
    imprime_prox("pizzas/pizzas4", 4);
    arvPizza = insere_arv_parametros(arvPizza ,7, 25.0, "Banana", "Doce");
    printf("Inseriu 7:\n");
    imprime_prox("pizzas/pizzas0", 0);
    imprime_prox("pizzas/pizzas2", 2);
    imprime_prox("pizzas/pizzas3", 3);
    imprime_prox("pizzas/pizzas4", 4);
    arvPizza = insere_arv_parametros(arvPizza ,12, 25.0, "Banana", "Doce");
    printf("Inseriu 12:\n");
    imprime_prox("pizzas/pizzas0", 0);
    imprime_prox("pizzas/pizzas2", 2);
    imprime_prox("pizzas/pizzas3", 3);
    imprime_prox("pizzas/pizzas4", 4);
    arvPizza = insere_arv_parametros(arvPizza ,99, 25.0, "Banana", "Doce");
    printf("Inseriu 99:\n");
    imprime_prox("pizzas/pizzas0", 0);
    imprime_prox("pizzas/pizzas2", 2);
    imprime_prox("pizzas/pizzas3", 3);
    imprime_prox("pizzas/pizzas4", 4);
    imprime(arvPizza);
    printf("-------------------------------\n");
}