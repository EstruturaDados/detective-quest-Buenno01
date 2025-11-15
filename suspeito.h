#ifndef SUSPEITO_H
#define SUSPEITO_H

#include "models.h"

// Funções para gerenciar Suspeitos e Tabela Hash
TabelaHash* inicializarHash();
int funcaoHash(const char* nome);
void inserirNaHash(TabelaHash* tabela, const char* pista, const char* nomeSuspeito);
void listarAssociacoes(TabelaHash* tabela);
void mostrarSuspeitoMaisCitado(TabelaHash* tabela);
void liberarHash(TabelaHash* tabela);

#endif // SUSPEITO_H

