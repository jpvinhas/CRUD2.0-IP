/*
 * 1) Ordem Alfabetica Pacientes Errada
 * 2) Codigo Nao aleatorio, verificar ou altera-lo
 * 3) Verificar se um paciente ja nao tem atendimento na data para salvar
 * 4) administrar se o vetorde novos pacientes e atendimentos ja esta cheio*/

#include <stdio.h>
#include <string.h>

#include "pacientes.h"
#include "atendimentos.h"
#include "util.h"

#define QNTD_PACIENTES 100
#define QNTD_ATENDIMENTOS 100

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

paciente* pacientes;
atendimento* atendimentos;

paciente novospacientes[10];
atendimento novos_atendimentos[10];

size_t qnt_pacientes = 0;
size_t qnt_atendimentos = 0;
int qnt_novos_pacientes = 0;
int qnt_novos_atendimentos = 2;
int qnt_pacientes_alterados = 2;
int qnt_atendimentos_alterados = 0;
int *pacientes_alterados;
int *atendimentos_alterados;


int pacientes_ativos[QNTD_PACIENTES];

char codigo_pacientes[QNTD_PACIENTES][8];  
char nomes_pacientes[QNTD_PACIENTES][40];
char RG_pacientes[QNTD_PACIENTES][12]; 
char CPF_pacientes[QNTD_PACIENTES][12];
char tipo_sanguineo_pacientes[QNTD_PACIENTES][3];
char fator_RH_pacientes[QNTD_PACIENTES][9];  
char endereco_pacientes[QNTD_PACIENTES][40];
char datas_nascimento_pacientes[QNTD_PACIENTES][40];


int atendimentos_ativos[QNTD_ATENDIMENTOS];

int paciente_do_atendimento[QNTD_ATENDIMENTOS];
char codigo_atendimentos[QNTD_ATENDIMENTOS][8];
char tipo_atendimentos[QNTD_ATENDIMENTOS][40];  
char data_atendimentos[QNTD_ATENDIMENTOS][40];
char status_atendimentos[QNTD_ATENDIMENTOS][40];  
float preco_atendimentos[QNTD_ATENDIMENTOS];


int main(void) {
    preenche_vetor_ativos(pacientes_ativos, QNTD_PACIENTES);
    preenche_vetor_ativos(atendimentos_ativos, QNTD_ATENDIMENTOS);

    pacientes = ler("pacientes.bin",&qnt_pacientes,sizeof(paciente));
    pacientes_alterados = malloc(qnt_pacientes * sizeof(int));
    preenche_vetor_ativos(pacientes_alterados,qnt_pacientes);

    atendimentos = ler("atendimentos.bin",&qnt_atendimentos,sizeof(atendimento));
    atendimentos_alterados= malloc(qnt_atendimentos * sizeof(int));
    preenche_vetor_ativos(atendimentos_alterados,qnt_atendimentos);

    while(1) {
        system("clear");
        
        int interacao_menu_principal = menu_principal();

        switch (interacao_menu_principal) {
            case 1:
                system("clear");
                printf(BLUE"\nMenu \"Paciente\" Selecionado...\n"RESET);
                while(1) {
                    int interacao_menu_pacientes = menu_pacientes(); 
                    int espaco_livre;                                                           
                    int informacao_nao_obrigatoria;                   
                    int formatacao_incorreta;


                    switch (interacao_menu_pacientes) {
                        case 1:
                            system("clear");
                            printf("\nOpção -> "BLUE"[1], \"Inserir um Novo Paciente\" "RESET"Selecionada...\n\n");
                            while (1) {

                                paciente* novopaciente = procura_paciente_livre(pacientes, qnt_pacientes);
                                /*
                                if(espaco_livre == NULL) {
                                    novopaciente = &novospacientes[qnt_alterados];
                                }
                                */
                                if(cadastra_nome_paciente(novopaciente, pacientes, qnt_pacientes)) {
                                    if(!coletar_opcao("Inserir outro paciente", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }
                                printf("%s\n",novopaciente->nome_paciente);
                                
                                for(;;){
                                    int k=0;
                                    cria_codigo2(novopaciente->codigo_paciente);
                                    for(int i=0;i < qnt_pacientes;i++){
                                        if(!strcmp(novopaciente->codigo_paciente,pacientes[i].codigo_paciente)) k=1;
                                        break;
                                    }
                                    if(k) continue;
                                    break;
                                }
                                
                                printf("%s\n",novopaciente->codigo_paciente);

                                cadastra_documento("RG", RG_pacientes[espaco_livre], espaco_livre);
                                if(procura_informacao(RG_pacientes[espaco_livre], RG_pacientes, 12, espaco_livre)) { 
                                    printf(RED"RG já cadastrado --> Impossível Inserir este Paciente!\n"RESET);

                                    if(!coletar_opcao("Inserir outro paciente", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }


                                cadastra_documento("CPF", CPF_pacientes[espaco_livre], espaco_livre);
                                if(procura_informacao(CPF_pacientes[espaco_livre], CPF_pacientes, 12, espaco_livre)) { 
                                    printf(RED"CPF já cadastrado --> Impossível Inserir este Paciente!\n"RESET);
                                    
                                    if(!coletar_opcao("Inserir outro paciente", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}

                                }

                                while (1) {
                                    printf("Selecione o seu Tipo Sanguíneo (Sem o Fator RH) ou ENTER para pular:\n");
                                    printf(BLUE"[1] A     [2] B     [3] AB     [4] O\n"RESET);  
                                    ler_str(tipo_sanguineo_pacientes[espaco_livre]);

                                    informacao_nao_obrigatoria = cadastro_informacao_nao_obrigatorio(tipo_sanguineo_pacientes[espaco_livre]);
                                    if(informacao_nao_obrigatoria) {break;}
                                    
                                    formatacao_incorreta = valida_tipo_sanguineo(tipo_sanguineo_pacientes[espaco_livre]);
                                    if(formatacao_incorreta) {
                                        printf(RED"Tipo Sanguíneo Inválido, Digite Novamente!\n"RESET);
                                        continue;
                                    }
                                    break;
                                }

                                while(1) {
                                    printf("Selecione o Fator RH do Paciente (Positivo ou Negativo) ou ENTER para pular:\n");
                                    printf(BLUE"[1] Positivo     [2] Negativo\n"RESET);
                                    ler_str(fator_RH_pacientes[espaco_livre]);

                                    informacao_nao_obrigatoria = cadastro_informacao_nao_obrigatorio(fator_RH_pacientes[espaco_livre]);
                                    if(informacao_nao_obrigatoria) {break;}
                                        
                                    formatacao_incorreta = valida_fato_rh(fator_RH_pacientes[espaco_livre]);
                                    if(formatacao_incorreta) {
                                        printf(RED"Fator RH Inválido, Digite Novamente!\n"RESET);
                                        continue;
                                    }
                                        break;
                                }

                                printf("Digite seu Endereço ou ENTER para pular:\n");
                                ler_str(endereco_pacientes[espaco_livre]);
                                informacao_nao_obrigatoria = cadastro_informacao_nao_obrigatorio(endereco_pacientes[espaco_livre]);

                                printf("Digite a Data de Nascimento do Paciente:\n");
                                receber_data(datas_nascimento_pacientes, espaco_livre);

                                system("clear");
                                exibe_informacoes_paciente(nomes_pacientes, codigo_pacientes, RG_pacientes, CPF_pacientes, tipo_sanguineo_pacientes, fator_RH_pacientes, endereco_pacientes, datas_nascimento_pacientes, espaco_livre);

                                pacientes_ativos[espaco_livre] = 1;
                                
                                if(!coletar_opcao("Incluir novo paciente", "Voltar ao Menu Pacientes")) {continue;}
                                else {break;}                   
                            }
                            break;
                        case 2:
                            system("clear");
                            while(1) {
                                printf("\nOpção -> "BLUE"[2], \"Alterar um Paciente Existente\""RESET" Selecionada...\n\n");

                                printf("Digite o Código do Paciente que Deseja Alterar: \n\n");

                                printf("-> Código: ");
                                char alterar_paciente_codigo[9];
                                scanf("%s", &alterar_paciente_codigo);

                                int index_paciente = procura_codigo(alterar_paciente_codigo,codigo_pacientes,QNTD_ATENDIMENTOS);
                                if(index_paciente >= 0) {
                                    printf(GREEN" ---> Paciente de Código %s Encontrado\n"RESET, alterar_paciente_codigo);

                                    printf("\nQual Informação Você deseja alterar?\n");
                                    printf(BLUE"[1] Nome     [2] RG     [3] CPF     [4] Tipo Sanguíneo     [5] Fator RH     [6] Endereço     [7] Data de Nascimento\n"RESET);
                                    int alteracao_desejada;
                                    scanf("%d", &alteracao_desejada);

                                    switch (alteracao_desejada) {  
                                        case 1:
                                            printf(BLUE"\nOpção -> [1], \"Alterar Nome\""RESET" Selecionada...\n\n");

                                            char nome_antigo[40];
                                            strcpy(nome_antigo ,nomes_pacientes[index_paciente]);                               
                                            /*
                                            if(cadastra_nome_paciente(nomes_pacientes, espaco_livre, QNTD_PACIENTES)) {
                                                if(!coletar_opcao("Inserir outro paciente", "Ir para o Menu Pacientes")) {continue;}
                                                else {break;}
                                            }
                                            */
                                            printf(GREEN"\nNome Alterado com Sucesso!\n"RESET);
                                            printf("De: %s ---> Para: %s\n", nome_antigo, nomes_pacientes[index_paciente]);

                                            break;
                                        case 2:
                                            printf(BLUE"\nOpção -> [2], \"Alterar RG\""RESET" Selecionada...\n\n");
                                            
                                            char RG_antigo[12];
                                            strcpy(RG_antigo ,RG_pacientes[index_paciente]); 

                                            cadastra_documento("RG", RG_pacientes[index_paciente], index_paciente);
                                            if(procura_informacao(RG_pacientes[index_paciente], RG_pacientes, 12, index_paciente)) { 
                                                printf(RED"RG já cadastrado --> Impossível Inserir este Paciente!\n"RESET);

                                                if(!coletar_opcao("Inserir outro paciente", "Ir para o Menu Pacientes")) {continue;}
                                                else {break;}
                                            }
                                            
                                            printf(GREEN"RG Alterado com Sucesso!\n"RESET);
                                            printf("De: %s ---> Para: %s\n", RG_antigo, RG_pacientes[index_paciente]);

                                            break;
                                        case 3:
                                            printf(BLUE"\nOpção -> [3], \"Alterar CPF\""RESET" Selecionada...\n\n");

                                            char CPF_antigo[12];
                                            strcpy(CPF_antigo ,CPF_pacientes[index_paciente]);

                                            cadastra_documento("CPF", CPF_pacientes[index_paciente], index_paciente);
                                            if(procura_informacao(CPF_pacientes[index_paciente], CPF_pacientes, 12, index_paciente)) { 
                                                printf(RED"CPF já cadastrado --> Impossível Inserir este Paciente!\n"RESET);
                                                
                                                if(!coletar_opcao("Inserir outro paciente", "Ir para o Menu Pacientes")) {continue;}
                                                else {break;}
                                            }

                                            printf(GREEN"CPF Alterado com Sucesso!\n"RESET);
                                            printf("De: %s ---> Para: %s\n", CPF_antigo, CPF_antigo[index_paciente]);

                                            break;
                                        case 4:
                                            printf("\nOpção -> "BLUE"[4], \"Alterar Tipo Sanguíneo\""RESET" Selecionada...\n\n");

                                            char tipo_sanguineo_antigo[3];
                                            strcpy(tipo_sanguineo_antigo ,tipo_sanguineo_pacientes[index_paciente]);

                                            while (1) {
                                                printf("Selecione o seu Tipo Sanguíneo:\n");
                                                printf(BLUE"[1] A     [2] B     [3] AB     [4] O\n"RESET);  
                                                ler_str(tipo_sanguineo_pacientes[index_paciente]);
                                
                                                formatacao_incorreta = valida_tipo_sanguineo(tipo_sanguineo_pacientes[index_paciente]);
                                                if(formatacao_incorreta) {
                                                    printf("Tipo Sanguíneo Inválido, Digite Novamente!\n");
                                                    continue;
                                                }

                                                break;
                                            }

                                            printf(GREEN"Tipo Sanguíneo Alterado com Sucesso!\n"RESET);
                                            printf("De: %s ---> Para: %s\n", tipo_sanguineo_antigo, tipo_sanguineo_pacientes[index_paciente]);

                                            break;
                                        case 5:
                                            printf("\nOpção -> "BLUE"[5], \"Alterar Fator RH\""RESET" Selecionada...\n\n");

                                            char fator_RH_antigo[9];
                                            strcpy(fator_RH_antigo ,fator_RH_pacientes[index_paciente]);

                                            while(1) {
                                                printf("Selecione o Fator RH do Paciente (Positivo ou Negativo):\n");
                                                printf(BLUE"[1] Positivo     [2] Negativo\n"RESET);
                                                ler_str(fator_RH_pacientes[index_paciente]);

                                                formatacao_incorreta = valida_fato_rh(fator_RH_pacientes[index_paciente]);
                                                if(formatacao_incorreta) {
                                                    printf("Fator RH Inválido, Digite Novamente!\n");
                                                    continue;
                                                }
                                                    break;
                                            }

                                            printf(GREEN"Fator RH Alterado com Sucesso!\n"RESET);
                                            printf("De: %s ---> Para: %s\n", fator_RH_antigo, fator_RH_pacientes[index_paciente]);

                                            break;
                                        case 6:
                                            printf("\nOpção -> "BLUE"[6], \"Alterar Endereço\""RESET" Selecionada...\n\n");

                                            char endereco_antigo[9];
                                            strcpy(endereco_antigo ,endereco_pacientes[index_paciente]);

                                            printf("Digite seu Endereço:\n");
                                            ler_str(endereco_pacientes[espaco_livre]);

                                            printf(GREEN"Endereço Alterado com Sucesso!\n"RESET);
                                            printf("De: %s ---> Para: %s\n", endereco_antigo, endereco_pacientes[index_paciente]);

                                            break;
                                        case 7:
                                            printf("\nOpção -> "BLUE"[7], \"Alterar Data de Nascimento\""RESET" Selecionada...\n\n");

                                            char data_nascimento_antiga[40];
                                            strcpy(data_nascimento_antiga, datas_nascimento_pacientes[index_paciente]);

                                            printf("Digite a Data de Nascimento do Paciente:\n");
                                            receber_data(datas_nascimento_pacientes, index_paciente);

                                            printf(GREEN"Data de Nascimento Alterado com Sucesso!\n"RESET);
                                            printf("De: %s ---> Para: %s\n", data_nascimento_antiga, datas_nascimento_pacientes[index_paciente]);

                                            break;
                                        default:
                                            printf("Selecione alguma das opções anteriores!\n");
                                            break;
                                    }  
                                }
                                else {
                                    printf(RED"Paciente de Código %s NÃO Encontrado Verifique o Código Inserido!\n\n"RESET, alterar_paciente_codigo);

                                    if(!coletar_opcao("Inserir Novo Código", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }

                                if(!coletar_opcao("Alterar Informação Novamente", "Ir para o Menu Pacientes")) {continue;}
                                else {break;}
                            }
                            break;
                        case 3:
                            printf("\nOpção -> "BLUE"[3], \"Excluir um Paciente\""RESET" Selecionada...\n\n");
                            while(1) {
                                printf("Digite o Código do Paciente que deseja excluir: ");
                                char codigo_paciente_excluido[8];
                                scanf("%s", &codigo_paciente_excluido);

                                int index_paciente = procura_codigo(codigo_paciente_excluido, codigo_pacientes, QNTD_ATENDIMENTOS);

                                if(index_paciente >= 0) {
                                    printf(GREEN"---> Paciente de Código %s Encontrado\n"RESET, codigo_paciente_excluido);
                                    exibe_informacoes_paciente(nomes_pacientes, codigo_pacientes, RG_pacientes, CPF_pacientes, tipo_sanguineo_pacientes, fator_RH_pacientes, endereco_pacientes, datas_nascimento_pacientes, index_paciente);

                                    printf(RED"\nDeseja Realmente Excluir esse paciente?\n"RESET);
                                    if(!coletar_opcao("Confirmar Exclusão", "Voltar para o Menu Pacientes")) {
                                        pacientes_ativos[index_paciente] = 0;
                                        strcpy(codigo_pacientes, "Espaco Livre");

                                        printf(GREEN"Paciente Excluído com Sucesso!"RESET);
                                        break;
                                    }
                                    else {break;}

                                }
                                else {
                                    printf(RED"\nPaciente de Código %s NÃO Encontrado Verifique o Código Inserido!\n"RESET, codigo_paciente_excluido);
                                    if(!coletar_opcao("Inserir Novo Código", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }
                            }
                            break;
                        case 4:
                            printf("\nOpção -> "BLUE"[4], \"Exibir os Dados de um Paciente pelo seu Código\""RESET" Selecionada...\n\n");

                            while(1) {
                                printf("Digite o Código do Paciente:");

                                char exibir_dados_codigo[9];
                                scanf("%s", &exibir_dados_codigo);

                                int index_paciente = procura_codigo(exibir_dados_codigo, codigo_pacientes, QNTD_ATENDIMENTOS);
                                if(index_paciente >= 0) {
                                    printf(GREEN"---> Paciente de Código %s Encontrado\n\n"RESET, exibir_dados_codigo);
                                    exibe_informacoes_paciente(nomes_pacientes, codigo_pacientes, RG_pacientes, CPF_pacientes, tipo_sanguineo_pacientes, fator_RH_pacientes, endereco_pacientes, datas_nascimento_pacientes, index_paciente);

                                    if(!coletar_opcao("Inserir Novo Código", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }
                                else {
                                    printf(RED"Paciente de Código %s NÃO Encontrado Verifique o Código Inserido!\n"RESET, exibir_dados_codigo);
                                    if(!coletar_opcao("Inserir Novo Código", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }
                            }
                            break;
                        case 5:
                            printf("\nOpção -> "BLUE"[5], \"Exibir os Dados de Pacientes que Apresentam o Mesmo"
                                " Tipo Sanguíneo\""RESET" Selecionada...\n\n");
                                
                            while(1) {
                                printf("Escolha um Tipo Sanguíneo para Vizualizar os Pacientes que pertecem a esse Determinado Grupo:\n");
                                printf(BLUE"[1] A     [2] B     [3] AB     [4] O\n"RESET);
                                char tp_sanguineo_selecionado[3];
                                scanf(" %s", &tp_sanguineo_selecionado);

                                if(valida_tipo_sanguineo(tp_sanguineo_selecionado)) {
                                    printf(RED"Tipo Sanguíneo Inválido, Digite Novamente!\n"RESET);
                                    continue;
                                }

                                exibe_tipo_sanguineo_pacientes(tp_sanguineo_selecionado, tipo_sanguineo_pacientes, fator_RH_pacientes, QNTD_ATENDIMENTOS, nomes_pacientes);

                                if(!coletar_opcao("Inserir Novo Tipo Sanguíneo", "Ir para o Menu Pacientes")) {continue;}
                                else {break;}
                            }
                            break;
                        case 6:
                            while(1) {
                                printf("\nOpção -> "BLUE"[6], \"Exibir os Dados de Pacientes pelo Dia de "
                                    "Consulta\""RESET" Selecionada...\n\n");

                                printf("Digite a Data da Consulta, para Exibir os Dados do(s) Paciente(s):\n");

                                char exibir_dados_data[1][40];
                                receber_data(exibir_dados_data, 0);

                                char copia_data_atendimento[1][40];
                                copia_matriz(copia_data_atendimento, data_atendimentos, QNTD_ATENDIMENTOS);

                                int count = 0;
                                for(int i = 0; i < QNTD_ATENDIMENTOS; i++) {
                                    int indice_paciente_do_atendimento = varrer_datas(exibir_dados_data, copia_data_atendimento, QNTD_ATENDIMENTOS);
                                    
                                    if(indice_paciente_do_atendimento >= 0) {
                                        strcpy(copia_data_atendimento[indice_paciente_do_atendimento], "JA EXIBIDO"); 

                                        int indice_nomes_paciente = paciente_do_atendimento[indice_paciente_do_atendimento];

                                        printf(YELLOW"\n---> Data com Consulta do Paciente: %s"RESET, nomes_pacientes[indice_nomes_paciente]);
                                        exibe_informacoes_paciente(nomes_pacientes, codigo_pacientes, RG_pacientes, CPF_pacientes, tipo_sanguineo_pacientes, fator_RH_pacientes, endereco_pacientes, datas_nascimento_pacientes, indice_nomes_paciente);
                                        
                                        count++;
                                    }                        
                                }

                                if(!count)
                                    printf(RED"Sem Consultas para essa Data!\n"RESET); 

                                if(!coletar_opcao("Inserir Outra Data", "Ir para o Menu Pacientes")) {continue;}
                                else {break;}
                            }
                            break;
                        case 7:
                            while(1) {
                                printf("\nOpção -> "BLUE"[7], \"Exibir Todos os Pacientes\""RESET" Selecionada...\n\n");

                                exibir_todos_pacientes(nomes_pacientes, pacientes_ativos, QNTD_ATENDIMENTOS);

                                if(!coletar_opcao("Exibir todos os Pacientes Novamente", "Ir para o Menu Pacientes")) {continue;}
                                else {break;}
                            }
                            break;
                        case 8:
                            printf("\nOpção -> "BLUE"[8], \"Exibir Todos os Pacientes em Ordem"
                                " Alfabética\""RESET" Selecionada...\n\n");

                            int index_paciente = verifica_pacientes_ativos(pacientes_ativos, QNTD_PACIENTES);
                            if(!index_paciente) {

                                const int TAM_VETOR = cria_tamanho_limitando_ativos(pacientes_ativos, QNTD_PACIENTES);
                                int limitando_ativos[TAM_VETOR]; 

                                completa_vetor_limitando_ativos(pacientes_ativos, TAM_VETOR, nomes_pacientes, QNTD_ATENDIMENTOS, limitando_ativos);
                                ordena_pacientes_ordem_alfabetica(nomes_pacientes, QNTD_PACIENTES, limitando_ativos);
                                exibe_pacientes_ordem_alfabetica(nomes_pacientes, limitando_ativos, TAM_VETOR);

                                break;
                            }
                            else {
                                printf(RED"Sem Pacientes Cadastrados!\n\n"RESET);
                                break;   
                            }
                        case 9:
                            while(1) {                         
                                printf("\nOpção -> "BLUE"[9], \"Exibir a Soma das Consultas Pagas por um Determinado Paciente\""RESET" Selecionada...\n\n");

                                printf("Digite o Nome do Paciente, para ver a soma das suas Consultas Pagas: "); 

                                char nome_paciente_consultas_pagas[40];
                                ler_str(nome_paciente_consultas_pagas);

                                if(verifica_cadastro_paciente(nomes_pacientes, QNTD_PACIENTES, nome_paciente_consultas_pagas)) {

                                    float soma_consultas = soma_consultas_pagas_pacientes(nome_paciente_consultas_pagas, nomes_pacientes, preco_atendimentos, QNTD_PACIENTES, paciente_do_atendimento);
                                    
                                    printf(GREEN"--> Soma das Consultas do Paciente %s = %.2f\n"RESET, nome_paciente_consultas_pagas, soma_consultas);

                                    if(!coletar_opcao("Selecionar Outro Paciente", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }
                                else {
                                    printf(RED"Paciente %s NÃO Cadastrado\n"RESET, nome_paciente_consultas_pagas);

                                    if(!coletar_opcao("Selecionar Outro Paciente", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }
                            }
                            break;
                        case 10:
                            printf("\nOpção -> "BLUE"[10], \"Voltar para o Menu Anterior\""RESET" Selecionada...\n\n");
                            break;
                        default:
                            printf(RED"\nSelecione alguma das opções anteriores!\n"RESET);
                            break;
                    }
                    if(interacao_menu_pacientes== 10){break;}
                    continue;    
                }break;
    
            case 2:
                system("clear");
                printf(BLUE"\nMenu \"Atendimento\" Selecionado...\n"RESET);
                while(1) {
                    int interacao_menu_atendimentos = menu_atendimento();
                    int espaco_livre;
                    int indice_do_paciente;

                    switch (interacao_menu_atendimentos) {
                        case 1:
                            system("clear");
                            while (1){
                                printf("\nOpção -> "BLUE"[1], \"Inserir um novo atendimento\""RESET" Selecionada...\n\n");

                                atendimentos = ler("atendimentos.bin", &qnt_atendimentos, sizeof(atendimento));
                                //verifica na structs com todos os atendimentos se tem algum inativo pra sobrescrever ele!
                                atendimento *novo_atendimento = procura_atendimento_livre(atendimentos, qnt_atendimentos);

                                if(novo_atendimento == NULL) {
                                    novo_atendimento = &novos_atendimentos[qnt_novos_atendimentos];
                                }

                                printf("Digite o Codigo do Paciente: \n");
                                ler_str(novo_atendimento->codigo_paciente);

                                paciente *teste_paciente = malloc(sizeof(pacientes) * 2);
                                strcpy(teste_paciente[0].codigo_paciente, "G6H8D0D");
                                strcpy(teste_paciente[1].codigo_paciente, "G6H8DOL");

                                //trocar "teste_paciente" por pacientes e 2 por qntd_pacientes na funcao abaixo!
                                if(!procura_paciente(teste_paciente, 2, novo_atendimento->codigo_paciente)) {
                                    printf(RED"Paciente nao cadastrado!\n"RESET);
                                    if(coletar_opcao("Inserir outro paciente", "Voltar ao menu de atendimentos")) {
                                        break;
                                    }else {continue;}
                                }

                                printf("\nPaciente "GREEN" %s"RESET"  Selecionado...\n", novo_atendimento->codigo_paciente);
                                /*
                                printf(BLUE"Dados da consulta:\n"RESET);
                                receber_data(data_atendimentos,espaco_livre);
                                
                                int data_ja_cadastrada=atendimento_ja_cadastrado(data_atendimentos,paciente_do_atendimento,espaco_livre,QNTD_ATENDIMENTOS);
                                if(data_ja_cadastrada)continue;
                                */

                                novo_atendimento->preco = receber_preco();

                                receber_status_atendimento(novo_atendimento);

                                cria_codigo2(novo_atendimento->codigo_atendimento);

                                receber_tipo_atendimento(novo_atendimento);

                                novo_atendimento->ativo = 1;
                                qnt_novos_atendimentos++;

                                system("cls");
                                exibir_dados_atendimento(novo_atendimento);
                                printf(GREEN"* Atendimento Cadastrado com sucesso! *\n"RESET);

                                if(coletar_opcao("Voltar","Inserir outro Atendimento"))continue;
                                else {break;}
                            }
                            break;
                        case 2:
                            system("clear");
                            while(1){
                                printf("\n----------------"BLUE"Alterar um Atendimento Existente"RESET"---------------\n");
                                
                                printf("Digite o código do atendimento que deseja alterar:\n");
                                int indice_do_atendimento = procura_atendimento(codigo_atendimentos,QNTD_ATENDIMENTOS,atendimentos_ativos);
                                if(indice_do_atendimento == -1)continue;;
                                if(indice_do_atendimento == -2)break;
                                
                                indice_do_paciente = paciente_do_atendimento[indice_do_atendimento];
                                
                                system("clear");
                                //exibir_dados_atendimento(codigo_atendimentos,nomes_pacientes,codigo_pacientes,indice_do_paciente,data_atendimentos,tipo_atendimentos,preco_atendimentos,status_atendimentos,indice_do_atendimento);
                                int opcao;
                                
                                printf("Qual dado deseja alterar?\n");
                                printf(BLUE"[1]"RESET"Paciente "BLUE"[2] "RESET"Data "BLUE"[3] "RESET"Tipo "BLUE"[4]"RESET" Preço "BLUE"[5]"RESET"Status\n");
                                scanf("%d",&opcao);

                                switch(opcao){
                                    case 1: 
                                        printf("Paciente anterior : %s \n",nomes_pacientes[indice_do_paciente]);
                                        /*int indice_novo_paciente = procura_paciente(nomes_pacientes,QNTD_PACIENTES);

                                        int data_ja_cadastrada=atendimento_ja_cadastrado(data_atendimentos,indice_novo_paciente,espaco_livre,QNTD_ATENDIMENTOS);
                                        if(data_ja_cadastrada)continue;
                                        
                                        paciente_do_atendimento[indice_do_atendimento]=indice_novo_paciente;
                                        printf(GREEN"Paciente do atendimento %s alterado!\n"RESET,codigo_atendimentos[indice_do_atendimento]);
                                        
                                        break;
                                    case 2:
                                        printf("Digite a nova data:\n");
                                        receber_data(data_atendimentos,indice_do_atendimento);
                                        printf(GREEN"Nova data cadastrada: %s\n"RESET,data_atendimentos[indice_do_atendimento]);
                                        break;
                                    case 3:
                                        receber_tipo_atendimento(tipo_atendimentos,indice_do_atendimento);
                                        printf(GREEN"Novo tipo cadastrado"RESET);
                                        break;
                                    case 4:
                                        printf("Digite o novo preço da consulta:\n");
                                        scanf("%f",&preco_atendimentos[indice_do_atendimento]);
                                        printf(GREEN"Novo preço cadastrado"RESET);
                                        break;
                                    case 5:
                                        printf("status atual: %s\n",status_atendimentos[indice_do_atendimento]);
                                        receber_status_atendimento(status_atendimentos,indice_do_atendimento);
                                        printf(GREEN"Status alterado\n"RESET);
                                        break;
                                    default:
                                        printf("digite apenas 1,2,3,4 ou 5");
                                        break;*/
                                }break;
                                if(coletar_opcao("Voltar","Alterar outro Atendimento"))continue;
                                else break;
                            }break;          
                        case 3:
                            system("clear");
                            while(1){
                                printf("---------------------"BLUE"Excluir um Atendimento"RESET"-----------------------\n");
                                
                                printf("Digite o código do atendimento que deseja excluir:\n");
                                int indice_do_atendimento =procura_atendimento(codigo_atendimentos,QNTD_ATENDIMENTOS,atendimentos_ativos);
                                
                                if(indice_do_atendimento == -1)continue;
                                if(indice_do_atendimento == -2)break;
                                indice_do_paciente = paciente_do_atendimento[indice_do_atendimento];
                                //exibir_dados_atendimento(codigo_atendimentos,nomes_pacientes,codigo_pacientes,indice_do_paciente,data_atendimentos,tipo_atendimentos,preco_atendimentos,status_atendimentos,indice_do_atendimento);
                                
                                printf("Tem certeza?\n");
                                if(coletar_opcao("Cancelar Operação","Excluir")) {
                                    atendimentos_ativos[indice_do_atendimento]=0;
                                    printf(GREEN"Atendimento Excluído\n"RESET);
                                    break;
                                }
                                printf(GREEN"Operacão Cancelada!"RESET);
                            }break;
                        case 4:
                            while(1){
                                system("clear");
                                printf("---------------------"BLUE"Exibir Atendimento(Código)"RESET"-------------------\n");
                                
                                printf("Digite o código do atendimento que deseja consultar:\n");
                                int indice_do_atendimento=procura_atendimento(codigo_atendimentos,QNTD_ATENDIMENTOS,atendimentos_ativos);
                                if(indice_do_atendimento == -1)continue;
                                if(indice_do_atendimento == -2)break;

                                indice_do_paciente = paciente_do_atendimento[indice_do_atendimento];
                                //exibir_dados_atendimento(codigo_atendimentos,nomes_pacientes,codigo_pacientes,indice_do_paciente,data_atendimentos,tipo_atendimentos,preco_atendimentos,status_atendimentos,indice_do_atendimento);
                                
                                if(coletar_opcao("Voltar","Exibir outro Atendimento"))continue;
                                else break; 
                            }break;
                        case 5:
                            while(1){
                                char codigo_paciente[8];
                                system("clear");
                                printf("----------------------"BLUE"Exibir Atendimento (Código do Paciente)"RESET"-----------------\n");
                                
                                int indice_do_paciente = procura_paciente_codigo(codigo_pacientes,QNTD_PACIENTES,pacientes_ativos);
                                if(indice_do_paciente == -1)continue;
                                if(indice_do_paciente == -2)break;
                               
                                for(int i = 0;i < QNTD_ATENDIMENTOS;i++){
                                    if(paciente_do_atendimento[i] == indice_do_paciente){
                                        if(atendimentos_ativos[i]==0) continue;
                                        int indice_do_atendimento=i;
                                        //exibir_dados_atendimento(codigo_atendimentos,nomes_pacientes,codigo_pacientes,indice_do_paciente,data_atendimentos,tipo_atendimentos,preco_atendimentos,status_atendimentos,indice_do_atendimento);
                                    }
                                }
                                
                                if(coletar_opcao("Voltar","Exibir Atendimentos de outro paciente"))continue;
                                else break; 
                            }break;    
                        case 6:
                           
                            while(1){
                                system("clear");
                                printf("-----------------------"BLUE"Exibir atendimento do paciente (Nome do Paciente)"RESET"------------------------\n");
                                
                                char nome_paciente[40];
                                //printf("Digite o nome do Paciente que deseja exibir:\n");
                                //int indice_do_paciente = procura_paciente(nomes_pacientes,QNTD_PACIENTES);
                                if(indice_do_paciente == -1)break;
                                
                                system("clear");
                                printf("Atendimentos do Paciente "BLUE"%s"RESET":\n",nomes_pacientes[indice_do_paciente]);
                                for(int i = 0;i < QNTD_ATENDIMENTOS;i++){
                                    if(atendimentos_ativos[i]==0) continue;
                                    if(paciente_do_atendimento[i] == indice_do_paciente){  
                                        int indice_do_atendimento=i;
                                        //exibir_dados_atendimento(codigo_atendimentos,nomes_pacientes,codigo_pacientes,indice_do_paciente,data_atendimentos,tipo_atendimentos,preco_atendimentos,status_atendimentos,indice_do_atendimento);
                                    }
                                }
                                if(coletar_opcao("Voltar","Exibir Atendimentos de outro paciente"))continue;
                                else break;
                            }break;   
                        case 7:
                            
                            while(1){
                                system("clear");
                                printf("-------------------"BLUE"Exibir Todos os Atendimentos do Dia"RESET"--------------------\n");
                                
                                char atendimentos_do_dia[1][40];
                                float soma=0,cont=0;
                                printf("Digite a data que deseja buscar atendimentos:\n");
                                receber_data(atendimentos_do_dia,0);
                                
                                for(int i = 0; i< QNTD_ATENDIMENTOS;i++){
                                    if(atendimentos_ativos[i]==0) continue;
                                    if(strcmp(atendimentos_do_dia[0],data_atendimentos[i]) == 0){
                                        int indice_do_atendimento=i;
                                        int indice_do_paciente= paciente_do_atendimento[indice_do_atendimento];
                                        //exibir_dados_atendimento(codigo_atendimentos,nomes_pacientes,codigo_pacientes,indice_do_paciente,data_atendimentos,tipo_atendimentos,preco_atendimentos,status_atendimentos,indice_do_atendimento);
                                        soma+=preco_atendimentos[i];
                                        cont++;
                                    }
                                }
                                if(cont==0){
                                    printf("Nenhum atendimento neste dia\n");
                                    if(coletar_opcao("Sair","Exibir Atendimentos de Outro Dia"))continue;
                                    else break;
                                }
                                printf("Total de Consultas Pagas no Dia[ %s ] = R$%.2f\n",atendimentos_do_dia[1],soma);
                                
                                if(coletar_opcao("Sair","Exibir Atendimentos de Outro Dia"))continue;
                                else break;
                            }break;
                        case 8:
                            while(1){
                                system("clear");
                                printf("-------------------"BLUE"Exibir Todos os Atendimentos(Data mais próxima)"RESET"--------------------\n");
                                
                                int ordem_datas[100];
                                ordenar_datas(data_atendimentos,ordem_datas,QNTD_ATENDIMENTOS,atendimentos_ativos);
                                int qnd_atend_ativos=0;
                                for(int i=0;i<QNTD_ATENDIMENTOS-1;i++){
                                    if(atendimentos_ativos[i]==1)qnd_atend_ativos++;
                                }
                                if(qnd_atend_ativos==0){
                                    printf(RED"Nenhum Atendimento Cadastrado"RESET);
                                }
                                for(int i=0;i < qnd_atend_ativos;i++){
                                int atendimento=ordem_datas[i];
                                int paciente = paciente_do_atendimento[i];
                                //exibir_dados_atendimento(codigo_atendimentos,nomes_pacientes,codigo_pacientes,paciente,data_atendimentos,tipo_atendimentos,preco_atendimentos,status_atendimentos,atendimento);
                                }
                                if(coletar_opcao("Sair","Exibir Atendimentos Novamente"))continue;
                                else break;
                            }break;
                        case 9:
                            printf("\nOpção -> [9], \"Voltar para o Menu Anterior\" Selecionada...\n\n");
                            break;
                        default:
                            printf(RED"\nSelecione alguma das opções anteriores!\n"RESET);
                            break;
                    }
                    if(interacao_menu_atendimentos==9)break;
                    continue;
                }continue;
            case 3:
                printf(GREEN"\nSaída do Sistema Confirmada!\n"RESET);
                return 0;
            default:
                printf(RED"Selecione alguma das opções anteriores!\n"RESET);
                break;
        }continue;
    }
    free(pacientes);
    free(atendimentos);
    return 0;
}