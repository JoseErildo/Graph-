#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

struct alist* new_alist(int a);
struct list* new_node(int v, int c);

void listaAdjacencia(struct alist** G);
void listaEncadeada(struct alist **G);
void insert_node(struct list **vert,int b, int c);

void print_adjBest(struct alist *G, int *memoria);
void print_adjBest_node(struct alist *G, struct list *t, int *memoria);
void print_node(struct list *vert);
void print_adj(struct alist *G);

int verificaVetor(int *v, int m, int k);
int* new_memoria(int m);

void search_weight(struct alist **F, struct alist *G, int *memoria);
int confereMemoria(int *memoria, int m);
int confereMemoria(int *memoria, int m);

void buscarPeso(struct alist **F, struct alist *G, int k, int *memoria);
void buscarPesoNo(struct alist **F, struct alist *G, struct list *t, int k, int *memoria, int i);

void percorreVetor(int n, int v, int *memoria, struct alist *G);
void addVetor(int v, int i, int *memoria, struct alist *G);
int* new_memoria(int m);

void printVetor(int *memoria);
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
    scanf("%d\n",&a);

    struct alist *G = new_alist(a);
    struct alist *F = new_alist(a);

    listaAdjacencia(&G);
    
    int *memoria = new_memoria(G->n);

    
    search_weight(&F, G, memoria);
    
    print_adj(F);

    return 0;
}
void printVetor(int *memoria){

    for(int i=0; i <7;i++){
        printf(" %d", memoria[i]);
    }
}

/*void print_adjBest(struct alist *G, int *memoria){

    for(int i = 0; i<G->n; i++){
        if (verificaVetor(memoria, G->n, G->t[i]->v)){
            printf("\n%d %d ", i+1, G->t[i]->v+1);
        }
        print_adjBest_node(G, G->t[i]->p, memoria);
    }
}

void print_adjBest_node(struct alist *G, struct list *t, int *memoria){

    if (t != NULL){
        if(verificaVetor(memoria, G->n, t->v)){
            printf("%d ", t->v+1);
        }
        print_adjBest_node(G, t->p, memoria);
    }
}*/

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
        printf("%d ",vert->v + 1);
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
        (*G)->e++;
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

void search_weight(struct alist **F, struct alist *G, int *memoria){

    int peso = 1;

    while((*F)->e != G->n-1){
        buscarPeso(&(*F), G, peso, memoria);
    
        peso++;
    }
}

void buscarPeso(struct alist **F, struct alist *G, int k, int *memoria){

    for(int i = 0; i < G->n; i++){
        if(G->t[i]->peso == k){
            if (memoria[i] != memoria[G->t[i]->v]){
                addVetor(G->t[i]->v, i, memoria, G);

                insert_node(&((*F)->t[i]), G->t[i]->v, G->t[i]->peso);
                insert_node(&((*F)->t[G->t[i]->v]), i, G->t[i]->peso);
                (*F)->e++;
            }        
        }
        
        buscarPesoNo(&(*F), G, G->t[i]->p, k, memoria, i);
    }
}

void buscarPesoNo(struct alist **F, struct alist *G, struct list *t, int k, int *memoria, int i){

    if  (t != NULL){
        if(t->peso == k){
            if (memoria[i] != memoria[t->v]){
                addVetor(t->v, i, memoria, G);

                insert_node(&((*F)->t[i]), t->v, t->peso);
                insert_node(&((*F)->t[t->v]), i, t->peso);
                (*F)->e++;
            }
        }
        buscarPesoNo(&(*F), G, t->p, k, memoria, i);
    }
}

void addVetor(int v, int i, int *memoria, struct alist *G){
    int n = memoria[v];

    memoria[v] = memoria[i];
    percorreVetor(n, memoria[v], memoria, G);
}

void percorreVetor(int n, int v, int *memoria, struct alist *G){

    for (int i=0; i < G->n; i++){
        if (memoria[i] == n){
            memoria[i] = v;
        }
    }
}

int* new_memoria(int m){

    int *v = (int*)malloc(m*sizeof(int));

    for (int i = 0; i<m; i++){
        v[i] = i;
    }

    return v;
}

