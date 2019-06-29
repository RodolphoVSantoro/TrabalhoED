#include <stdio.h>
#include <stdlib.h>
#include "pizza.h"

int main(){
	ArvBM arvPizza = busca_raiz("pizzas");
	printf("%d\n", arvPizza.k);
	return 0;
}