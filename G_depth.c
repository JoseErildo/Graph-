#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

struct alist* new_alist(int a);
struct list* new_node(int v);
void listaAdjacencia(struct alist** G);
void insert_node(struct list **vert,int b);
void print_node(struct list *vert);
void print_adj(struct alist *G);

void addVetor(int *vetor, int v);
int verificaVetor(int *v, int m, int k);

void listaEncadeada(struct alist **G);
void naoEncadeada(struct alist **G);

int search_depth(struct alist *G, int posicao,int k, int *memoria, int *pilha);
int search_Node(struct alist *G, struct list *t, int k, int *memoria, int *pilha);
int* new_vetor(int m);
void removePilha(struct alist* G, int *pilha);

struct alist{ //grafo;

    struct list **t; //lista de adjacencias;
    unsigned int n; // qtd de nos;
    unsigned int e; // qtd de arestas;
};

struct list{ //vertice;

    int v; //valor do vertice;
    struct list *p; //ponteiro proximo vertice;
};

int main(){
    int a;

    scanf("%d\n",&a); //recebe o numero de vertices do grafo;

    struct alist *G = new_alist(a); //cria uma nova estrutura alist e armazena em um ponteiro para a variavel G;

    listaAdjacencia(&G); //cria-se a lista de adjacencia;

            //chamada para a busca em profundidade;
    int u = search_depth(G, 1, 3, new_vetor(G->n), new_vetor(G->n)); //*grafo, índice a se iniciar a percurssão, chave, memoria de marcação, pilha);

    printf("%d \n",u); //printa o retorno da busca em profundidade;
    print_adj(G);   //printa a lista de adjacencia;

    return 0;
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

struct list* new_node(int v){

    struct list* node = (struct list*)malloc(sizeof(struct list));
    node->v = v;
    node->p = NULL;

    return node;
}

void listaAdjacencia(struct alist** G){
    char s;
    
    scanf("%c",&s);
    if (s == 'n'){
        listaEncadeada(&(*G));
    }
    else{
        naoEncadeada(&(*G));
    }
    
}

void listaEncadeada(struct alist **G){

    int a,b;

    while (scanf("%d %d", &a, &b) != EOF){
        insert_node(&((*G)->t[a - 1]), b - 1);
        insert_node(&((*G)->t[b - 1]), a - 1);
    }
}

void naoEncadeada(struct alist **G){

    int a,b;

    while (scanf("%d %d", &a, &b) != EOF){
        insert_node(&((*G)->t[a - 1]), b - 1);
    }
}

void insert_node(struct list **vert,int b){
    if (*vert == NULL){
        *vert = new_node(b);
    }
    else{
        insert_node(&((*vert)->p), b);
    }
}

//busca em profundidade
int search_depth(struct alist *G, int posicao,int k, int *memoria, int *pilha){ //*grafo, posição da memoria, chave, memoria de marcação, pilha*

    //se houver conteúdo na posição -1 (-1 devido o primeiro índice de um vetor começar em 0);
    if (G->t[posicao-1] != NULL){
        //se não estiver marcado;
        if (!verificaVetor(memoria, G->n, G->t[posicao-1]->v)){
            if (G->t[posicao-1]->v == k){ //se o vertice for igual a chave;
                return k; //retorna a chave;
            }   
            addVetor(memoria, G->t[posicao-1]->v); //adiciona o vertice na marcação;
            addVetor(pilha,G->t[posicao-1]->v); //adiciona o vertice na pilha;

            //busca-se o vertice que corresponderia ao ultimo elemento da pilha;
            //se a chave for encontrada;
            if(search_depth(G, G->t[posicao-1]->v, k, memoria, pilha)){
                return k; //retorna a chave;
            }
            //remove o ultimo elemento da pilha;
            removePilha(G, pilha);
        }

        //busca-se os nós do vetor atual;
        //se a chave for encontrada;
        if(search_Node(G, G->t[posicao-1]->p,k, memoria, pilha)){
            return k;   //retorna-se a chave;
        }
        
    }
    return 0;   //se a chave não for encontrada, retorna-se 0;
}

//busca-se os nós do vetor atual;
int search_Node(struct alist *G, struct list *t, int k, int *memoria, int *pilha){ //*grafo, vetor atual, chave, memoria de marcação, pilha*

    //se houver conteúdo na memória;
    if (t != NULL){

        //se o vetor não estiver marcado;
        if (!verificaVetor(memoria, G->n,t->v)){
                        
            if (t->v == k){ //se o vetor for igual a chave;
                return k; //retorna-se a chave;  
            } 

            addVetor(memoria, t->v); //marca-se o vetor atual;
            addVetor(pilha,t->v);   //adiciona o vetor à pilha;

            //busca-se o vertice que corresponderia ao ultimo elemento da pilha;
            //se a chave for encontrada;
            if(search_depth(G, t->v, k, memoria, pilha)){
                return k; //retorna-se a chave;
            }
            //remove o ultimo elemento da pilha;
            removePilha(G, pilha);
        }

        //busca-se os nós do vetor atual;
        //se a chave for encontrada;
        if (search_Node(G,t->p,k,memoria, pilha)){
            return k; //retorna-se a chave;
        }
    }
    return 0;   //se a chave não for encontrada, retorna-se 0;
}

//remove ultimo elemento da pilha.
void removePilha(struct alist* G, int *pilha){

    int i = 0;
    
    //enquanto a posição da memória for diferente de 0 estiver dentro do vetor;
    while ((pilha[i] != 0) || (pilha[i] != '\0')){
        i++;
    }

    //se a posição for diferente de 0, adiciona-se 0 a posição i da pilha;
    pilha[i] = 0;
}

//Verifica se um número está contido no vetor
int verificaVetor(int *v, int m, int k){ //*vetor, tamanho, vertice*

    for(int i = 0; i<m; i++){
        if (v[i] == k){ //se o vertice estiver no vetor;
            return 1;   //está marcado;
        }
    }
    return 0;   //não está marcado;
}

//adiciona um elemento a um vetor;
void addVetor(int *vetor, int v){
    int i = 0;

    //enquanto a posição do vetor for diferente de 0;
    while (vetor[i] != 0){
        i++;
    }

    //atribui-se a posição i do vetor o valor v;
    vetor[i] = v;
}

//novo vetor;
int* new_vetor(int m){

    //armazena espaço na memoria de tamanho m para um ponteiro da variavel v;
    int *v = (int*)malloc(m*sizeof(int));

    //zera o vetor;
    for (int i = 0; i<m; i++){
        v[i] = 0;
    }

    //v[0] = 1;  //Se houver algum erro, reveja essa condição

    return v; //retorna o vetor;
}
