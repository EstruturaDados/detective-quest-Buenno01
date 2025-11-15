#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sala.h"
#include "pista.h"
#include "suspeito.h"

// ========== FUNÇÕES DE MENU ==========

void exibirMenuPrincipal() {
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║     🔍 DETECTIVE QUEST 🔍             ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    printf("Escolha seu nível:\n");
    printf("  [1] 🌱 Nível Novato - Explorar a Mansão\n");
    printf("  [2] 🛡️  Nível Aventureiro - Coletar Pistas\n");
    printf("  [3] 🏆 Nível Mestre - Resolver o Mistério\n");
    printf("  [0] Sair\n");
    printf("Opção: ");
}

void nivelNovato() {
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║     🌱 NÍVEL NOVATO                   ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    printf("Explore a mansão usando árvore binária!\n");
    
    Sala* mansao = construirMansao();
    explorarSalas(mansao);
    liberarSalas(mansao);
}

void nivelAventureiro() {
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║     🛡️  NÍVEL AVENTUREIRO             ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    printf("Explore a mansão e colete pistas!\n");
    
    Sala* mansao = construirMansao();
    Pista* arvore_pistas = NULL;
    Sala* atual = mansao;
    char opcao;
    
    printf("\nVocê está no(a): %s\n", atual->nome);
    
    while (1) {
        printf("\n--- Você está em: %s ---\n", atual->nome);
        
        // Pistas por sala
        if (strcmp(atual->nome, "Biblioteca") == 0) {
            arvore_pistas = inserirPista(arvore_pistas, "Livro de veneno aberto");
        } else if (strcmp(atual->nome, "Cozinha") == 0) {
            arvore_pistas = inserirPista(arvore_pistas, "Faca enferrujada");
        } else if (strcmp(atual->nome, "Sótão") == 0) {
            arvore_pistas = inserirPista(arvore_pistas, "Carta ameaçadora");
        } else if (strcmp(atual->nome, "Jardim") == 0) {
            arvore_pistas = inserirPista(arvore_pistas, "Pegadas na lama");
        } else if (strcmp(atual->nome, "Escritório") == 0) {
            arvore_pistas = inserirPista(arvore_pistas, "Documento rasgado");
        } else if (strcmp(atual->nome, "Adega") == 0) {
            arvore_pistas = inserirPista(arvore_pistas, "Garrafa quebrada");
        } else if (strcmp(atual->nome, "Porão") == 0) {
            arvore_pistas = inserirPista(arvore_pistas, "Corda com sangue");
        }
        
        // Verifica caminhos
        int temEsquerda = (atual->esquerda != NULL);
        int temDireita = (atual->direita != NULL);
        
        if (!temEsquerda && !temDireita) {
            printf("Você chegou a um beco sem saída!\n");
            printf("Escolha:\n");
            printf("  [v] - Voltar ao início\n");
            printf("  [p] - Ver todas as pistas coletadas\n");
            printf("  [s] - Sair\n");
            printf("Opção: ");
            scanf(" %c", &opcao);
            
            if (opcao == 'v' || opcao == 'V') {
                atual = mansao;
                continue;
            } else if (opcao == 'p' || opcao == 'P') {
                printf("\n=== PISTAS COLETADAS (ordem alfabética) ===\n");
                if (arvore_pistas != NULL) {
                    listarPistas(arvore_pistas);
                    printf("Total: %d pistas\n", contarPistas(arvore_pistas));
                } else {
                    printf("Nenhuma pista coletada ainda.\n");
                }
                continue;
            } else {
                break;
            }
        }
        
        printf("Escolha:\n");
        if (temEsquerda) printf("  [e] - Ir para a esquerda (%s)\n", atual->esquerda->nome);
        if (temDireita) printf("  [d] - Ir para a direita (%s)\n", atual->direita->nome);
        printf("  [p] - Ver pistas coletadas\n");
        printf("  [s] - Sair\n");
        printf("Opção: ");
        
        scanf(" %c", &opcao);
        
        if (opcao == 's' || opcao == 'S') {
            break;
        } else if (opcao == 'p' || opcao == 'P') {
            printf("\n=== PISTAS COLETADAS (ordem alfabética) ===\n");
            if (arvore_pistas != NULL) {
                listarPistas(arvore_pistas);
                printf("Total: %d pistas\n", contarPistas(arvore_pistas));
            } else {
                printf("Nenhuma pista coletada ainda.\n");
            }
        } else if ((opcao == 'e' || opcao == 'E') && temEsquerda) {
            atual = atual->esquerda;
        } else if ((opcao == 'd' || opcao == 'D') && temDireita) {
            atual = atual->direita;
        } else {
            printf("Opção inválida!\n");
        }
    }
    
    // Exibe pistas finais
    printf("\n=== RESUMO DAS PISTAS COLETADAS ===\n");
    if (arvore_pistas != NULL) {
        listarPistas(arvore_pistas);
        printf("Total: %d pistas\n", contarPistas(arvore_pistas));
    } else {
        printf("Nenhuma pista foi coletada.\n");
    }
    
    liberarPistas(arvore_pistas);
    liberarSalas(mansao);
}

void nivelMestre() {
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║     🏆 NÍVEL MESTRE               ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    printf("Explore, colete pistas e resolva o mistério!\n");
    
    Sala* mansao = construirMansao();
    Pista* arvore_pistas = NULL;
    TabelaHash* hash_suspeitos = inicializarHash();
    Sala* atual = mansao;
    char opcao;
    
    printf("\nVocê está no(a): %s\n", atual->nome);
    printf("\n📋 Suspeitos conhecidos: Sr. Smith, Dra. Watson, Chef Marcel, Mordomo James\n");
    
    while (1) {
        printf("\n--- Você está em: %s ---\n", atual->nome);
        
        // Pistas e associações por sala
        if (strcmp(atual->nome, "Biblioteca") == 0 && arvore_pistas == NULL) {
            arvore_pistas = inserirPista(arvore_pistas, "Livro de veneno aberto");
            inserirNaHash(hash_suspeitos, "Livro de veneno aberto", "Dra. Watson");
        } else if (strcmp(atual->nome, "Cozinha") == 0) {
            Pista* temp = arvore_pistas;
            arvore_pistas = inserirPista(arvore_pistas, "Faca enferrujada");
            if (arvore_pistas != temp || temp == NULL) {
                inserirNaHash(hash_suspeitos, "Faca enferrujada", "Chef Marcel");
            }
        } else if (strcmp(atual->nome, "Sótão") == 0) {
            Pista* temp = arvore_pistas;
            arvore_pistas = inserirPista(arvore_pistas, "Carta ameaçadora");
            if (arvore_pistas != temp || temp == NULL) {
                inserirNaHash(hash_suspeitos, "Carta ameaçadora", "Sr. Smith");
            }
        } else if (strcmp(atual->nome, "Jardim") == 0) {
            Pista* temp = arvore_pistas;
            arvore_pistas = inserirPista(arvore_pistas, "Pegadas na lama");
            if (arvore_pistas != temp || temp == NULL) {
                inserirNaHash(hash_suspeitos, "Pegadas na lama", "Mordomo James");
            }
        } else if (strcmp(atual->nome, "Escritório") == 0) {
            Pista* temp = arvore_pistas;
            arvore_pistas = inserirPista(arvore_pistas, "Documento rasgado");
            if (arvore_pistas != temp || temp == NULL) {
                inserirNaHash(hash_suspeitos, "Documento rasgado", "Sr. Smith");
            }
        } else if (strcmp(atual->nome, "Adega") == 0) {
            Pista* temp = arvore_pistas;
            arvore_pistas = inserirPista(arvore_pistas, "Garrafa quebrada");
            if (arvore_pistas != temp || temp == NULL) {
                inserirNaHash(hash_suspeitos, "Garrafa quebrada", "Dra. Watson");
            }
        } else if (strcmp(atual->nome, "Porão") == 0) {
            Pista* temp = arvore_pistas;
            arvore_pistas = inserirPista(arvore_pistas, "Corda com sangue");
            if (arvore_pistas != temp || temp == NULL) {
                inserirNaHash(hash_suspeitos, "Corda com sangue", "Mordomo James");
            }
        } else if (strcmp(atual->nome, "Sala de Estar") == 0) {
            Pista* temp = arvore_pistas;
            arvore_pistas = inserirPista(arvore_pistas, "Cinzas de cigarro");
            if (arvore_pistas != temp || temp == NULL) {
                inserirNaHash(hash_suspeitos, "Cinzas de cigarro", "Sr. Smith");
            }
        }
        
        // Verifica caminhos
        int temEsquerda = (atual->esquerda != NULL);
        int temDireita = (atual->direita != NULL);
        
        if (!temEsquerda && !temDireita) {
            printf("Você chegou a um beco sem saída!\n");
            printf("Escolha:\n");
            printf("  [v] - Voltar ao início\n");
            printf("  [p] - Ver pistas coletadas\n");
            printf("  [a] - Ver associações pista → suspeito\n");
            printf("  [c] - Ver suspeito mais provável\n");
            printf("  [s] - Sair\n");
            printf("Opção: ");
            scanf(" %c", &opcao);
            
            if (opcao == 'v' || opcao == 'V') {
                atual = mansao;
                continue;
            } else if (opcao == 'p' || opcao == 'P') {
                printf("\n=== PISTAS COLETADAS ===\n");
                if (arvore_pistas != NULL) {
                    listarPistas(arvore_pistas);
                    printf("Total: %d pistas\n", contarPistas(arvore_pistas));
                } else {
                    printf("Nenhuma pista coletada ainda.\n");
                }
                continue;
            } else if (opcao == 'a' || opcao == 'A') {
                listarAssociacoes(hash_suspeitos);
                continue;
            } else if (opcao == 'c' || opcao == 'C') {
                mostrarSuspeitoMaisCitado(hash_suspeitos);
                continue;
            } else {
                break;
            }
        }
        
        printf("Escolha:\n");
        if (temEsquerda) printf("  [e] - Ir para a esquerda (%s)\n", atual->esquerda->nome);
        if (temDireita) printf("  [d] - Ir para a direita (%s)\n", atual->direita->nome);
        printf("  [p] - Ver pistas coletadas\n");
        printf("  [a] - Ver associações\n");
        printf("  [c] - Ver suspeito mais provável\n");
        printf("  [s] - Sair\n");
        printf("Opção: ");
        
        scanf(" %c", &opcao);
        
        if (opcao == 's' || opcao == 'S') {
            break;
        } else if (opcao == 'p' || opcao == 'P') {
            printf("\n=== PISTAS COLETADAS ===\n");
            if (arvore_pistas != NULL) {
                listarPistas(arvore_pistas);
                printf("Total: %d pistas\n", contarPistas(arvore_pistas));
            } else {
                printf("Nenhuma pista coletada ainda.\n");
            }
        } else if (opcao == 'a' || opcao == 'A') {
            listarAssociacoes(hash_suspeitos);
        } else if (opcao == 'c' || opcao == 'C') {
            mostrarSuspeitoMaisCitado(hash_suspeitos);
        } else if ((opcao == 'e' || opcao == 'E') && temEsquerda) {
            atual = atual->esquerda;
        } else if ((opcao == 'd' || opcao == 'D') && temDireita) {
            atual = atual->direita;
        } else {
            printf("Opção inválida!\n");
        }
    }
    
    // Exibe resultado final
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║     RESULTADO DA INVESTIGAÇÃO        ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    
    printf("\n=== PISTAS COLETADAS (ordem alfabética) ===\n");
    if (arvore_pistas != NULL) {
        listarPistas(arvore_pistas);
        printf("Total: %d pistas\n", contarPistas(arvore_pistas));
    } else {
        printf("Nenhuma pista foi coletada.\n");
    }
    
    listarAssociacoes(hash_suspeitos);
    mostrarSuspeitoMaisCitado(hash_suspeitos);
    
    liberarPistas(arvore_pistas);
    liberarHash(hash_suspeitos);
    liberarSalas(mansao);
}

// ========== FUNÇÃO PRINCIPAL ==========

int main() {
    int opcao;
    
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   BEM-VINDO AO DETECTIVE QUEST!      ║\n");
    printf("║   Um jogo de mistério e investigação ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    
    do {
        exibirMenuPrincipal();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                nivelNovato();
                break;
            case 2:
                nivelAventureiro();
                break;
            case 3:
                nivelMestre();
                break;
            case 0:
                printf("\n👋 Obrigado por jogar Detective Quest!\n");
                break;
            default:
                printf("\n⚠ Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
    
    return 0;
}
