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
	arvPizza = insere_arv_parametros(arvPizza, 15, 32.0, "Bianca", "Salgada");
	arvPizza = insere_arv_parametros(arvPizza ,18, 40.0, "Estrogonoff com Cogumelos", "Especial");
	arvPizza = insere_arv_parametros(arvPizza ,25, 25.0, "Banana", "Doce");
    arvPizza = insere_arv_parametros(arvPizza ,30, 25.0, "Banana", "Doce");
    arvPizza = insere_arv_parametros(arvPizza ,27, 25.0, "Banana", "Doce");
    arvPizza = insere_arv_parametros(arvPizza ,28, 25.0, "Banana", "Doce");
    arvPizza = insere_arv_parametros(arvPizza ,7, 25.0, "Banana", "Doce");
    arvPizza = insere_arv_parametros(arvPizza ,12, 25.0, "Banana", "Doce");
    arvPizza = insere_arv_parametros(arvPizza ,99, 25.0, "Banana", "Doce"); 
    arvPizza = insere_arv_parametros(arvPizza ,109, 25.0, "Banana", "Doce"); 
    arvPizza = insere_arv_parametros(arvPizza ,21, 25.0, "Banana", "Doce"); 
    arvPizza = insere_arv_parametros(arvPizza ,33, 25.0, "Banana", "Doce"); 
    arvPizza = insere_arv_parametros(arvPizza ,34, 25.0, "Banana", "Doce"); 
    arvPizza = insere_arv_parametros(arvPizza ,4, 25.0, "Banana", "Doce"); 
    arvPizza = insere_arv_parametros(arvPizza ,24, 25.0, "Banana", "Doce"); 
    arvPizza = insere_arv_parametros(arvPizza ,300, 25.0, "Banana", "Doce"); 
    printf("I1:\n");
    imprime_interno("pizzas/pizzas1");
    printf("I5:\n");
    imprime_interno("pizzas/pizzas5");
    printf("I6:\n");
    imprime_interno("pizzas/pizzas6");
    printf("I10:\n");
    imprime_interno("pizzas/pizzas10");
    printf("-------------------------------\n");
    printf("F0:\n");
    imprime_folha("pizzas/pizzas0");
    printf("F2:\n");
    imprime_folha("pizzas/pizzas2");
    printf("F3:\n");
    imprime_folha("pizzas/pizzas3");
    printf("F4:\n");
    imprime_folha("pizzas/pizzas4");
    printf("F7:\n");
    imprime_folha("pizzas/pizzas7");
    printf("F8:\n");
    imprime_folha("pizzas/pizzas8");
    printf("F9:\n");
    imprime_folha("pizzas/pizzas9");
    printf("F11:\n");
    imprime_folha("pizzas/pizzas11");
    printf("-------------------------------\n");
	imprime(arvPizza);
	return 0;
}
