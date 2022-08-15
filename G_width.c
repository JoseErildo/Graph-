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

int search_width(struct alist *G, int k);
int buscaNode(struct alist *G, struct list *p, int *fila, int k, int *memoria);
void ordenaFila(struct alist *G, int *fila);
void zeraVetor(struct alist *G, int *fila);
void addVetor(int *vetor, int v);
int verificaVetor(int *v, int m, int k);

void listaEncadeada(struct alist **G);
void naoEncadeada(struct alist **G);

struct alist{ //grafo

    struct list **t; //lista de adj
    unsigned int n; // qtd de nos
    unsigned int e; // qtd de arestas
};

struct list{    //vertice

    int v;  //valor
    struct list *p; //proximo
};

int main(){

    int a;
    scanf("%d\n",&a); //armazena tamanho do vetor de acordo com o txt;

    struct alist *G = new_alist(a); //cria uma estrutura alist com uma lista de adjacencia com tamanho a de linhas;
    listaAdjacencia(&G);    //cria a lista de adjacencia da estrutura G;

    int u = search_width(G, 3); //inicia a busca em largura pelo vertice 3 e retorna o resultado à variavel u;
    printf("%d \n",u);  //printa a variavel u para saber se foi encontrado ou nao.
    print_adj(G);   //printa a lista de adjacencia

    return 0;
}

//função para printar a lista de adjacencia
void print_adj(struct alist *G){

    //enquanto todas as colunas não forem verificadas
    for (int i = 0; i<G->n;i++){
        printf("%d: ", i + 1);  //print valor de i + 1 (isso é devido a primeira posição de memoria começar com 0, portanto precisando-se somar com 1);
        print_node(G->t[i]);    //percorre as ligações do vertice da posição i na lista;
        printf("\n");   //pula uma linha;
    }
}

//função para printar as ligações do vertice
void print_node(struct list *vert){
    if (vert != NULL)   //se houver conteúdo no vertice 
    {
        printf("%d ",vert->v + 1);  //printe o valor do vertice + 1 (devido ter sido subtraído 1 do valor dos vertices na criação da lista de adj;

        print_node(vert->p);    //parte para a próxima ligação do vertice
    }
}

//criação do grafo
struct alist* new_alist(int a){

    //aloca memoria para um ponteiro da variavel l;
    struct alist *l = (struct alist*)malloc(sizeof(struct alist));
    l->t = (struct list**)malloc(a*sizeof(struct list*));   //define o numero de linhas para a lista de adjacencia a partir do valor de a;

    //anula todos os campos da lista de adjacencia;
    for (int i = 0; i<a;i++){
        l->t[i] = NULL;
    }

   //atribuções de valores as variaveis da estrutra do grafo, alist;
    l->n = a;   //numero de vertices = a;
    l->e = 0;   //numero de arestas = 0, por enquanto;

    return l;   //retorna a estrutura criada;
}

//criação de vertice
struct list* new_node(int v){

    //aloca memoria para um ponteiro da estrutura node;
    struct list* node = (struct list*)malloc(sizeof(struct list));
    node->v = v;    //valor do vertice = valor da variavel v;
    node->p = NULL; //proximo da estrutura = NULL;

    return node;    //retorna a estrutura criada;
}

//criação da lista de adjacencia;
void listaAdjacencia(struct alist** G){
   
     char s;    //armazena o tipo de lista, encadeada/ordenada ou não;
    
    scanf("%c",&s); 
    if (s == 'n'){  //se s for = n, então será criada uma lista nao ordenada;
        naoEncadeada(&(*G));
    }
    else{   //caso contrário, lista ordenada;
        listaEncadeada(&(*G));
    }
    
}

//criação de lista nao ordenada
void naoEncadeada(struct alist **G){

    int a,b; //armazenam a posição(a) a ser colocado o vetor(b);

    //enquanto houver linha;
    while (scanf("%d %d", &a, &b) != EOF){
        insert_node(&((*G)->t[a - 1]), b - 1);  //adiciona um novo nó à lista de adjacencia na posição a-1 com o valor de b-1 (isso devido a condição de o primeiro índice do vetor iniciar com 0);

        insert_node(&((*G)->t[b - 1]), a - 1);  //*dupla ligação* adiciona um novo nó à lista de adjacencia na posição b-1 (valor vetor) com o valor de a-1 (posição vetor);
    }
}

//criação de lista ordenada;
void listaEncadeada(struct alist **G){

    int a,b; a,b; //armazenam a posição(a) a ser colocado o vetor(b);

    //enquanto houver linha;
    while (scanf("%d %d", &a, &b) != EOF){
        insert_node(&((*G)->t[a - 1]), b - 1);  //adiciona um novo nó à lista de adjacencia na posição a-1 com o valor de b-1 (isso devido a condição de o primeiro índice do vetor iniciar com 0);
    }
}

//insere um novo nó à lista de adjacencia;
void insert_node(struct list **vert,int b){

    if (*vert == NULL){ //se a posição chamada for igual a null;
        *vert = new_node(b); //a posição da memoria recebera um vertice de valor b;
    }
    else{ //caso contrário a posição seja diferente de null;
        insert_node(&((*vert)->p), b); //chamada para a inserção, passando o proximo endereço do vertice atual;
    }
}

//busca em largura;
int search_width(struct alist *G, int k){ //*grafo, chave*

    //criam-se dois vetores de tamanho do numero de vertices e os zeram;
    int fila[G->n]; //fila de sequencia;
    int memoria[G->n]; //marcação de arestas;
    zeraVetor(G,memoria);
    zeraVetor(G, fila);

    fila[0] = 1;    //atribui o valor 1 à posição de memoria 0 da fila;
    
    while (fila[0] != 0){  //enquanto houver conteúdo na fila;
    
        //verifica se um vertice está marcado;
        if (!verificaVetor(memoria, G->n, G->t[fila[0]-1]->v)){ //caso nao
            
            if (G->t[fila[0]-1]->v == k){ //verifica se a posição elemento fila -1 da lista da adjacencia é igual a chave; 
                return k;   //se for o elemento procurado, retorna a chave;
            }
            //se não, marca-se o vetor;
            addVetor(memoria,G->t[fila[0]-1]->v);
        }   

        //se houver conteudo no proximo do vertice atual;
        if (G->t[fila[0]-1]->p != NULL){
            
            //continua a busca entre os vizinhos
            if (buscaNode(G, G->t[fila[0]-1]->p, fila, k, memoria)){    //se tiver encontrado a chave;
                
                return k;   //retorna a chave;
            }
        }

        //remove o primeiro elemento da fila e os ordena, para seguir a sequencia;
        fila[0] = 0;
        ordenaFila(G, fila);
    }

    return -1;  //se a chave nao for encontrada, retorna-se -1;
}

//continua a busca através dos nós;
int buscaNode(struct alist *G, struct list *p, int *fila, int k, int *memoria){ //*grafo, vertice, fila, chave, memoria);

    //se o vertice atual nao estiver marcado;
    if (!verificaVetor(memoria, G->n, p->v)){
        if (p->v == k){ //verifica se é o elemento buscado
            return k;
        }

        //caso não seja, adiciona o vertice atual na fila e o marca;
        addVetor(fila, p->v);
        addVetor(memoria, p->v);
    }

    //se houver conteúdo no proximo do vertice atual;
    if (p->p != NULL){
        if (buscaNode(G, p->p, fila, k, memoria)){ //se tiver encontrado a chave;
            return k; //retorna a chave;
        }
    }

    return 0; //se a chave nao for encontrada, retorna 0;
}

//Verifica se um número está contido no vetor
int verificaVetor(int *v, int m, int k){ //*vetor, tamanho, valor do vertice*

    //percorre o vetor
    for(int i = 0; i<m; i++){
        if (v[i] == k){ //se houver algum elemento no vetor igual ao vertice;
            return 1;   //o vertice está marcado;
        }
    }
    return 0;   //caso nao, o vertice não está marcado;
}

//ordena a fila;
void ordenaFila(struct alist *G, int *fila){

//ordena a fila de forma que a posição 0 do vetor, seja diferente de 0;
int i = 0, j = 1;

    //enquanto i < que a quantidade de vertices -1 e j < que a quantidade de vertices;
    while ((i < G->n-1) && (j <G->n)){

        //faz ordenação        
        int aux = fila[i]; 
            fila[i] = fila[j];
            fila[j] = aux;

        //atribui-se +1 as variaveis;
            i++;
            j++;
    }
}

//zera um vetor;
void zeraVetor(struct alist *G, int *fila){

//todas as posições do vetor são zeradas;
    for (int i = 0;i<G->n;i++){
        fila[i] = 0;
    }
}

//adiciona um elemento ao vetor;
void addVetor(int *vetor, int v){
 
   int i = 0;
    while (vetor[i] != 0){  //enquanto a posição do vetor for diferente de 0;
        i++;
    }

    //se a posição i de um vetor for diferente de 0, atribui-se o valor v ao vetor[i];
    vetor[i] = v;
}
