#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CIANO   "\x1b[36m"
#define RESET   "\x1b[0m"

#include <stdio.h>
#include <string.h>
#include "atendimentos.h"

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
void exibir_dados_atendimento(char codigo[][8],char paciente[][40],char codigo_paciente[][8],int indice_paciente,char data[][40],char tipo[][40],float preco[],char status[][40],int indice_atendimento){
    printf("Código------Paciente------------Código do Paciente----------Data-----------Tipo----------Preço---------Status--------\n");
    printf("%s   |   %s   |  %s   |   %s   |   %s   |   R$%.2f   |   %s  \n   ",codigo[indice_atendimento],paciente[indice_paciente],codigo_paciente[indice_paciente],data[indice_atendimento],tipo[indice_atendimento],preco[indice_atendimento],status[indice_atendimento]);
}
void receber_status_atendimento(char vetor_status_atendimentos[][40],int indice_do_atendimento){
    char opcao;
    printf(BLUE"Status da consulta:\n"RESET);
    printf(BLUE"[1]"RESET"Agendado "BLUE"[2]"RESET"Esperando "BLUE"[3]"RESET"Em atendimento "BLUE"[4]"RESET"Atendido\n");
    fflush(stdin);
    printf(BLUE);  
    opcao=getchar();
    printf(RESET);
    switch(opcao){
        case  '1':strcpy(vetor_status_atendimentos[indice_do_atendimento],"Agendado");break;
        case  '2':strcpy(vetor_status_atendimentos[indice_do_atendimento],"Esperando");break;
        case  '3':strcpy(vetor_status_atendimentos[indice_do_atendimento],"Em atendimento");break;
        case  '4':strcpy(vetor_status_atendimentos[indice_do_atendimento],"Atendido");break;
        case  '\0': strcpy(vetor_status_atendimentos[indice_do_atendimento],"Não Informado");break;
    }
}
int procura_paciente(char nomes_pacientes[][40],int tamanho){
    char nome[40];
    int indice_paciente;
    while(1){
        printf("Digite o Nome do Paciente: \n");
        ler_str(nome);
        formata_string_maisculo(nome);

        indice_paciente=procura_string(nome,nomes_pacientes,tamanho);
 
        if(strcmp(nome,"SAIR")==0)return -1;
        if(indice_paciente < 0){
            printf(RED"Paciente não cadastrado!\n"RESET);
            if(coletar_opcao("Voltar","Tentar novamente"))continue;
            return -1;
        }
        break;
    }
    return indice_paciente;
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
void receber_tipo_atendimento(char tipo_atendimentos[][40],int espaco_livre){
    
    printf(BLUE"Tipo de Atendimento:\n"RESET);
    int opcao=coletar_opcao("Consulta","Retorno");
    
    if(opcao) strcpy(tipo_atendimentos[espaco_livre],"Retorno") ;
    else strcpy(tipo_atendimentos[espaco_livre],"Consulta");
}
float receber_preco(){
    float preco;

    while(1){
        printf(BLUE"Digite o preço da consulta:\n"RESET);

        scanf("%f",&preco);

        if(preco < 0){
            printf(RED"Digite o preço Corretamente!"RESET);
            continue;
        }
        break;
    }return preco;
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
void adicionar_atendimentos(const char* nomeArquivo, atendimento* novosatendimentos,int qnd_novos_atendimentos,size_t tam_struct) {
    FILE* arquivo = fopen(nomeArquivo, "ab+");  // Abre o arquivo em modo de leitura e escrita no final
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

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
        int compara_nomes = strcmp(nome, atendimentos[i].paciente);
        if(compara_nomes == 0) {
            soma_consultas += atendimentos[i].preco;
        }
    }
    
    return soma_consultas;
}