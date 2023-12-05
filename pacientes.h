#ifndef PACIENTES_H
#define PACIENTES_H


#include "util.h"
#include "atendimentos.h"

typedef struct {
    long int codigo2;
    char codigo[8]; // codigo not
    char nome[40];
    char RG[12];
    char CPF[12];
    char tipo_sanguineo[3];
    char fator_RH[9];
    char endereco[40];
    char data_nascimento[40];
    struct paciente *proximo_paciente;
}pacientes;

pacientes todos_pacientes[100];

int menu_pacientes();
void exibe_informacoes_paciente(pacientes todos_pacientes, int espaco_livre);
int valida_tipo_sanguineo(char tipo_sanguineo[]);
int valida_fato_rh(char fator_rh[]);
int valida_documento(char documento[]);
int cadastra_documento(char tipo_documento[], char str_documento[]);
int cadastro_informacao_nao_obrigatorio(char documento[]);
int procura_informacao(pacientes todos_pacientes[], int espaco_livre, int tamanho, int controle);
int cadastra_nome_paciente(pacientes *novo_paciente);
void exibe_tipo_sanguineo_pacientes(char tipo_sanguineo[], char matriz_tipo_sanguineo[][3], char matriz_fator_RH[][9], int tam_matriz_tp_sanguineo,char matriz_pacientes[][40]);
void busca_tipo_sanguineo(int tam_matriz_tp_sanguineo, char tipo_sanguineo[], char matriz_tipo_sanguineo[][3], char matriz_fator_RH[][9], char fator_rh_escolhido[] ,char matriz_pacientes[][40]);
void exibir_todos_pacientes(char matriz_pacientes[][40], int vetor_ativos[], int tamanho_matriz);
int cria_tamanho_limitando_ativos(int vetor_pacientes_ativos[], int tamanho_pacientes_ativos);
void completa_vetor_limitando_ativos(int vetor_pacientes_ativos[], int TAM_VETOR, char matriz_nomes_pacientes[][40], int tamanho_nomes_pacientes, int vetor_limitando_ativos[]);
void ordena_pacientes_ordem_alfabetica(char nomes_pacientes[][40], int tamanho_nomes_pacientes, int vetor_limitando_ativos[]);
void exibe_pacientes_ordem_alfabetica(char nomes_pacientes[][40], int vetor_limitando_ativos[], int tamanho_vetor_limitando_ativos);
int verifica_pacientes_ativos(int vetor_pacientes_ativos[], int tam_vetor_pacientes_ativos);
int verifica_cadastro_paciente(char matriz_nomes_paciente[][40], int tam_matriz_nomes_paciente, char nome_paciente_verificado[]);


#endif