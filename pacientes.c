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
    printf("\n"BLUE"[8]"RESET" Exibir Todos os Pacientes em Ordem Alfabética\n"BLUE"[9]"RESET" Exibir a Soma das Consultas Pagas por um Determinado Paciente");
    printf(BLUE"\n[10]"RESET" Voltar para o Menu Principal");
    printf(BLUE"\n[11]"RESET" Salvar");

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

        return interacao_menu_pacientes;
    }
}

void exibe_informacoes_paciente2(paciente *infopaciente){
    printf("\n-----------"GREEN"Paciente"RESET"-----------\n");
    printf("-> "BLUE"Nome:"RESET" "GREEN"%s\n"RESET, infopaciente->nome);
    printf("-> "BLUE"Código do Paciente:"RESET" "GREEN"%s\n"RESET, infopaciente->codigo);
    printf("-> "BLUE"RG do Paciente:"RESET" "GREEN"%s\n"RESET, infopaciente->RG);
    printf("-> "BLUE"CPF do Paciente:"RESET" "GREEN"%s\n"RESET, infopaciente->CPF);
    printf("-> "BLUE"Tipo Sanguíneo do Paciente:"RESET" "GREEN"%s\n"RESET, infopaciente->tipo_sanquineo);
    printf("-> "BLUE"Fator RH  do Paciente:"RESET" "GREEN"%s\n"RESET, infopaciente->fator_RH);
    printf("-> "BLUE"Endereço do Paciente:"RESET" "GREEN"%s\n"RESET, infopaciente->endereco);
    printf("-> "BLUE"Data de Nascimento do Paciente:"RESET GREEN"%s\n"RESET, infopaciente->data_nascimento);
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

int valida_documento(char* documento) {
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

int procura_informacao2(char* informacao_paciente, paciente*pacientes, int tamanho_matriz,int opcao,int index) {  
    switch(opcao){
        case 1:
            for(int i = 0; i < tamanho_matriz; i++){
                if(!(strcmp(informacao_paciente, pacientes[i].nome))) return i;
            }
            break;
        case 2:
            for(int i = 0; i < tamanho_matriz; i++){
                if(!(strcmp(informacao_paciente, pacientes[i].codigo))) return i;
            }
            break;
        case 3:
            for(int i = 0; i < tamanho_matriz; i++){
                if(i == index) continue;
                if(strcmp(informacao_paciente, "Não Informado") == 0) break;
                if(!(strcmp(informacao_paciente, pacientes[i].RG))) return 1;
            }
            break;
        case 4:
            for(int i = 0; i < tamanho_matriz; i++){
                if(i == index) continue;
                if(pacientes[i].ativo == 0)continue;
                if(!(strcmp(informacao_paciente, pacientes[i].CPF))) return 1;
            }
            break;
        default:
            printf("erro");
            break;
    }
    if(index == -2)return -1;

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
        if(strcmp(novopaciente,"sair")==0)return 1;

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


void exibe_tipo_sanguineo_pacientes(char * tipo_sanguineo,int tam,paciente*pacientes){
    printf("Tipo Selecionado %s:\n", tipo_sanguineo);

    printf(BLUE"\n--------------------------Grupo %s-----------------------\n"RESET, tipo_sanguineo);
    int contador = 0;

    for(int i = 0; i < tam; i++) {
        if(pacientes[i].ativo == 0)continue;
        if(!strcmp(tipo_sanguineo, pacientes[i].tipo_sanquineo)) {
            printf("-> Paciente: %s\n", pacientes[i].nome);
            contador++;
        }
    }

    if(!contador) {
        printf("Sem Pacientes!\n");
    }
    printf(BLUE"\n---------------------------------------------------------\n"RESET);
}

void exibir_todos_pacientes2(paciente*pacientes, int tamanho) {
    int count = 0;

    printf(BLUE"----Pacientes cadastrados na Clinica Fátima----\n"RESET);
    for(int i = 0; i < tamanho; i++) {
        if(pacientes[i].ativo) {
            printf("-> "GREEN"Paciente (%03d): %s"RESET"\n", i , pacientes[i].nome);
            exibe_informacoes_paciente2(&pacientes[i]);
            count++;;
        }
    }
    if(!count){printf(RED"Sem Pacientes Cadastrados!\n"RESET);}

    printf(BLUE"-----------------------------------------------\n\n"RESET);
}

int procura_paciente_livre(paciente* vetordestructs, int tamanho_vetor) {
    for (int i = 0; i < tamanho_vetor; i++) {
        if(vetordestructs[i].ativo == 0) {
            return i;
        }
    }
    return -1;
}
int ja_existe(char* string,paciente*pacientes,int tamanho){
    for(int i = 0; i < tamanho; i++){
        if(pacientes[i].ativo == 0)continue;
        if(strcmp(string,pacientes[i].nome) == 0){
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
int procura_codigo_paciente2(char*codigo,paciente*pacientes,int tamanho) {
    for(int i = 0; i < tamanho; i++){
        if(pacientes[i].ativo == 0)continue;
        if(strcmp(codigo,pacientes[i].codigo) == 0) {
            return i;
        }

    }
    return -1;
}
int compara_nome(const char* nome1, const char* nome2) {
    int resultado = strcmp(nome1, nome2);
    if (resultado > 0)return 1;
    return 0;
}
void ordenar_pacientes(paciente*pacientes,int* ordem_pacientes,int tamanho){
    for (int i = 0; i < tamanho; i++) {
        ordem_pacientes[i] = i;
    }
    for (int i = 0; i < tamanho - 1; i++) {
        if(pacientes[i].ativo == 0) continue;
        for (int j = i + 1; j < tamanho; j++) {
            if(pacientes[j].ativo == 0) continue;
            if (compara_nome(pacientes[ordem_pacientes[i]].nome, pacientes[ordem_pacientes[j]].nome)) {
                int aux = ordem_pacientes[i];
                ordem_pacientes[i] = ordem_pacientes[j];
                ordem_pacientes[j] = aux;
            }
        }
    }
}
void cadastrar_tipo_sanguineo(char * paciente_tiposanguineo){
    int informacao_nao_obrigatoria = 0;
    int formatacao_incorreta = 0;
    while (1) {
        printf("Selecione o seu Tipo Sanguíneo (Sem o Fator RH) ou ENTER para pular:\n");
        printf(BLUE"[1] A     [2] B     [3] AB     [4] O\n"RESET);  
        ler_str(paciente_tiposanguineo);

        informacao_nao_obrigatoria = cadastro_informacao_nao_obrigatorio(paciente_tiposanguineo);
        if(informacao_nao_obrigatoria) {break;}
        
        formatacao_incorreta = valida_tipo_sanguineo(paciente_tiposanguineo);
        if(formatacao_incorreta) {
            printf(RED"Tipo Sanguíneo Inválido, Digite Novamente!\n"RESET);
            continue;
        }
        break;
    }
}
void cadastrar_fator_rh(char * paciente_fator_rh){
    int informacao_nao_obrigatoria = 0;
    int formatacao_incorreta = 0;
    while(1) {
        printf("Selecione o Fator RH do Paciente (Positivo ou Negativo) ou ENTER para pular:\n");
        printf(BLUE"[1] Positivo     [2] Negativo\n"RESET);
        ler_str(paciente_fator_rh);

        informacao_nao_obrigatoria = cadastro_informacao_nao_obrigatorio(paciente_fator_rh);
        if(informacao_nao_obrigatoria) {break;}
            
        formatacao_incorreta = valida_fato_rh(paciente_fator_rh);
        if(formatacao_incorreta) {
            printf(RED"Fator RH Inválido, Digite Novamente!\n"RESET);
            continue;
        }
        break;
    }
}