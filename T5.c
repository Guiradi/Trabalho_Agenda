#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

typedef struct reg * no;

struct reg
{
    // Struct dos compromissos
    char compromisso [81];
    int dia, mes, ano, hora, minuto;
    float data, horario;
    struct reg * prox;
};

// Insere compromissos
void insere(no * agenda)
{
    // Lista auxiliar:
    no p = (no) malloc(sizeof(struct reg));
    
    system("cls");
    printf("\t\t\tAGENDA");

    do
    {
        printf("\n\n\tDigite a data do seu compromisso (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &p->dia, &p->mes, &p->ano);
    } while ((p->dia > 31) && (p->dia < 1) && (p->mes < 1) && (p->mes > 12) && (p-> ano < 0));

    p->data = p->dia + p->mes * 30.5 + p->ano * 365.25;

    do
    {
        printf("\n\tDigite o horario do seu compromisso (hh:mm): ");
        scanf("%d:%d", &p->hora, &p->minuto);
    } while ((p->hora > 23) && (p->hora < 0) && (p->minuto < 0) && (p->minuto > 59));

    p->horario = p->hora*60 + p->minuto;

    fflush(stdin);
    printf("\n\tDigite uma descricao para o seu compromisso: ");
    gets(p->compromisso);


    if ((*agenda) == NULL || p->data < (*agenda)->data)
    {
        p->prox = (*agenda);
        (*agenda) = p;
    }
    else
    {
        no q = (*agenda), r;
        while (q != NULL && q->data <= p->data)
        {
            if (q->data == p->data)
                if (q->horario > p->horario)
                    break;
            r = q;
            q = q -> prox;
        }
        p->prox = q;
        r->prox = p;
    }

    printf("\n\n\tCompromisso registrado!\n\t");
    system("pause");
}

void leitura(no agenda)
{
    system("cls");
    no p = agenda;
    while (p != NULL)
    {
        printf("\n\nData: %d/%d/%d", p->dia, p->mes, p->ano);
        printf("\nHora: %d:%d", p->hora, p->minuto);
        printf("\nCompromisso: %s\n\n", p->compromisso);
        p = p->prox;
    }
    system("pause");
}
// Remove compromissos digitando a data
void remover(no * agenda)
{
    // Lista auxiliar:
    no p = (no) malloc(sizeof(struct reg));

    system("cls");
    printf("\t\t\tAGENDA");

    if (*agenda == NULL)
    {
        printf("\n\n\tSem compromissos para apagar!\n\n");
        system("pause");
        return;
    }

    do
    {
        printf("\n\n\tDigite a data de hoje (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &p->dia, &p->mes, &p->ano);
    } while ((p->dia > 31) && (p->dia < 1) && (p->mes < 1) && (p->mes > 12) && (p-> ano < 0));

    p->data = p->dia + p->mes * 30.5 + p->ano * 365.25;

    // APAGAR
    no q = *agenda;
    while((q) && (q->data <= p->data))
    {
        no q = *agenda;
		no r = q;
        q = q->prox;
        free(r);
    }

    printf("\n\n\tCompromissos de hoje e anteriores apagados!\n\n");
    system("pause");
}

// Consulta compromissos por data

// Consulta compromissos por palavra

// salva em agenda.txt

// le os dados

// termina a execução

// MENU
int main()
{
    /*Cria lista de compromissos para o programa todo*/
    no compromissos = (no)malloc(sizeof(struct reg)); // cria uma lista compromissos
    compromissos = NULL; // faz a lista iniciar como nula
    
    // Variáveis:
    char escolha;

    /* - MENU - */
    do
    {
        system("cls");
        printf("\t\t\tAGENDA");
        printf("\n\n\t1. Inserir novo compromisso.");
        printf("\n\t2. Remover compromisso da agenda.");
        printf("\n\t3. Consultar compromisso por data.");
        printf("\n\t4. Procurar compromisso por palavra.");
        printf("\n\t5. Salvar compromissos em disco.");
        printf("\n\t6. Ler compromissos em disco.");
        printf("\n\t0. Sair.\n\t");
            
        do
        {
            escolha = getch();
        } while ((escolha < '0') && (escolha > '7'));

        switch (escolha)
        {
            case '1':
                // inserir
                insere(&compromissos);
                break;

            case '2':
                // remover
                remover(&compromissos);
                break;

            case '3':
                // consultar compromisso por data
                break;
            
            case '4':
                // consultar compromisso por palavra
                break;
            
            case '5':
                // salvar compromisso em disco
                break;
            
            case '6':
                // ler compromisso em disco
                break;
            
            case '7':
                //
                leitura(compromissos);
                break;

            case '0':
                break;

            default:
                system("cls");
                printf("Erro encontrado. Favor consultar o desenvolvedor do programa.\n");
                system("pause");
                return;
        }
    } while (escolha != '0');
}
