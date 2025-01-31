#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct reg * no;

struct reg
{
    // Struct dos compromissos
    char compromisso [81]; // Descricao do Compromisso
    int dia, mes, ano, hora, minuto; // Dia/Mes/Ano e Hora:Minuto do compromisso
    float data, horario; // Floats definidos para calcular o tempo do compromisso e comparar
    struct reg * prox; // Proximo no
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

/*void leitura(no agenda)
{
    system("cls");
    no p = agenda;
    while (p != NULL)
    {
        printf("\n\nData: %2d/%2d/%2d", p->dia, p->mes, p->ano);
        printf("\nHora: %2d:%2d", p->hora, p->minuto);
        printf("\nCompromisso: %s\n\n", p->compromisso);
        p = p->prox;
    }
    printf("\t");
    system("pause");
}*/
// Remove compromissos digitando a data
void remover(no * agenda)
{
    // Lista auxiliar:
    no p = (no) malloc(sizeof(struct reg));

    system("cls");
    printf("\t\t\tAGENDA");

    if (*agenda == NULL)
    {
        printf("\n\n\tSem compromissos para apagar!\n\n\t");
        system("pause");
        return;
    }

    do
    {
        printf("\n\n\tDigite a data de hoje (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &p->dia, &p->mes, &p->ano);
    } while ((p->dia > 31) && (p->dia < 1) && (p->mes < 1) && (p->mes > 12) && (p-> ano < 0));

    p->data = p->dia + (p->mes * 30.5) + (p->ano * 365.25);

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
    printf("\t");
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
        printf("\n\n\tSem compromissos na agenda!\n\t");
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
    
    printf("\t");
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
        printf("\n\n\tSem compromissos na agenda!\n\t");
        system("pause");
        return;
    }

    printf("\n\n\tConsultar compromissos que contenham a palavra: ");
    fflush(stdin);
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

    printf("\t");
    
    system("pause");
    return;
}


// salva em agenda.txt
void salva_disco(no agenda)
{
    FILE * arquivo;
    char compromisso[150], data[5];

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
        printf("\n\n\tNao foi possivel criar o arquivo agenda.txt.\n\n\t");
        system("pause");
        return;
    }

    no q = agenda;
    while (q != NULL)
    {
        strcpy(compromisso, "Compromisso: ");
        strcat(compromisso, q->compromisso);
        strcat(compromisso, "\nData: ");
        itoa(q->dia, data, 10);
        strcat(compromisso, data );
        strcat(compromisso, "/");
        itoa(q->mes, data, 10);
        strcat(compromisso, data );
        strcat(compromisso, "/");
        itoa(q->ano, data, 10);
        strcat(compromisso, data );
        strcat(compromisso, "\nHora: ");
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
void le_dados(no * agenda)
{
    FILE * arquivo;
    char linha[101];
    char * tok;
    no q = (no) malloc (sizeof(struct reg)), p = NULL;

    system("cls");
    printf("\t\t\tAGENDA\n");

    if ((arquivo = fopen("agenda.txt", "r")) == NULL)
    {
        printf("\n\n\tNao foi possivel abrir o arquivo agenda.txt.\n\n\t");
        system("pause");
        return;
    }

    while(fgets(linha,100,arquivo) != NULL)
    {
        tok = strtok(linha, ": ");
        if (strcmp("Compromisso", tok) == 0)
        {
			tok = strtok(NULL, "\n");
            strcpy(q->compromisso, tok);
        }
        else 
        {
            if (strcmp("Data", tok) == 0)
            {
                tok = strtok(NULL, "/");
                q->dia = atoi(tok);
                tok = strtok(NULL, "/");
                q->mes = atoi(tok);
                tok = strtok(NULL, " \n");
                q->ano = atoi(tok);
                q->data = q->dia + q->mes * 30.5 + q->ano * 365.25;
            }
            else
            {
                if (strcmp("Hora", tok) == 0)
                {
                    tok = strtok(NULL, ":");
                    q->hora = atoi(tok);
                    tok = strtok(NULL, " \n");
                    q->minuto = atoi(tok);
                    q->horario = q->hora*60 + q->minuto;

                    if (p == NULL)
                    {
                        q->prox = NULL;
                        p = q;
                    }
                    else
                    {
                    	q->prox = NULL;
						p->prox = q;
					}
                }
            }
        }
    }

    *agenda = p;

    printf("\n\n\tDados carregados!\n\t");
    system("pause");
    return;
}

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
        } while ((escolha < '0') && (escolha > '6'));

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
                le_dados(&compromissos);
                break;
            
            /*case '7':
                // ler todos os compromissos
                ler_lista(compromissos);
                break;*/

            case '0':
                break;

            default:
                printf("\n\n\nDigite um dos numeros do menu!\n\t");
                system("pause");
        }
    } while (escolha != '0');

    system("cls");
    printf("Obrigado por usar a agenda!\n");
    system("pause");
    return 0;
}
