#ifndef PISTA_H
#define PISTA_H

#include "models.h"

// Funções para gerenciar Pistas (Árvore de Busca Binária)
Pista* inserirPista(Pista* raiz, const char* texto);
void listarPistas(Pista* raiz);
void liberarPistas(Pista* raiz);
int contarPistas(Pista* raiz);

#endif // PISTA_H

