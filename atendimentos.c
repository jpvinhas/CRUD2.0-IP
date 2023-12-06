#include <stdio.h>
#include <string.h>

#include "atendimentos.h"
#include "util.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CIANO   "\x1b[36m"
#define RESET   "\x1b[0m"


int menu_atendimento() {
    printf("\n-----------------------------"BLUE"MENU ATENDIMENTO"RESET"-----------------------------\n");
    printf("Selecione a funcionalidade que desejar: \n");
    printf(BLUE"\n[1]"RESET" Inserir um Novo Atendimento\n"BLUE"[2]"RESET" Alterar um Atendimento Existente");
    printf(BLUE"\n[3]"RESET" Excluir Atendimento\n"BLUE"[4]"RESET" Exibir Atendimento(Código)");
    printf(BLUE"\n[5]"RESET" Exibir Atendimentos de um Paciente(Código do Paciente)");
    printf(BLUE"\n[6]"RESET" Exibir Atendimentos de um Paciente(Nome do Paciente)\n"BLUE"[7]"RESET" Exibir Todos Atendimentos do Dia");
    printf(BLUE"\n[8]"RESET" Exibir Todos Atendimentos(Data mais Próxima)\n"BLUE"[9]"RESET" Voltar para o Menu Anterior\n");
    printf("\n---------------------------------------------------------------------------\n");

    printf("\nDigite a Funcionalidade Desejada: ");
    int opcao;
    
    printf(BLUE);
    fflush(stdin);
    scanf("%d",&opcao);
    printf(RESET);

    return opcao;
}
void exibir_dados_atendimento(atendimento *novo_atendimento) {
    printf("*--Código-----Código do Paciente------Data-------Tipo-----Preço-----Status----*\n");
    printf("   %s  |       %s       |   22/22/2222  |   %s   |  R$%.2f  | %s\n\n",
           novo_atendimento->codigo_atendimento,
           novo_atendimento->codigo_paciente,
           //novo_atendimento->data,
           novo_atendimento->tipo,
           novo_atendimento->preco,
           novo_atendimento->status);
}
void receber_status_atendimento(atendimento *novo_atendimento){
    char opcao;
    printf(BLUE"Selecione o status da consulta:\n"RESET);
    printf(BLUE"[1]"RESET"Agendado "BLUE"[2]"RESET"Esperando "BLUE"[3]"RESET"Em atendimento "BLUE"[4]"RESET"Atendido\n");

    fflush(stdin);
    printf(BLUE);  
    opcao=getchar();
    printf(RESET);

    switch(opcao){
        case '1':strcpy(novo_atendimento->status,"Agendado");break;
        case '2':strcpy(novo_atendimento->status,"Esperando");break;
        case '3':strcpy(novo_atendimento->status,"Em atendimento");break;
        case '4':strcpy(novo_atendimento->status,"Atendido");break;
        case '\0': strcpy(novo_atendimento->status,"Não Informado");break;
    }
}
int procura_paciente(paciente *todos_pacientes, int qntd_pacientes, char codigo_paciente[]) {
        for(int i = 0; i < qntd_pacientes; i++) {
            if(!strcmp(codigo_paciente, todos_pacientes[i].codigo_paciente)) {
                return 1;
            }
        }
    return 0;
}


int procura_paciente_codigo(char codigo_pacientes[][8],int QNTD_PACIENTES,int pacientes_ativos[]){
    char codigo_paciente[8];
    ler_str(codigo_paciente);                            
    
    int indice_do_paciente = procura_codigo(codigo_paciente,codigo_pacientes,QNTD_PACIENTES);
    if(indice_do_paciente == -1){
        printf(RED"Paciente não cadastrado\n"RESET);
        if(coletar_opcao("Voltar","Tentar novamente"))return -1;
        return -2;
    }
    if(pacientes_ativos[indice_do_paciente]== 0){
        printf(RED"Paciente não cadastrado ou Excluido recentemente\n"RESET);
        if(coletar_opcao("Voltar","Tentar novamente"))return -1;
        return -2;
    }
    return indice_do_paciente;
}


int procura_atendimento(char codigo_atendimentos[][8],int QNTD_ATENDIMENTOS,int atendimentos_ativos[]){
    char codigo_atendimento[8];
    ler_str(codigo_atendimento);
    int indice_do_atendimento = procura_codigo(codigo_atendimento,codigo_atendimentos,QNTD_ATENDIMENTOS);
    if(indice_do_atendimento == -1){
        printf(RED"Atendimento não cadastrado\n"RESET);
        if(coletar_opcao("Voltar","Tentar novamente"))return -1;
        return -2;
    }
    if(atendimentos_ativos[indice_do_atendimento]== 0){
        printf(RED"Atendimento não cadastrado ou Excluido recentemente\n"RESET);
        if(coletar_opcao("Voltar","Tentar novamente"))return -1;
        return -2;
    }
    return indice_do_atendimento;
}

int atendimento_ja_cadastrado(char data_atendimentos[][40],int paciente_do_atendimento[],int atendimento_atual,int tamanho){
    int atendimento_ja_cadastrado=0;
    for(int i=0;i<tamanho;i++){
        if(i==atendimento_atual) continue;
        if(paciente_do_atendimento[i] == paciente_do_atendimento[atendimento_atual]){
            int data_paciente_igual= !(strcmp(data_atendimentos[i],data_atendimentos[atendimento_atual]));
            if(data_paciente_igual){
                printf(RED"Paciente ja tem atendimento nesta data!\n"RESET);
                atendimento_ja_cadastrado=1;
            }
        }

    }return atendimento_ja_cadastrado;
}
void receber_tipo_atendimento(atendimento *novo_atendimento){
    
    printf(BLUE"Selecione o Tipo de Atendimento:\n"RESET);
    int opcao = coletar_opcao("Consulta","Retorno");
    
    if(opcao) {strcpy(novo_atendimento->tipo,"Retorno");}
    else {strcpy(novo_atendimento->tipo,"Consulta");}
}

float receber_preco(){
    float preco;

    while(1){
        printf(BLUE"Digite o preço da consulta:\n"RESET);

        scanf("%f",&preco);

        if(preco <= 0){
            printf(RED"Digite um preço REAL!\n"RESET);
            continue;
        }
        break;
    }
    return preco;
}

int compara_data(char data1[],char data2[]) {
    
    int dia1, mes1, ano1, dia2, mes2, ano2;

    sscanf(data1, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(data2, "%d/%d/%d", &dia2, &mes2, &ano2);

    if (ano1 > ano2) {
        return 1;
    } else if (ano1 < ano2) {
        return 0;
    } else {
        if (mes1 > mes2) {
            return 1;
        } else if (mes1 < mes2) {
            return 0;
        } else {
            if (dia1 > dia2) {
                return 1;
            } else if (dia1 < dia2) {
                return 0;
            } else {
                return 0; // As datas são iguais
            }
        }
    }
}
void ordenar_datas(char datas[][40],int ordem_datas[],int tamanho,int atendimentos_ativos[]){
    for (int i = 0; i < tamanho; i++) {
        ordem_datas[i] = i;
    }
    for (int i = 0; i < tamanho - 1; i++) {
        if(atendimentos_ativos[i]==0) continue;
        for (int j = i + 1; j < tamanho; j++) {
            if(atendimentos_ativos[j]==0) continue;
            if (compara_data(datas[ordem_datas[j]], datas[ordem_datas[i]])) {
                int aux = ordem_datas[i];
                ordem_datas[i] = ordem_datas[j];
                ordem_datas[j] = aux;
            }
        }
    }
}


void* procura_atendimento_livre(atendimento* atendimentos_arquivados, int tamanho_vetor) {
    for (int i = 0; i < tamanho_vetor; i++) {
        if(atendimentos_arquivados[i].ativo) {
            return &atendimentos_arquivados[i];
        }
    }
    return NULL;
}