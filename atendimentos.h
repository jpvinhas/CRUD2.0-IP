#ifndef ATENDIMENTOS_H
#define ATENDIMENTOS_H

#include "pacientes.h"
#include "util.h"

typedef struct
{   char codigo_paciente[8]; // da para colocar um ponteiro que aponte para esse codigo
    char codigo_atendimento[8];
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
void exibir_dados_atendimento(char codigo[][8],char paciente[][40],char codigo_paciente[][8],int indice_paciente,char data[][40],char tipo[][40],float preco[],char status[][40],int indice_atendimento);
void receber_status_atendimento(atendimento *novo_atendimento);
int procura_paciente(paciente *todos_pacientes, int qntd_pacientes, char codigo_paciente[]);
int procura_paciente_codigo(char codigo_pacientes[][8],int QNTD_PACIENTES,int pacientes_ativos[]);
int procura_atendimento(char codigo_atendimentos[][8],int QNTD_ATENDIMENTOS,int atendimentos_ativos[]);
int atendimento_ja_cadastrado(char data_atendimentos[][40],int paciente_do_atendimento[],int atendimento_atual,int tamanho);
void receber_tipo_atendimento(atendimento *novo_atendimento);
float receber_preco();
int compara_data(char data1[],char data2[]);
void ordenar_datas(char datas[][40],int ordem_datas[],int tamanho,int atendimentos_ativos[]);

#endif