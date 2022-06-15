#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct lista {
    int info;
    struct lista* prox;
} TLista;


int main(void) {

}

TLista* insere(TLista* lista, int valor) {
    TLista* novo = (TLista*)malloc(sizeof(TLista));
    novo->info = valor;
    novo->prox = lista;
    return novo;
}

TLista* remove(TLista* lista, int valor) {
    TLista* anterior = NULL;
    TLista* p = lista;

    while (p != NULL && p->info != valor) {
        anterior = p;
        p = p->prox;
    }
    
    if (p == NULL) return lista;

    if (anterior == NULL) {
        lista = p->prox;
    }

    else {
        anterior->prox = p->prox;
    }

    free(p);
    return lista;
}

void imprime(TLista* lista) {
    TLista* p;
    for (p=lista; p!=NULL; p=p->prox) {
        printf("info = %d\n", p->info);
    }
}

void libera(TLista *lista) {
    TLista* p = lista;

    while (p != NULL) {
        TLista* proximo = p->prox;
        free(p);
        p = proximo;
    }
}