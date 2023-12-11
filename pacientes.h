#ifndef PACIENTES_H
#define PACIENTES_H

typedef struct {
    char nome[40];
    char codigo[9]; 
    char RG[20]; 
    char CPF[12];
    char tipo_sanquineo[20];
    char fator_RH[20];  
    char endereco[40];
    char data_nascimento[40];
    int ativo;
}paciente;
#include "util.h"

int menu_pacientes();
void exibe_informacoes_paciente2(paciente *infopaciente);
int valida_tipo_sanguineo(char tipo_sanguineo[]);
int valida_fato_rh(char fator_rh[]);
int valida_documento(char* documento);
int cadastra_documento2(char* tipo_documento, char* str_documento);
int cadastro_informacao_nao_obrigatorio(char* str_documento);
int procura_informacao2(char* informacao_paciente, paciente*pacientes, int tamanho_matriz,int opcao,int index);
int cadastra_nome_paciente2(char* novopaciente,paciente*pacientes, int qnt_pacientes);
void exibe_tipo_sanguineo_pacientes(char * tipo_sanguineo,int tam,paciente*pacientes);
void exibir_todos_pacientes2(paciente*pacientes, int tamanho) ;
int procura_paciente_livre(paciente* vetordestructs, int tamanho_vetor);
int ja_existe(char* string,paciente*pacientes,int tamanho);
void adicionar_pacientes(const char* nomeArquivo, paciente* novospaciente,int qnd_novos_pacientes,size_t tam_struct);
int procura_codigo_paciente2(char*codigo,paciente*pacientes,int tamanho);    
int compara_nome(const char* nome1, const char* nome2);
void ordenar_pacientes(paciente*pacientes,int* ordem_pacientes,int tamanho);
void cadastrar_tipo_sanguineo(char * paciente_tiposanguineo);
void cadastrar_fator_rh(char * paciente_fator_rh);
#endif