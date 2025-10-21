#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5

struct Peca {
    char nome;
    int id;
};

struct Fila {
    struct Peca pecas[MAX_FILA];
    int frente;
    int tras;
    int quantidade;
};

void inicializarFila(struct Fila *fila);
int filaVazia(struct Fila *fila);
int filaCheia(struct Fila *fila);
void enfileirar(struct Fila *fila, struct Peca nova);
void desenfileirar(struct Fila *fila);
void exibirFila(struct Fila *fila);
struct Peca gerarPeca(int idAtual);

int main() {
    struct Fila filaPecas;
    int opcao;
    int contadorID = 0;

    srand(time(NULL));
    inicializarFila(&filaPecas);

    for (int i = 0; i < MAX_FILA; i++) {
        struct Peca nova = gerarPeca(contadorID++);
        enfileirar(&filaPecas, nova);
    }

    do {
        printf("\n=== TETRIS STACK - FILA DE PECAS FUTURAS ===\n");
        exibirFila(&filaPecas);
        printf("\nOpcoes de acao:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                desenfileirar(&filaPecas);
                break;
            case 2:
                if (!filaCheia(&filaPecas)) {
                    struct Peca nova = gerarPeca(contadorID++);
                    enfileirar(&filaPecas, nova);
                } else {
                    printf("\nA fila esta cheia! Nao e possivel adicionar nova peca.\n");
                }
                break;
            case 0:
                printf("\nEncerrando o simulador...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

void inicializarFila(struct Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->quantidade = 0;
}

int filaVazia(struct Fila *fila) {
    return fila->quantidade == 0;
}

int filaCheia(struct Fila *fila) {
    return fila->quantidade == MAX_FILA;
}

struct Peca gerarPeca(int idAtual) {
    struct Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = idAtual;
    return nova;
}

void enfileirar(struct Fila *fila, struct Peca nova) {
    if (filaCheia(fila)) {
        printf("\nErro: a fila esta cheia!\n");
        return;
    }

    fila->tras = (fila->tras + 1) % MAX_FILA;
    fila->pecas[fila->tras] = nova;
    fila->quantidade++;

    printf("\nPeca [%c %d] adicionada ao final da fila.\n", nova.nome, nova.id);
    exibirFila(fila);
}

void desenfileirar(struct Fila *fila) {
    if (filaVazia(fila)) {
        printf("\nA fila esta vazia! Nenhuma peca para jogar.\n");
        return;
    }

    struct Peca removida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % MAX_FILA;
    fila->quantidade--;

    printf("\nPeca [%c %d] jogada (removida da fila).\n", removida.nome, removida.id);
    exibirFila(fila);
}

void exibirFila(struct Fila *fila) {
    printf("\nFila de pecas: ");
    if (filaVazia(fila)) {
        printf("[Vazia]\n");
        return;
    }

    int indice = fila->frente;
    for (int i = 0; i < fila->quantidade; i++) {
        struct Peca atual = fila->pecas[indice];
        printf("[%c %d] ", atual.nome, atual.id);
        indice = (indice + 1) % MAX_FILA;
    }
    printf("\n");
}

