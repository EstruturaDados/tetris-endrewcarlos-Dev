#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5        // tamanho máximo da fila
#define TAM_FILA 5
#define TAM_PILHA 3  // limite de peças que podem ser reservadas

// ---------- ESTRUTURAS ----------

// Estrutura que representa uma peça do jogo
typedef struct {
    char tipo; // Tipos possíveis: 'I', 'O', 'T', 'L'
    int id;    // Identificador único da peça
} Peca;

// Estrutura da fila circular (peças disponíveis)
typedef struct {
    Peca pecas[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// Estrutura da pilha (peças reservadas)
typedef struct {
    Peca pecas[TAM_PILHA];
    int topo;
} Pilha;


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

// ---------- FUNÇÕES DE PILHA ----------

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Insere uma peça no topo da pilha (reserva)
void push(Pilha *p, Peca novaPeca) {
    if (pilhaCheia(p)) {
        printf("A pilha de reserva está cheia! Não é possível reservar mais peças.\n");
        return;
    }
    p->pecas[++p->topo] = novaPeca;
    printf("Peça [%c %d] reservada com sucesso!\n", novaPeca.tipo, novaPeca.id);
}

// Remove a peça do topo da pilha (usa a reserva)
Peca pop(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("A pilha de reserva está vazia! Nenhuma peça para usar.\n");
        Peca vazia = {' ', -1};
        return vazia;
    }
    Peca retirada = p->pecas[p->topo--];
    printf("Peça usada: [%c %d]\n", retirada.tipo, retirada.id);
    return retirada;
}

// Exibe as peças atualmente na pilha
void mostrarPilha(Pilha *p) {
    printf("\nPilha de reserva (Topo -> Base): ");
    if (pilhaVazia(p)) {
        printf("(vazia)\n");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->pecas[i].tipo, p->pecas[i].id);
        }
        printf("\n");
    }
}


// ---------- FUNÇÕES DE FILA (continuação) ----------

// Gera uma nova peça aleatória
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.tipo = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Insere uma nova peça no final da fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("A fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }
    f->pecas[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;  // movimentação circular
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
    printf("     TETRIS STACK   \n");
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
    Pilha pilha;
    int opcao;
    int idAtual = 0;

    srand(time(NULL));
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Fila começa com 5 peças geradas aleatoriamente
    for (int i = 0; i < 5; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    // Exibe o estado inicial
    mostrarFila(&fila);
    mostrarPilha(&pilha);

    // Loop principal do jogo
    do {
        mostrarFila(&fila);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // jogar peça (remove da fila e adiciona nova)
                dequeue(&fila);
                enqueue(&fila, gerarPeca(idAtual++));
                break;
            case 2: // reservar a peça do início da fila
                if (!filaVazia(&fila)) {
                    Peca reservada = fila.pecas[fila.inicio];
                    dequeue(&fila);
                    push(&pilha, reservada);
                    enqueue(&fila, gerarPeca(idAtual++));
                } else {
                    printf("Não há peça na fila para reservar!\n");
                }
                break;
            case 3: // usar peça reservada (retira da pilha)
                pop(&pilha);
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