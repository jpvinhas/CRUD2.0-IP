#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CIANO   "\x1b[36m"
#define RESET   "\x1b[0m"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "atendimentos.h"


int menu_atendimento() {
    printf("\n-----------------------------"BLUE"MENU ATENDIMENTO"RESET"-----------------------------\n");
    printf(YELLOW"Selecione a funcionalidade que desejar: \n"RESET);
    printf(BLUE"\n[1]"RESET" Inserir um Novo Atendimento\n"BLUE"[2]"RESET" Alterar um Atendimento Existente");
    printf(BLUE"\n[3]"RESET" Excluir um Atendimento\n"BLUE"[4]"RESET" Exibir os Dados de um Atendimento com base no seu código");
    printf(BLUE"\n[5]"RESET" Exibir Todos os Atendimentos de um Paciente com base no seu código");
    printf(BLUE"\n[6]"RESET" Exibir Todos os Atendimentos e seu Somatório Total Diário\n"BLUE"[7]"RESET" Exibir os Atendimentos em Ordem de Data de Atendimento");
    printf(BLUE"\n[8]"RESET" Exibir o Somatório dos Atendimentos pagos de um determinado período de atendimento\n"BLUE"[9]"RESET" Exibir Todos os Atendimentos\n");
    printf(BLUE"[10]"RESET" Salvar Atendimentos Pendentes\n"BLUE"[11]"RESET" Voltar para o Menu Anterior\n");
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
    printf("*--Código-----Código do Paciente------Data----------Tipo--------Preço--------Status----*\n");
    printf("   %s  |       %s       |   %s  |   %s   |  R$%.2f  | %s\n\n",
           novo_atendimento->codigo_atendimento,
           novo_atendimento->codigo_paciente,
           novo_atendimento->data,
           novo_atendimento->tipo,
           novo_atendimento->preco,
           novo_atendimento->status);
}
void receber_status_atendimento(atendimento *novo_atendimento){
    while(1) {
        char opcao;
        int erro = 0;
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
            default: printf(RED"* Selecione um Status Válido! *\n"RESET); erro = 1;break;
        }
        if(erro) {
            continue;
        }break;
    }
}
int procura_paciente(paciente *todos_pacientes, int qntd_pacientes, char codigo_paciente[]) {
        for(int i = 0; i < qntd_pacientes; i++) {
            //if(!todos_pacientes[i].ativo)break;
            if(!strcmp(codigo_paciente, todos_pacientes[i].codigo)) {
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
    char codigo_atendimento[9];
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


int procura_atendimento2(atendimento *todos_atendimentos, size_t qnt_atendimentos) {
    int status_procura;
    char codigo_atendimento[9];

    ler_str(codigo_atendimento);

    for(int i = 0; i < qnt_atendimentos; i++) {
        status_procura = procura_codigo_atendimento(todos_atendimentos[i].codigo_atendimento, qnt_atendimentos, codigo_atendimento);
        if(status_procura  && todos_atendimentos[i].ativo) {
            return i;

        }
    }
    printf(RED"Atendimento NÃO cadastrado ou ainda NÃO salvo!\n"RESET);
    return -1;
}

int atendimento_ja_cadastrado(atendimento *todos_atendimentos, char paciente_codigo[], char data_analisada[], size_t qnt_atendimentos) {
    for (int i = 0; i < qnt_atendimentos; i++) {
        if(!strcmp(todos_atendimentos[i].codigo_paciente, paciente_codigo)) {
            if(!strcmp(todos_atendimentos[i].data, data_analisada)) {
                return 1;
            }
        }
    }
    return 0;
}

void receber_tipo_atendimento(atendimento *novo_atendimento){
    
    printf(BLUE"Selecione o Tipo de Atendimento:\n"RESET);
    int opcao = coletar_opcao("Consulta","Retorno");
    
    if(opcao) {strcpy(novo_atendimento->tipo,"Retorno");}
    else {strcpy(novo_atendimento->tipo,"Consulta");}
}

float receber_preco(){
    char preco[10];
    double new_preco;

    while(1){
        printf(BLUE"Digite o preço da consulta:\n"RESET);
        ler_str(preco);

        new_preco = atof(preco);
        if(new_preco == 0.0) {
            printf(RED"Preco Invalido!\n"RESET);
            continue;
        }else {
            return (float)new_preco;
        }
    }
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
void ordenar_datas(atendimento *todos_atendimentos,int ordem_datas[],size_t qnt_atendimentos){
    for (int i = 0; i < qnt_atendimentos; i++) {
        ordem_datas[i] = i;
    }
    for (int i = 0; i < qnt_atendimentos - 1; i++) {
        if(!todos_atendimentos[i].ativo) {continue;}
        for (int j = i + 1; j < qnt_atendimentos; j++) {
            if(!todos_atendimentos[i].ativo) {continue;}
            if (compara_data(todos_atendimentos[ordem_datas[j]].data, todos_atendimentos[ordem_datas[i]].data)) {
                int aux = ordem_datas[i];
                ordem_datas[i] = ordem_datas[j];
                ordem_datas[j] = aux;
            }
        }
    }
}
void adicionar_atendimentos(const char* nomeArquivo, atendimento* novosatendimentos,int qnd_novos_atendimentos,size_t tam_struct) {
    FILE* arquivo = fopen(nomeArquivo, "ab+");  // Abre o arquivo em modo de leitura e escrita no final
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    printf("1");
    // Escreve os novos structs no final do arquivo
    fseek(arquivo, 0, SEEK_END);  // Move o ponteiro para o final do arquivo
    fwrite(novosatendimentos, tam_struct, qnd_novos_atendimentos, arquivo);
    
    fclose(arquivo);
}
void salvar(paciente* pacientes,atendimento* atendimentos, int* alteracoes_pacientes, int* alteracoes_atendimentos, size_t qnd_pacientes,size_t qnd_atendimentos){
    for(int i=0; i< qnd_pacientes;i++){
        if(alteracoes_pacientes[i]==1) alterar("pacientes.bin",i,&pacientes[i],sizeof(paciente));
    }
    for(int i=0; i< qnd_atendimentos;i++){
        if(alteracoes_atendimentos[i]==1) alterar("atendimentos.bin",i,&atendimentos[i],sizeof(atendimento));
    }
}
void salvar_novos(paciente* pacientes,atendimento* atendimentos,paciente* novos_pacientes,atendimento*novos_atendimentos,int qnt_novos_pacientes, int qnt_novos_atendimentos, int qnt_pacientes,int qnt_atendimentos){
    adicionar_pacientes("pacientes.bin",novos_pacientes,qnt_novos_pacientes,sizeof(paciente));
    adicionar_atendimentos("atendimentos.bin",novos_atendimentos,qnt_novos_atendimentos,sizeof(atendimento));
    qnt_novos_pacientes = 0;
    qnt_novos_atendimentos= 0;
}
float soma_consultas_pagas_pacientes(char *nome,atendimento *atendimentos,int qnt_atendimentos) {
    float soma_consultas = 0;

    for(int i = 0; i < qnt_atendimentos; i++) {
        int compara_nomes = strcmp(nome, atendimentos[i].codigo_paciente);
        if(compara_nomes == 0) {
            soma_consultas += atendimentos[i].preco;
        }
    }
    
    return soma_consultas;
}

int procura_atendimento_livre(atendimento* atendimentos_arquivados, int tamanho_vetor) {
    for (int i = 0; i < tamanho_vetor; i++) {
        if(atendimentos_arquivados[i].ativo == 0) {
            return i;
        }
    }
    return -1;
}

int verifica_codigo_atendimento(atendimento *todos_atendimentos, char input_codigo[], int qnt_atendimentos) {
    for (int i = 0; i < qnt_atendimentos; i++) {
        if(!strcmp(input_codigo, todos_atendimentos[i].codigo_atendimento)) {
            return 1;
        }
    }
    return 0;
}


float intervalo_entre_datas(char data1[], char data2[], atendimento *todos_atendimentos, size_t qntd_atendimentos) {
    char aux[40];
    if(compara_data(data1, data2)) {
        strcpy(aux, data1);
        strcpy(data1, data2);
        strcpy(data2, aux);
    }
    int dia_incial, mes_inicial, ano_inicial;
    sscanf(data1, "%d/%d/%d", &dia_incial, &mes_inicial, &ano_inicial);

    int dia_final, mes_final, ano_final;
    sscanf(data2, "%d/%d/%d", &dia_final, &mes_final, &ano_final);

    float somatorio_preco_atendimentos = 0;
    int flag_dias = 0;
    int flag_mes = 0;
    char data_comparada[40];

    for(int index_atendimento = 0; index_atendimento < qntd_atendimentos; index_atendimento++) {
        int compara_dia, compara_mes;
        for(int compara_ano = ano_inicial; compara_ano <= ano_final; compara_ano++) {
            if(flag_mes) {
                mes_inicial = 1;
            }
            for(compara_mes = mes_inicial; compara_mes <= 12; compara_mes++) {
                if(compara_mes == 12 && compara_ano == ano_inicial && !flag_mes) {
                    flag_mes = 1;
                }

                if(flag_dias) {
                    dia_incial = 1;
                }
                for(compara_dia = dia_incial; compara_dia <= 31; compara_dia++) {

                    if((compara_dia == dia_final) && (compara_mes == mes_final) && (compara_ano == ano_final)) {

                        sprintf(data_comparada, "%02d/%02d/%04d", compara_dia, compara_mes, compara_ano);
                        if(!datas_diferentes(data_comparada, todos_atendimentos[index_atendimento].data)) {
                            somatorio_preco_atendimentos += todos_atendimentos[index_atendimento].preco;
                        }
                        break;
                    }

                    if(compara_dia == 31 && compara_mes == mes_inicial && !flag_dias) {

                        sprintf(data_comparada, "%02d/%02d/%04d", compara_dia, compara_mes, compara_ano);
                        if(!datas_diferentes(data_comparada, todos_atendimentos[index_atendimento].data)) {
                            somatorio_preco_atendimentos += todos_atendimentos[index_atendimento].preco;

                        }
                        flag_dias = 1;
                        break;
                    }
                    sprintf(data_comparada, "%02d/%02d/%04d", compara_dia, compara_mes, compara_ano);
                    if(!datas_diferentes(data_comparada, todos_atendimentos[index_atendimento].data)) {
                        somatorio_preco_atendimentos += todos_atendimentos[index_atendimento].preco;
                    }

                }
                if(compara_mes == mes_final && compara_ano == ano_final) {
                    //faz a ultima comparacao
                    break;
                }
            }
        }
    }
    return somatorio_preco_atendimentos;
}


int datas_diferentes(char data1[],char data2[]) {

    int dia1, mes1, ano1, dia2, mes2, ano2;

    sscanf(data1, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(data2, "%d/%d/%d", &dia2, &mes2, &ano2);

    if (ano1 > ano2) {
        return 1;
    } else if (ano1 < ano2) {
        return 2;
    } else {
        if (mes1 > mes2) {
            return 1;
        } else if (mes1 < mes2) {
            return 2;
        } else {
            if (dia1 > dia2) {
                return 1;
            } else if (dia1 < dia2) {
                return 2;
            } else {
                return 0; // As datas são iguais
            }
        }
    }
}