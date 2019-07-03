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
    printf("----------------------------------------------------------------------------------I1\n");
    imprime(arvPizza);
	arvPizza = insere_arv_parametros(arvPizza, 15, 32.0, "Bianca", "Salgada");
    printf("----------------------------------------------------------------------------------I2\n");
    imprime(arvPizza);
	arvPizza = insere_arv_parametros(arvPizza ,18, 40.0, "Estrogonoff com Cogumelos", "Especial");
    printf("----------------------------------------------------------------------------------I3\n");
    imprime(arvPizza);
	arvPizza = insere_arv_parametros(arvPizza ,25, 25.0, "Banana", "Docee");
    printf("----------------------------------------------------------------------------------I4\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,30, 25.0, "Banana", "Daoce");
    printf("----------------------------------------------------------------------------------I5\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,27, 25.0, "Banana", "Ddoce");
    printf("----------------------------------------------------------------------------------I6\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,28, 25.0, "Banana", "Dfoce");
    printf("----------------------------------------------------------------------------------I7\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,7, 25.0, "Banana", "Dgoce");
    printf("----------------------------------------------------------------------------------I8\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,12, 25.0, "Banana", "Dhoce");
    printf("----------------------------------------------------------------------------------I9\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,99, 25.0, "Banana", "Dioce"); 
    printf("----------------------------------------------------------------------------------I10\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,109, 25.0, "Banana", "Djoce"); 
    printf("----------------------------------------------------------------------------------I11\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,21, 25.0, "Banana", "Dkoce"); 
    printf("----------------------------------------------------------------------------------I12\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,33, 25.0, "Banana", "Dloce"); 
    printf("----------------------------------------------------------------------------------I13\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,34, 25.0, "Banana", "Dmoce"); 
    printf("----------------------------------------------------------------------------------I14\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,4, 25.0, "Banana", "Dnoce"); 
    printf("----------------------------------------------------------------------------------I15\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,24, 25.0, "Banana", "Dqoce"); 
    printf("----------------------------------------------------------------------------------I16\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,300, 25.0, "Banana", "Droce"); 
    printf("----------------------------------------------------------------------------------I17\n");
    imprime(arvPizza);
    arvPizza = insere_arv_parametros(arvPizza ,38, 25.0, "Bdaanana", "Droce"); 
    printf("----------------------------------------------------------------------------------I17\n");
    imprime(arvPizza);
    printf("-------------------------------------------------------------------------------------\n");
    printf("Salgadas:\n");
    imprimeCategoria("pizzas", "Salgada");
    return 0;
}
