#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CIANO   "\x1b[36m"
#define RESET   "\x1b[0m"


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "util.h"


int menu_principal() {
    printf(BLUE"\n******************************************\n"RESET);
    printf("\n"BLUE"*"RESET YELLOW"Seja Muito Bem vindo(a) a Clinica Fatima"RESET BLUE"*\n"RESET);
    printf(BLUE"\n******************************************\n"RESET);

    printf(YELLOW"\nSelecione como você deseja acessar nosso sistema: \n"RESET);
    printf(BLUE"[1]"RESET "Paciente");
    printf(BLUE" \t[2] "RESET"Atendimento\t");
    printf(BLUE"\t[3]"RESET" Encerrar\n");

    while(1) {
        int interacao_menu_pacientes;

        __fpurge(stdin);
        interacao_menu_pacientes = getchar();

        switch (interacao_menu_pacientes)
        {
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '\n':
            break;
        default:
            printf(RED"Selecione uma das opções anteriores!\n"RESET);
            break;
        };
    }
}

int coletar_opcao(char opcao1[],char opcao2[]){
    while(1) {
        char opcao;
        printf(BLUE"[0]"RESET" %s   "BLUE"[1]"RESET"%s\n",opcao1,opcao2);;
        
        printf(BLUE);
        __fpurge(stdin);  
        opcao=getchar();
        printf(RESET);
        
        switch(opcao){
            case '0':
                printf("\nOpção -> "BLUE"[0], \"%s\""RESET"Selecionada...\n", opcao1); 
                return 0;
            case '1':
                printf("\nOpção -> "BLUE"[1], \"%s\""RESET" Selecionada...\n", opcao2); 
                return 1;
            case '\n':
                break;
            default:
                printf("Digite Apenas 0 ou 1\n");                            
                break;
        }
    }
}
int preenche_vetor_ativos(int vetor_ativos[], int tamanho_vetor) {
    for (int i = 0; i < tamanho_vetor; i++)
        vetor_ativos[i] = 0;
}


int preenche_matriz_bidimensional(char vetor_ativos[][40], int tamanho_vetor) {
    for (int i = 0; i < tamanho_vetor; i++)
        strcpy(vetor_ativos[i], "VOID");}


int procura_espaco_livre(int vetor_ativos[], int tamanho_vetor) {
    for (int i = 0; i < tamanho_vetor; i++) {

        if(!vetor_ativos[i]) {
            return i;
        }
    }
    return -1;
}


void ler_str(char string[]) {
    
    printf(BLUE);
    __fpurge(stdin);  
    gets(string);
    printf(RESET);
}
int checar_string(char string[]){
    if(string == NULL || string[0] =='\0'){
        return 1;
    }
    for(int i = 0; string[i] != '\0';i++){
        if(string[i] == ' '){
            continue;
        }
        if(isdigit(string[i]) || !isalnum(string[i])){
          return 1;  
        }
    }return 0;
}

void formata_string_maisculo(char string[]) {
    int string_tamanho = strlen(string);

    for (int i = 0; i < string_tamanho; ++i)
        string[i] = toupper(string[i]);
}

int ja_existe(char string[],char vetor[][40],int tamanho,int indice){
    for(int i = 0; i < tamanho; i++){
        if(i == indice)
            continue;
        if(strcmp(string,vetor[i]) == 0){
            return 1;
        }
    }return 0;
}
int procura_string(char string[],char vetor[][40],int tamanho){
    for(int i = 0; i < tamanho; i++){
        if(strcmp(string,vetor[i]) == 0){
            return i;
        }
    }return -1;
}
int procura_codigo(char codigo_unico_paciente[],char matriz_codigos_pacientes[][8],int tamanho_matriz) {
    for(int i = 0; i < tamanho_matriz; i++){
        if(strcmp(matriz_codigos_pacientes[i],codigo_unico_paciente) == 0) {
            return i;
        }

    }
    return -1;
}
void receber_data(char vetor[][40],int indice_livre) {
    int dia, mes, ano;
    while(1){
        printf(BLUE"Digite o dia: "RESET);
        scanf("%d", &dia);

        printf(BLUE"Digite o mês: "RESET);
        scanf("%d", &mes);

        printf(BLUE"Digite o ano (ex. 2023): "RESET);
        scanf("%d", &ano);
        
        if (!(dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 1000)){
        printf("Data inválida!\n");
        if(coletar_opcao("Voltar","Tentar novamente"))continue;
        return;
        }

        sprintf(vetor[indice_livre],"%02d/%02d/%04d", dia, mes, ano);

        break;
    }

}

void imprimir_vetor(char vetor[][40],int tamanho){
    for(int i=0;i<tamanho;i++){
        printf("%d - %s\n",i,vetor[i]);
    }
}
void imprimir_vetor_codigos(char vetor[][8],int tamanho){
    for(int i=0;i<tamanho;i++){
        printf("%d - %s\n",i,vetor[i]);
    }
}

void cria_codigo(char vetor[][8],int indice_livre){
    char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";//36 caracteres
    char novo_codigo[8];
    
    srand(time(NULL));

    for(int i = 0; i < 8; i++) {
        if(i==7)break;
        int indice_aleatorio = rand() % 36;
        novo_codigo[i] = caracteres[indice_aleatorio];
        
    }
    strcpy(vetor[indice_livre],novo_codigo);
}


float soma_consultas_pagas_pacientes(char nome_paciente_desejado[], char matriz_nomes_paciente[][40], float vetor_preco_atendimentos[], int tamanho_vetores, int vetor_paciente_atendimento_indice[]) {
    float soma_consultas = 0;

    for(int i = 0; i < tamanho_vetores; i++) {
        int paciente_com_atendimento = vetor_preco_atendimentos[i];
        int compara_nomes = strcmp(nome_paciente_desejado, matriz_nomes_paciente[paciente_com_atendimento]);
        if(compara_nomes) {
            soma_consultas += vetor_preco_atendimentos[i];
        }
    }
    
    return soma_consultas;
}


void copia_matriz(char matriz1[][40], char matriz2[][40], int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        strcpy(matriz1[i], matriz2[i]);
    }
}


int varrer_datas(char data[][40], char matriz_datas_atendimentos_copia[][40], int tam_matriz_datas_atendimentos) {
    for(int i = 0; i < tam_matriz_datas_atendimentos; i++) {
        int compara_datas = !strcmp(data, matriz_datas_atendimentos_copia[i]);

        if(compara_datas) {
            return i;
        }
    }
    return -1;
}