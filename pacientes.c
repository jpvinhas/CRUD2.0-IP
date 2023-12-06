#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "pacientes.h"



int menu_pacientes() {
    printf("\n-----------------------------"BLUE"MENU PACIENTES"RESET"-----------------------------\n");
    printf(YELLOW"Selecione a funcionalidade que desejar: \n"RESET);
    printf("\n"BLUE"[1]"RESET" Inserir um Novo Paciente\n"BLUE"[2]"RESET" Alterar um Paciente Existente");
    printf("\n"BLUE"[3]"RESET" Excluir um Paciente\n"BLUE"[4]"RESET" Exibir os Dados de um Paciente pelo seu Código");
    printf("\n"BLUE"[5]"RESET" Exibir os Dados de Pacientes que Apresentam o Mesmo Tipo Sanguíneo");
    printf("\n"BLUE"[6]"RESET" Exibir os Dados de Pacientes pelo Dia de Consulta\n"BLUE"[7]"RESET" Exibir Todos os Pacientes");
    printf("\n"BLUE"[8]"RESET"Exibir Todos os Pacientes em Ordem Alfabética\n"BLUE"[9]"RESET"Exibir a Soma das Consultas Pagas por um Determinado Paciente");
    printf(BLUE"\n[10]"RESET"Voltar para o Menu Principal");
    printf(BLUE"\n[11]"RESET"Salvar");

    printf("\n------------------------------------------------------------------------\n");

    while(1) {
        printf(YELLOW"\n\nSelecione a Funcionalidade Desejada: \n"RESET);
        fflush(stdin);
        int interacao_menu_pacientes;
        
        fflush(stdin);
        scanf("%d", &interacao_menu_pacientes);

        if(interacao_menu_pacientes < 1 || interacao_menu_pacientes > 11){
            printf(RED"Selecione uma das Opções Anteriores!\n"RESET);
            continue;
        }

        system("clear");

        return interacao_menu_pacientes;
    }
}


void exibe_informacoes_paciente(char nomes_pacientes[][40], char codigo_pacientes[][8], char RG_pacientes[][12], char CPF_pacientes[][12], char tipo_sanguineo_pacientes[][3], char fator_RH_pacientes[][9], char endereco_pacientes[][40], char datas_nascimento_pacientes[][40], int espaco_livre) {
    printf("\n-----------"GREEN"Paciente"RESET"-----------\n");
    printf("-> "BLUE"Nome:"RESET" "GREEN"%s\n"RESET, nomes_pacientes[espaco_livre]);
    printf("-> "BLUE"Código do Paciente:"RESET" "GREEN"%s\n"RESET, codigo_pacientes[espaco_livre]);
    printf("-> "BLUE"RG do Paciente:"RESET" "GREEN"%s\n"RESET, RG_pacientes[espaco_livre]);
    printf("-> "BLUE"CPF do Paciente:"RESET" "GREEN"%s\n"RESET, CPF_pacientes[espaco_livre]);
    printf("-> "BLUE"Tipo Sanguíneo do Paciente:"RESET" "GREEN"%s\n"RESET, tipo_sanguineo_pacientes[espaco_livre]);
    printf("-> "BLUE"Fator RH  do Paciente:"RESET" "GREEN"%s\n"RESET, fator_RH_pacientes[espaco_livre]);
    printf("-> "BLUE"Endereço do Paciente:"RESET" "GREEN"%s\n"RESET, endereco_pacientes[espaco_livre]);
    printf("-> "BLUE"Data de Nascimento do Paciente:"RESET GREEN"%s\n"RESET, datas_nascimento_pacientes[espaco_livre]);
    printf("--------------------------------------------\n");

}
void exibe_informacoes_paciente2(paciente *infopaciente){
    printf("\n-----------"GREEN"Paciente"RESET"-----------\n");
    printf("-> "BLUE"Nome:"RESET" "GREEN"%s\n"RESET, infopaciente->nome_paciente);
    printf("-> "BLUE"Código do Paciente:"RESET" "GREEN"%s\n"RESET, infopaciente->codigo_paciente);
    printf("-> "BLUE"RG do Paciente:"RESET" "GREEN"%s\n"RESET, infopaciente->RG_paciente);
    printf("-> "BLUE"CPF do Paciente:"RESET" "GREEN"%s\n"RESET, infopaciente->CPF_paciente);
    printf("-> "BLUE"Tipo Sanguíneo do Paciente:"RESET" "GREEN"%s\n"RESET, infopaciente->tipo_sanguineo_paciente);
    printf("-> "BLUE"Fator RH  do Paciente:"RESET" "GREEN"%s\n"RESET, infopaciente->fator_RH_paciente);
    printf("-> "BLUE"Endereço do Paciente:"RESET" "GREEN"%s\n"RESET, infopaciente->endereco_paciente);
    printf("-> "BLUE"Data de Nascimento do Paciente:"RESET GREEN"%s\n"RESET, infopaciente->data_nascimento_paciente);
    printf("--------------------------------------------\n");

}

int valida_tipo_sanguineo(char tipo_sanguineo[]) {
    int tipo_sanguineo_convertido = atoi(tipo_sanguineo);

    if(tipo_sanguineo_convertido < 1 || tipo_sanguineo_convertido > 4) {
        return 1;
    }
    else {
        switch (tipo_sanguineo_convertido) {
            case 1:
                strcpy(tipo_sanguineo, "A");
                break;
            
            case 2:
                strcpy(tipo_sanguineo, "B");
                break;

            case 3: 
                strcpy(tipo_sanguineo, "AB");
                break;
            default:
                strcpy(tipo_sanguineo, "O");
                break;
        }

        return 0;
    }
}


int valida_fato_rh(char fator_rh[]) {
    int fator_rh_convertido = atoi(fator_rh);

    if(fator_rh_convertido < 1 || fator_rh_convertido > 2) {
        return 1;
    }
    else {
        switch (fator_rh_convertido) {
            case 1:
                strcpy(fator_rh, "Positivo");
                break;
            default:
                strcpy(fator_rh, "Negativo");
        }

        return 0;
    }

}

int valida_documento(char documento[]) {
    int tamanho_documento = strlen(documento);

    if(tamanho_documento < 11 || tamanho_documento > 11) {
        return 1;
    }

    int eh_alfanumerico;
    for(int i  = 0; i < tamanho_documento; i++) {
        eh_alfanumerico = isdigit(documento[i]);
        if(!(eh_alfanumerico)) {
            return 1;
        }
        
    }

    return 0;
}
int cadastra_documento(char tipo_documento[], char str_documento[], int espaco_livre) {
    while(1) {
        printf("Digite o %s do Paciente", tipo_documento);

        int documento_nao_obrigatorio = !(strcmp(tipo_documento, "RG"));
        if(documento_nao_obrigatorio) {
            printf(" ou ENTER para Não Informar:\n");
        }
        else {
            printf(":\n");
        }

        ler_str(str_documento);

        int enter_pressionado = cadastro_informacao_nao_obrigatorio(str_documento);
        if(documento_nao_obrigatorio && enter_pressionado) {
            return 1;
        }
    
        int documento_invalido = valida_documento(str_documento);
        if(documento_invalido) {
            printf(RED"%s Inválido!\n"RESET, tipo_documento);
            continue;
        }

        break;
    }
    
    return 0;
}

int cadastra_documento2(char* tipo_documento, char* str_documento) {
    while(1) {
        printf("Digite o %s do Paciente", tipo_documento);

        int documento_nao_obrigatorio = !(strcmp(tipo_documento, "RG"));
        if(documento_nao_obrigatorio) {
            printf(" ou ENTER para Não Informar:\n");
        }
        else {
            printf(":\n");
        }

        ler_str(str_documento);

        int enter_pressionado = cadastro_informacao_nao_obrigatorio(str_documento);
        if(documento_nao_obrigatorio && enter_pressionado) {
            return 1;
        }
    
        int documento_invalido = valida_documento(str_documento);
        if(documento_invalido) {
            printf(RED"%s Inválido!\n"RESET, tipo_documento);
            continue;
        }

        break;
    }
    
    return 0;
}


int cadastro_informacao_nao_obrigatorio(char* str_documento) {
    int documento_nao_obrigatorio_vazio = str_documento[0] == '\0';
    if(documento_nao_obrigatorio_vazio) {
        strcpy(str_documento, "Não Informado");
        return 1;
    }
    return 0;
}

int procura_informacao(char informacao_paciente[], char matriz_informacao_paciente[][12], int tamanho_matriz, int indice_matriz) {  
        for(int i = 0; i < tamanho_matriz; i++){
            if(i == indice_matriz)
                continue;
            if(!(strcmp(informacao_paciente, matriz_informacao_paciente[i]))){
                return 1;
            }
    }
    
    return 0;
}
int procura_informacao2(char* informacao_paciente, paciente*pacientes, int tamanho_matriz) {  
    
    for(int i = 0; i < tamanho_matriz; i++){
        if(!(strcmp(informacao_paciente, pacientes[i].nome_paciente))) return 1;
    }
    return 0;
}
int cadastra_nome_paciente(char* novopaciente,paciente*pacientes, int qnt_pacientes) {
    while(1) {
        printf("Digite o Nome do Paciente:\n");
        ler_str(novopaciente);
        
        int nome_incorreto = checar_string(novopaciente);
        if(nome_incorreto) {
            printf(RED"Digite o nome corretamente!\n"RESET);
            continue;
        }

        formata_string_maisculo(novopaciente);
        
        int ja_cadastrado = ja_existe(novopaciente, pacientes,qnt_pacientes);
        if(ja_cadastrado) { 
            printf(RED"Paciente já cadastrado!\n"RESET);
            return 1;
        }

        break;
    }

    return 0;
}
int cadastra_nome_paciente2(char* novopaciente,paciente*pacientes, int qnt_pacientes) {
    while(1) {
        printf("Digite o Nome do Paciente:\n");
        ler_str(novopaciente);
        
        int nome_incorreto = checar_string(novopaciente);
        if(nome_incorreto) {
            printf(RED"Digite o nome corretamente!\n"RESET);
            continue;
        }

        formata_string_maisculo(novopaciente);
        
        int ja_cadastrado = ja_existe(novopaciente, pacientes,qnt_pacientes);
        if(ja_cadastrado) { 
            printf(RED"Paciente já cadastrado!\n"RESET);
            return 1;
        }

        break;
    }

    return 0;
}


void exibe_tipo_sanguineo_pacientes(char tipo_sanguineo[], char matriz_tipo_sanguineo[][3], char matriz_fator_RH[][9], int tam_matriz_tp_sanguineo,char matriz_pacientes[][40]) {

    printf("Tipo Selecionado %s:\n", tipo_sanguineo);

    printf(BLUE"\n--------------------------Grupo %s-----------------------\n"RESET, tipo_sanguineo);
    printf(YELLOW"---> %s Positivo\n"RESET, tipo_sanguineo);
    busca_tipo_sanguineo(tam_matriz_tp_sanguineo, tipo_sanguineo, matriz_tipo_sanguineo, matriz_fator_RH, "Positivo", matriz_pacientes);
    printf(BLUE"\n---------------------------------------------------------"RESET);
    printf(YELLOW"\n---> %s Negativo\n"RESET, tipo_sanguineo);
    busca_tipo_sanguineo(tam_matriz_tp_sanguineo, tipo_sanguineo, matriz_tipo_sanguineo, matriz_fator_RH, "Negativo", matriz_pacientes);
    printf(BLUE"\n---------------------------------------------------------\n"RESET);
}


void busca_tipo_sanguineo(int tam_matriz_tp_sanguineo, char tipo_sanguineo[], char matriz_tipo_sanguineo[][3], char matriz_fator_RH[][9], char fator_rh_escolhido[] ,char matriz_pacientes[][40]) {
        int contador = 0;

        for(int i = 0; i < tam_matriz_tp_sanguineo; i++) {
            if(!(strcmp(tipo_sanguineo, matriz_tipo_sanguineo[i])) && !strcmp(fator_rh_escolhido, matriz_fator_RH[i])) {
                printf("-> Paciente: %s\n", matriz_pacientes[i]);
                contador++;
            }
        }

        if(!contador) {
            printf("Sem Pacientes!\n");
        }
}


void exibir_todos_pacientes(char matriz_pacientes[][40], int vetor_ativos[], int tamanho_matriz) {
    int count = 0;

    printf(BLUE"----Pacientes cadastrados na Clinica Fátima----\n"RESET);
    for(int i = 0; i < tamanho_matriz; i++) {
        if(vetor_ativos[i]) {
            printf("-> "GREEN"Paciente (%03d): %s"RESET"\n", i , matriz_pacientes[i]);
            count++;;
        }
    }
    if(!count){printf(RED"Sem Pacientes Cadastrados!\n"RESET);}

    printf(BLUE"-----------------------------------------------\n\n"RESET);
}
void exibir_todos_pacientes2(paciente*pacientes, int tamanho) {
    int count = 0;

    printf(BLUE"----Pacientes cadastrados na Clinica Fátima----\n"RESET);
    for(int i = 0; i < tamanho; i++) {
        if(pacientes[i].ativo) {
            printf("-> "GREEN"Paciente (%03d): %s"RESET"\n", i , pacientes[i].nome_paciente);
            exibe_informacoes_paciente2(&pacientes[i]);
            count++;;
        }
    }
    if(!count){printf(RED"Sem Pacientes Cadastrados!\n"RESET);}

    printf(BLUE"-----------------------------------------------\n\n"RESET);
}


int cria_tamanho_limitando_ativos(int vetor_pacientes_ativos[], int tamanho_pacientes_ativos) {
    int TAM_VETOR = 0;

    for(int i = 0; i < tamanho_pacientes_ativos; i++) {
        if(vetor_pacientes_ativos[i]) {
            TAM_VETOR++;
        }
    }

    return TAM_VETOR;
}


void completa_vetor_limitando_ativos(int vetor_pacientes_ativos[], int TAM_VETOR, char matriz_nomes_pacientes[][40], int tamanho_nomes_pacientes, int vetor_limitando_ativos[]) {
    for(int i = 0; i < tamanho_nomes_pacientes; i++) {
         if(vetor_pacientes_ativos[i] == 1) {    
            vetor_limitando_ativos[i] = i;
         }
    }
 } 

void ordena_pacientes_ordem_alfabetica(char nomes_pacientes[][40], int tamanho_nomes_pacientes, int vetor_limitando_ativos[]) {
    int compara_strings;

    for(int i = 0; i < tamanho_nomes_pacientes - 1; i++) {
        int menor = i;
        int aux = 0;
        
        for(int j = i + 1; j < tamanho_nomes_pacientes; j++) {
            compara_strings = strcmp(nomes_pacientes[menor], nomes_pacientes[j]);

            if(compara_strings > 0) {
                menor = j;
            }
        }

        if(menor != i) {
            aux = vetor_limitando_ativos[menor];
            vetor_limitando_ativos[menor] = vetor_limitando_ativos[i];
            vetor_limitando_ativos[i] = aux;
        }
    }
}


 void exibe_pacientes_ordem_alfabetica(char nomes_pacientes[][40], int vetor_limitando_ativos[], int tamanho_vetor_limitando_ativos) {
    int indice_ordenado;
    
    printf(BLUE"---------Pacientes em Ordem Alfabética----------\n"RESET);

    for(int i = 0; i < tamanho_vetor_limitando_ativos; i++) {
        indice_ordenado = vetor_limitando_ativos[i];
        printf(GREEN"-> %s\n"RESET, nomes_pacientes[indice_ordenado]);
    }

    printf(BLUE"------------------------------------------------\n"RESET);
} 

int verifica_pacientes_ativos(int vetor_pacientes_ativos[], int tam_vetor_pacientes_ativos) {
    for(int i = 0; i < tam_vetor_pacientes_ativos; i++) {
        if(vetor_pacientes_ativos[i]) {
            return 0;
        }
    }
    return 1;
}


int verifica_cadastro_paciente(char matriz_nomes_paciente[][40], int tam_matriz_nomes_paciente, char nome_paciente_verificado[]) {
    for(int i = 0; i < tam_matriz_nomes_paciente; i++) {
        formata_string_maisculo(nome_paciente_verificado);
        formata_string_maisculo(matriz_nomes_paciente[i]);

        int compara_nomes = !strcmp(nome_paciente_verificado, matriz_nomes_paciente[i]);

        if(compara_nomes) {
            return 1;
        }
    }
    return 0;
}
void* procura_paciente_livre(paciente* vetordestructs, int tamanho_vetor) {
    for (int i = 0; i < tamanho_vetor; i++) {

        if(vetordestructs[i].ativo) {
            return &vetordestructs[i];
        }
    }
    return NULL;
}
int ja_existe(char* string,paciente*pacientes,int tamanho){
    for(int i = 0; i < tamanho; i++){
        if(strcmp(string,pacientes[i].nome_paciente) == 0){
            return 1;
        }
    }return 0;
}
void adicionar_pacientes(const char* nomeArquivo, paciente* novospaciente,int qnd_novos_pacientes,size_t tam_struct) {
    FILE* arquivo = fopen(nomeArquivo, "ab+");  // Abre o arquivo em modo de leitura e escrita no final
    printf("4");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Escreve os novos structs no final do arquivo
    fseek(arquivo, 0, SEEK_END);  // Move o ponteiro para o final do arquivo
    fwrite(novospaciente, tam_struct, qnd_novos_pacientes, arquivo);
    
    fclose(arquivo);
}