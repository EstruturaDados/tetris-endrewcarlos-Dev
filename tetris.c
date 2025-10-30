#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

// Estrutura que representa uma peça
typedef struct {
    char tipo; // 'I', 'O', 'T', 'L'
    int id;
} Peca;

// Estrutura da fila
typedef struct {
    Peca pecas[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// ---------- FUNÇÕES DE FILA ----------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Gera uma peça aleatória
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.tipo = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Insere uma peça no final da fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("A fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }
    f->pecas[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

// Remove uma peça da frente da fila (dequeue)
void dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }
    printf("Peça jogada: [%c %d]\n", f->pecas[f->inicio].tipo, f->pecas[f->inicio].id);
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

// Mostra o estado atual da fila
void mostrarFila(Fila *f) {
    printf("\n====================\n");
    printf("     TETRIS STACK    \n");
    printf("====================\n\n");

    if (filaVazia(f)) {
        printf("(fila vazia)\n");
    } else {
        printf(" Fila de peças:\n");
        int i = f->inicio;
        for (int c = 0; c < f->total; c++) {
            printf("[%c %d] ", f->pecas[i].tipo, f->pecas[i].id);
            i = (i + 1) % MAX;
        }
        printf("\n");
    }
}

// ---------- PROGRAMA PRINCIPAL ----------
int main() {
    Fila fila;
    int opcao;
    int idAtual = 0;

    srand(time(NULL));
    inicializarFila(&fila);

    // Inicializa com 5 peças aleatórias
    for (int i = 0; i < 5; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    do {
        mostrarFila(&fila);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;
            case 2:
                enqueue(&fila, gerarPeca(idAtual++));
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}