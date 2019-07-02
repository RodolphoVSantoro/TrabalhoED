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
void insereNaCategoria(const char* nome, int id, char categoria[21]);
void retiraDaCategoria(const char* nome, int id, char categoria[21]);
void imprime_pizza(Pizza *p);

typedef struct nodePizza{
	Pizza *p;
	struct nodePizza *prox;
}ListaPizza;

ListaPizza* cria_lista();
ListaPizza* insere_lista(ListaPizza *l, Pizza *p);
ListaPizza* retira_lista(ListaPizza *l, int cod);
void imprime_lista(ListaPizza *l);
void libera_lista(ListaPizza *l);

/*f_id é o id do arquivo, ele começa em 0, e a medida que cria outros nós, salva no arquivo "raiz" o último que criou+1*/
/*no inicio de todo arquivo de nó, tem se o nó é folha, e quantos filhos ele tem*/
/*
	quando for arquivo de indices, tem em sequecia vários grupos de 2 ints, 
	o segundo é a chave , o primeiro é o f_id do nó que tem valores menores que essa chave
	no final do arquivo de indices, tem o f_id do filho maior que todas as chaves
*/
/*
	quando for arquivo de dados, tem as structs escritas em ordem, e no final, o f_id proximo irmao
*/
/*nome é a pasta onde ficam os arquivos de indices, dados, categorias e raiz*/
/*ind é usado para retorno de funcao que busca um id especifico, indice referente a esse id*/
typedef struct arvbm{
	int t, f_id, ind, nk, folha, prox;
	char nome[2048];
}ArvBM;

/*pega o nome referente ao arquivo da arvore a e salva em fname*/
void getNome(ArvBM a, char fname[2048]);
/*pega o menor f_id ainda não usado, e modifica essa informação no arquivo "raiz"*/
int new_f_id(const char* nome);
/*cria o arquivo que guarda qual nó é a raiz, e o t da árvore*/
/*inicialmente com raiz=-1 e sem t*/
void cria_raiz(const char* nome);
void muda_raiz(const char* nome, int f_id);
/*inicializa os valores nescessários pra criar o nó*/
/*inicia com número de chaves 0, indice 0 e o resto -1*/
ArvBM inicializa(const char *nome);
/*
	cria a pasta onde os arquivos referentes a árvore ficam salvos,
	o arquivo raiz, e cria um nó vazio na MP
*/
ArvBM cria_arvore(const char* nome, int t);
/*cria uma folha na MP e na MS*/
ArvBM cria_folha(ArvBM arv, Pizza *p);
/*cria um nó interno na MP e na MS*/
ArvBM cria_no_interno(ArvBM, int f_id_filho, int key);
/*deleta os arquivos e a pasta da árvore*/
void deleta_arv(ArvBM a);
/*cria na MS um nó sem keys ou pizzas*/
void escreve_no(ArvBM a);
/*escreve uma key no indice ind no arquivo de um nó interno a*/
void escreve_chave(ArvBM a, int ind, int k);
/*escreve a key inicial do filho de a no indice ind no arquivo de um nó interno a*/
void escreve_filho_f_id(ArvBM a, int ind, int f_id);
/*escreve uma pizza no indice ind no arquivo de uma folha a*/
void escreve_pizza(ArvBM a, int ind, Pizza *p);
/*pega a key inicial do filho ind do nó interno a, no seu arquivo*/
int get_filho_f_id(ArvBM a, int ind);
/*pega a key ind no arquivo do nó interno a*/
int get_chave(ArvBM a, int ind);
/*atualiza o número de chaves de a no seu arquivo*/
void atualiza_nchaves(ArvBM a);
/*escreve no final do arquivo de a(uma folha) qual o f_id da próxima folha*/
void escreve_prox(ArvBM a, int prox_f_id);
int get_prox(ArvBM a);
void imprime_prox(const char *fname, int n_arq);

void imprime_raiz(const char *nome);
void imprime_folha(const char *nome);
void imprime_interno(const char *nome);

/*insere fazendo as modificações nescerssárias*/
ArvBM insere_arv(ArvBM a, Pizza *p);
/*cria a pizza e chama a insere_arv*/
ArvBM insere_arv_parametros(ArvBM a, int cod, float preco, char nome[51], char categoria[21]);
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

/* pra não precisar colocar 0 no segundo argumento toda vez */
void imprime(ArvBM a);

/* é chamada por imprime, essa sim faz a impressão*/
void imprime_rec(ArvBM a, int andar);

#endif