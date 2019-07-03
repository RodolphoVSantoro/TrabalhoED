#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "pizza.h"

void copia(ArvBM *c, ArvBM a){
	c->t = a.t;
	c->nk = a.nk;
	c->f_id = a.f_id;
	c->ind = a.ind;
	c->folha = a.folha;
	c->prox = a.prox;
	strcpy(c->nome, a.nome);
}

void getNome(ArvBM a, char fname[2048]){
	sprintf(fname, "%s/%s%d", a.nome, a.nome, a.f_id);
}

int new_f_id(const char* nome){
	int nfid;
	char fname[2048];
	sprintf(fname, "%s/raiz", nome);
	FILE *arq = fopen(fname, "rb+");
	fseek(arq, sizeof(int)*2, SEEK_SET);
	fread(&nfid, sizeof(int), 1, arq);
	nfid++;
	fseek(arq, sizeof(int)*2, SEEK_SET);
	fwrite(&nfid, sizeof(int), 1, arq);
	fclose(arq);
	nfid--;
	return nfid;
}

void cria_raiz(const char* nome){
	int f_id=-1, t=0, last_f_id=0;
	char fname[2048];
	sprintf(fname, "%s/raiz", nome);
	FILE *arq = fopen(fname, "wb");
	fwrite(&f_id, sizeof(int), 1, arq);
	fwrite(&t, sizeof(int), 1, arq);
	fwrite(&last_f_id, sizeof(int), 1, arq);
	fclose(arq);    
}

void muda_raiz(const char* nome, int f_id){
	char fname[2048];
	sprintf(fname, "%s/raiz", nome);
	FILE *arq = fopen(fname, "rb+");
	fwrite(&f_id, sizeof(int), 1, arq);
	fclose(arq);
}

ArvBM inicializa(const char *nome){
	ArvBM a;
	strcpy(a.nome, nome);
	a.f_id=a.t=a.folha=a.prox=-1;
	a.nk=0;
	a.ind=0;
	return a;
}

ArvBM cria_arvore(const char* nome, int t){
	char cmd[2048], fname[2048];
	int f_id=0;
	sprintf(cmd, "mkdir %s", nome);
	system(cmd);
	cria_raiz(nome);
	sprintf(fname, "%s/raiz", nome);
	FILE *arq = fopen(fname, "rb+");
	fseek(arq, sizeof(int), SEEK_SET);
	fwrite(&t, sizeof(int), 1, arq);
	fclose(arq);
	ArvBM a = inicializa(nome);
	a.t=t;
	return a;
}

ArvBM cria_folha(ArvBM arv, Pizza *p){
	ArvBM a = inicializa(arv.nome);
	a.t=arv.t;
	a.f_id = new_f_id(arv.nome);
	a.nk=1;
	a.ind=0;
	a.folha=1;
 	a.prox=-1;
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "wb");
	/*primeiro 1 diz que e folha*/
	fwrite(&a.folha, sizeof(int), 1, arq);
	/*segundo a quantidade de chaves*/
	fwrite(&a.nk, sizeof(int), 1, arq);
 	/*terceiro o proximo*/
	fwrite(&a.prox, sizeof(int), 1, arq);
	fwrite(p, sizeof(Pizza), 1, arq);
	fclose(arq);
	return a;
}

ArvBM cria_no_interno(ArvBM arv, int f_id_filho, int key){
	ArvBM a = inicializa(arv.nome);
	a.t=arv.t;
	a.f_id=new_f_id(arv.nome);
	a.nk=1;
	a.ind=0;
	a.folha=0;
	a.prox=-1;
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "wb");
	int folha = 0;
	fwrite(&folha, sizeof(int), 1, arq);
	fwrite(&a.nk, sizeof(int), 1, arq);
	fwrite(&a.prox, sizeof(int), 1, arq);
	fwrite(&f_id_filho, sizeof(int), 1, arq);
	fwrite(&key, sizeof(int), 1, arq);
	fclose(arq);
	return a;
}

void deleta_arv(ArvBM a){
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb");
	if(arq==NULL)return;
	fclose(arq);
	char cmd[2048];
	//windows
	sprintf(cmd,"rmdir /s /q %s", a.nome);
	//linux
	//sprintf(cmd,"rm -rf %s", a.nome);
	system(cmd);
}

void escreve_no(ArvBM a){
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb+");
	if(arq==NULL)
		arq = fopen(fname, "wb");
	fwrite(&a.folha, sizeof(int), 1, arq);
	fwrite(&a.nk, sizeof(int), 1, arq);
	fwrite(&a.prox, sizeof(int), 1, arq);
	fclose(arq);
}

void escreve_chave(ArvBM a, int ind, int k){
	if(a.folha==1)return;
	int end = sizeof(int)*(3+2*ind+1);
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb+");
	fseek(arq, end, SEEK_SET);
	fwrite(&k, sizeof(int), 1, arq);
	fclose(arq);
}

void escreve_filho_f_id(ArvBM a, int ind, int f_id){
	if(a.folha==1)return;
	int end = sizeof(int)*(3+2*ind);
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb+");
	fseek(arq, end, SEEK_SET);
	fwrite(&f_id, sizeof(int), 1, arq);
	fclose(arq);
}

void escreve_pizza(ArvBM a, int ind, Pizza *p){
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb+");
	int end = 3*sizeof(int) + ind*sizeof(Pizza);
	fseek(arq, end, SEEK_SET);
	fwrite(p, sizeof(Pizza), 1, arq);
	fclose(arq);
}

int get_filho_f_id(ArvBM a, int ind){
	if(a.folha==1)return INT_MIN;
	int end = sizeof(int)*(3+2*ind), f_id;
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb");
	fseek(arq, end, SEEK_SET);
	fread(&f_id, sizeof(int), 1, arq);
	fclose(arq);
	return f_id;
}

int get_chave_pizza(ArvBM a, int ind){
	if(a.folha!=1)return INT_MIN;
	int end = 3*sizeof(int) + ind*sizeof(Pizza), k;
	Pizza *p = (Pizza*)malloc(sizeof(Pizza));
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb");
	fseek(arq, end, SEEK_SET);
	fread(p, sizeof(Pizza), 1, arq);
	fclose(arq);
	k = p->cod;
	free(p);
	return k;
}

int get_chave(ArvBM a, int ind){
	if(a.folha==1)return INT_MIN;
	int end = sizeof(int)*(3+2*ind+1), k;
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

void escreve_prox(ArvBM a, int prox_f_id){
	int end = 2*sizeof(int);
	char fname[2048];
	getNome(a, fname);
	FILE *arq = fopen(fname, "rb+");
	fseek(arq, end, SEEK_SET);
	fwrite(&prox_f_id, sizeof(int), 1, arq);
	fclose(arq);
}

int get_prox(ArvBM a){
	if(a.folha!=1)return -1;
 	char fname[2048];
	getNome(a, fname);
	int prox_f_id;
	int end = 2*sizeof(int);
 	FILE *arq = fopen(fname, "rb");
	if(arq==NULL)return -1;
	fseek(arq, end, SEEK_SET);
	fread(&prox_f_id, sizeof(int), 1, arq);
	fclose(arq);
	return prox_f_id;
}

void imprime_prox(const char *fname, int n_arq){
	int prox_f_id;
	int end = 2*sizeof(int);
	FILE *arq = fopen(fname, "rb");
	if(arq==NULL)return;
	fseek(arq, end, SEEK_SET);
	fread(&prox_f_id, sizeof(int), 1, arq);
	fclose(arq);
	printf("prox de %d=%d\n", n_arq, prox_f_id);
}

void imprime_raiz(const char *nome){
	FILE *arq = fopen(nome, "rb");
	int tmp;
	fread(&tmp, sizeof(int), 1, arq);
	printf("raiz=%d ", tmp);
	fread(&tmp, sizeof(int), 1, arq);
	printf("t=%d\n", tmp);
	fread(&tmp, sizeof(int), 1, arq);
	printf("last_f_id=%d\n", tmp);
	fclose(arq);
	printf("\n\n");
}

void imprime_folha(const char *nome){
	int as;
	FILE *arq = fopen(nome, "rb");
	int tmp, nk, prox;
	Pizza *p = (Pizza*)malloc(sizeof(Pizza));
	fread(&tmp, sizeof(int), 1, arq);
	printf("folha=%d ", tmp);
	fread(&nk, sizeof(int), 1, arq);
	printf("nk=%d\n", nk);
	fread(&prox, sizeof(int), 1, arq);
	for(tmp=0;tmp<nk;tmp++){
		fread(p, sizeof(Pizza), 1, arq);
		imprime_pizza(p);
	}
	printf("prox_f_id=%d\n", prox);
	fclose(arq);
	free(p);
	printf("\n\n");
}

void imprime_interno(const char *nome){
	FILE *arq = fopen(nome, "rb");
	int tmp, nk, fk, k, prox;
	fread(&tmp, sizeof(int), 1, arq);
	printf("folha=%d ", tmp);
	fread(&nk, sizeof(int), 1, arq);
	printf("nk=%d\n", nk);
	fread(&prox, sizeof(int), 1, arq);
	printf("prox=%d\n", prox);
	for(tmp=0;tmp<nk;tmp++){
		fread(&fk, sizeof(int), 1, arq);
		fread(&k, sizeof(int), 1, arq);
		printf("%d:filho_f_id=%d,k=%d\n", tmp, fk, k);
	}
	fread(&fk, sizeof(int), 1, arq);
	printf("%d:filho_f_id=%d\n", tmp, fk);
	fclose(arq);
	printf("\n\n");
}

ArvBM divisao(ArvBM b, int i, ArvBM *ap){
	ArvBM a;
	copia(&a, *ap);
	int t=ap->t;
	ArvBM c = inicializa(b.nome);
	c.f_id=new_f_id(b.nome); 
	c.folha = a.folha;
	int j;
	if(a.folha!=1){
		c.nk = t-1;
		escreve_no(c);
		for(j=0;j<t-1;j++)
			escreve_chave(c, j, get_chave(a, j+t));
		for(j=0;j<t;j++)
			escreve_filho_f_id(c, j, get_filho_f_id(a, j+t));
	}
	else {
		c.nk = t;
		escreve_no(c);
		for(j=0;j<t;j++)
			escreve_pizza(c, j, get_pizza(a, j+t-1));
			//escreve_filho_f_id(c, j, get_filho_f_id(a, j+t-1));
 		escreve_prox(c, get_prox(a));
		escreve_prox(a, c.f_id);
	}
	a.nk=t-1;
	atualiza_nchaves(a);
	for(j=b.nk; j>=i; j--)
		escreve_filho_f_id(b, j+1, get_filho_f_id(b, j));
	escreve_filho_f_id(b, i, c.f_id);
	for(j=b.nk; j>=i; j--)
		escreve_chave(b, j, get_chave(b, j-1));
	if(a.folha) escreve_chave(b, i-1, get_chave_pizza(a, t-1));
	else escreve_chave(b, i-1, get_chave(a, t-1));
	b.nk++;
	atualiza_nchaves(b);
	copia(ap, a);
	return b;
}

ArvBM insere_pagina(ArvBM a, Pizza *p){
	int i = a.nk-1, t = a.t, k;
	if(a.folha==1){
		while((i>=0) && (p->cod < get_chave_pizza(a, i))){
			escreve_pizza(a, i+1, get_pizza(a, i));
			i--;
		}
		escreve_pizza(a, i+1, p);
		a.nk++;
		atualiza_nchaves(a);
		return a;
	}
	while((i>=0) && (p->cod < get_chave(a, i))) 
		i--;
	i++;
	ArvBM filho = get_filho(a, i);
	if(filho.nk == 2*t-1){
		a = divisao(a, i+1, &filho);
		if(a.folha==1) k = get_chave_pizza(a, i);
		else k = get_chave(a, i);
		if(p->cod > k)
			filho = get_filho(a, i+1);
	}
	filho = insere_pagina(filho, p);
	atualiza_nchaves(filho);
	return a;
}

ArvBM insere_arv(ArvBM a, Pizza *p){
	ArvBM res_busca = busca_arv(a, p->cod);
	if(res_busca.f_id!=-1) return a;
	insereNaCategoria(a.nome, p->cod, p->categoria);
	if(a.f_id==-1){
		a = cria_folha(a, p);
		muda_raiz(a.nome, a.f_id);
		return a;
	}
	if(a.nk == (2*a.t)-1){
		ArvBM b = cria_no_interno(a, a.f_id, -1);
		b.nk=0;
		atualiza_nchaves(b);
		b = divisao(b,1,&a);
		b = insere_pagina(b, p);
		muda_raiz(b.nome, b.f_id);
		return b;
	}
	a = insere_pagina(a, p);
	muda_raiz(a.nome, a.f_id);
	return a;
}

ArvBM insere_arv_parametros(ArvBM a, int cod, float preco, char nome[51], char categoria[21]){
	Pizza *p = cria_pizza(cod, preco, nome, categoria);
	a = insere_arv(a, p);
	free(p);
	return a;
}

/*recupera dados de uma arvore do hd apos abrir o programa depois que ela foi criada*/
ArvBM busca_raiz(const char* nome){
	char fname[2048];
	sprintf(fname, "%s/raiz", nome);
	FILE *arq = fopen(fname, "rb");
	if(!arq){
		printf("Erro ao abrir raiz\n");
		exit(1);
	}
	int f_id, t, prox;
	fread(&f_id, sizeof(int), 1, arq);
 fread(&t, sizeof(int), 1, arq);
	fclose(arq);
	ArvBM a = inicializa(nome);
	a.f_id = f_id;
	a.t = t;
	a.ind=0;
	a.prox=-1;
	getNome(a, fname);
	if(a.f_id!=-1){
		getNome(a, fname);
		arq = fopen(fname, "rb");
		fread(&a.folha, sizeof(int), 1, arq);
		fread(&a.nk, sizeof(int), 1, arq);
 		fread(&a.prox, sizeof(int), 1, arq);
		fclose(arq);
	}
	return a;
}

ArvBM get_filho(ArvBM a, int index){
	ArvBM filho = inicializa(a.nome);
	if(a.folha==1) return filho;
	char fname[2048];
	getNome(a, fname);
	int f_id;
	FILE *arq = fopen(fname, "rb");
	int end = sizeof(int)*(3+2*index);
	fseek(arq, end, SEEK_SET);
	fread(&f_id, sizeof(int), 1, arq);
	fclose(arq);
	filho.f_id=f_id;
	filho.t=a.t;
	filho.ind=0;
	getNome(filho, fname);
	arq = fopen(fname, "rb");
	if(arq==NULL){
		printf("Filho %d n existe\n", f_id);
		exit(1);
	}
	fread(&filho.folha, sizeof(int), 1, arq);
	fread(&filho.nk, sizeof(int), 1, arq);
	fread(&filho.prox, sizeof(int), 1, arq);
	fclose(arq);
	return filho;
}

/*retorna a.f_id=-1 caso n existir*/
/*retorna arvore com a.ind=indice da pizza*/
ArvBM busca_arv(ArvBM a, int key){
	int nk = a.nk, i, k;
	Pizza *p;
	if(a.folha==0){
		for(i=0;i<nk;i++){
			k = get_chave(a, i);
			if(key > k) break;
		}
		return busca_arv(get_filho(a, i), key);
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
			b.f_id=a.f_id;
			b.ind=i;
			b.t=a.t;
		}
		return b;
	}
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
	int end = 3*sizeof(int) + ind*sizeof(Pizza);
	Pizza *p=(Pizza*)malloc(sizeof(Pizza));
	fseek(arq, end, SEEK_SET);
	fread(p, sizeof(Pizza), 1, arq);
	fclose(arq);
	return p;
}

Pizza* buscaPizza(ArvBM a, int key){
	ArvBM ap = busca_arv(a, key);
	if(ap.f_id==-1)return NULL;
	Pizza *p = get_pizza(ap, ap.ind);
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
	fclose(arq);
	return l;
}

void retira_categoria_arv(ArvBM a, char categoria[21]){
	FILE *arq = fopen(categoria, "rb");
	if(arq==NULL)return;
	int key;
	while(!feof(arq)){
		fread(&key, sizeof(int), 1, arq);
		retira_arv(a, key);
	}
	fclose(arq);
	//função da stdio que remove arquivos
	remove(categoria);
}

void altera_pizza(ArvBM a, int key, float preco, char nome[51], char categoria[21]){
	ArvBM ap = busca_arv(a, key);
	if(ap.f_id==-1)return;
	Pizza *p = get_pizza(ap, ap.ind);
	if(strcmp(p->categoria,categoria)!=0){
		retiraDaCategoria(a.nome, p->cod, p->categoria);
		insereNaCategoria(a.nome, p->cod, categoria);
	}
	setPizza(p, preco, nome, categoria);
	char fname[2048];
	getNome(ap, fname);
	FILE *arq = fopen(fname, "rb+");
	int end = 2*sizeof(int) + ap.ind*sizeof(Pizza);
	fseek(arq, end, SEEK_SET);
	fwrite(p, sizeof(Pizza), 1, arq);
	fclose(arq);
}

void imprime(ArvBM a){
	imprime_rec(a, 0);	
}

void imprime_rec(ArvBM a, int andar){
	if(a.f_id!=-1){
		int i, j, k;
		for(i=0;i<a.nk;i++){
			ArvBM filho = get_filho(a, i);
			imprime_rec(get_filho(a, i), andar+1);
			for(j=0;j<=andar;j++)
				printf("   ");
			if(a.folha){
				Pizza *p = get_pizza(a, i);
				imprime_pizza(p);
				free(p);
			}
			else printf("%d\n", get_chave(a, i));
		}
		ArvBM filho = get_filho(a, i);
		imprime_rec(get_filho(a, i), andar+1);
	}
}

ArvBM retira_arv(ArvBM a, int key){
	if(a.f_id==-1) return a;
	ArvBM ap = busca_arv(a, key);
	Pizza *p = get_pizza(ap, ap.ind);
	retiraDaCategoria(a.nome, p->cod, p->categoria);
	free(p);
	int x;
	Pizza* temp = get_pizza(a, a.nk-1);
	Pizza* temp2;
	for(x = a.nk-2; x >= 0; x--){
		if(temp->cod > key){
			temp2 = get_pizza(a, x);
			escreve_pizza(a, x, temp);
			free(temp);
			temp = temp2;
		}
	}
	a.nk--;
	atualiza_nchaves(a);
	return a;
}

int verifica_caso(ArvBM no_at){
	return -1;
}

ArvBM merge_direita(ArvBM no_at){
	return inicializa(no_at.nome);
}
ArvBM merge_esquerda(ArvBM no_at){
	return inicializa(no_at.nome);
}
void empresta_direita(ArvBM no_at){
	return;
}
void empresta_esquerda(ArvBM no_at){
	return;
}

void arruma_arv(ArvBM no_at){
	int a = verifica_caso(no_at);
	//caso 1 = fazer merge a direita
	if(a == 1){
		merge_direita(no_at);
	}
	//caso 3 = fazer merge a esquerda
	else if(a == 2){
		merge_esquerda(no_at);
	}
	//caso 4 = emprestar da direita
	else if(a == 3){
		empresta_direita(no_at);
	}
	//caso 2 = emprestar da esquerda
	else{
		empresta_esquerda(no_at);
	}
	return;
}
