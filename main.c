/*
 * 1) Ordem Alfabetica Pacientes Errada
 * 2) Codigo Nao aleatorio, verificar ou altera-lo (tanto para atendimento quanto para pacientes) -> Alterado no atendimento so falta no pacientes
 * 3) Verificar se um paciente ja nao tem atendimento na data para salvar
 * 4) administrar se o vetorde novos pacientes e atendimentos ja esta cheio
 * 6) APAGAR COEMNTARIOS DO CODIGO
 * 7) Fazer opcao de descartar salvos
 * 9) Testar erros de entradas
 * 10) Nao deixar um paciente ter atendimento no mesmo data*/

#include <stdio.h>
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

size_t qnt_pacientes=0;
size_t qnt_atendimentos = 0;

int qnt_novos_pacientes = 0;
int qnt_novos_atendimentos = 0;

int qnt_pacientes_alterados = 0;
int qnt_atendimentos_alterados = 0;

int *pacientes_alterados;
int *atendimentos_alterados;

int qnt_alteracoes = 0;


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
    pacientes_alterados= malloc(qnt_pacientes * sizeof(int));
    preenche_vetor_ativos(pacientes_alterados,qnt_pacientes);
    
    atendimentos = ler("atendimentos.bin",&qnt_atendimentos,sizeof(atendimento));
    atendimentos_alterados = malloc(qnt_atendimentos * sizeof(int));
    preenche_vetor_ativos(atendimentos_alterados,qnt_atendimentos);

    int qnt_adicionados = 0;
    while(1) {
        if(qnt_alteracoes) printf(RED"VOCÊ POSSUI %d ALTERACOES NÃO SALVAS!\n"RESET,qnt_alteracoes);
        int interacao_menu_principal = menu_principal();

        switch (interacao_menu_principal) {
            case 1:
                system("clear");
                printf(BLUE"\nMenu \"Paciente\" Selecionado...\n"RESET);
                while(1) {
                    if(qnt_alteracoes>0) printf(RED"VOCÊ POSSUI %d ALTERACOES NÃO SALVAS!\n"RESET,qnt_alteracoes);
                    int interacao_menu_pacientes = menu_pacientes();                                                           
                    int informacao_nao_obrigatoria;                   
                    int formatacao_incorreta;


                    switch (interacao_menu_pacientes) {
                        case 1:
                            printf("\nOpção -> "BLUE"[1], \"Inserir um Novo Paciente\" "RESET"Selecionada...\n\n");
                            while (1) {

                                paciente* novopaciente;
                                int novo = 0;
                                int index = procura_paciente_livre(pacientes, qnt_pacientes);
                                
                                if(index<0) {
                                    novopaciente = &novospacientes[qnt_novos_pacientes];
                                    novo=1;
                                }else{novopaciente=&pacientes[index];}
                                
                                //printf("%d",index);
                                
                                if(cadastra_nome_paciente2(novopaciente->nome, pacientes, qnt_pacientes)) {
                                    if(!coletar_opcao("Inserir outro paciente", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }
                                
                                for(;;){
                                    int k=0;
                                    cria_codigo2(novopaciente->codigo);
                                    for(int i=0;i < qnt_pacientes;i++){
                                        if(pacientes[i].ativo == 0 )continue;
                                        if(!strcmp(novopaciente->codigo,pacientes[i].codigo)) k=1;
                                        break;
                                    }
                                    if(k) continue;
                                    break;
                                }

                                cadastra_documento2("RG", novopaciente->RG);
                                if(procura_informacao2(novopaciente->RG, pacientes, qnt_pacientes,3,index)) { 
                                    printf(RED"RG já cadastrado --> Impossível Inserir este Paciente!\n"RESET);

                                    if(!coletar_opcao("Inserir outro paciente", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }

                                cadastra_documento2("CPF", novopaciente->CPF);
                                if(procura_informacao2(novopaciente->CPF, pacientes, qnt_pacientes,4,index)) { 
                                    printf(RED"CPF já cadastrado --> Impossível Inserir este Paciente!\n"RESET);

                                    if(!coletar_opcao("Inserir outro paciente", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}

                                }

                                cadastrar_tipo_sanguineo(novopaciente->tipo_sanquineo);
                                cadastrar_fator_rh(novopaciente->fator_RH);

                                printf("Digite seu Endereço ou ENTER para pular:\n");
                                ler_str(novopaciente->endereco);
                                informacao_nao_obrigatoria = cadastro_informacao_nao_obrigatorio(novopaciente->endereco);
                                
                                printf("Digite a Data de Nascimento do Paciente:\n");
                                receber_data2(novopaciente->data_nascimento);
                                
                                if(novo) qnt_novos_pacientes++;
                                if(!novo) pacientes_alterados[index] = 1;
                                qnt_alteracoes++;
                                novopaciente->ativo=1;
                                exibe_informacoes_paciente2(novopaciente);
                                
                                if(!coletar_opcao("Incluir novo paciente", "Voltar ao Menu Pacientes")) {continue;}
                                else {break;}
                            }
                            break;
                        case 2:
                            system("clear");
                            printf("\nOpção -> "BLUE"[2], \"Alterar um Paciente Existente\""RESET" Selecionada...\n\n");
                            while(1) {
                                printf("Digite o Código do Paciente que Deseja Alterar: \n\n");

                                printf("-> Código: ");
                                char alterar_paciente_codigo[9];
                                scanf("%s", &alterar_paciente_codigo);
                                paciente * paciente_a_alterar;
                                int index = 0;
                                index = procura_codigo_paciente2(alterar_paciente_codigo,pacientes, qnt_pacientes);

                                if(index<0) {
                                    index =procura_codigo_paciente2(alterar_paciente_codigo,novospacientes,qnt_novos_pacientes);
                                    if(index < 0){
                                        printf(RED"\nPaciente de Código %s NÃO Encontrado Verifique o Código Inserido!\n"RESET, alterar_paciente_codigo);
                                        if(!coletar_opcao("Inserir Novo Código", "Ir para o Menu Pacientes")) {continue;}
                                        else {break;}
                                    }
                                    printf("Paciente %s encontrado, mas ainda não salvo no arquivo",pacientes);  
                                    if(!coletar_opcao("Inserir Novo Código", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }else{paciente_a_alterar = &pacientes[index];}
                                
                                printf(GREEN" ---> Paciente %s de Código %s Encontrado\n"RESET, paciente_a_alterar->nome,paciente_a_alterar->codigo);
                                printf("\nQual Informação Você deseja alterar?\n");
                                printf(BLUE"[1] Nome     [2] RG     [3] CPF     [4] Tipo Sanguíneo     [5] Fator RH     [6] Endereço     [7] Data de Nascimento\n"RESET);
                                int alteracao_desejada;
                                int saida=0;
                                scanf("%d", &alteracao_desejada);

                                switch (alteracao_desejada) {  
                                    case 1:
                                        printf(BLUE"\nOpção -> [1], \"Alterar Nome\""RESET" Selecionada...\n\n");
                                        char novo_nome[40];    
                                        if(cadastra_nome_paciente2(novo_nome, pacientes, qnt_pacientes)) {
                                            if(!coletar_opcao("Alterar outro paciente", "Ir para o Menu Pacientes")) {saida=1;}
                                            else {saida=2;}
                                            break;
                                        }
                                        strcpy(paciente_a_alterar->nome,novo_nome);
                                
                                        printf(GREEN"\nNome Alterado com Sucesso!\n"RESET);
                                        qnt_alteracoes++;
                                        break;
                                    case 2:
                                        printf(BLUE"\nOpção -> [2], \"Alterar RG\""RESET" Selecionada...\n\n");
                                        char novo_rg[40]; 
                                        cadastra_documento2("RG", novo_rg);
                                        if(procura_informacao2(novo_rg, pacientes, qnt_pacientes, 2,index)) { 
                                            printf(RED"RG já cadastrado --> Impossível Inserir este Paciente!\n"RESET);

                                            if(!coletar_opcao("Alterar outro paciente", "Ir para o Menu Pacientes")) {saida=1;}
                                            else {saida=2;}
                                            break;
                                        }
                                        strcpy(paciente_a_alterar->RG,novo_rg);
                                        printf(GREEN"\nRG Alterado com Sucesso!\n"RESET);
                                        qnt_alteracoes++;
                                        break;
                                    case 3:
                                        printf(BLUE"\nOpção -> [3], \"Alterar CPF\""RESET" Selecionada...\n\n");
                                        char novo_cpf[40]; 
                                        cadastra_documento2("CPF", novo_cpf);
                                        if(procura_informacao2(novo_cpf, pacientes, qnt_pacientes,3,index)) { 
                                            printf(RED"CPF já cadastrado --> Impossível Inserir este Paciente!\n"RESET);
                                            
                                            if(!coletar_opcao("Alterar outro paciente", "Ir para o Menu Pacientes")) {saida=1;}
                                            else {saida=2;}
                                            break;
                                        }
                                        strcpy(paciente_a_alterar->CPF,novo_cpf);
                                        printf(GREEN"\nCPF Alterado com Sucesso!\n"RESET);
                                        qnt_alteracoes++;
                                        break;
                                    case 4:
                                        printf("\nOpção -> "BLUE"[4], \"Alterar Tipo Sanguíneo\""RESET" Selecionada...\n\n");

                                        cadastrar_tipo_sanguineo(paciente_a_alterar->tipo_sanquineo);
                                        
                                        printf(GREEN"\nTipo sanguíneo Alterado com Sucesso!\n"RESET);
                                        qnt_alteracoes++;

                                        break;
                                    case 5:
                                        printf("\nOpção -> "BLUE"[5], \"Alterar Fator RH\""RESET" Selecionada...\n\n");

                                        cadastrar_fator_rh(paciente_a_alterar->fator_RH);

                                        printf(GREEN"Fator RH Alterado com Sucesso!\n"RESET);
                                        qnt_alteracoes++;
                                        break;
                                    case 6:
                                        printf("\nOpção -> "BLUE"[6], \"Alterar Endereço\""RESET" Selecionada...\n\n");

                                        printf("Digite seu Endereço:\n");
                                        ler_str(paciente_a_alterar->endereco);

                                        printf(GREEN"Endereço Alterado com Sucesso!\n"RESET);
                                        qnt_alteracoes++;
                                        break;
                                    case 7:
                                        printf("\nOpção -> "BLUE"[7], \"Alterar Data de Nascimento\""RESET" Selecionada...\n\n");

                                        printf("Digite a Data de Nascimento do Paciente:\n");
                                        receber_data2(paciente_a_alterar->data_nascimento);

                                        printf(GREEN"Data de Nascimento Alterado com Sucesso!\n"RESET);
                                        qnt_alteracoes++;
                                        break;
                                    default:
                                        printf("Selecione alguma das opções anteriores!\n");
                                        break;
                
                                }
                                if(saida == 1)continue;
                                if(saida == 2)break;
                                pacientes_alterados[index]=1;
                                qnt_pacientes_alterados++;
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
                                paciente* paciente_a_excluir;
                                int index = 0;
                                index = procura_codigo_paciente2(codigo_paciente_excluido,pacientes, qnt_pacientes);

                                if(index<0) {
                                    index =procura_codigo_paciente2(codigo_paciente_excluido,novospacientes,qnt_novos_pacientes);
                                    if(index < 0){
                                        printf(RED"\nPaciente de Código %s NÃO Encontrado Verifique o Código Inserido!\n"RESET, codigo_paciente_excluido);
                                        if(!coletar_opcao("Inserir Novo Código", "Ir para o Menu Pacientes")) {continue;}
                                        else {break;}
                                    }
                                    printf("Paciente %s encontrado, mas ainda não salvo no arquivo");  
                                    if(!coletar_opcao("Inserir Novo Código", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }else{paciente_a_excluir = &pacientes[index];}
                                
                                printf(GREEN"---> Paciente de Código %s Encontrado\n"RESET, codigo_paciente_excluido);
                                exibe_informacoes_paciente2(paciente_a_excluir);

                                printf(RED"\nDeseja Excluir esse paciente?\n"RESET);
                                if(!coletar_opcao("Confirmar Exclusão", "Voltar para o Menu Pacientes")) {
                                    paciente_a_excluir->ativo = 0;
                                    printf(GREEN"Paciente Excluído com Sucesso! Salve as alterações para confirmar!\n"RESET);
                                    pacientes_alterados[index]=1;
                                    qnt_pacientes_alterados++;
                                    qnt_alteracoes++;
                                    int qnt;
                                    for(int i=0; i<qnt_atendimentos;i++){
                                        if(strcmp(paciente_a_excluir->codigo,atendimentos[i].codigo_paciente) == 0){
                                            atendimentos[i].ativo = 0;
                                            qnt++;
                                        }
                                    }
                                    printf("O paciente tinha %d atendimentos cadastrados",qnt);
                                }
                                if(!coletar_opcao("Excluir outro paciente", "Ir para o Menu Pacientes")) {continue;}
                                else {break;}
                            }
                            break;
                        case 4:
                            printf("\nOpção -> "BLUE"[4], \"Exibir os Dados de um Paciente pelo seu Código\""RESET" Selecionada...\n\n");

                            while(1) {
                                printf("Digite o Código do Paciente: ");
                                char exibir_dados_codigo[9];
                                scanf("%s", &exibir_dados_codigo);

                                paciente* paciente_a_exibir;
                                int index = 0;
                                index = procura_codigo_paciente2(exibir_dados_codigo,pacientes, qnt_pacientes);

                                if(index<0) {
                                    index =procura_codigo_paciente2(exibir_dados_codigo,novospacientes,qnt_novos_pacientes);
                                    if(index < 0){
                                        printf(RED"\nPaciente de Código %s NÃO Encontrado Verifique o Código Inserido!\n"RESET, exibir_dados_codigo);
                                        if(!coletar_opcao("Inserir Novo Código", "Ir para o Menu Pacientes")) {continue;}
                                        else {break;}
                                    }
                                    printf(RED"Paciente %s encontrado, mas ainda não salvo no arquivo"RESET);
                                }else{paciente_a_exibir = &pacientes[index];}
                                exibe_informacoes_paciente2(paciente_a_exibir);
                                if(!coletar_opcao("Exibir outro paciente", "Ir para o Menu Pacientes")) {continue;}
                                else {break;}

                            }
                            break;
                        case 5:
                            printf("\nOpção -> "BLUE"[5], \"Exibir os Dados de Pacientes que Apresentam o Mesmo"
                                " Tipo Sanguíneo\""RESET" Selecionada...\n\n");
                            
                            char tp_sanguineo_selecionado[3];   
                            cadastrar_tipo_sanguineo(tp_sanguineo_selecionado);
                            exibe_tipo_sanguineo_pacientes(tp_sanguineo_selecionado,qnt_pacientes,pacientes);
                            if(!coletar_opcao("Voltar para o menu", "\0")) {break;}
                            else {break;}
                            break;
                        case 6:
                            while(1) {
                                printf("\nOpção -> "BLUE"[6], \"Exibir os Dados de Pacientes pelo Dia de "
                                       "Consulta\""RESET" Selecionada...\n\n");

                                printf("Digite a Data da Consulta, para Exibir os Dados do(s) Paciente(s):\n");

                                char data[40];
                                receber_data2(data);
                                
                                int count = 0;
                                for(int i = 0; i < qnt_atendimentos; i++) {                                    
                                    if(strcmp(atendimentos[i].data,data)) {
                                        paciente *paciente_atendimento;
                                        paciente_atendimento = &pacientes[procura_informacao2(atendimentos[i].codigo_paciente,pacientes,qnt_pacientes,2,-1)];
                                        printf(YELLOW"\n---> Data com Consulta do Paciente: %s"RESET, paciente_atendimento->nome);
                                        exibe_informacoes_paciente2(paciente_atendimento);
                                        count++;
                                    }
                                }

                                if(!count)
                                    printf(RED"Sem Consultas para essa Data!\n"RESET);

                                if(!coletar_opcao("Inserir Outra Data", "Ir para o Menu Pacientes")) {continue;}
                                else {break;}
                            }  //precisa testar
                            break;
                        case 7:
                            while(1) {
                                printf("\nOpção -> "BLUE"[7], \"Exibir Todos os Pacientes\""RESET" Selecionada...\n\n");

                                exibir_todos_pacientes2(pacientes,qnt_pacientes);

                                if(!coletar_opcao("Exibir todos os Pacientes Novamente", "Ir para o Menu Pacientes")) {continue;}
                                else {break;}
                            }
                            break;
                        case 8:
                            printf("\nOpção -> "BLUE"[8], \"Exibir Todos os Pacientes em Ordem"
                                   " Alfabética\""RESET" Selecionada...\n\n");

                            int* ordem_pacientes = malloc(qnt_pacientes * sizeof(int));
                            ordenar_pacientes(pacientes,ordem_pacientes,qnt_pacientes);
                            int qnd_pac_ativos=0;
                            for(int i=0;i<qnt_pacientes;i++){
                                if(pacientes[i].ativo==1)qnd_pac_ativos++;
                            }
                            if(qnd_pac_ativos==0){
                                printf(RED"Nenhum Atendimento Cadastrado"RESET);
                            }
                            for(int i=0;i < qnd_pac_ativos;i++){
                            int index = ordem_pacientes[i];
                            exibe_informacoes_paciente2(&pacientes[index]);

                            }
                            if(coletar_opcao("Sair","Exibir Atendimentos Novamente"))continue;
                            else break;
                        case 9:
                            while(1) {
                                printf("\nOpção -> "BLUE"[9], \"Exibir a Soma das Consultas Pagas por um Determinado Paciente\""RESET" Selecionada...\n\n");

                                printf("Digite o Nome do Paciente, para ver a soma das suas Consultas Pagas: ");

                                char nome[40];
                                ler_str(nome);
                                formata_string_maisculo(nome);
                                float soma_consultas = 0;

                                if(ja_existe(nome,pacientes,qnt_pacientes)) {

                                    soma_consultas = soma_consultas_pagas_pacientes(nome,atendimentos,qnt_atendimentos);
                                    printf(GREEN"--> Soma das Consultas do Paciente %s = %.2f\n"RESET, nome, soma_consultas);

                                    if(!coletar_opcao("Selecionar Outro Paciente", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }
                                else {
                                    printf(RED"Paciente %s NÃO Cadastrado\n"RESET, nome);

                                    if(!coletar_opcao("Selecionar Outro Paciente", "Ir para o Menu Pacientes")) {continue;}
                                    else {break;}
                                }
                            }
                            break;
                        case 10:
                            printf("\nOpção -> "BLUE"[10], \"Voltar para o Menu Anterior\""RESET" Selecionada...\n\n");
                            break;
                        case 11:
                            salvar(pacientes,atendimentos,pacientes_alterados,atendimentos_alterados,qnt_pacientes,qnt_atendimentos);
                            salvar_novos(pacientes,atendimentos,&novospacientes,&novos_atendimentos,qnt_novos_pacientes,qnt_novos_atendimentos,qnt_pacientes,qnt_atendimentos);
                            
                            free(pacientes);
                            free(pacientes_alterados);
                            qnt_novos_pacientes=0;
                            qnt_pacientes_alterados=0;
                            
                            pacientes = ler("pacientes.bin",&qnt_pacientes,sizeof(paciente));
                            pacientes_alterados= malloc(qnt_pacientes * sizeof(int));
                            preenche_vetor_ativos(pacientes_alterados,qnt_pacientes);
                            
                            free(atendimentos);
                            free(atendimentos_alterados);
                            qnt_novos_atendimentos=0;
                            qnt_atendimentos_alterados=0;
    
                            atendimentos = ler("atendimentos.bin",&qnt_atendimentos,sizeof(atendimento));
                            atendimentos_alterados= malloc(qnt_atendimentos * sizeof(int));
                            preenche_vetor_ativos(atendimentos_alterados,qnt_atendimentos);
                            
                            qnt_alteracoes=0;
                            printf(GREEN"Alterações Salvas! \n"RESET);
                            break;
                        default:
                            printf(RED"\nSelecione alguma das opções anteriores!\n"RESET);
                            break;
                    }
                    if(interacao_menu_pacientes== 10){break;}
                    //continue;
                }break;

            case 2:
                system("cls");
                printf(BLUE"\nMenu \"Atendimento\" Selecionado...\n"RESET);
                while(1) {
                    if(qnt_alteracoes) {printf(RED"VOCÊ POSSUI %d ALTERACOES NÃO SALVAS!\n"RESET, qnt_alteracoes);}

                    int interacao_menu_atendimentos = menu_atendimento();
                    int espaco_livre;
                    int indice_do_paciente;

                    switch (interacao_menu_atendimentos) {
                        case 1:
                            system("clear");
                            while (1) {
                                printf("\nOpção -> "BLUE"[1], \"Inserir um Novo Atendimento\""RESET" Selecionada...\n\n");

                                atendimento *novo_atendimento;

                                int eh_novo = 0;
                                int ja_arquivado = procura_atendimento_livre(atendimentos,qnt_atendimentos);

                                if(ja_arquivado < 0) {
                                    novo_atendimento = &novos_atendimentos[qnt_novos_atendimentos];
                                    eh_novo = 1;
                                }else{novo_atendimento = &atendimentos[ja_arquivado];}

                                printf("Digite o Codigo do Paciente: \n");
                                ler_str(novo_atendimento->codigo_paciente);

                                if (!procura_paciente(pacientes, qnt_pacientes, novo_atendimento->codigo_paciente)) {
                                    printf(RED"Paciente não cadastrado ou não Salvo!\n"RESET);
                                    if (coletar_opcao("Inserir outro paciente", "Voltar ao menu de atendimentos")) {
                                        break;
                                    } else {continue;}
                                }

                                printf("\nPaciente "GREEN" %s"RESET"  Selecionado...\n",
                                       novo_atendimento->codigo_paciente);

                                printf(BLUE"Dados da consulta:\n"RESET);
                                //receber_data(data_atendimentos,espaco_livre);

                                int data_ja_cadastrada=atendimento_ja_cadastrado(data_atendimentos,paciente_do_atendimento,espaco_livre,QNTD_ATENDIMENTOS);
                                if(data_ja_cadastrada)continue;

                                receber_data2(novo_atendimento->data);

                                novo_atendimento->preco = receber_preco();

                                receber_status_atendimento(novo_atendimento);

                                do {
                                    cria_codigo2(novo_atendimento->codigo_atendimento);
                                }while(verifica_codigo_atendimento(atendimentos, novo_atendimento->codigo_atendimento, qnt_atendimentos));

                                receber_tipo_atendimento(novo_atendimento);

                                novo_atendimento->ativo = 1;
                                qnt_alteracoes++;
                                exibir_dados_atendimento(novo_atendimento);
                                printf(" %s",novos_atendimentos[qnt_novos_atendimentos].codigo_atendimento);

                                if(eh_novo) {qnt_novos_atendimentos++;}
                                else {atendimentos_alterados[ja_arquivado] = 1;}

                                printf(GREEN"* Atendimento Cadastrado com sucesso! *\n"RESET);

                                if (coletar_opcao("Voltar ao Menu Atendimento", "Inserir outro Atendimento"))continue;
                                else {break;}
                            }
                            break;
                        case 2:
                            system("cls");

                            while (1) {
                                printf("\nOpção -> "BLUE"[2], \"Alterar um Atendimento Existente\""RESET" Selecionada...\n\n");

                                printf("Digite o código do atendimento que deseja alterar:\n");

                                int indice_do_atendimento = procura_atendimento2(atendimentos, qnt_atendimentos);
                                if (indice_do_atendimento == -1) {
                                    if (coletar_opcao("Tentar alterar outro atendimento",
                                                      "Voltar ao menu atendimento")) { break; }
                                    else {continue;}
                                }

                                atendimento *atendimento_alterado = &atendimentos[indice_do_atendimento];
                                exibir_dados_atendimento(atendimento_alterado);

                                int opcao;
                                printf("Qual dado deseja alterar?\n");
                                printf(BLUE"[1]"RESET"Paciente "BLUE"[2] "RESET"Data "BLUE"[3] "RESET"Tipo "BLUE"[4]"RESET" Preço "BLUE"[5]"RESET"Status\n");
                                scanf("%d", &opcao);

                                switch (opcao) {
                                    case 1:
                                        printf("\nPaciente anterior : %s \n", atendimento_alterado->codigo_paciente);
                                        char paciente_antigo[40];
                                        strcpy(paciente_antigo, atendimento_alterado->codigo_paciente);

                                        printf("--> Digite o codigo do paciente que deseja trocar:\n");
                                        ler_str(atendimento_alterado->codigo_paciente);

                                        //trocar "teste_paciente" por pacientes e 2 por qntd_pacientes na funcao abaixo!
                                        if (!procura_paciente(pacientes, qnt_pacientes,atendimento_alterado->codigo_paciente)) {
                                            printf(RED"Paciente nao cadastrado!\n"RESET);

                                            if (coletar_opcao("Inserir outro paciente",
                                                              "Voltar ao menu de atendimentos")) {
                                                break;
                                            } else {continue;}
                                        }
                                        /*
                                        int data_ja_cadastrada=atendimento_ja_cadastrado(data_atendimentos,indice_novo_paciente,espaco_livre,QNTD_ATENDIMENTOS);
                                        if(data_ja_cadastrada)continue;
                                        */
                                        printf("Paciente anterior = %s --> Novo paciente = \"GREEN\"%s\"RESET\"\n", paciente_antigo,
                                               atendimento_alterado->codigo_paciente);
                                        printf(GREEN"* Paciente do atendimento Alterado com Sucesso! *\n"RESET);

                                        break;
                                    case 2:
                                        break;
                                        /*
                                    case 2:
                                        printf("Digite a nova data:\n");
                                        receber_data(data_atendimentos,indice_do_atendimento);
                                        printf(GREEN"Nova data cadastrada: %s\n"RESET,data_atendimentos[indice_do_atendimento]);
                                        break;
                                         */
                                    case 3:
                                        receber_tipo_atendimento(atendimento_alterado);

                                        printf("\n--> Novo Tipo = \"GREEN\"%s\"RESET\"\n", atendimento_alterado->tipo);
                                        printf(GREEN"* Novo tipo cadastrado com Sucesso! *\n"RESET);
                                        break;
                                                //3KPKJCMD//UU58FE9O
                                    case 4:
                                        printf("Digite o novo preço da consulta:\n");

                                        atendimento_alterado->preco = receber_preco();
                                        printf(GREEN"Novo preço cadastrado --> "GREEN"R$%.2f"RESET"\n"RESET, atendimento_alterado->preco);
                                        break;
                                    case 5:
                                        printf("Digite o novo status do atendimento:");

                                        receber_status_atendimento(atendimento_alterado);
                                        printf("--> Novo Status = "GREEN"%s"RESET"\n", atendimento_alterado->status);
                                        printf(GREEN"* Status alterado com Sucesso! *\n"RESET);
                                        break;
                                    default:
                                        printf("Selecione apenas as opções acima!\n");
                                        break;
                                }
                                if(opcao >= 1 || opcao <= 5) {
                                    novos_atendimentos[qnt_novos_atendimentos] = *atendimento_alterado;
                                    qnt_novos_atendimentos++;
                                }
                                if(coletar_opcao("Voltar","Alterar outro Atendimento")){continue;}
                                else {break;}
                            }
                            break;
                        case 3:
                            while (1) {
                                printf("\nOpção -> "BLUE"[3], \"Excluir um Atendimento\""RESET" Selecionada...\n\n");

                                printf("-> Digite o Atendimento que você deseja Excluír:");
                                int indice_do_atendimento = procura_atendimento2(atendimentos,qnt_atendimentos);
                                if (indice_do_atendimento == -1) {
                                    if (coletar_opcao("Tentar alterar outro atendimento",
                                                      "Voltar ao menu atendimento")) {break;}
                                    else {continue;}
                                }

                                atendimento *atendimento_solicitado = &atendimentos[indice_do_atendimento];
                                exibir_dados_atendimento(atendimento_solicitado);

                                printf("Tem certeza que deseja"RED" Excluir este Atendimento?"RESET"\n");
                                if (coletar_opcao("Cancelar Operação", "Excluir Atendimento")) {
                                    atendimento_solicitado->ativo = 0;
                                    strcpy(atendimento_solicitado->codigo_atendimento, "EXLUIDO");
                                    strcpy(atendimento_solicitado->codigo_paciente, "EXLUIDO");

                                    novos_atendimentos[qnt_novos_atendimentos] = *atendimento_solicitado;
                                    qnt_novos_atendimentos++;
                                    printf(GREEN"* Atendimento Excluído *\n"RESET);
                                    break;
                                }
                                printf(GREEN"* Operacão Cancelada com Sucesso! *"RESET);
                            }
                            break;
                        case 4:
                            while (1) {
                                system("cls");
                                printf("\nOpção -> "BLUE"[4], \"Exibir os Dados de um Atendimento com base no seu código\""RESET" Selecionada...\n\n");

                                printf("Digite o código do atendimento que deseja consultar:\n");

                                int indice_do_atendimento = procura_atendimento2(atendimentos,qnt_atendimentos);
                                if (indice_do_atendimento < 0) {
                                    printf(RED"* Atendimento não encontrado *\n"RESET);
                                    if (coletar_opcao("Tentar alterar outro atendimento","Voltar ao menu atendimento")) {break;}
                                    else {continue;}
                                }

                                exibir_dados_atendimento(&atendimentos[indice_do_atendimento]);

                                if (coletar_opcao("Voltar", "Exibir outro Atendimento")) {continue;}
                                else {break;}
                            }
                            break;
                        case 5:
                            while (1) {
                                printf("\nOpção -> "BLUE"[5], \"Exibir Todos os Atendimentos de um Paciente com base no seu código\""RESET" Selecionada...\n\n");

                                char codigo_paciente[8];
                                printf("-> Digite o codigo do paciente para exibir todos os seus atendimentos:");
                                ler_str(codigo_paciente);

                                if (!procura_paciente(pacientes, qnt_pacientes, codigo_paciente)) {
                                    printf(RED"Paciente não cadastrado ou não Salvo!\n"RESET);
                                    if (coletar_opcao("Inserir outro paciente", "Voltar ao menu de atendimentos")) {
                                        break;
                                    } else {continue;}
                                }
                                printf("\nPaciente "GREEN" %s"RESET"  Selecionado...\n", codigo_paciente);

                                int conta_atendimentos = 0;
                                for(int i = 0; i < qnt_pacientes; i++) {
                                    if(!strcmp(codigo_paciente, atendimentos[i].codigo_paciente)) {
                                        printf("* Atendimento:\n");
                                        exibir_dados_atendimento(&atendimentos[i]);
                                        conta_atendimentos++;
                                    }
                                }
                                if(!conta_atendimentos){printf(YELLOW"Paciente %s sem nenhum atendimento ativo!\n"RESET, codigo_paciente);}

                                if (coletar_opcao("Voltar", "Exibir Atendimentos de outro paciente"))continue;
                                else break;
                            }
                            break;
                        case 6:
                            while (1) {
                                float soma = 0;
                                int count = 0;

                                system("cls");
                                printf("\nOpção -> "BLUE"[6], \"Exibir Todos os Atendimentos e seu Somatório Total Diário\""RESET" Selecionada...\n\n");

                                char atendimentos_do_dia[1][40];
                                printf("Digite a data que você deseja acessar as informações:");
                                receber_data2(atendimentos_do_dia[0]);

                                for (int i = 0; i < qnt_atendimentos; i++) {
                                    if (!strcmp(atendimentos_do_dia[0], atendimentos[i].data)) {
                                        exibir_dados_atendimento(&atendimentos[i]);

                                        soma += atendimentos[i].preco;
                                        count++;
                                    }
                                }
                                if (!count) {
                                    printf(RED"* Nenhum atendimento neste dia! *\n\n"RESET);
                                    if (coletar_opcao("Sair", "Exibir Atendimentos de Outro Dia")) {continue;}
                                    else {break;}
                                }
                                printf(GREEN"--> Total de Consultas Pagas no Dia[%d] = R$%.2f\n\n"RESET,count, soma);

                                if (coletar_opcao("Sair", "Selecionar outro dia")) {continue;}
                                else {break;}
                            }
                            break;
                        case 7: //Parei aqui
                            while (1) {
                                system("clear");
                                printf("\nOpção -> "BLUE"[6], \"Exibir os Atendimentos em Ordem de Data de Atendimento\""RESET" Selecionada...\n\n");

                                int ordem_datas[100];
                                ordenar_datas(data_atendimentos, ordem_datas, QNTD_ATENDIMENTOS,
                                              atendimentos_ativos);
                                int qnd_atend_ativos = 0;
                                for (int i = 0; i < QNTD_ATENDIMENTOS - 1; i++) {
                                    if (atendimentos_ativos[i] == 1)qnd_atend_ativos++;
                                }
                                if (qnd_atend_ativos == 0) {
                                    printf(RED"Nenhum Atendimento Cadastrado"RESET);
                                }
                                for (int i = 0; i < qnd_atend_ativos; i++) {
                                    int atendimento = ordem_datas[i];
                                    int paciente = paciente_do_atendimento[i];
                                    //exibir_dados_atendimento(codigo_atendimentos,nomes_pacientes,codigo_pacientes,paciente,data_atendimentos,tipo_atendimentos,preco_atendimentos,status_atendimentos,atendimento);
                                }
                                if (coletar_opcao("Sair", "Exibir Atendimentos Novamente"))continue;
                                else break;
                            }
                            break;
                        case 8:
                            printf("\nOpção -> [8], \"Exibir o Somatório dos Atendimentos pagos de um\n"
                                   "determinado período de atendimento.\" Selecionada...\n\n");
                            break;
                        case 9:
                            printf("\nOpção -> [9], \"Voltar para o Menu Anterior\" Selecionada...\n\n");
                            break;
                        case 10:
                            printf("\nOpção -> [10], \"Salvar Atendimentos Pendentes\" Selecionada...\n\n");

                            salvar(pacientes,atendimentos,pacientes_alterados,atendimentos_alterados,qnt_pacientes,qnt_atendimentos);
                            salvar_novos(pacientes,atendimentos,&novospacientes,&novos_atendimentos,qnt_novos_pacientes,qnt_novos_atendimentos,qnt_pacientes,qnt_atendimentos);

                            free(pacientes);
                            free(pacientes_alterados);
                            qnt_novos_pacientes=0;
                            qnt_pacientes_alterados=0;

                            pacientes = ler("pacientes.bin",&qnt_pacientes,sizeof(paciente));
                            pacientes_alterados= malloc(qnt_pacientes * sizeof(int));
                            preenche_vetor_ativos(pacientes_alterados,qnt_pacientes);

                            free(atendimentos);
                            free(atendimentos_alterados);
                            qnt_novos_atendimentos=0;
                            qnt_atendimentos_alterados=0;

                            atendimentos = ler("atendimentos.bin",&qnt_atendimentos,sizeof(atendimento));
                            atendimentos_alterados= malloc(qnt_atendimentos * sizeof(int));
                            preenche_vetor_ativos(atendimentos_alterados,qnt_atendimentos);

                            qnt_alteracoes = 0;
                            printf(GREEN"Alterações Salvas! \n"RESET);
                            for(int i = 0; i < qnt_atendimentos; i++) {
                                exibir_dados_atendimento(&atendimentos[i]);
                            }
                            break;
                            default:
                                printf(RED"\nSelecione alguma das opções anteriores!\n"RESET);
                            break;
                    }
                        if (interacao_menu_atendimentos == 9){break;}
                }
                    continue;
            case 3:
                if(qnt_alteracoes!=0) {
                    printf(RED"Você possui alteracoes pendentes. Deseja encerrar mesmo assim?\n"RESET);
                    if(!coletar_opcao("Sair sem salvar","Voltar e Salvar"))return 0;
                    else break;;
                }
                printf(GREEN"\nSaída do Sistema Confirmada!\n"RESET);
                return 0;
            default:
                printf(RED"Selecione alguma das opções anteriores!\n"RESET);
                break;
        }
    }
    free(pacientes);
    free(atendimentos);
    free(pacientes_alterados);
    free(atendimentos_alterados);
    return 0;
}