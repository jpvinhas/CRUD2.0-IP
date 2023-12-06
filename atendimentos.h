#ifndef ATENDIMENTOS_H
#define ATENDIMENTOS_H

#include "pacientes.h"

typedef struct
{   char paciente_do_atendimento[40];
    char codigo_atendimento[8];
    char tipo_atendimento[40];  
    char data_atendimento[40];
    char status_atendimento[40];  
    float preco_atendimento;
    int ativo;
}atendimento;

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CIANO   "\x1b[36m"
#define RESET   "\x1b[0m"


int menu_atendimento();
void exibir_dados_atendimento(char codigo[][8],char paciente[][40],char codigo_paciente[][8],int indice_paciente,char data[][40],char tipo[][40],float preco[],char status[][40],int indice_atendimento);
void receber_status_atendimento(char vetor_status_atendimentos[][40],int indice_do_atendimento);
int procura_paciente(char nomes_pacientes[][40],int tamanho);
int procura_paciente_codigo(char codigo_pacientes[][8],int QNTD_PACIENTES,int pacientes_ativos[]);
int procura_atendimento(char codigo_atendimentos[][8],int QNTD_ATENDIMENTOS,int atendimentos_ativos[]);
int atendimento_ja_cadastrado(char data_atendimentos[][40],int paciente_do_atendimento[],int atendimento_atual,int tamanho);
void receber_tipo_atendimento(char tipo_atendimentos[][40],int espaco_livre);
float receber_preco();
int compara_data(char data1[],char data2[]);
void ordenar_datas(char datas[][40],int ordem_datas[],int tamanho,int atendimentos_ativos[]);
void adicionar_atendimentos(const char* nomeArquivo, atendimento* novosatendimentos,int qnd_novos_atendimentos,size_t tam_struct);
void salvar(paciente* pacientes,atendimento* atendimentos, int* alteracoes_pacientes, int* alteracoes_atendimentos, int qnd_pacientes,int qnd_atendimentos);
void salvar_novos(paciente* pacientes,atendimento* atendimentos,paciente* novos_pacientes,atendimento*novos_atendimentos,int qnt_novos_pacientes, int qnt_novos_atendimentos, int qnt_pacientes,int qnt_atendimentos);
#endif