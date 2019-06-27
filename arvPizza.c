#include <stdio.h>
#include <stdlib.h>
#include "pizza.h"

const char* getNome(ArvBM a){
	char fname[2048];
	sprintf(fname, "%s/%s%s", a.nome, a.nome, a.k);
	return fname;
}

void cria_raiz(const char* nome){
	int cod=-1;
	char fname[2048];
	sprintf(fname, "%s/raiz", nome);
	FILE *arq = fopen(fname, "wb");
	frwite(&cod, sizeof(int), 1, arq);
	fclose(arq);
}

void muda_raiz(const char* nome, int cod){
	char fname[2048];
	sprintf(fname, "%s/raiz", nome);
	FILE *arq = fopen(fname, "rb+");
	frwite(&cod, sizeof(int), 1, arq);
	fclose(arq);
}

ArvBM inicializa(const char *nome){
	ArvBM a;
	strcpy(a.nome, nome);
	a.k=a.t=-1;
	a.ind=0;
	return a;
}

void cria_arvore(const char* nome, int t){
	char cmd[2048], fname[2048];
	sprintf(cmd, "mkdir %s", nome);
	system(cmd);
	cria_raiz(nome, -1);
	sprintf(fname, "%s/raiz", nome);
	FILE *arq = fopen(fname, "ab");
	fwrite(&t, sizeof(int), 1, arq);
	fclose(arq);
}

ArvBM cria_folha(const char* nome, int t, Pizza *p){
	ArvBM a = inicializa(nome);
	a.t=t;
	a.k=p->cod;
	a.ind=0;
	char fname[2048];
	strcpy(fname, getNome(a));
	FILE *arq = fopen(fname, "wb");
	int u = 1;
	/*primeiro 1 diz que e folha*/
	fwrite(&u, sizeof(int), 1, arq);
	/*segundo a quantidade de chaves*/
	fwrite(&u, sizeof(int), 1, arq);
	escreve_pizza(arq,p);
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

/* modifica os nos de indice se preciso*/
void insere_arv(ArvBM a, Pizza *p){

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
}

int isFolha(ArvBM a){
	int folha;
	char fname[2048];
	strcpy(fname, getNome(a));
	FILE *arq = fopen(fname,"r");
	fread(&folha, sizeof(int), 1, arq);
	fclose(arq);
	return folha;
}

ArvBM getFilho(ArvBM a, int index){
	char fname[2048];
	strcpy(fname, getNome(a));
	int k;
	FILE *arq = fopen(fname, "rb");
	int end = getEnderecoFilho(a, index);
	fread(&k, sizeof(int), 1, arq);
	fclose(arq);
	ArvBM filho = inicializa(a.nome);
	filho.k=k;
	filho.t=a.t;
	return filho;
}

/*retorna a.k=-1 caso n existir*/
ArvBM busca_arv(ArvBM a, int key){
	int nk = getNKeys(a), i, folha=0, k;
	folha = isFolha(a);
	Pizza *p;
	if(!folha){
		for(i=0;i<nk;i++){
			k = getKey(a, i);
			if(key > k) break;
		}
		return busca_arv(getFilho(a,i), key);
	}
	else{
		for(i=0;i<nk;i++){
			p = getPizza(a, i);
			k = p->cod;
			free(p);
			if(key>=k)break;
		}
		ArvBM b = inicializa(a.nome);
		if(key==p->cod){
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

/*Pega o endereco da index-esima pizza no arquivo arq*/
int getEnderecoPizza(FILE *arq, int index){
	int tmp = ftell(arq);
	rewind(arq);
	int end = ftell(arq);
	fseek(arq, tmp, SEEK_SET);
	end += 2*sizeof(int) + index*sizeof(Pizza);
	return end;
}

int getEnderecoFilho(FILE *arq, int index){
	int tmp = ftell(arq);
	rewind(arq);
	int end = ftell(arq);
	fseek(arq, tmp, SEEK_SET);
	end += 2*sizeof(int) + 2*index*sizeof(int);
	return end;
}

int getEnderecoKey(FILE *arq, int index){
	int tmp = ftell(arq);
	rewind(arq);
	int end = ftell(arq);
	fseek(arq, tmp, SEEK_SET);
	end += 2*sizeof(int) + 2*index*sizeof(int) + sizeof(int);
	return end;
}

int getNKeys(ArvBM a){
	char fname[2048];
	int nkeys;
	strcpy(fname, getNome(a));
	FILE *arq = fopen(fname, "rb");
	fseek(arq, sizeof(int), SEEK_SET);
	fread(&nkeys, sizeof(int), 1, arq);
	fclose(arq);
	return nkeys;
}

Pizza* getPizza(ArvBM a, int ind){
	char fname[2048];
	strcpy(fname,getNome(a));
	FILE *arq = fopen(fname, "rb");
	int end = getEnderecoPizza(arq, ind);
	Pizza *p=(Pizza*)malloc(sizeof(Pizza));
	fseek(arq, end, SEEK_SET);
	fread(p, sizeof(Pizza), 1, arq);
	fclose(arq);
	return p;
}

int getKey(ArvBM a, int ind){
	int key
	char fname[2048];
	strcpy(fname,getNome(a));
	FILE *arq = fopen(fname, "rb");
	int end = getEnderecoKey(arq, ind);
	fseek(arq, end, SEEK_SET);
	fread(&key, sizeof(int), 1, arq);
	fclose(arq);
	return p;	
}

Pizza* buscaPizza(ArvBM a, int key){
	ArvBM ap = busca_arv(a, key);
	if(ap.k==-1)return NULL;
	Pizza *p = getPizza(ap, key);
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
}

void alteraPizza(ArvBM a, int key, float preco, char nome[51], char categoria[21]){
	ArvBM ap = busca_arv(a, key);
	if(ap.k==-1)return;
	Pizza *p = getPizza(ap, key);
	if(strcmp(p->categoria,categoria)!=0){
		retiraDaCategoria(p->cod, p->categoria);
		insereNaCategoria(p->cod, categoria);
	}
	setPizza(p, preco, nome, categoria);
	char fname[2048];
	strcpy(fname, getNome(ap));
	FILE *arq = fopen(fname, "rb+");
	int end = getEnderecoPizza(arq, ind);
	fseek(arq, end, SEEK_SET);
	fwrite(p, sizeof(Pizza), 1, arq);
}

