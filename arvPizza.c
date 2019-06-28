#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "pizza.h"

void getNome(ArvBM a, char fname[2048]){
	sprintf(fname, "%s/%s%s", a.nome, a.nome, a.k);
}

void cria_raiz(const char* nome){
	int cod=-1;
	char fname[2048];
	sprintf(fname, "%s/raiz", nome);
	FILE *arq = fopen(fname, "wb");
	fwrite(&cod, sizeof(int), 1, arq);
	fclose(arq);
}

void muda_raiz(const char* nome, int cod){
	char fname[2048];
	sprintf(fname, "%s/raiz", nome);
	FILE *arq = fopen(fname, "rb+");
	fwrite(&cod, sizeof(int), 1, arq);
	fclose(arq);
}

ArvBM inicializa(const char *nome){
	ArvBM a;
	strcpy(a.nome, nome);
	a.k=a.t=a.folha=-1;
	a.nk=0;
	a.ind=0;
	return a;
}

ArvBM cria_arvore(const char* nome, int t){
	char cmd[2048], fname[2048];
	sprintf(cmd, "mkdir %s", nome);
	system(cmd);
	cria_raiz(nome);
	sprintf(fname, "%s/raiz", nome);
	FILE *arq = fopen(fname, "ab");
	fwrite(&t, sizeof(int), 1, arq);
	fclose(arq);
	return inicializa(nome);
}

ArvBM cria_folha(const char* nome, int t, Pizza *p){
	ArvBM a = inicializa(nome);
	a.t=t;
	a.k=p->cod;
	a.nk=1;
	a.ind=0;
	a.folha=1;
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "wb");
	/*primeiro 1 diz que e folha*/
	fwrite(&a.nk, sizeof(int), 1, arq);
	/*segundo a quantidade de chaves*/
	fwrite(&a.nk, sizeof(int), 1, arq);
	fwrite(p, sizeof(Pizza), 1, arq);
	fclose(arq);
	return a;
}

ArvBM cria_no_interno(const char* nome, int t, int key){
	ArvBM a = inicializa(nome);
	a.t=t;
	a.k=key;
	a.nk=1;
	a.ind=0;
	a.folha=0;
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb+");
	int zero = 0;
	fwrite(&zero, sizeof(int), 1, arq);
	fwrite(&a.nk, sizeof(int), 1, arq);
	fwrite(&key, sizeof(int), 1, arq);
	fclose(arq);
	return a;
}

void libera_arv(ArvBM a){
	char cmd[2048];
	#ifdef WIN_32
		sprintf(cmd,"rmdir /s /q %s", a.nome);
	#endif
	#ifdef linux
		sprintf(cmd,"rm -rf %s", a.nome);
	#endif
	system(cmd);
}

void escreve_no(ArvBM a){
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "wb");
	fwrite(&a.folha, sizeof(int), 1, arq);
	fwrite(&a.nk, sizeof(int), 1, arq);
	fclose(arq);
}

void escreve_chave(ArvBM a, int ind, int k){
	if(a.folha==1)return;
	int end = 2*sizeof(int)*(1+ind) + sizeof(int);
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb+");
	fseek(arq, end, SEEK_SET);
	fwrite(&k, sizeof(int), 1, arq);
	fclose(arq);
}

void escreve_filho_key(ArvBM a, int ind, int k){
	if(a.folha==1)return;
	int end = 2*sizeof(int)*(1+ind);
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb+");
	fseek(arq, end, SEEK_SET);
	fwrite(&k, sizeof(int), 1, arq);
	fclose(arq);
}

void escreve_pizza(ArvBM a, int ind, Pizza *p){
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb+");
	int end = 2*sizeof(int) + ind*sizeof(Pizza);
	fseek(arq, end, SEEK_SET);
	fwrite(p, sizeof(Pizza), 1, arq);
	fclose(arq);
}

int get_filho_key(ArvBM a, int ind){
	if(a.folha==1)return INT_MIN;
	int end = 2*sizeof(int)*(1+ind), k;
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb");
	fseek(arq, end, SEEK_SET);
	fread(&k, sizeof(int), 1, arq);
	fclose(arq);
	return k;
}

int get_chave(ArvBM a, int ind){
	if(a.folha==1)return INT_MIN;
	int end = 2*sizeof(int)*(1+ind) + sizeof(int), k;
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb");
	fseek(arq, end, SEEK_SET);
	fread(&k, sizeof(int), 1, arq);
	fclose(arq);
	return k;
}

void atualiza_nchaves(ArvBM a){
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb+");
	fseek(arq, sizeof(int), SEEK_SET);
	fwrite(&a.nk, sizeof(int), 1, arq);
	fclose(arq);
}

void escreve_prox(ArvBM a, int prox){
	int end = 2*sizeof(int) + a.nk*sizeof(Pizza);
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb+");
	fwrite(&prox, sizeof(int), 1, arq);
	fclose(arq);
}

ArvBM divisao(ArvBM b, int i, ArvBM a){
	ArvBM c = inicializa(b.nome);
	int t = c.t = b.t;
	c.folha = a.folha;
	escreve_no(c);
	int j;
	if(a.folha==0){
		c.nk = t-1;
		atualiza_nchaves(c);
		for(j=0;j<t-1;j++){
			escreve_chave(c, j, get_filho_key(a, j+t));
			escreve_filho_key(c, j, get_filho_key(a, j+t));
		}
		escreve_filho_key(c, t-1, get_filho_key(a, j+t));
	}
	else {
		c.nk = t;
		atualiza_nchaves(c);
		for(j=0;j<t;j++)
			escreve_chave(c, j, get_chave(a, j+t-1));
		escreve_prox(a, c.k);
	}
	a.nk = t;
	atualiza_nchaves(a);
	for(j=b.nk;j>=i;j--)
		escreve_filho_key(b, j+1, get_filho_key(b, j));
	escreve_filho_key(b, i, c.k);
	for(j=b.nk;j>=i;j--)
		escreve_chave(b, j, get_chave(b, j-1));
	escreve_chave(b, i-1, get_chave(a, t-1));
	b.nk++;
	atualiza_nchaves(b);
	return b;
}

ArvBM insere_nao_completo(ArvBM a, Pizza *p){
	int i;
	if(a.folha==1){
		for(i=a.nk-1;i>=0 && p->cod < get_chave(a, i);i--){
			Pizza *tmp = get_pizza(a, i);
			if(!tmp){
				printf("Pizza com indice fora de alcance\n");
				exit(1);
			}
			escreve_pizza(a, i+1, tmp);
		}
		escreve_pizza(a, i+1, p);
		a.nk++;
		atualiza_nchaves(a);
		return a;
	}
	while(i>=0 && p->cod < get_chave(a, i)) i--;
	i++;
	ArvBM filho = get_filho(a, i);
	if(filho.nk == (2*a.t-1)){
		a = divisao(a, i+1, filho);
		if(p->cod > get_chave(filho, i))
			i++;
	}
	filho = get_filho(a, i);
	filho = insere_nao_completo(filho, p);
	return a;
}


/* modifica os nos de indice se preciso*/
ArvBM insere_arv(ArvBM a, Pizza *p){
	ArvBM res_busca = busca_arv(a, p->cod);
	if(res_busca.k != -1)
		return a;
	insereNaCategoria(p->cod, p->categoria);
	if(a.k == -1){
		a=cria_folha(a.nome, a.t, p);
		return a;
	}
	if(a.nk == (2*a.t)-1){
		ArvBM b = cria_no_interno(a.nome, a.t, a.k);
		b = divisao(b, 1, a);
		b = insere_nao_completo(b, p);
		b = divisao(b,1,a);
		b = insere_nao_completo(a, p);
		muda_raiz(b.nome, b.k);
		return b;
	}
	a = insere_nao_completo(a, p);
	return a;
}

/*recupera dados de uma arvore do hd apos abrir o programa depois que ela foi criada*/
ArvBM busca_raiz(const char* nome){
	char fname[2048];
	sprintf(fname, "%s/raiz", nome);
	FILE *arq = fopen(fname, "rb");
	int k, t;
	fread(&k, sizeof(int), 1, arq);
	fclose(arq);
	ArvBM a;
	a.k = k;
	fread(&t, sizeof(int), 1, arq);
	a.t = t;
	a.ind=0;
	getNome(a, fname);
	arq = fopen(fname, "rb");
	fread(&a.folha, sizeof(int), 1, arq);
	fread(&a.nk, sizeof(int), 1, arq);
	fclose(arq);
	return a;
}

ArvBM get_filho(ArvBM a, int index){
	char fname[2048];
	getNome(a, fname);
	int k;
	FILE *arq = fopen(fname, "rb");
	int end = 2*sizeof(int)*(1+index);
	fread(&k, sizeof(int), 1, arq);
	fclose(arq);
	ArvBM filho = inicializa(a.nome);
	filho.k=k;
	filho.t=a.t;
	filho.ind=0;
	getNome(filho, fname);
	arq = fopen(fname, "rb");
	fread(&filho.folha, sizeof(int), 1, arq);
	fread(&filho.nk, sizeof(int), 1, arq);
	fclose(arq);
	return filho;
}

/*retorna a.k=-1 caso n existir*/
/*retorna arvore com a.ind=indice da pizza*/
ArvBM busca_arv(ArvBM a, int key){
	int nk = a.nk, i, k;
	Pizza *p;
	if(a.folha==0){
		for(i=0;i<nk;i++){
			k = get_chave(a, i);
			if(key > k) break;
		}
		return busca_arv(get_filho(a,i), key);
	}
	else{
		for(i=0;i<nk;i++){
			p = get_pizza(a, i);
			k = p->cod;
			free(p);
			if(key>=k)break;
		}
		ArvBM b = inicializa(a.nome);
		if(p!=NULL && key==p->cod){
			b.k=k;
			b.ind=i;
			b.t=a.t;
		}
		return b;
	}
}

void retira_arv(ArvBM a, int key){



	return;
}

int getNKeys(ArvBM a){
	char fname[2048];
	int nkeys;
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb");
	fseek(arq, sizeof(int), SEEK_SET);
	fread(&nkeys, sizeof(int), 1, arq);
	fclose(arq);
	return nkeys;
}

Pizza* get_pizza(ArvBM a, int ind){
	if(ind>=a.nk)return NULL;
	if(!a.folha)return NULL;
	char fname[2048];
	getNome(a,fname);
	FILE *arq = fopen(fname, "rb");
	int end = 2*sizeof(int)*(1+ind);
	Pizza *p=(Pizza*)malloc(sizeof(Pizza));
	fseek(arq, end, SEEK_SET);
	fread(p, sizeof(Pizza), 1, arq);
	fclose(arq);
	return p;
}

Pizza* buscaPizza(ArvBM a, int key){
	ArvBM ap = busca_arv(a, key);
	if(ap.k==-1)return NULL;
	Pizza *p = get_pizza(ap, key);
	return p;
}

ListaPizza* busca_categoria_arv(ArvBM a,  char categoria[21]){
	ListaPizza *l = cria_lista();
	FILE *arq = fopen(categoria, "rb");
	int key;
	while(!feof(arq)){
		fread(&key, sizeof(int), 1, arq);
		Pizza *p = buscaPizza(a, key);
		if(p) l = insere_lista(l, p);
	}
	return l;
}

void retira_categoria_arv(ArvBM a, char categoria[21]){
	FILE *arq = fopen(categoria, "rb");
	int key;
	while(!feof(arq)){
		fread(&key, sizeof(int), 1, arq);
		retira_arv(a, key);
	}
	//função da stdio que remove arquivos
	remove(categoria);
}

void altera_pizza(ArvBM a, int key, float preco, char nome[51], char categoria[21]){
	ArvBM ap = busca_arv(a, key);
	if(ap.k==-1)return;
	Pizza *p = get_pizza(ap, key);
	if(strcmp(p->categoria,categoria)!=0){
		retiraDaCategoria(p->cod, p->categoria);
		insereNaCategoria(p->cod, categoria);
	}
	setPizza(p, preco, nome, categoria);
	char fname[2048];
	getNome(ap, fname);
	FILE *arq = fopen(fname, "rb+");
	int end = 2*sizeof(int) + ap.ind*sizeof(Pizza);
	fseek(arq, end, SEEK_SET);
	fwrite(p, sizeof(Pizza), 1, arq);
}
