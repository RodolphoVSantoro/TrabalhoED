#ifndef PIZZA_H
#define PIZZA_H

typedef struct pizza{
	int cod;
	float preco;
	char nome[51], categoria[21];
}Pizza;

Pizza *cria_pizza(int cod, float preco, char nome[51], char categoria[21]);
void setPizza(Pizza *p, float preco, char nome[51], char categoria[21]);

typedef struct nodePizza{
	Pizza *p;
	struct nodePizza *prox;
}ListaPizza;

ListaPizza* cria_lista();
ListaPizza* insere_lista(ListaPizza *l, Pizza *p);
ListaPizza* retira_lista(ListaPizza *l, int cod);
void imprime_lista(ListaPizza *l);
void libera_lista(ListaPizza *l);

/*k é a primeira chave no arquivo*/
/*no inicio de todo arquivo de nó, tem se o nó é folha, e quantos filhos ele tem*/
/*
	quando for arquivo de indices, tem em sequecia vários grupos de 2 ints, 
	o segundo é a chave , o primeiro é o filho que tem valores menores que essa chave	
	no final do arquivo de indices, tem a chave do filho maior que todas as chaves
*/
/*
	quando for arquivo de dados, tem as structs escritas em ordem, e no final, a chave do proximo irmao
*/
/*nome é a pasta onde ficam os arquivos de indices, dados, categorias e raiz*/
/*ind é usado para retorno de funcao que busca um id especifico, indice referente a esse id*/

typedef struct arvbm{
	int t, k, ind;
	char *nome;
}ArvBM;

ArvBM cria_arv(ArvBM a, int t);
void libera_arv(ArvBM a);
void insere_arv(ArvBM a, int t, Pizza *p);
void retira_arv(ArvBM a, int t, int key);
arvbm busca_arv(ArvBM a, int t);
Pizza* busca_pizza(ArvBM a, int key);
ListaPizza* busca_categoria_arv(ArvBM a,  char categoria[21]);
void retira_categoria_arv(ArvBM a, char categoria[21]);

#endif
