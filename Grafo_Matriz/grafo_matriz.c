#include <stdio.h>
#include<stdbool.h>
#define V 5
#include<stdlib.h>
#include<limits.h>
int flags[V];

typedef struct estrutura{

    int adj;
    struct estrutura* prox;
}NOLISTA;

typedef struct {

    NOLISTA* inicio;

}VERTICE;

typedef struct s{
    int chave;
    struct s* prox;
}NOFILA;

typedef struct {
    NOFILA* inicio;
    NOFILA* fim;
}FDINAM;

void inicializarFila(FDINAM* f){
    f->inicio = NULL;
    f->fim = NULL;
}

int tamanhoFDINAM(FDINAM* f){

    int tam = 0;
    NOFILA* p = f->inicio;
    while(p){
        tam++;
        p = p->prox;
    }
    return tam;
}

void insereFila(FDINAM* f, int ch){

    NOFILA* novo = (NOFILA*)malloc(sizeof(NOFILA));
    novo->chave = ch;
    novo->prox = NULL;
    if(f->fim){ 
        f->fim->prox = novo; 
        f->fim = novo;
    }
    else f->inicio = novo;
    f->fim = novo;
}

int sairFila(FDINAM* f){

    if(!(f->inicio)) return -1;
    NOFILA* aux = f->inicio;
    int ch = aux->chave;
    f->inicio = aux->prox;
    free(aux);
    if(!(f->inicio)) f->fim = NULL;
    return ch;
}

void inicializar(int matriz[V][V]){
    for(int i = 0; i <= V; i++){
        for(int j = 0; j <= V; j++){
            matriz[i][j] = 0;
        }
    }
}

bool arestaExiste(int matriz[V][V], int v1, int v2){

    if(matriz[v1][v2] == 1) return true;

    return false;
}

void insereAresta(int matriz[V][V], int v1, int v2){
    
    if(arestaExiste(matriz, v1, v2)) return; //a aresta já existe
    matriz[v1][v2] = 1;
}

void excluiAresta(int matriz[V][V], int v1, int v2){

    if(!arestaExiste(matriz, v1, v2)) return; //a aresta não existe
    matriz[v1][v2] = 0;
}

int grauSaida(int matriz[V][V], int v){
    int cont = 0;
    for(int j = 1; j <= V; j++){
        if(matriz[v][j] == 1) cont++;
    }
    return cont;
}

int grauEntrada(int matriz[V][V], int v){
    int resp = 0;
        for(int i = 1; i <= V; i++){
            if(matriz[i][v] == 1) resp++;
        }
        return resp;
    }

void imprimeGrafo(int matriz[V][V]){

    for(int i = 1; i<= V; i++){
        printf("Vértice:%d Adjacentes:", i);
        for(int j = 1; j<=V; j++){
            if(matriz[i][j] == 1) printf("%d\t", j);
        }
        printf("\n");
    }
}

void imprimeGrafoLista(VERTICE* g){
    
    for(int i = 1; i <= V; i++){
        NOLISTA* p = g[i].inicio;
        printf("Vértice:%d Lista de adjacentes:", i);
        while(p){
            printf("%d\t", p->adj);
            p = p->prox;
        }
        printf("\n");
    }
}

////Implementação do algoritmo de Busca em Profundidade

void prof(int m[V][V], int i, int flags[V]){
    
    flags[i] = 1;
        for(int j = 1; j <= V; j++){
            if(m[i][j] == 1 && flags[j] == 0){
                prof(m, j, flags);
            }
        }
        flags[i] = 2;
    }

//Exercício: verificar se o vértice "fim" é alcançável a partir do vértice "i"

void ehAlcancavel(int m[V][V], int i, int fim, bool* achou, int flags[V]){

    if(i == fim){
        *achou = true;
        return;
    }
    
    flags[i] = 1;

        for(int j = 1; j <= V; j++){
            if(m[i][j] == 1 && flags[j] == 0){
                ehAlcancavel(m, j, fim, achou, flags);
            }
        }
        flags[i] = 2;
    }

void zerarFlags(int flags[V]){

    for(int i = 1; i <= V; i++){
        flags[i] = 0;
    }
}

//Algoritmos de busca em largura garantem que o caminho mais curto será garantidamente encontrado primeiro, diferente da busca em profundidade

void largura(int m[V][V], int i, int flags[V]){

    FDINAM f;
    inicializarFila(&f);
    zerarFlags(flags);
    insereFila(&f, i);
    flags[i] = 1;
    int atual;
    
    while(f.inicio){

        atual = sairFila(&f);
        flags[atual] = 2;

        for(int j = 1; j <= V; j++){
            if(m[atual][j] == 1 && flags[j] == 0){
                insereFila(&f, j);
                flags[j] = 1;
            }
        }
    }
    for(int i = 1; i <= V; i++){
        for(int j = 1; j <= V; j++){

        }
    }
}

/*Exercício: Escreva um algoritmo que dado um grafo m representado em matriz, retorne o mesmo grafo em
listas de adjacências.*/

VERTICE* matrizLista(int m[V][V]){

    VERTICE* listaAdj = (VERTICE*)malloc(sizeof(VERTICE) * (V+1));
    for(int i = 1; i <= V; i++){
        for(int j = 1; j <= V; j++){
            listaAdj[i].inicio = NULL;
            if(m[i][j] == 1){
                NOLISTA*  novo = (NOLISTA*)malloc(sizeof(NOLISTA));
                novo->adj = j;
                novo->prox = listaAdj[i].inicio;
                listaAdj[i].inicio = novo;
            }
        }
    }
    return listaAdj;
}



int main(){

int m[V][V];
insereAresta(m, 1, 2);
insereAresta(m, 2, 4);
insereAresta(m, 2, 3);
imprimeGrafo(m);

VERTICE* grafoLista = matrizLista(m);
printf("Imprimindo conversão de grafo matriz para grafo lista:\n");
imprimeGrafoLista(grafoLista);


    return 0;
}
