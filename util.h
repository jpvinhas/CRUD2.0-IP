#ifndef UTIL_H
#define UTIL_H

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "atendimentos.h"
#include "pacientes.h"

int menu_principal();
int coletar_opcao(char opcao1[],char opcao2[]);
int preenche_vetor_ativos(int vetor_ativos[], int tamanho_vetor);
int preenche_matriz_bidimensional(char vetor_ativos[][40], int tamanho_vetor);
void ler_str(char string[]);
int checar_string(char string[]);
void formata_string_maisculo(char string[]);
int ja_existe(char* string,paciente*pacientes,int tamanho);
int procura_string(char string[],char vetor[][40],int tamanho);
int procura_codigo(char codigo_unico_paciente[],char matriz_codigos_pacientes[][8],int tamanho_matriz);
void* procura_paciente_livre(paciente* vetordestructs, int tamanho_vetor);
int procura_espaco_livre(int vetor_ativos[], int tamanho_vetor);
void receber_data(char vetor[][40],int indice_livre);

void imprimir_vetor(char vetor[][40],int tamanho);
void cria_codigo(char vetor[][8],int indice_livre);
void cria_codigo2(char* codigo);
float soma_consultas_pagas_pacientes(char nome_paciente_desejado[], char matriz_nomes_paciente[][40], float vetor_preco_atendimentos[], int tamanho_vetores, int vetor_paciente_atendimento_indice[]);
void copia_matriz(char matriz1[][40], char matriz2[][40], int tamanho);
int varrer_datas(char data[][40], char matriz_datas_atendimentos_copia[][40], int tam_matriz_datas_atendimentos);
FILE* abrir_arquivo(const char nome[], const char modo[]);
void* ler(const char* nomeArquivo, size_t* numero_structs,size_t tamanho_struct);
void adicionar(const char* nomeArquivo, void* novo_add,int qnd_novos);
void alterar(const char* nomeArquivo, size_t indice, void* novainformacao, size_t tamanho_struct);
void* salvar(void*pacientes,void*atendimentos, int* alteracoes_pacientes, int* alteracoes_atendimentos, size_t qnd_pacientes,size_t qnd_atendimentos);
void* salvar_novos(void*novos_pacientes,void*novos_atendimentos,int* qnt_novos_pacientes, int* qnt_novos_atendimentos);
#endif