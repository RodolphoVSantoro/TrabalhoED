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

/*pega o nome referente ao arquivo da arvore a e salva em fname*/
void getNome(ArvBM a, char fname[2048]);
/*cria o arquivo que guarda qual nó é a raiz, e o t da árvore*/
/*inicialmente com raiz=-1 e sem t*/
void cria_raiz(const char* nome);
void muda_raiz(const char* nome, int cod);
/*inicializa os valores nescessários pra criar o nó*/
/*inicia com número de chaves 0, indice 0 e o resto -1*/
ArvBM inicializa(const char *nome);
/*
	cria a pasta onde os arquivos referentes a árvore ficam salvos,
	o arquivo raiz, e cria um nó vazio na MP
*/
ArvBM cria_arvore(const char* nome, int t);
/*cria uma folha na MP e na MS*/
ArvBM cria_folha(const char* nome, int t, Pizza *p);
/*cria um nó interno na MP e na MS*/
ArvBM cria_no_interno(const char* nome, int t, int key);
/*deleta os arquivos e a pasta da árvore*/
void libera_arv(ArvBM a);
/*cria na MS um nó sem keys ou pizzas*/
void escreve_no(ArvBM a);
/*escreve uma key no indice ind no arquivo de um nó interno a*/
void escreve_chave(ArvBM a, int ind, int k);
/*escreve a key inicial do filho de a no indice ind no arquivo de um nó interno a*/
void escreve_filho_key(ArvBM a, int ind, int k);
/*escreve uma pizza no indice ind no arquivo de uma folha a*/
void escreve_pizza(ArvBM a, int ind, Pizza *p);
/*pega a key inicial do filho ind do nó interno a, no seu arquivo*/
int get_filho_key(ArvBM a, int ind);
/*pega a key ind no arquivo do nó interno a*/
int get_chave(ArvBM a, int ind);
/*atualiza o número de chaves de a no seu arquivo*/
void atualiza_nchaves(ArvBM a);
/*escreve no final do arquivo de a(uma folha) qual a próxima folha*/
void escreve_prox(ArvBM a, int prox);
ArvBM divisao(ArvBM b, int i, ArvBM a);
ArvBM insere_nao_completo(ArvBM a, Pizza *p);
/*insere fazendo as modificações nescerssárias*/
ArvBM insere_arv(ArvBM a, Pizza *p);
/*recupera dados da raiz de uma arvore do hd após abrir o programa depois que ela foi criada*/
ArvBM busca_raiz(const char* nome);
/*pega os dados do filho index do nó interno a*/
ArvBM get_filho(ArvBM a, int index);
/*
	retorna a.k=-1 caso n existir
	retorna o nó a que tem a pizza com cod=key, 
	com a.ind=<indice da pizza no arquivo>
*/
ArvBM busca_arv(ArvBM a, int key);
/*remove um nó da árvore*/
void retira_arv(ArvBM a, int key);
/*pega o número de chaves de um nó*/
int getNKeys(ArvBM a);
/*pega a pizza número ind do arquivo a(folha)*/
Pizza* get_pizza(ArvBM a, int ind);
/*
	Procura a pizza com cod=key em a(se for folha)
	ou em seus filhos(se for nó interno)
 */
Pizza* buscaPizza(ArvBM a, int key);
/*retorna uma lista com todas as pizzas de uma categoria*/
ListaPizza* busca_categoria_arv(ArvBM a,  char categoria[21]);
/*retira todas as pizzas de uma categoria*/
void retira_categoria_arv(ArvBM a, char categoria[21]);
/*muda uma pizza*/
void altera_pizza(ArvBM a, int key, float preco, char nome[51], char categoria[21]);

#endif