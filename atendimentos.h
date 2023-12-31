#ifndef ATENDIMENTOS_H
#define ATENDIMENTOS_H

#include "pacientes.h"

typedef struct
{   char codigo_paciente[9];
    char codigo_atendimento[9];
    char tipo[40];  
    char data[40];
    char status[40];  
    float preco;
    int ativo;
}atendimento;

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"


int menu_atendimento();
void exibir_dados_atendimento(atendimento *novo_atendimento);
void receber_status_atendimento(atendimento *novo_atendimento);
int procura_paciente(paciente *todos_pacientes, int qntd_pacientes, char codigo_paciente[]);
int atendimento_ja_cadastrado(atendimento *todos_atendimentos, char paciente_codigo[], char data_analisada[], size_t qnt_atendimentos);
void receber_tipo_atendimento(atendimento *novo_atendimento);
float receber_preco();
int compara_data(char data1[],char data2[]);
void ordenar_datas(atendimento *todos_atendimentos,int ordem_datas[],size_t qnt_atendimentos);
void adicionar_atendimentos(const char* nomeArquivo, atendimento* novosatendimentos,int qnd_novos_atendimentos,size_t tam_struct);
void salvar(paciente* pacientes,atendimento* atendimentos, int* alteracoes_pacientes, int* alteracoes_atendimentos, size_t qnd_pacientes,size_t qnd_atendimentos);
void salvar_novos(paciente* pacientes,atendimento* atendimentos,paciente* novos_pacientes,atendimento*novos_atendimentos,int qnt_novos_pacientes, int qnt_novos_atendimentos, int qnt_pacientes,int qnt_atendimentos);
float soma_consultas_pagas_pacientes(char *nome,atendimento *atendimentos,int qnt_atendimentos);
int procura_atendimento_livre(atendimento* atendimentos_arquivados, int tamanho_vetor);
int procura_atendimento2(atendimento *todos_atendimentos, size_t qnt_atendimentos);
int verifica_codigo_atendimento(atendimento *todos_atendimentos, char input_codigo[], int qnt_atendimentos);
float intervalo_entre_datas(char data1[], char data2[], atendimento *todos_atendimentos, size_t qntd_atendimentos);
int datas_diferentes(char data1[],char data2[]);

#endif