#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sala.h"

// Cria uma nova sala
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memória para sala.\n");
        return NULL;
    }
    strncpy(novaSala->nome, nome, MAX_NOME - 1);
    novaSala->nome[MAX_NOME - 1] = '\0';
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Conecta salas (esquerda e direita) a uma sala pai
void conectarSalas(Sala* pai, Sala* esquerda, Sala* direita) {
    if (pai != NULL) {
        pai->esquerda = esquerda;
        pai->direita = direita;
    }
}

// Explora as salas de forma interativa
void explorarSalas(Sala* raiz) {
    if (raiz == NULL) {
        printf("Não há salas para explorar.\n");
        return;
    }

    Sala* atual = raiz;
    char opcao;

    printf("\n=== BEM-VINDO À MANSÃO ===\n");
    printf("Você está no(a): %s\n", atual->nome);

    while (1) {
        printf("\n--- Você está em: %s ---\n", atual->nome);
        
        // Verifica se há caminhos disponíveis
        int temEsquerda = (atual->esquerda != NULL);
        int temDireita = (atual->direita != NULL);

        if (!temEsquerda && !temDireita) {
            printf("Você chegou a um beco sem saída!\n");
            printf("Pressione 'v' para voltar ao início ou 's' para sair: ");
            scanf(" %c", &opcao);
            if (opcao == 'v' || opcao == 'V') {
                atual = raiz;
                continue;
            } else {
                break;
            }
        }

        printf("Escolha seu caminho:\n");
        if (temEsquerda) printf("  [e] - Ir para a esquerda (%s)\n", atual->esquerda->nome);
        if (temDireita) printf("  [d] - Ir para a direita (%s)\n", atual->direita->nome);
        printf("  [s] - Sair da exploração\n");
        printf("Opção: ");
        
        scanf(" %c", &opcao);

        if (opcao == 's' || opcao == 'S') {
            printf("Saindo da exploração...\n");
            break;
        } else if ((opcao == 'e' || opcao == 'E') && temEsquerda) {
            atual = atual->esquerda;
        } else if ((opcao == 'd' || opcao == 'D') && temDireita) {
            atual = atual->direita;
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// Libera a memória de todas as salas
void liberarSalas(Sala* raiz) {
    if (raiz == NULL) return;
    liberarSalas(raiz->esquerda);
    liberarSalas(raiz->direita);
    free(raiz);
}

// Constrói a estrutura da mansão
Sala* construirMansao() {
    // Criando as salas
    Sala* hall = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* sotao = criarSala("Sótão");
    Sala* jardim = criarSala("Jardim");
    Sala* sala_estar = criarSala("Sala de Estar");
    Sala* quarto = criarSala("Quarto Principal");
    Sala* adega = criarSala("Adega");
    Sala* porao = criarSala("Porão");
    Sala* escritorio = criarSala("Escritório");

    // Montando a árvore
    conectarSalas(hall, biblioteca, cozinha);
    conectarSalas(biblioteca, sotao, jardim);
    conectarSalas(cozinha, sala_estar, quarto);
    conectarSalas(sotao, adega, NULL);
    conectarSalas(jardim, NULL, porao);
    conectarSalas(quarto, escritorio, NULL);

    return hall;
}

