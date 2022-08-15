#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

struct alist* new_alist(int a);
struct list* new_node(int v, int c);

void listaAdjacencia(struct alist** G);
void listaEncadeada(struct alist **G);
void insert_node(struct list **vert,int b, int c);

void print_node(struct list *vert);
void print_adj(struct alist *G);

void menorCaminho(struct alist *G, int *memoria, int *lista, int *dist);
int menorDistancia(struct alist *G, int aux, int *dist, int *memoria);
int verificaVetor(int *v, int m, int k);
int verificaLista(struct alist *G, int *lista);
int elementoLista(struct alist *G, int *lista);
void removeLista(int *lista, int w);
void relaxamento(struct list *t, int *dist, int w);
int* new_memoria(int m);
int* new_list(int m);
int* new_dist(int m);
void addMemoria(int *vetor, int v);

void printDist(int *dist, int m);

struct alist{

    struct list **t;
    unsigned int n; // qtd de nos
    unsigned int e; // qtd de arestas
};

struct list{

    int v;
    int peso;
    struct list *p;
};

int main(){

    int a;    
    scanf("%d\n",&a); //armazena a quantidade de vertices do grafo;

    struct alist *G = new_alist(a);
    
    //criação de vetor de distancia;
    //armazena-se o vetor retornado em new_dist para o ponteiro da variável dist;
    int *dist = new_dist(G->n);

    //cria-se a lista de adjacencia;
    listaAdjacencia(&G);

    //inicia-se a busca pelo menor caminho;
    menorCaminho(G, new_memoria(G->n), new_list(G->n), dist); //*grafo, memoria de marcação, lista de sequencia, vetor de distancias*

    print_adj(G);
    //printDist(dist, G->n);

    return 0;
}

//printa as distancias;
void printDist(int *dist, int m){
    
    //printa as distancias do vetor dist;
    for(int i = 0; i < m; i++){
        printf("%d\n", dist[i]);
    }
}

void print_adj(struct alist *G){

    for (int i = 0; i<G->n;i++){
        printf("%d: ", i + 1);
        print_node(G->t[i]);
        printf("\n");
    }
}
void print_node(struct list *vert){
    if (vert != NULL)
    {
        printf("%d %d ",vert->v + 1, vert->peso);
        print_node(vert->p);
    }
}

struct alist* new_alist(int a){

    struct alist *l = (struct alist*)malloc(sizeof(struct alist));
    l->t = (struct list**)malloc(a*sizeof(struct list*));

    for (int i = 0; i<a;i++){
        l->t[i] = NULL;
    }

    l->n = a;
    l->e = 0;

    return l;
}

struct list* new_node(int v, int c){

    struct list* node = (struct list*)malloc(sizeof(struct list));
    node->v = v;
    node->peso = c;
    node->p = NULL;

    return node;
}

void listaAdjacencia(struct alist** G){
    char s;
    
    scanf("%c",&s);

    listaEncadeada(&(*G));
 
}

void listaEncadeada(struct alist **G){

    int a,b, c;

    while (scanf("%d %d %d", &a, &b, &c) != EOF){
        insert_node(&((*G)->t[a - 1]), b - 1, c);
        insert_node(&((*G)->t[b - 1]), a - 1, c);
    }
}

void insert_node(struct list **vert,int b, int c){
    if (*vert == NULL){
        *vert = new_node(b, c);
    }
    else{
        insert_node(&((*vert)->p), b, c);
    }
}

//busca-se o menor caminho
void menorCaminho(struct alist *G, int *memoria, int *lista, int *dist){

    //será percorrido todos os índices da lista de adjacencias;
    for(int i = 0; i< G->n; i++){

        //se a lista de conteúdo for diferente de 0;
        if (verificaLista(G, lista)){
            //procura-se a menor distancia que há no vetor dist e armazena-o em w;
            int w = menorDistancia(G, elementoLista(G, lista)-1, dist, memoria);
            
            //adiciona o valor de w+1 na memoria de marcação;
            addMemoria(memoria, w + 1);

            //remove a posição w da lista;
            removeLista(lista, w);
            //faz o relaxamento;
            relaxamento(G->t[w], dist, w);
        }
    }
}

int verificaLista(struct alist *G, int *lista){    
    for (int i = 0; i < G->n; i++){
        if (lista[i] != 0){
            return 1;
        }
    }
    return 0;
}

//procura-se a menor distância que há no vetor dist;
int menorDistancia(struct alist *G, int aux, int *dist , int *memoria){

    //percorre o vetor;
    for (int i = aux+1; i< G->n; i++){
        //se posição dist[aux] for maior que posição dist[i] e não estiver marcado;
        if ((dist[aux] > dist[i])  && (!verificaVetor(memoria, G->n, i)) ){
            aux = i;
        }
    }
    return aux;
}

//verifica se há marcação
int verificaVetor(int *v, int m, int k){ //*vetor, tamanho, vertice*

    for(int i = 0; i<m; i++){ //percorre o vetor;
        if (v[i] == k){ //se alguma posição do vetor for igual ai vertice;
            return 1;   //está marcado;
        }
    }
    return 0;   //se não estiver marcado, retorna 0;
}

int elementoLista(struct alist *G, int *lista){

    for (int i = 0; i< G->n; i++){
        if (lista[i] != 0){
            return lista[i];
        }
    }    
}

//remover a posição w da lista;
void removeLista(int *lista, int w){

    lista[w] = 0;
}

//relaxamento
void relaxamento(struct list *t, int *dist, int w){

    if(dist[t->v] > dist[w] + t->peso){
        dist[t->v] = dist[w] + t->peso;
    }

    if (t->p != NULL){
        relaxamento(t->p, dist, w);
    }
}

int* new_memoria(int m){

    int *v = (int*)malloc(m*sizeof(int));

    for (int i = 0; i<m; i++){
        v[i] = 0;
    }

    return v;
}

int* new_list(int m){

    int *v = (int*)malloc(m*sizeof(int));

    for (int i = 0; i<m; i++){
        v[i] = i+1;
    }

    return v;
}

int* new_dist(int m){

    int *v = (int*)malloc(m*sizeof(int));

    for (int i = 0; i<m; i++){
        v[i] = 999;
    }
    v[0] = 0;

    return v;
}

//adiciona elemento na memoria de marcação;
void addMemoria(int *vetor, int v){
    int i = 0;

    //enquanto o elemento do vetor for diferente de 0;
    while (vetor[i] != 0){
        i++;
    }
    //posiçao i do vetor = valor de v;
    vetor[i] = v;
}
