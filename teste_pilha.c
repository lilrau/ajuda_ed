#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct lista {
    int info;
    struct lista* prox;
} TLista;

typedef struct pilha {
    TLista* topo;
} TPilha;

int main(void) {

}

TPilha* cria(void){
    TPilha* p = (TPilha*)malloc(sizeof(TPilha));
    p->topo = NULL;
    return p;
}

void push(TPilha* pilha, int valor) {
    TLista* novo = (TLista*)malloc(sizeof(TLista));
    novo->info = valor;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

int pop(TPilha *pilha) {
    TLista* t;
    int valor;

    if(pilha->topo == NULL) {
        printf("\nVazia!\n");
        return;
    }

    t = pilha->topo;
    valor = t->info;
    pilha->topo = t->prox;
    free(t);
    return valor;
}

void libera(TPilha* pilha) {
    TLista* aux = pilha->topo;
    while(aux != NULL) {
        TLista* aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(pilha);
}