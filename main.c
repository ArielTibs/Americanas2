#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menuConta()
{
    printf("\n-- Menu do Cliente --\n");
    printf("1. Exibir contas cadastradas\n");
    printf("2. Adicionar conta\n");
    printf("3. Remover conta\n");
    printf("4. Voltar\n");
}

void menuEstoque()
{
    printf("\n-- Menu Estoque --\n");
    printf("1. Listar estoque\n");
    printf("2. Adicionar item\n");
    printf("3. Remover item\n");
    printf("4. Valor do estoque\n");
    printf("5. Voltar\n");
}

typedef struct
{
    char nome[100];
    int quantidade;
    float valor_unitario;
} ItemEstoque;

int compararItens(const void *a, const void *b)
{
    ItemEstoque *item1 = (ItemEstoque *)a;
    ItemEstoque *item2 = (ItemEstoque *)b;
    return strcmp(item1->nome, item2->nome);
}

float calcularValorTotalEstoque(ItemEstoque *estoque, int num_itens)
{
    float valor_total = 0.0;
    for (int i = 0; i < num_itens; i++)
    {
        valor_total += estoque[i].quantidade * estoque[i].valor_unitario;
    }
    return valor_total;
}

void gerarListaEstoque(ItemEstoque *estoque, int num_itens) {
    FILE *arquivo;
    arquivo = fopen("lista_estoque.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir.\n");
        return;
    }
    fprintf(arquivo, "-- Estoque em Ordem Alfabética --\n");
    for (int i = 0; i < num_itens; i++) {
        fprintf(arquivo, "%s - Quantidade: %d - Valor Unitário: R$ %.2f\n", estoque[i].nome, estoque[i].quantidade, estoque[i].valor_unitario);
    }
    fclose(arquivo);
    printf("Lista de estoque salva com sucesso no arquivo 'lista_estoque.txt'.\n");
}

int main()
{
    char email_cadastrado[80];
    char senha_cadastrada[80];
    char **lista_emails = NULL;

    int num_emails = 0;

    while (1)
    {
        printf("\nBem vindo ao menu do Estoque Americanas.\n");
        printf("Por favor, cadastre um email: ");
        scanf("%s", email_cadastrado);

        if (strchr(email_cadastrado, '@') != NULL)
        {
            lista_emails = realloc(lista_emails, (num_emails + 1) * sizeof(char *));
            lista_emails[num_emails] = malloc(80 * sizeof(char));
            strcpy(lista_emails[num_emails], email_cadastrado);
            num_emails++;
            break;
        }
        else
        {
            printf("\nO email é inválido, ele deve conter '@' pra ser um email válido.\n");
        }
    }

    printf("Por favor, cadastre sua senha: ");
    scanf("%s", senha_cadastrada);

    printf("\nCadastro concluido, faça login para continuar.\n");

    ItemEstoque *estoque = NULL;
    int num_itens = 0;

    while (1)
    {
        char email[80];
        char senha[80];

        printf("\nInsira seu email: ");
        scanf("%s", email);
        printf("Insira sua senha: ");
        scanf("%s", senha);

        if (strcmp(email, email_cadastrado) == 0 && strcmp(senha, senha_cadastrada) == 0)
        {
            printf("\nBem vindo ao Controle de Estoque Americanas.\n");

            int escolha;
            while (1)
            {
                printf("\n-- Menu Principal --\n");
                printf("1. Conta\n");
                printf("2. Estoque\n");
                printf("3. Imprimir Estoque\n");
                printf("4. Logout\n");
                printf("\nEscolha uma opção: \n");
                scanf("%d", &escolha);

                switch (escolha)
                {
                case 1:
                    // Código para gerenciar contas
                    break;
                case 2:
                    // Código para gerenciar estoque
                    break;
                case 3:
                    gerarListaEstoque(estoque, num_itens);
                    break;
                case 4:
                    printf("Até o proximo login\n");
                    // Liberar memória alocada
                    for (int i = 0; i < num_emails; i++)
                    {
                        free(lista_emails[i]);
                    }
                    free(lista_emails);
                    for (int i = 0; i < num_itens; i++)
                    {
                        free(estoque[i].nome);
                    }
                    free(estoque);
                    return 0;
                default:
                    printf("Opção inexistente. Escolha uma opção disponível.\n");
                    break;
                }
            }

            break; 
        }
        else
        {
            printf("Email ou senha incorretos. Tente novamente.\n");
        }
    }

    return 0;
}