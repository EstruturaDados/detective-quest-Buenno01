#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pista.h"

// Insere uma pista na árvore de busca binária
Pista* inserirPista(Pista* raiz, const char* texto) {
    if (raiz == NULL) {
        Pista* novaPista = (Pista*)malloc(sizeof(Pista));
        if (novaPista == NULL) {
            printf("Erro ao alocar memória para pista.\n");
            return NULL;
        }
        strncpy(novaPista->texto, texto, MAX_TEXTO - 1);
        novaPista->texto[MAX_TEXTO - 1] = '\0';
        novaPista->esquerda = NULL;
        novaPista->direita = NULL;
        printf("✓ Pista coletada: \"%s\"\n", texto);
        return novaPista;
    }

    int comparacao = strcmp(texto, raiz->texto);
    
    if (comparacao < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    } else if (comparacao > 0) {
        raiz->direita = inserirPista(raiz->direita, texto);
    } else {
        printf("⚠ Pista já coletada anteriormente.\n");
    }

    return raiz;
}

// Lista todas as pistas em ordem alfabética (percurso em ordem)
void listarPistas(Pista* raiz) {
    if (raiz == NULL) return;
    
    listarPistas(raiz->esquerda);
    printf("  - %s\n", raiz->texto);
    listarPistas(raiz->direita);
}

// Libera a memória de todas as pistas
void liberarPistas(Pista* raiz) {
    if (raiz == NULL) return;
    liberarPistas(raiz->esquerda);
    liberarPistas(raiz->direita);
    free(raiz);
}

// Conta o número total de pistas
int contarPistas(Pista* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarPistas(raiz->esquerda) + contarPistas(raiz->direita);
}

