#ifndef MODELS_H
#define MODELS_H

#define MAX_NOME 50
#define MAX_TEXTO 100
#define TAM_HASH 10

// Estrutura para representar uma Sala (Árvore Binária)
typedef struct Sala {
    char nome[MAX_NOME];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Estrutura para representar uma Pista (Árvore de Busca Binária)
typedef struct Pista {
    char texto[MAX_TEXTO];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;

// Estrutura para Lista Encadeada de Pistas (usada na Hash)
typedef struct NoPista {
    char texto[MAX_TEXTO];
    struct NoPista* proximo;
} NoPista;

// Estrutura para representar um Suspeito
typedef struct Suspeito {
    char nome[MAX_NOME];
    int contadorPistas;
    NoPista* pistas;  // Lista encadeada de pistas
    struct Suspeito* proximo;  // Para encadeamento na hash (colisões)
} Suspeito;

// Estrutura da Tabela Hash
typedef struct TabelaHash {
    Suspeito* tabela[TAM_HASH];
} TabelaHash;

#endif // MODELS_H

