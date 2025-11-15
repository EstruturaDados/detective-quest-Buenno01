#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suspeito.h"

// Inicializa a tabela hash
TabelaHash* inicializarHash() {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    if (tabela == NULL) {
        printf("Erro ao alocar memória para tabela hash.\n");
        return NULL;
    }
    
    for (int i = 0; i < TAM_HASH; i++) {
        tabela->tabela[i] = NULL;
    }
    
    return tabela;
}

// Função hash simples (soma ASCII % TAM_HASH)
int funcaoHash(const char* nome) {
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        soma += nome[i];
    }
    return soma % TAM_HASH;
}

// Busca um suspeito na lista encadeada
Suspeito* buscarSuspeito(Suspeito* lista, const char* nome) {
    Suspeito* atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// Insere uma pista associada a um suspeito na hash
void inserirNaHash(TabelaHash* tabela, const char* pista, const char* nomeSuspeito) {
    if (tabela == NULL) return;
    
    int indice = funcaoHash(nomeSuspeito);
    
    // Busca o suspeito na lista encadeada
    Suspeito* suspeito = buscarSuspeito(tabela->tabela[indice], nomeSuspeito);
    
    if (suspeito == NULL) {
        // Cria um novo suspeito
        suspeito = (Suspeito*)malloc(sizeof(Suspeito));
        if (suspeito == NULL) {
            printf("Erro ao alocar memória para suspeito.\n");
            return;
        }
        strncpy(suspeito->nome, nomeSuspeito, MAX_NOME - 1);
        suspeito->nome[MAX_NOME - 1] = '\0';
        suspeito->contadorPistas = 0;
        suspeito->pistas = NULL;
        suspeito->proximo = tabela->tabela[indice];
        tabela->tabela[indice] = suspeito;
    }
    
    // Adiciona a pista ao suspeito
    NoPista* novaPista = (NoPista*)malloc(sizeof(NoPista));
    if (novaPista == NULL) {
        printf("Erro ao alocar memória para pista.\n");
        return;
    }
    strncpy(novaPista->texto, pista, MAX_TEXTO - 1);
    novaPista->texto[MAX_TEXTO - 1] = '\0';
    novaPista->proximo = suspeito->pistas;
    suspeito->pistas = novaPista;
    suspeito->contadorPistas++;
    
    printf("✓ Pista \"%s\" associada a %s\n", pista, nomeSuspeito);
}

// Lista todas as associações pista → suspeito
void listarAssociacoes(TabelaHash* tabela) {
    if (tabela == NULL) return;
    
    printf("\n=== ASSOCIAÇÕES PISTAS → SUSPEITOS ===\n");
    int encontrouAlguem = 0;
    
    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito* atual = tabela->tabela[i];
        while (atual != NULL) {
            encontrouAlguem = 1;
            printf("\n👤 Suspeito: %s (Total de pistas: %d)\n", atual->nome, atual->contadorPistas);
            printf("   Pistas:\n");
            
            NoPista* pista = atual->pistas;
            while (pista != NULL) {
                printf("     • %s\n", pista->texto);
                pista = pista->proximo;
            }
            
            atual = atual->proximo;
        }
    }
    
    if (!encontrouAlguem) {
        printf("Nenhuma associação registrada ainda.\n");
    }
}

// Mostra o suspeito mais citado
void mostrarSuspeitoMaisCitado(TabelaHash* tabela) {
    if (tabela == NULL) return;
    
    Suspeito* maisCitado = NULL;
    int maxPistas = 0;
    
    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito* atual = tabela->tabela[i];
        while (atual != NULL) {
            if (atual->contadorPistas > maxPistas) {
                maxPistas = atual->contadorPistas;
                maisCitado = atual;
            }
            atual = atual->proximo;
        }
    }
    
    printf("\n=== SUSPEITO MAIS PROVÁVEL ===\n");
    if (maisCitado != NULL) {
        printf("🔍 O suspeito mais citado é: %s\n", maisCitado->nome);
        printf("   Número de pistas: %d\n", maisCitado->contadorPistas);
    } else {
        printf("Nenhum suspeito registrado ainda.\n");
    }
}

// Libera a memória da tabela hash
void liberarHash(TabelaHash* tabela) {
    if (tabela == NULL) return;
    
    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito* suspeito = tabela->tabela[i];
        while (suspeito != NULL) {
            Suspeito* tempSuspeito = suspeito;
            suspeito = suspeito->proximo;
            
            // Libera as pistas do suspeito
            NoPista* pista = tempSuspeito->pistas;
            while (pista != NULL) {
                NoPista* tempPista = pista;
                pista = pista->proximo;
                free(tempPista);
            }
            
            free(tempSuspeito);
        }
    }
    
    free(tabela);
}

