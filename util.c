#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CIANO   "\x1b[36m"
#define RESET   "\x1b[0m"

#include "util.h"

int menu_principal() {
    printf(BLUE"\n******************************************\n"RESET);
    printf("\n"BLUE"*"RESET YELLOW"Seja Muito Bem vindo(a) a Clinica Fatima"RESET BLUE"*\n"RESET);
    printf(BLUE"\n******************************************\n"RESET);

    printf(YELLOW"\nSelecione como você deseja acessar nosso sistema: \n"RESET);
    printf(BLUE"[1]"RESET "Paciente");
    printf(BLUE" \t[2] "RESET"Atendimento\t");
    printf(BLUE"\t[3]"RESET" Encerrar\n");

    while(1) {
        int interacao_menu_pacientes;

        fflush(stdin);
        interacao_menu_pacientes = getchar();

        switch (interacao_menu_pacientes)
        {
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '\n':
            break;
        default:
            printf(RED"Selecione uma das opções anteriores!\n"RESET);
            break;
        };
    }
}

int coletar_opcao(char opcao1[],char opcao2[]){
    while(1) {
        char opcao;
        printf(BLUE"[0]"RESET" %s  ",opcao1);
        if(strcmp(opcao2,"\0") != 0)printf(BLUE"[1]"RESET" %s \n",opcao2);
        else{printf("\n");}
        
        printf(BLUE);
        fflush(stdin);  
        opcao = getchar();
        printf(RESET);
        
        switch(opcao){
            case '0':
                printf("\nOpção -> "BLUE"[0], \"%s\""RESET" Selecionada...\n", opcao1);
                return 0;
            case '1':
                printf("\nOpção -> "BLUE"[1], \"%s\""RESET" Selecionada...\n", opcao2); 
                return 1;
            case '\n':
                break;
            default:
                printf(RED"Digite Apenas 0 ou 1\n"RESET);
                break;
        }
    }
}
int preenche_vetor_ativos(int vetor_ativos[], int tamanho_vetor) {
    for (int i = 0; i < tamanho_vetor; i++)
        vetor_ativos[i] = 0;
}

// void* procura_paciente_livre(paciente* vetordestructs, int tamanho_vetor) {
//     for (int i = 0; i < tamanho_vetor; i++) {

//         if(vetordestructs[i].ativo) {
//             return &vetordestructs[i];
//         }
//     }
//     return NULL;
// }
int procura_espaco_livre(int vetor_ativos[], int tamanho_vetor) {
    for (int i = 0; i < tamanho_vetor; i++) {

        if(!vetor_ativos[i]) {
            return i;
        }
    }
    return -1;
}

void ler_str(char* string) {
    printf(BLUE);
    fflush(stdin);  
    gets(string);
    fflush(stdin);
    printf(RESET);
}
int checar_string(char string[]){
    if(string == NULL || string[0] =='\0'){
        return 1;
    }
    for(int i = 0; string[i] != '\0';i++){
        if(string[i] == ' '){
            continue;
        }
        if(isdigit(string[i]) || !isalnum(string[i])){
          return 1;  
        }
    }return 0;
}

void formata_string_maisculo(char string[]) {
    int string_tamanho = strlen(string);

    for (int i = 0; i < string_tamanho; ++i)
        string[i] = toupper(string[i]);
}

// int ja_existe(char* string,paciente*pacientes,int tamanho){
//     for(int i = 0; i < tamanho; i++){
//         if(strcmp(string,pacientes[i].nome_paciente) == 0){
//             return 1;
//         }
//     }return 0;
// }
int procura_string(char string[],char vetor[][40],int tamanho){
    for(int i = 0; i < tamanho; i++){
        if(strcmp(string,vetor[i]) == 0){
            return i;
        }
    }return -1;
}


int procura_codigo(char codigo_unico_paciente[],char matriz_codigos_pacientes[][8],int tamanho_matriz) {
    for(int i = 0; i < tamanho_matriz; i++){
        if(!strcmp(matriz_codigos_pacientes[i],codigo_unico_paciente)) {
            return i;
        }

    }
    return -1;
}


int procura_codigo_atendimento(char codigo_atendimento_comparado[], int qntd_atendimentos, char atendimento_solicitado[]) {
        if(!strcmp(codigo_atendimento_comparado, atendimento_solicitado)) {
            return 1;
        }
    return 0;
}


void receber_data_atendimento(char* data) {
    int dia, mes, ano;

    while (1) {
        printf(BLUE"Digite o dia: "RESET);
        scanf("%d", &dia);

        printf(BLUE"Digite o mês: "RESET);
        scanf("%d", &mes);

        printf(BLUE"Digite o ano (ex. 2024): "RESET);
        scanf("%d", &ano);

        int ano_bisexto = (ano % 4 == 0) && ((ano % 100 != 0) || (ano % 400 == 0));
        int dias_no_mes = 31;
        if(ano == 2023){
            printf("Fim de ano, Vamos festejar! --> * Marque conosco a partir de 2024! *\n");
            continue;
        }
        if (mes < 1 || mes > 12 || ano <= 2023) {
            printf(RED"Data inválida!\n"RESET);
            continue;
        }

        if (mes == 2) {
            if(ano_bisexto) {dias_no_mes = 29;}
            else{dias_no_mes = 28;}
        } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
            dias_no_mes = 30;
        }

        if (dia < 1 || dia > dias_no_mes) {
            printf(RED"Data inválida!\n"RESET);
            continue;
        }

        sprintf(data, "%02d/%02d/%04d", dia, mes, ano);
        return;
    }

} 
int validar_data(int dia, int mes, int ano) {
    if (dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 1900) {
        return 1;  // Data válida
    } else {
        printf("Data inválida!\n");
        return 0;  // Data inválida
    }
}

void receber_data2(char* data) {
    int dia, mes, ano;

    while (1) {
        printf(BLUE"Digite a data no formato DD/MM/AAAA: "RESET);

        fflush(stdin);
        if (scanf("%2d/%2d/%4d", &dia, &mes, &ano) != 3) {
            printf("Formato de data inválido! Certifique-se de digitar a data no formato DD/MM/AAAA.\n");

        } else if (!validar_data(dia, mes, ano)) {
            continue;
        } else {
            sprintf(data, "%02d/%02d/%04d", dia, mes, ano);
            break;
        }
    }
}


void imprimir_vetor(char vetor[][40],int tamanho){
    for(int i=0;i<tamanho;i++){
        printf("%d - %s\n",i,vetor[i]);
    }
}
void imprimir_vetor_codigos(char vetor[][8],int tamanho){
    for(int i=0;i<tamanho;i++){
        printf("%d - %s\n",i,vetor[i]);
    }
}

void cria_codigo(char vetor[][8],int indice_livre){
    char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";//36 caracteres
    char novo_codigo[8];
    
    srand(time(NULL));

    for(int i = 0; i < 8; i++) {
        if(i==7)break;
        int indice_aleatorio = rand() % 36;
        novo_codigo[i] = caracteres[indice_aleatorio];
    }
    novo_codigo[8]='\0';
    strcpy(vetor[indice_livre],novo_codigo);
}
void cria_codigo2(char* codigo) {
    char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char novo_codigo[9];

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 8; i++) {
        int indice_aleatorio = rand() % 36;
        novo_codigo[i] = caracteres[indice_aleatorio];
    }

    novo_codigo[8] = '\0';

    strcpy((char*)codigo, novo_codigo);
}

void copia_matriz(char matriz1[][40], char matriz2[][40], int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        strcpy(matriz1[i], matriz2[i]);
    }
}


int varrer_datas(char data[][40], char matriz_datas_atendimentos_copia[][40], int tam_matriz_datas_atendimentos) {
    for(int i = 0; i < tam_matriz_datas_atendimentos; i++) {
        int compara_datas = !strcmp(data, matriz_datas_atendimentos_copia[i]);

        if(compara_datas) {
            return i;
        }
    }
    return -1;
}

FILE* abrir_arquivo(const char nome[], const char modo[]){
    FILE *arquivo = fopen(nome,modo);
    if(arquivo == NULL){
        arquivo= fopen(nome,"wb+");
        printf("Arquivo %s criado! \n",nome);
    }
    printf("Arquivo %s aberto! \n",nome);
    return arquivo;
}

void* ler(const char* nomeArquivo, size_t* numero_structs,size_t tamanho_struct) {
    FILE* arquivo = abrir_arquivo(nomeArquivo, "rb+");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Obtém o tamanho total do arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    *numero_structs = tamanhoArquivo / tamanho_struct;

    // Aloca dinamicamente memória para o vetor de structs
    void* vetorStructs = malloc(*numero_structs * tamanho_struct); // atendimento* vetor= (atendimento*)malloc(numero_structs * sizeof(atendimento));

    if (vetorStructs == NULL) {
        perror("Erro ao alocar memória para o vetor de structs");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    fread(vetorStructs, tamanho_struct, *numero_structs, arquivo);

    fclose(arquivo);

    return vetorStructs;
}
void adicionar(const char* nomeArquivo, void* novospaciente,int qnd_novos_pacientes,size_t tam_struct) {
    FILE* arquivo = fopen(nomeArquivo, "ab+");  // Abre o arquivo em modo de leitura e escrita no final
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Escreve os novos structs no final do arquivo
    fseek(arquivo, 0, SEEK_END);  // Move o ponteiro para o final do arquivo
    fwrite(novospaciente, tam_struct, qnd_novos_pacientes, arquivo);
    
    fclose(arquivo);
}
void alterar(const char* nomeArquivo, int indice, void* novainformacao, size_t tamanho_struct) {
    FILE* arquivo = fopen(nomeArquivo, "rb+");  // Abre o arquivo em modo de leitura e escrita

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    fseek(arquivo, indice * tamanho_struct, SEEK_SET);

    // Escreve a nova struct na posição calculada
    fwrite(novainformacao, tamanho_struct, 1, arquivo);

    fclose(arquivo);
}
