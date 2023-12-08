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


int menu_principal();
int coletar_opcao(char opcao1[],char opcao2[]);
int preenche_vetor_ativos(int vetor_ativos[], int tamanho_vetor);
void ler_str(char* string);
int checar_string(char string[]);
void formata_string_maisculo(char string[]);
int procura_string(char string[],char vetor[][40],int tamanho);
int procura_codigo(char codigo_unico_paciente[],char matriz_codigos_pacientes[][8],int tamanho_matriz);
int procura_espaco_livre(int vetor_ativos[], int tamanho_vetor);
int procura_codigo_atendimento(char codigo_atendimento_comparado[], int qntd_atendimentos, char atendimento_solicitado[]);
void receber_data(char vetor[][40],int indice_livre);
void receber_data2(char* data);

void imprimir_vetor(char vetor[][40],int tamanho);
void cria_codigo(char vetor[][8],int indice_livre);
void cria_codigo2(char* codigo);
void copia_matriz(char matriz1[][40], char matriz2[][40], int tamanho);
int varrer_datas(char data[][40], char matriz_datas_atendimentos_copia[][40], int tam_matriz_datas_atendimentos);
FILE* abrir_arquivo(const char nome[], const char modo[]);
void* ler(const char* nomeArquivo, size_t* numero_structs,size_t tamanho_struct);
void adicionar(const char* nomeArquivo, void* novospaciente,int qnd_novos_pacientes,size_t tam);
void alterar(const char* nomeArquivo, int indice, void* novainformacao, size_t tamanho_struct);
#endif