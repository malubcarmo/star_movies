#include <stdio.h>
#include <string.h>

#define MAX 15

// Estrutura de dados para armazenar informações do filme
typedef struct {
    char nome[50];      
    int ano;
    float notaMedia;
    int qtdAvaliacoes;
} Filme;

// Variável global acessada por várias funções
Filme lista[MAX];
int total = 0;      

// Protótipos
int cadastrarFilme();
int adicionarAvaliacao();
void exibirFilmes();

// Função principal com repetição e controle
int main() {

    int opcao;

    // Estrutura de repetição
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
        getchar();

        // Controle de fluxo com switch e if
        switch (opcao) {
            case 1:
                if (cadastrarFilme())
                    printf("\nFilme cadastrado com sucesso!\n");
                else
                    printf("\nErro ao cadastrar filme.\n");
                break;

            case 2:
                if (adicionarAvaliacao())
                    printf("\nAvaliacao registrada com sucesso!\n");
                else
                    printf("\nErro! Filme nao encontrado.\n");
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

// Função 1 — Cadastrar Filme
int cadastrarFilme() {

    if (total >= MAX) {
        printf("\nLimite maximo de filmes atingido.\n");
        return 0;
    }

    // Variáveis locais
    printf("\nDigite o nome do filme: ");
    fgets(lista[total].nome, 50, stdin);
    lista[total].nome[strcspn(lista[total].nome, "\n")] = '\0';

    printf("Digite o ano de lancamento: ");
    scanf("%d", &lista[total].ano);
    getchar();

    // Atribuições
    lista[total].notaMedia = 0;
    lista[total].qtdAvaliacoes = 0;

    // Operação aritmética
    total++;

    // Escopo de bloco 
    if (total == MAX) {
        int i = total;
        printf("\nAviso: atingiu o limite de %d filmes (variavel i=%d)\n", MAX, i);
    }

    return 1;
}

// Função 2 — Adicionar Avaliação
int adicionarAvaliacao() {

    char nomeBusca[50];  
    float nota;          

    printf("\nDigite o nome do filme: ");
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    printf("Digite a nota (0 a 5): ");
    scanf("%f", &nota);
    getchar();

    if (nota < 0 || nota > 5) {
        printf("Nota invalida!\n");
        return 0;
    }

    // Estrutura de repetição
    for (int i = 0; i < total; i++) {

        // Comparação de strings
        if (strcmp(lista[i].nome, nomeBusca) == 0) {

            // Cálculo da nova média (aritmética)
            lista[i].notaMedia =
                ((lista[i].notaMedia * lista[i].qtdAvaliacoes) + nota) /
                (lista[i].qtdAvaliacoes + 1);

            lista[i].qtdAvaliacoes++;

            return 1;
        }
    }

    return 0;
}

// Procedimento (void) — sem retorno
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
