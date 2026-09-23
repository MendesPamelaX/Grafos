#include<stdio.h>
#include<stdbool.h>
#define V 5
#include<math.h>
#include<stdlib.h>
#include<limits.h>

typedef struct s{
    int adj;
    struct s* prox;
    int peso;
    int cia;
}NO;

typedef struct{
    NO* inicio;
    int flag;
    int via;
    int custo;
    int requerVisto;
    int capacidade;
    int dist;
    int tipo;
}VERTICE;

typedef struct estrutura{
    int chave;
    struct estrutura* prox;
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
    aux->prox = NULL;
    free(aux);
    if(!(f->inicio)) f->fim = NULL;
    return ch;
}

void inicializar(VERTICE* g){

    for(int i = 1; i <= V; i++){
        g[i].inicio = NULL;
    }
}

bool arestaExiste(VERTICE* g, int v1, int v2, NO** ant){
    *ant = NULL;
    NO* p = g[v1].inicio;

    while(p){
        if(p->adj == v2) return true;
        *ant = p;
        p = p->prox;
    }
    return false;
}

bool insereAresta(VERTICE*g, int v1, int v2){
    NO* ant = NULL;
    if(arestaExiste(g, v1, v2, &ant)) return false;
    NO* novo = (NO*)malloc(sizeof(NO));
    novo->adj = v2;
    novo->prox = g[v1].inicio;
    g[v1].inicio = novo;
    return true;
}

bool excluiAresta(VERTICE* g, int v1, int v2){
    bool ok = false;
    NO* ant = NULL;
    NO* aux;
    if(!(ok = arestaExiste(g, v1, v2, &ant))) return false; //aresta não existe;
    if(ant){
        aux = ant->prox;
        ant->prox = aux->prox;
    }
    aux = g[v1].inicio;
    g[v1].inicio = aux->prox;
    free(aux);
    return true;

}

int grauSaida(VERTICE* g, int v){
    int resp = 0;
    NO* p = g[v].inicio;
    while(p){
        resp++;
        p = p->prox;
    }
return resp;
}

int grauEntrada(VERTICE*g, int v){
    int resp = 0;

    for(int i = 1; i <= V; i++){
        NO* p = g[i].inicio;
        while(p){
            if(p->adj == v) resp++;
            p = p->prox;
        }
    }
    return resp;
}
void imprimeGrafo(VERTICE* g){
    
    for(int i = 1; i <= V; i++){
        NO* p = g[i].inicio;
        printf("Vértice:%d Lista de adjacentes:", i);
        while(p){
            printf("%d\t", p->adj);
            p = p->prox;
        }
        printf("\n");
    }
}

//Exercício: verificar se as arestas de g2 estão contidas em g1

bool arestag1(VERTICE* g1, VERTICE* g2){

    NO* p; bool ok = false; NO* ant = NULL;

    for(int i = 1; i <= V; i++){
        p = g2[i].inicio;
        while(p){
            if(!(ok = arestaExiste(g1, i, p->adj, &ant))) return false;
            p = p->prox;
        }
    }
    return true;
}

//Exercício: criar uma cópia de um grafo

VERTICE* copia(VERTICE*g){

    VERTICE* novoGrafo = (VERTICE*)malloc(sizeof(VERTICE)*(V+1));
    NO* p; 
    for(int i = 1; i <= V; i++){
        p = g[i].inicio;
        while(p){
            if(!insereAresta(novoGrafo, i, p->adj)){
                printf("Erro na criação de um novo vértice!\n");
                return NULL;
            }
            p = p->prox;
        }
    }
    return novoGrafo;
}

//Exercício: criar uma cópia transposta de um grafo versão I

VERTICE* copiaTransposta(VERTICE* g){

    NO* p; 
    VERTICE* novoGrafoT = (VERTICE*)malloc(sizeof(NO)*(V+1));
    for(int i = 1; i <= V; i++){
        p = g[i].inicio;

        while(p){

           if(!insereAresta(novoGrafoT, p->adj, i)){
            printf("Erro na criação de um novo vértice!\n");
            return NULL;
             }
            p = p->prox;
        }
    }
    return novoGrafoT;
}

//Exercício: criar uma cópia transposta versão II

VERTICE* copiaTranspostaII(VERTICE*g){
    NO* p;
    VERTICE* grafoTransposto = (VERTICE*)malloc(sizeof(NO)*(V+1));
    for(int i = 1; i <= V; i++){
        p = g[i].inicio;
        grafoTransposto[i].inicio = NULL;
        while(p){
            NO* novo = (NO*)malloc(sizeof(NO));
            novo->adj = i;
            novo->prox = grafoTransposto[p->adj].inicio;
            grafoTransposto[p->adj].inicio = novo;
        }
    }
    return grafoTransposto;
}

//Exercício: transformar grafo dirigido em não dirigido

void grafoNaoDirigido(VERTICE* g){
    NO* p;
    for(int i = 1; i <= V; i++){
        p = g[i].inicio;
        while(p){
            if(!insereAresta(g, p->adj, i)){
                printf("Erro na alocação de um novo vértice!\n");
                return;
            }
            p = p->prox;
        }
    }
}

//Exercício: verificar se dois grafos implementados através de listas de adjacências são idênticos

bool grafosIdenticos(VERTICE* g1, VERTICE* g2){

    NO* p; bool ok = false; NO* ant = NULL;

    for(int i = 1; i <= V; i++){
        p = g1[i].inicio;
        while(p){
            if(!(ok = arestaExiste(g2, i, p->adj, &ant))) return false;
        }
    }
    ok = false;

    for(int i = 1; i <= V; i++){
        p = g2[i].inicio;
        while(p){
            if(!(ok = arestaExiste(g1, i, p->adj, &ant))) return false;
        }
    }
    return true;
}

//Exercício: verificar se dois grafos com implementações diferentes idênticos

bool grafosIdenticosII(VERTICE* g, int m[V][V]){

    NO* p; bool ok = false; NO* ant = NULL;
      for(int i = 1; i <= V; i++){
        p = g[i].inicio;
        while(p){
            if(m[i][p->adj] != 1) return false;
            p = p->prox;
        }

        for(int i = 1; i <= V; i++){
            for(int j = 1; j <= V; j++){
                if(m[i][j] == 1){
                    if(!(ok = arestaExiste(g, i, j, &ant))) return false;
                }
            }
        }  
}
return true;
}

//Implementação do algoritmo de Busca em Profundidade

void prof(VERTICE* g, int i){

    g[i].flag = 1;
    NO* p = g[i].inicio;
    while(p){
        if(g[p->adj].flag == 0){
            prof(g, p->adj);
        }
        p = p->prox;
    }
    g[i].flag = 2;
}

//Exercício: verificar se o vértice "fim" é alcançável a partir do vértice "i"

void ehAlcancavel(VERTICE*g, int i, int fim, bool* achou){

    g[i].flag = 1;

    if(i == fim){
        *achou = true;
        return;
    }

    NO* p = g[i].inicio;
        while(p){
            if(g[p->adj].flag == 0  && !(*achou)){
                ehAlcancavel(g, p->adj, fim, achou);
            }
            p = p->prox;
        }
        
        g[i].flag = 2;
    }
    
//Exercício: exibir ciclos

void exibirCiclos(VERTICE* g, int i){

    g[i].flag = 1;

    NO* p = g[i].inicio;
    while(p){
        if(g[p->adj].flag == 1) printf("Ciclo encontrado: %d -> %d", i, p->adj);
        if(g[p->adj].flag == 0) exibirCiclos(g, p->adj);
    }
    g[i].flag = 2;
}

//Exercício: quantos vértices são alcançáveis a partir do vértice i?

void verticesAlcancaveis(VERTICE* g, int *cont, int i){

    g[i].flag = 1;
    NO* p = g[i].inicio;
    while(p){

        if(g[p->adj].flag == 0){
        (*cont)++;
         verticesAlcancaveis(g, cont, p->adj);
        }
        p = p->prox;
    }
    g[i].flag = 2;
}

//Exercício: retornar uma lista ligada em que os vértices representam países em que é possível viajar sem visto

void paisesSemVisto(VERTICE* g, int i, NO** resp){

    g[i].flag = 1;
    NO* p = g[i].inicio;
    while(p){
        if(g[p->adj].flag == 0){
            paisesSemVisto(g, p->adj, resp);
        }
        p = p->prox;
    }
    g[i].flag = 2;

    if(g[i].requerVisto == 1){

        NO* novo = (NO*)malloc(sizeof(NO));
        novo->adj = i;
        novo->prox = *resp;
        *resp = novo;
    }
}

//Exercício: verifique se é possível viajar de A até B usando apenas voos da compannhia x

void verifica(VERTICE* g, int a, int b, int x, bool* achou){

    if(a == b){
        *achou = true;
        return;
    }

    g[a].flag = 1;
    NO* p = g[a].inicio;
        while(p){

            if(g[p->adj].flag == 0 && p->cia == x){
                g[p->adj].flag = 1;
                verifica(g, p->adj, b, x, achou);
                if(*achou) return;
            }
            p = p->prox;
        }
    }

//Exercício: converter um grafo matriz em listas de adjacências

void converter(int m[V][V], VERTICE* g){

    for(int i = 1; i <= V; i++){
        for(int j = 1; j <= V; j++){
            if(m[i][j] == 1){
                NO* novo = (NO*)malloc(sizeof(NO));
                novo->adj = j;
                novo->prox = g[i].inicio;
                g[i].inicio = novo;
            }
        }
    }
}

//Exercício: verifique se há um caminho de a até b passando por x

bool caminho(VERTICE* g, int a, int b, int x){

    bool achou = false;
    ehAlcancavel(g, a, x, &achou);
    if (!achou) return false;
    achou = false;
    ehAlcancavel(g, x, b, &achou);
    if(!achou) return false;
    return true;
}

//Exibir até N salas com capacidade >= x, alcançáveis a partir de um início i

void exibir(VERTICE* g, int i, int x, int* n){

    if(*n == 0){
        return;
    }

    if(g[i].capacidade >= x){

        printf("%d\t", i);
        *n = (*n) - 1;

    }

    g[i].flag = 1;
    NO* p = g[i].inicio;

    while(p){

        if(g[i].flag == 0){
            g[i].flag = 1;
            exibir(g, p->adj, x, n);
        }
        p = p->prox;
    }
    g[i].flag = 2;
}

//Exercício: verifique se há um caminho de a até b que não passe por x

void haCaminho(VERTICE* g, int a, int b, int x, bool* achou){

    if(a == b){
        *achou = true;
        return;
    }

    g[a].flag = 1;
    NO* p = g[a].inicio;
    while(p){
        
        if(g[p->adj].flag == 0 && !(*achou) && p->adj != x){
            g[p->adj].flag = 1;
            haCaminho(g, p->adj, b, x, achou);
        }
        p = p->prox;
    }
    g[a].flag = 2;
}

void zerarFlags(VERTICE* g){

    for(int i = 1; i <= V; i++){
        g[i].flag = 0;
    }
}

//Algoritmos de busca em largura garantem que o caminho mais curto será garantidamente encontrado primeiro, diferente da busca em profundidade

void largura(VERTICE* g, int i){

    FDINAM f;
    inicializarFila(&f);
    zerarFlags(g);
    g[i].flag = 1;
    insereFila(&f, i);
    NO* p;
    int atual;

    while(f.inicio){

        atual = sairFila(&f);
        g[atual].flag = 2;
        p = g[atual].inicio;
        while(p){

            if(g[p->adj].flag == 0){
                insereFila(&f, p->adj);
                g[p->adj].flag = 1;
            }
            p = p->prox;
        }
    }
}

//Exercício: encontrar posto de gasolina mais próximo representado por x

void larguraII(VERTICE* g, int x, int i){

    FDINAM f;
    inicializarFila(&f);
    insereFila(&f, i);
    zerarFlags(g);
    g[i].flag = 1;
    int atual;
    NO* p;

    for(int i = 1; i <= V; i++){
        g[i].dist = -1;
    }

    g[i].dist = 0;

    while(f.inicio){


        atual = sairFila(&f);

        if(g[atual].tipo == x){
            printf("Posto encontrado! Distância: %d", g[atual].dist);
        }
        g[atual].flag = 2;
        p = g[atual].inicio;

        while(p){
            if(g[p->adj].flag == 0){
                g[p->adj].dist = g[atual].dist + 1;
                g[p->adj].flag = 1;
                insereFila(&f, p->adj);
            }
            p = p->prox;
        }
    }
}

void caminhos(VERTICE* g, int i){

    FDINAM f;
    inicializarFila(&f);

    for(int i = 1; i <= V; i++){
        g[i].flag = 0;
        g[i].custo = INT_MAX;
        g[i].via = -1;
    }

    g[i].custo = 0;
    g[i].flag = 1;
    insereFila(&f, i);
    int atual;
    NO* p;

    while(f.inicio){

        atual = sairFila(&f);
        g[atual].flag = 2;
        p = g[atual].inicio;

        while(p){

            if(g[p->adj].flag == 0){
                g[p->adj].flag = 1;
                g[p->adj].custo = g[atual].custo + p->peso;
                g[p->adj].via = atual;
                insereFila(&f, p->adj);
            }
            p = p->prox;
        }
    }
}

void imprimeVia(VERTICE* g, int i){

    int k = g[i].via;
    while(k != -1){
        printf("%d\t", k);
        k = g[k].via;
    }
}

/*O algoritmo de busca em largura serve para encontrar o caminho mais custo em termos de número de arestas, 
assumindo que todas têm o mesmo peso. Já o algoritmo de Dijkstra é usado para encontrar o caminho de peso mínimo (arestas com menor peso)*/

void dijkstra(VERTICE*g, int i){

    for(int i = 1; i <= V; i++){
        g[i].custo = INT_MAX;
        g[i].flag = 0;
        g[i].via = -1;
    }
    g[i].custo = 0;
    g[i].flag = 1;
    NO* p;
    int z;
    int custoz;

    while(true){

        z = -1;
        custoz = INT_MAX;

        for(int i = 1; i <= V; i++){
            if(g[i].flag == 0 && g[i].custo < custoz){
                z = i;
                custoz = g[i].custo;
            }
        }
        if(z == -1) return;
        g[z].flag = 1;
        p = g[z].inicio;

        while(p){
            int temp = g[z].custo + p->peso;
            if(temp < g[p->adj].custo){
                g[p->adj].custo = temp;
                g[p->adj].via = z;
            }
            p = p->prox;
        }
    }
}

//Exercício: verificar a quantidade de laços em um grafo

int lacos(VERTICE*g){

    int cont = 0;
    NO* p;
    for(int i = 1; i <= V; i++){
        p = g[i].inicio;

        while(p){

            if(p->adj == i){ 
                cont++;
                break;
            }

            p = p->prox;
        }
    }
    return cont;
}

//Exercício: remover laços de um grafo

void removeLacos(VERTICE* g){

    NO*p;
    for(int i = 1; i <= V; i++){
        p = g[i].inicio;
        while(p){
            if(p->adj == i) excluiAresta(g, i, p->adj);
            p = p->prox;
        }
    }
}
//Exercício: Escreva um algoritmo para destruir as arestas de um grafo, tornando-o vazio

void destroiArestas(VERTICE* g){

    NO* p;
    for(int i = 1; i <= V; i++){
        p = g[i].inicio;
        while(p){
            excluiAresta(g, i, p->adj);
            p = p->prox;
        }
    }
}

//Exercício: Seja um grafo g dirigido. Escreva um algoritmo para retornar o grafo transposto de g.

VERTICE* grafoTranspostoII(VERTICE* g){

    NO* p;
    VERTICE* grafoTransposto = (VERTICE*)malloc(sizeof(VERTICE) * (V+1));
    for(int i = 1; i <= V; i++){
        p = g[i].inicio;
        while(p){
            NO* novo = (NO*)malloc(sizeof(NO));
            novo->adj = i;
            novo->prox = grafoTransposto[p->adj].inicio;
            grafoTransposto[p->adj].inicio = novo;
            p = p->prox;
        }
    }
    return grafoTransposto;
}

int main(){

    VERTICE* g = (VERTICE*)malloc(sizeof(VERTICE) * (V + 1));
    inicializar(g);
    insereAresta(g, 1, 2);
    insereAresta(g, 2, 4);
    insereAresta(g, 2, 3);
    insereAresta(g, 1, 1);
    insereAresta(g, 3, 3);
    imprimeGrafo(g);

    VERTICE* gT = grafoTranspostoII(g);
    printf("Grafo transposto\n");
    imprimeGrafo(gT);

    int auxiliar = lacos(g);
    printf("Quantidade de laços: %d\n", auxiliar);
    removeLacos(g);
    auxiliar = lacos(g);
    printf("Quantidade de laços após remoção de auto-laços: %d\n", auxiliar);
    imprimeGrafo(g);
    destroiArestas(g);
    printf("Grafo após destruição de todas as arestas:\n");
    imprimeGrafo(g);
    





    free(g);
    free(gT);
    return 0;
}