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
	//printf("I:1\n");
	//imprime(arvPizza);
	arvPizza = insere_arv_parametros(arvPizza, 15, 32.0, "Bianca", "Salgada");
	//printf("I:2\n");
	//imprime(arvPizza);
	arvPizza = insere_arv_parametros(arvPizza ,18, 40.0, "Estrogonoff com Cogumelos", "Especial");
	//printf("I:3\n");
	//imprime(arvPizza);
	arvPizza = insere_arv_parametros(arvPizza ,25, 25.0, "Banana", "Doce");
	printf("I:4\n");
	imprime(arvPizza);
	return 0;
}
