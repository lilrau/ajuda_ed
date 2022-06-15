#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct lista {
    int info;
    struct lista* prox;
} TLista;

typedef struct fila {
    TLista* inicio;
    TLista* fim;
} TFila;

int main(void) {

}

TFila* cria(void) {
    TFila* fila = (TFila*)malloc(sizeof(TFila));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void insere(TFila* fila, int valor) {
    TLista* novo = (TLista*)malloc(sizeof(TLista));
    novo->info = valor;
    novo->prox = NULL;

    if(fila->fim == NULL) {
        fila->fim->prox = novo;
    }
    else {
        fila->inicio = novo;
    }

    fila->fim = novo;
}

int remove(TFila* fila) {
    TLista* t;
    int valor;

    if(fila->inicio == NULL) {
        printf("\nVazia\n");
        return;
    }

    t = fila->inicio;
    valor = t->info;
    fila->inicio = t->prox;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(t);
    return valor;
}

void libera(TFila* fila) {
    TLista* aux = fila->inicio;

    while (aux != NULL) {
        TLista* aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(fila);
}