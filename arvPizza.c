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
	cria_raiz(nome, -1);
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
	strcpy(fname, getNome(a));
	FILE *arq = fopen(fname, "wb");
	/*primeiro 1 diz que e folha*/
	fwrite(&a.nk, sizeof(int), 1, arq);
	/*segundo a quantidade de chaves*/
	fwrite(&a.nk, sizeof(int), 1, arq);
	escreve_pizza(arq,p);
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
	strcpy(fname, getNome(a));
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
	strcpy(fname, getNome(a));
	FILE *arq = fopen(fname, "wb");
	fwrite(&a.folha, sizeof(int), 1, arq);
	fwrite(&a.nk, sizeof(int), 1, arq);
	fclose(arq);
}

void escreve_chave(ArvBM a, int ind, int k){
	if(a.folha==1)return;
	int end = 2*sizeof(int)*(1+ind) + sizeof(int);
	char fname[2048];
	strcpy(fname, getNome(a));
	FILE *arq = fopen(fname, "rb+");
	fseek(arq, end, SEEK_SET);
	fwrite(&k, sizeof(int), 1, arq);
	fclose(arq);
}

void escreve_filho(ArvBM a, int ind, int kFilho){
	if(a.folha==1)return;
	int end = 2*sizeof(int)*(1+ind);
	char fname[2048];
	strcpy(fname, getNome(a));
	FILE *arq = fopen(fname, "rb+");
	fseek(arq, end, SEEK_SET);
	fwrite(&k, sizeof(int), 1, arq);
	fclose(arq);
}

int get_filho(ArvBM a, int ind){
	if(a.folha==1)return;
	int end = 2*sizeof(int)*(1+ind), k;
	char fname[2048];
	strcpy(fname, getNome(a));
	FILE *arq = fopen(fname, "rb");
	fseek(arq, end, SEEK_SET);
	fread(&k, sizeof(int), 1, arq);
	fclose(arq);
	return k;
}

int get_chave(ArvBM a, int ind){
	if(a.folha==1)return;
	int end = 2*sizeof(int)*(1+ind) + sizeof(int), k;
	char fname[2048];
	strcpy(fname, getNome(a));
	FILE *arq = fopen(fname, "rb");
	fseek(arq, end, SEEK_SET);
	fread(&k, sizeof(int), 1, arq);
	fclose(arq);
	return k;
}

void atualiza_nchaves(ArvBM a){
	char fname[2048];
	strcpy(fname, getNome(a));
	FILE *arq = fopen(fname, "rb+");
	fseek(arq, sizeof(int), SEEK_SET);
	fwrite(&a.nk, sizeof(int), 1, arq);
	fclose(arq);
}

void escreve_prox(){

}

ArvBM divisao(ArvBM b, int i, ArvBM a){
	ArvBM c = inicializa(b.nome);
	int t = c.t = b.t;
	c.folha = a.folha;
	escreve_no(c);
	int j;
	if(!a.folha){
		c.nk = t-1;
		atualiza_nchaves(c);
		for(j=0;j<t-1;j++){
			escreve_chave(c, j, get_filho(a, j+t));
			escreve_filho(c, j, get_filho(a, j+t));
		}
		escreve_filho(c, t-1, get_filho(a, j+t));
	}
	else {
		c.nk = t;
		atualiza_nchaves(c);
		for(j=0;j<t;j++)
			escreve_chave(c, j, get_chave());
			z->chave[j] = y->chave[j+t-1];
		escreve_prox(a, c->k);
	}
	a.nk = t;
	atualiza_nchaves(a);
	for(j=b.nk;j>=i;j--)
		escreve_filho(b, j+1, get_filho(b, j));
	escreve_filho(b, i, c.k);
	for(j=b.nk;j>=i;j--)
		escreve_chave(b, j, get_chave(b, j-1));
		x->chave[j] = x->chave[j-1];
	x->chave[i-1] = y->chave[t-1];
	x->nchaves++;
	return x;
}

TABM *insere_nao_completo(TABM *x, int mat, int t){
  int i = x->nchaves-1;
  if(x->folha){
    while((i>=0) && (mat < x->chave[i])){
      x->chave[i+1] = x->chave[i];
      i--;
    }
    x->chave[i+1] = mat;
    x->nchaves++;
    return x;
  }
  while((i>=0) && (mat < x->chave[i])) i--;
  i++;
  if(x->filho[i]->nchaves == ((2*t)-1)){
    x = divisao(x, (i+1), x->filho[i], t);
    if(mat > x->chave[i]) i++;
  }
  x->filho[i] = insere_nao_completo(x->filho[i], mat, t);
  return x;
}


/* modifica os nos de indice se preciso*/
ArvBM insere_arv(ArvBM a, Pizza *p){
	ArvBM res_busca = busca_arv(a, p->cod);
	if(res_busca.k != -1)
		return a;
	if(a.k == -1){
		a=cria_folha(p);
		return a;
	}
	if(a.nk == (2*a.t)-1){
		ArvBM b = cria_no_interno(a.nome, t, key);
		b = divisao();
		b = insere_nao_completo();
		//b = divisao(b,1,a,t);
		//b = insere_nao_completo(a, mat, t);
		muda_raiz(b.k);
		return b;
	}
	a = insere_nao_completo();
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
/*retorna arvore com a.ind=indice da pizza*/
ArvBM busca_arv(ArvBM a, int key){
	int nk = a.nk, i, folha=0, k;
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

