#include <stdio.h>
#include <stdlib.h>
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

    no q = *agenda;
    while((q != NULL) && (q->data <= p->data))
        q = q->prox;
    no r = (*agenda);
    if (q == NULL)
    {
        (*agenda) = NULL;
        free(r);
    }
    else
    {
        (*agenda) = q;
        free(r);
    }

    printf("\n\n\tCompromissos de hoje e anteriores apagados!\n\n");
    system("pause");
}

// Consulta compromissos por data
void consulta(no agenda)
{
    int dia, mes, ano;
    float data;

    system("cls");
    printf("\t\t\tAGENDA\n");

    if (agenda == NULL)
    {
        printf("\n\n\tSem compromissos na agenda!\n");
        system("pause");
        return;
    }

    do
    {
        printf("\n\n\tDigite a data que deseja pesquisar (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
    } while ((dia > 31) && (dia < 1) && (mes < 1) && (mes > 12) && (ano < 0));

    data = dia + mes * 30.5 + ano * 365.25;

    no q = agenda;
    int i = 1;
    
    while (q != NULL)
    {
        if (q->data == data)
            printf("\n\tCompromisso %d: %s\n\tData: %d/%d/%d\n\tHora: %dh%d\n", i++, q->compromisso, q->dia, q->mes, q->ano, q->hora, q->minuto);
        q = q->prox;
    }

    if (i == 1)
        printf("\n\tNenhum compromisso encontrado na data: %d/%d/%d\n", dia, mes, ano);
    
    system("pause");
    return;
}


// Consulta compromissos por palavra
void consulta_palavra(no agenda)
{
    char str[81], compromisso[81];
    char * tok;
    int j;

    system("cls");
    printf("\t\t\tAGENDA\n");

    if (agenda == NULL)
    {
        printf("\n\n\tSem compromissos na agenda!\n");
        system("pause");
        return;
    }

    printf("\n\n\tConsultar compromissos que contenham a palavra: ");
    gets(str);
    for(j = 0; str[j]; j++)
        str[j] = tolower(str[j]);

    no q = agenda;
    int i = 1;
    
    while (q != NULL)
    {
        strcpy(compromisso, q->compromisso);

        tok = strtok(compromisso, " ,.;-/_\n");

        do
        {    
            for(j = 0; tok[j]; j++)
                tok[j] = tolower(tok[j]);
            if (strcmp(tok,str) == 0)
                printf("\n\tCompromisso %d: %s\n\tData: %d/%d/%d\n\tHora: %dh%d\n", i++, q->compromisso, q->dia, q->mes, q->ano, q->hora, q->minuto);
            tok = strtok(NULL, " ,.;-/_\n" );
        } while (tok != NULL);
        q = q->prox;
    }

    if (i == 1)
        printf("\n\tNenhum compromisso encontrado com a palavra: %s\n", str);
    
    system("pause");
    return;
}


// salva em agenda.txt
void salva_disco(no agenda)
{
    FILE * arquivo;
    char compromisso[100], data[5];

    system("cls");
    printf("\t\t\tAGENDA\n");

    if (agenda == NULL)
    {
        printf("\n\n\tNao ha compromissos para salvar em disco!\n\t");
        system("pause");
        return;
    }

    if ((arquivo = fopen("agenda.txt", "w")) == NULL)
    {
        printf("\n\n\tNao foi possivel abrir/criar o arquivo agenda.txt.\n\n\t");
        system("pause");
        return;
    }

    no q = agenda;
    while (q != NULL)
    {
        strcpy(compromisso, "Compromisso: ");
        strcat(compromisso, q->compromisso);
        strcat(compromisso, "\ndata: ");
        itoa(q->dia, data, 10);
        strcat(compromisso, data );
        strcat(compromisso, "/");
        itoa(q->mes, data, 10);
        strcat(compromisso, data );
        strcat(compromisso, "/");
        itoa(q->ano, data, 10);
        strcat(compromisso, data );
        strcat(compromisso, "\nhora: ");
        itoa(q->hora, data, 10);
        strcat(compromisso, data );
        strcat(compromisso, ":");
        itoa(q->minuto, data, 10);
        strcat(compromisso, data );
        strcat(compromisso, "\n\n");

        fputs(compromisso, arquivo);

        q = q->prox;
    }
    fclose(arquivo);
    printf("\n\n\tCompromissos salvos em disco!\n\t");
    system("pause");
    return;
}

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
                consulta(compromissos);
                break;
            
            case '4':
                // consultar compromisso por palavra
                consulta_palavra(compromissos);
                break;
            
            case '5':
                // salvar compromisso em disco
                salva_disco(compromissos);
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
