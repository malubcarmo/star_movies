#include <stdio.h>
#include <string.h>

#define MAX 15   // Quantidade máxima de filmes que podem ser cadastrados

// -------------------------------
// Definição da Estrutura Filme
// -------------------------------
typedef struct {
    char nome[50];
    int ano;
    float notaMedia;
    int qtdAvaliacoes;
} Filme;

// Array estático de filmes
Filme lista[MAX];
int total = 0; // Quantidade de filmes cadastrados

// -------------------------------
// Protótipos das Funções
// -------------------------------
int cadastrarFilme();
int adicionarAvaliacao();
void exibirFilmes();

// -------------------------------
// Função Principal (Menu)
// -------------------------------
int main() {
    int opcao;

    do {
        printf("\n===============================\n");
        printf("  SISTEMA DE AVALIACAO DE FILMES\n");
        printf("===============================\n");
        printf("1 - Cadastrar novo filme\n");
        printf("2 - Adicionar avaliacao\n");
        printf("3 - Exibir todos os filmes\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                if (cadastrarFilme())
                    printf("\nFilme cadastrado com sucesso!\n");
                else
                    printf("\nErro ao cadastrar filme (limite atingido).\n");
                break;

            case 2:
                if (adicionarAvaliacao())
                    printf("\nAvaliacao registrada com sucesso!\n");
                else
                    printf("\nFilme nao encontrado.\n");
                break;

            case 3:
                exibirFilmes();
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}

// ----------------------------------------
// Função 1: Cadastrar um novo filme
// ----------------------------------------
int cadastrarFilme() {
    if (total >= MAX) {
        printf("\nLimite máximo de %d filmes atingido. Não é possível cadastrar mais.\n", MAX);
        return 0;
    }

    printf("\nDigite o nome do filme: ");
    fgets(lista[total].nome, 50, stdin);
    lista[total].nome[strcspn(lista[total].nome, "\n")] = '\0';

    printf("Digite o ano de lancamento: ");
    scanf("%d", &lista[total].ano);
    getchar();

    lista[total].notaMedia = 0;
    lista[total].qtdAvaliacoes = 0;

    total++;

    //Aviso de limite atingido
    if (total == MAX) {
        printf("\nATENÇÃO: Você cadastrou o filme número %d.\n", MAX);
        printf("O limite máximo foi atingido. Não será possível cadastrar novos filmes.\n");
    }

    return 1;
}

// ----------------------------------------
// Função 2: Adicionar avaliação a um filme
// ----------------------------------------
int adicionarAvaliacao() {
    char nomeBusca[50];
    float nota;

    printf("\nDigite o nome do filme que deseja avaliar: ");
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    printf("Digite a nota (0 a 5): ");
    scanf("%f", &nota);
    getchar();

    if (nota < 0 || nota > 5) {
        printf("Nota invalida!\n");
        return 0;
    }

    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].nome, nomeBusca) == 0) {

            // Atualiza média
            lista[i].notaMedia =
                ((lista[i].notaMedia * lista[i].qtdAvaliacoes) + nota) /
                (lista[i].qtdAvaliacoes + 1);

            lista[i].qtdAvaliacoes++;

            return 1;
        }
    }

    return 0; // Filme não encontrado
}

// ----------------------------------------
// Função 3: Exibir todos os filmes
// ----------------------------------------
void exibirFilmes() {
    printf("\n====== LISTA DE FILMES ======\n");

    if (total == 0) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nFilme %d\n", i + 1);
        printf("Nome: %s\n", lista[i].nome);
        printf("Ano: %d\n", lista[i].ano);
        printf("Avaliacoes: %d\n", lista[i].qtdAvaliacoes);
        printf("Nota Media: %.2f\n", lista[i].notaMedia);
        printf("------------------------------\n");
    }
}
