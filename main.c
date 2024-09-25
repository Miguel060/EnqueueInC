#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int contadorSenha = 0;
int contadorSenhaPrioridade = 0;

typedef struct st_filaPadrao {
    char nome[50];
    struct st_filaPadrao *prox;
    struct st_filaPadrao *ant;
    int senha;
    int senhaPrioridade;
} filaPadrao;

typedef struct st_filaPadraoPreferencial {
    char nome[50];
    struct st_filaPadraoPreferencial *prox;
    struct st_filaPadraoPreferencial *ant;
    int senhaPrioridade;
} filaPadraoPreferencial;

void iniciarfilaPadrao(filaPadrao *f) {
    f->prox = NULL;
}

void iniciarfilaPadraoPrioridade(filaPadraoPreferencial *fp) {
    fp->prox = NULL;
}

int v_vaziaPadrao(filaPadrao *f) {
    if (f->prox == NULL) {
        return 1;
    } else {
        return 0;
    }
}

int v_vaziaPreferencial(filaPadraoPreferencial *fpe) {
    if (fpe->prox == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void inserirNafilaPadrao(filaPadrao *f) {
    filaPadrao *novoNo;
    int op;
    char nome[50];
    novoNo = (filaPadrao *) malloc(sizeof(filaPadrao));
    novoNo->senha = ++contadorSenha;
    filaPadrao *aux;
    printf("Digite o nome do próximo da fila padrao: ");
    scanf("%s", nome);
    strcpy(novoNo->nome, nome);
    if (v_vaziaPadrao(f)) {
        f->prox = novoNo;
        novoNo->prox = NULL;
        novoNo->ant = NULL;
    } else {
        aux = f->prox;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novoNo;
        novoNo->ant = aux;
        novoNo->prox = NULL;
    }
}

void inserirNafilaPadraoPrioritaria(filaPadraoPreferencial *fp) {
    filaPadraoPreferencial *novoNo;
    char nome[50];
    novoNo = (filaPadraoPreferencial *) malloc(sizeof(filaPadraoPreferencial));
    novoNo->senhaPrioridade = ++contadorSenhaPrioridade;
    filaPadraoPreferencial *aux;
    printf("Digite o nome do próximo da fila prioritaria: ");
    scanf("%s", nome);
    strcpy(novoNo->nome, nome);
    if (v_vaziaPreferencial(fp)) {
        fp->prox = novoNo;
        novoNo->prox = NULL;
        novoNo->ant = NULL;
    } else {
        aux = fp->prox;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novoNo;
        novoNo->ant = aux;
        novoNo->prox = NULL;
    }
}


void printList(filaPadrao *f, filaPadraoPreferencial *fp) {
    filaPadrao *aux;
    aux = f->prox;
    printf("Fila Padrão:\n");
    while (aux != NULL) {
        printf("%s(%d)", aux->nome, aux->senha);
        aux = aux->prox;
    }
    filaPadraoPreferencial *aux2;
    aux2 = fp->prox;
    printf("\n--------------------------------------\n");
    printf("Fila Preferencial:\n");
    while (aux2 != NULL) {
        printf("%s(%dp)", aux2->nome, aux2->senhaPrioridade);
        aux2 = aux2->prox;
    }
    printf("\n--------------------------------------\n");
    printf("Fila com todos elementos:\n");
    aux2 = fp->prox;
    aux = f->prox;
    while (aux2 != NULL) {
        printf("%s(%dp)", aux2->nome, aux2->senhaPrioridade);
        aux2 = aux2->prox;
    }
    while (aux != NULL) {
        printf("%s(%d)", aux->nome, aux->senha);
        aux = aux->prox;
    }
}

void remover(filaPadraoPreferencial *fp, filaPadrao *f) {
    filaPadraoPreferencial *aux;
    filaPadrao *aux2;
    if(fp->prox != NULL) {
        aux = fp->prox;
        if(aux->prox == NULL) {
            fp->prox = NULL;
            free(aux);
        }else {
            fp->prox = aux->prox;
            aux->prox->ant = NULL;
            free(aux);
        }
    }else {
        aux2 = f->prox;
        if(aux2->prox == NULL) {
            f->prox = NULL;
            free(aux2);
        }else {
            f->prox = aux2->prox;
            aux2->prox->ant = NULL;
            free(aux2);
        }
    }
}


int menu() {
    int opt;
    printf("\nSwitch option: \n");
    printf("1- Mostrar fila:\n");
    printf("2- Inserir próximo na fila:\n");
    printf("3. Remover da fila:\n");
    printf("4- Encerrar:\n");
    printf("Option: ");
    scanf("%d", &opt);
    printf("\n");
    return opt;
}

void option(filaPadrao *f, filaPadraoPreferencial *fp, int option) {
    int opF;
    switch (option) {
        case 1:
            printList(f, fp);
            break;
        case 2:
            printf("Fila prioritária?(1-SIM/2-NAO):");
            scanf("%d", &opF);
            if (opF == 1) {
                inserirNafilaPadraoPrioritaria(fp);
            } else if (opF == 2) {
                inserirNafilaPadrao(f);
            }
            break;
        case 3:
            remover(fp, f);
            break;
        case 4:
            printf("Encerrar:\n");
            exit(0);
        default:
            printf("Invalid option\n");
    }
}

int main(void) {
    int opt;
    filaPadrao *f = (filaPadrao *) malloc(sizeof(filaPadrao));
    filaPadraoPreferencial *fp = (filaPadraoPreferencial *) malloc(sizeof(filaPadraoPreferencial));
    if (!f) {
        printf("Erro ao criar filaPadrao\n");
    }
    if (!fp) {
        printf("Erro ao criar filaPreferencial\n");
    }
    iniciarfilaPadrao(f);
    iniciarfilaPadraoPrioridade(fp);
    do {
        opt = menu();
        option(f, fp, opt);
    } while (opt);
    free(f);
    free(fp);
    return 0;
}
