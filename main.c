
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 500

typedef struct {
    char genero;
    int idade;
    int gestante;
    int lactante;
    int necessidadeEspecial;
    int obeso;
    char senha[10];
} Paciente;

typedef struct {
    Paciente dados[MAX];
    int inicio;
    int fim;
    int quantidade;
} Fila;

Fila normal = { .inicio = 0, .fim = 0, .quantidade = 0 };
Fila preferencial = { .inicio = 0, .fim = 0, .quantidade = 0 };
Fila urgente = { .inicio = 0, .fim = 0, .quantidade = 0 };

int contadorN = 0;
int contadorP = 0;
int contadorU = 0;

Paciente pacienteAtual;
int existeAtendimento = 0;

void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;
}

int filaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

int filaCheia(Fila *fila) {
    return fila->quantidade == MAX;
}

int inserirFila(Fila *fila, Paciente paciente) {
    if (filaCheia(fila)) {
        return 0;
    }

    fila->dados[fila->fim] = paciente;
    fila->fim = (fila->fim + 1) % MAX;
    fila->quantidade++;

    return 1;
}

int retirarFila(Fila *fila, Paciente *paciente) {
    if (filaVazia(fila)) {
        return 0;
    }

    *paciente = fila->dados[fila->inicio];

    fila->inicio = (fila->inicio + 1) % MAX;
    fila->quantidade--;

    return 1;
}

int classificarPaciente(Paciente p) {

    if (p.idade > 80) {
        return 3;
    }

    if (
        (p.genero == 'F' && p.idade >= 60) ||
        (p.genero == 'M' && p.idade >= 65) ||
        p.gestante ||
        p.lactante ||
        p.necessidadeEspecial ||
        p.obeso
    ) {
        return 2; 
    }

    return 1; 
}

void gerarSenha(Paciente *p, int categoria) {

    if (categoria == 3) {
        contadorU++;
        sprintf(p->senha, "U%03d", contadorU);
    }
    else if (categoria == 2) {
        contadorP++;
        sprintf(p->senha, "P%03d", contadorP);
    }
    else {
        contadorN++;
        sprintf(p->senha, "N%03d", contadorN);
    }
}

int lerSimNao(char mensagem[]) {
    char resposta;

    while (1) {
        printf("%s (S/N): ", mensagem);
        scanf(" %c", &resposta);
        resposta = toupper((unsigned char)resposta);

        if (resposta == 'S') return 1;
        if (resposta == 'N') return 0;

        printf("Resposta invalida! Digite S ou N.\n");
    }
}

int lerIdade() {
    int idade;

    while (1) {
        printf("dade: ");

        if (scanf("%d", &idade) != 1) {
            printf("Digite uma idade valida.\n");
            while (getchar() != '\n');
            continue;
        }

        if (idade >= 0 && idade <= 120) {
            return idade;
        }

        printf("dade deve estar entre 0 e 120.\n");
    }
}

void cadastrarPaciente() {

    Paciente p;
    int categoria;

    printf("\n===== CADASTRO DE PACIENTE =====\n");

    printf("Genero (F/M): ");
    scanf(" %c", &p.genero);
    p.genero = toupper((unsigned char)p.genero);

    while (p.genero != 'F' && p.genero != 'M') {
        printf("Genero invalido! Digite F ou M: ");
        scanf(" %c", &p.genero);
        p.genero = toupper((unsigned char)p.genero);
    }

    p.idade = lerIdade();

    p.gestante = 0;

    if (p.genero == 'F') {
        p.gestante = lerSimNao("A paciente esta gestante?");
    }

    p.lactante = lerSimNao("E lactante?");
    p.necessidadeEspecial =
        lerSimNao("Poss necessidade especial?");
    p.obeso = lerSimNao("Possui condicao de obesidade?");

    categoria = classificarPaciente(p);

    gerarSenha(&p, categoria);

    if (categoria == 3) {
        inserirFila(&urgente, p);
        printf("\nCategoria: URGENTE\n");
    }
    else if (categoria == 2) {
        inserirFila(&preferencial, p);
        printf("\nCategoria: PREFERENCIAL\n");
    }
    else {
        inserirFila(&normal, p);
        printf("\nCategoria: NORMAL\n");
    }

    printf("Senha gerada: %s\n", p.senha);
}

int consultarProxima() {

    if (!filaVazia(&urgente)) {
        printf("Proxima senha: %s (URGENTE)\n",
               urgente.dados[urgente.inicio].senha);
        return 1;
    }

    if (!filaVazia(&preferencial)) {
        printf("Proxima senha: %s (PREFERENCIAL)\n",
               preferencial.dados[preferencial.inicio].senha);
        return 1;
    }

    if (!filaVazia(&normal)) {
        printf("Proxima senha: %s (NORMAL)\n",
               normal.dados[normal.inicio].senha);
        return 1;
    }

    printf("Nao existem pacientes aguardando.\n");
    return 0;
}

void chamarPaciente() {

    if (existeAtendimento) {
        printf("\nFinalize o atendimento atual antes de chamar outro.\n");
        return;
    }

    if (retirarFila(&urgente, &pacienteAtual)) {
        printf("\nChamando URGENTE: %s\n",
               pacienteAtual.senha);
    }
    else if (retirarFila(&preferencial, &pacienteAtual)) {
        printf("\nChamando PREFERENCIAL: %s\n",
               pacienteAtual.senha);
    }
    else if (retirarFila(&normal, &pacienteAtual)) {
        printf("\nChamando NORMAL: %s\n",
               pacienteAtual.senha);
    }
    else {
        printf("\nNao existem pacientes na fila.\n");
        return;
    }

    existeAtendimento = 1;
}

void finalizarAtendimento() {

    if (!existeAtendimento) {
        printf("\nNao existe atendimento em andamento.\n");
        return;
    }

    printf("\nAtendimento da senha %s finalizado!\n",
           pacienteAtual.senha);

    existeAtendimento = 0;
}

void apresentarPainel() {

    printf("\n----- PAINEL DE ATENDIMENTO -----\n");

    if (existeAtendimento) {
        printf("Senha atual: %s\n", pacienteAtual.senha);
    }
    else {
        printf("Senha atual: Nenhuma\n");
    }

    printf("\nPROXIMAS SENHAS:\n");

    int total = urgente.quantidade +
                preferencial.quantidade +
                normal.quantidade;

    int i;

    if (total == 0) {
        printf("Nenhum paciente aguardando.\n");
    }

    for (i = 0; i < urgente.quantidade; i++) {
        int pos = (urgente.inicio + i) % MAX;
        printf("%s - URGENTE\n", urgente.dados[pos].senha);
    }

    for (i = 0; i < preferencial.quantidade; i++) {
        int pos = (preferencial.inicio + i) % MAX;
        printf("%s - PREFERENCIAL\n",
               preferencial.dados[pos].senha);
    }

    for (i = 0; i < normal.quantidade; i++) {
        int pos = (normal.inicio + i) % MAX;
        printf("%s - NORMAL\n", normal.dados[pos].senha);
    }

    printf("\nQUANTIDADE EM ESPERA:\n");
    printf("Urgentes: %d\n", urgente.quantidade);
    printf("Preferenciais: %d\n", preferencial.quantidade);
    printf("Normais: %d\n", normal.quantidade);

    printf("Total: %d\n", total);

    printf("===========================================\n");
}

void exibirMenu() {

    printf("\n===== SISTEMA DE SENHAS CLINICA =====\n");
    printf("1 - Cadastrar paciente\n");
    printf("2 - Consultar proxima senha\n");
    printf("3 - Chamar paciente\n");
    printf("4 - Finalizar atendimento\n");
    printf("5 - Exibir painel\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {

    int opcao;

    inicializarFila(&normal);
    inicializarFila(&preferencial);
    inicializarFila(&urgente);

    do {

        exibirMenu();

        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (opcao) {

            case 1:
                cadastrarPaciente();
                break;

            case 2:
                consultarProxima();
                break;

            case 3:
                chamarPaciente();
                break;

            case 4:
                finalizarAtendimento();
                break;

            case 5:
                apresentarPainel();
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
