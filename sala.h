#ifndef SALA_H
#define SALA_H

#include "models.h"

// Funções para gerenciar Salas (Árvore Binária)
Sala* criarSala(const char* nome);
void conectarSalas(Sala* pai, Sala* esquerda, Sala* direita);
void explorarSalas(Sala* raiz);
void liberarSalas(Sala* raiz);
Sala* construirMansao();

#endif

