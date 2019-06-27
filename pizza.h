#ifndef PIZZA_H
#define PIZZA_H

typedef struct pizza{
	int cod;
	float preco;
	char nome[51], categoria[21];
}Pizza;

Pizza *cria_pizza(int cod, float preco, char nome[51], char categoria[21]);
void setPizza(Pizza *p, float preco, char nome[51], char categoria[21]);
void escreve_cod(FILE *arq, int ind, Pizza *p);
void insereNaCategoria(int id, char categoria[21]);
void retiraDaCategoria(int id, char categoria[21]);

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
	int t, k, ind, nk, folha;
	char nome[2048];
}ArvBM;

void getNome(ArvBM a, char fname[2048]);
void cria_raiz(const char* nome);
void muda_raiz(const char* nome, int cod);
ArvBM inicializa(const char *nome);
ArvBM cria_arvore(const char* nome, int t);
ArvBM cria_folha(const char* nome, int t, Pizza *p);
ArvBM cria_no_interno(const char* nome, int t, int key);
void libera_arv(ArvBM a);
void escreve_no(ArvBM a);
void escreve_chave(ArvBM a, int ind, int k);
void escreve_filho_key(ArvBM a, int ind, int k);
void escreve_pizza(ArvBM a, int ind, Pizza *p);
int get_filho_key(ArvBM a, int ind);
int get_chave(ArvBM a, int ind);
void atualiza_nchaves(ArvBM a);
void escreve_prox(ArvBM a, int prox);
ArvBM divisao(ArvBM b, int i, ArvBM a);
ArvBM insere_nao_completo(ArvBM a, Pizza *p);
/* modifica os nos de indice se preciso*/
ArvBM insere_arv(ArvBM a, Pizza *p);
/*recupera dados de uma arvore do hd apos abrir o programa depois que ela foi criada*/
ArvBM busca_raiz(const char* nome);
ArvBM get_filho(ArvBM a, int index);
/*retorna a.k=-1 caso n existir*/
/*retorna arvore com a.ind=indice da pizza*/
ArvBM busca_arv(ArvBM a, int key);
void retira_arv(ArvBM a, int key);
int getNKeys(ArvBM a);
Pizza* get_pizza(ArvBM a, int ind);
Pizza* buscaPizza(ArvBM a, int key);
ListaPizza* busca_categoria_arv(ArvBM a,  char categoria[21]);
void retira_categoria_arv(ArvBM a, char categoria[21]);
void altera_pizza(ArvBM a, int key, float preco, char nome[51], char categoria[21]);

#endif