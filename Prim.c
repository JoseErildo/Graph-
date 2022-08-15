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
int* new_vetor(int m);

void buscarPeso(struct alist *G, struct alist **F, int i, int *memoria, int *vetor);
void buscarPesoNo(struct alist *G, struct alist **F, struct list *t, int i, int *memoria, int *vetor);

void menor(struct alist *G, struct list *t, int *vetor, int i, int *memoria);
void addVetorMenor(int peso, int *vetor);
void zeraVetor(struct alist *G, int *vetor);
int nMenor(struct alist *G, int *vetor);

void percorreVetor(int n, int v, int *memoria, struct alist *G);
void addVetor(int v, int i, int *memoria, struct alist *G);
int* new_memoria(int m);
void infinityVetor(struct alist *G, int *vetor);
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
    int *vetor = new_vetor(G->n);
    

    menor(G, G->t[0], vetor, 0, memoria);
    buscarPeso(G, &F, 0, memoria, vetor);
    
    
    print_adj(F);

    return 0;
}
void printVetor(int *memoria){

    for(int i=0; i <7;i++){
        printf(" %d", memoria[i]);
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

void buscarPeso(struct alist *G, struct alist **F, int i, int *memoria, int *vetor){

    if((*F)->e = G->n-1){
        if (G->t[i] ->peso == nMenor(G, vetor)){
            infinityVetor(G, vetor);

            if(memoria[i] != memoria[G->t[i]->v]){
                addVetor(G->t[i]->v, i, memoria, G);

                insert_node(&((*F)->t[i]), G->t[i]->v, G->t[i]->peso);
                insert_node(&((*F)->t[G->t[i]->v]), i, G->t[i]->peso);
                (*F)->e++;
                }

                menor(G, G->t[G->t[i]->v], vetor, G->t[i]->v, memoria);
                buscarPeso(G, &(*F), G->t[i]->v, memoria, vetor);
        }
        else{
            buscarPesoNo(G, &(*F), G->t[i]->p, i, memoria, vetor);
        }
    }
}

void menor(struct alist *G, struct list *t, int *vetor, int i, int *memoria){
    
    if (t != NULL){
        if(memoria[i] != memoria[t->v]){
            addVetorMenor(t->peso, vetor);
        }   
        menor(G, t->p, vetor, i, memoria); 
    }
    
}

void addVetorMenor(int peso, int *vetor){
    
    int i = 0;
    while (vetor[i] != 999){
        i++;
    }

    vetor[i] = peso;
}

void infinityVetor(struct alist *G, int *vetor){

    for (int i=0; i<G->n; i++){
        vetor[i] = 999;
    }
}

int nMenor(struct alist *G, int *vetor){
    int aux = 0;

    for (int i = 1; i< G->n; i++){
        if (vetor[aux] > vetor[i]){
            aux = i;
        }
    }

    aux = vetor[aux];
    

    return aux;
}

void buscarPesoNo(struct alist *G, struct alist **F, struct list *t, int i, int *memoria, int *vetor){

        if (t != NULL){
            if(t->peso == nMenor(G, vetor)){ 
                infinityVetor(G, vetor);

                if(memoria[i] != memoria[t->v]){
                    addVetor(t->v, i, memoria, G);
                    insert_node(&((*F)->t[i]), t->v, t->peso);
                    insert_node(&((*F)->t[t->v]), i, t->peso);
                    (*F)->e++;
                }   
                menor(G, G->t[t->v], vetor, t->v, memoria);
                buscarPeso(G, &(*F), t->v, memoria, vetor);
            }
        else{
            buscarPesoNo(G, &(*F), t->p, i, memoria, vetor);
        }
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

int* new_vetor(int m){

    int *v = (int*)malloc(m*sizeof(int));

    for (int i = 0; i<m; i++){
        v[i] = 999;
    }
    return v;
}
