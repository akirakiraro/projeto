#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
// limpa o terminal
void limpa(){
    system("cls");
}
// limpa o buffer
void limpar_buffer(){
    int c;
    // Lê e descarta todos os caracteres até encontrar um Enter ('\n') ou EOF
    while ((c = getchar()) != '\n' && c != EOF);
}

int add_usuario (int cpf, int senha, int real){
    char pasta[255] = "usuario.txt";

    FILE *login;                                                // define que login  eh um arquivo
    login = fopen ("usuario.bin", "wb");                        // abre o arquivo em modo de "write binario"
    fwrite(&cpf, sizeof(int), 1, login);                        // escreve no arquivo o cpf
    fwrite(&senha, sizeof(int), 1, login);                      // escreve no arquivo a senha
    fwrite(&real, sizeof(int), 1, login);                       // escreve no arquivo a qntd de reais
    fclose(login);                                              // fecha o arquivo
}

// Funcao que faz o login do cpf do usuario ---------------------------------------------------------------------------------------
int Login_cpf (){
    // define inteiros e ponteiros para variaveis
    int cpf_entrada, cpf_usuario, resultado_scan;
    int aprovacao_cpf = 0;
    int *ptr_aprovacao;
    ptr_aprovacao = &aprovacao_cpf;
    limpa();
    // faz uma repeticao para ficar pedindo o cpf
    do {
        // Teste para ver qual o valor de ptr antes da repeticao
        // printf("valor de ptr_aprovacao antes: %d\n", *ptr_aprovacao);

        // faz um looping até o usuario digitar um numero valido
        do {
            // pede o cpf e coloca na var cpf_entrada
            printf("Digite seu cpf: \n");
            resultado_scan = scanf("%d", &cpf_entrada);

            // se digitar um numero o scan sai com o numero 1, caso contrario sai como 0
            if (resultado_scan != 1) {
                limpa();
                printf("Entrada invalida, digite um numero.\n\n");

                // limpa o buffer de entrada
                while (getchar() != '\n');
            }

        } while (resultado_scan != 1);

        // teste para saber valores do ptr e cpf
        // printf("valor de ptr_aprovacao pos: %d\n", *ptr_aprovacao);
        // printf("valor do cpf_entrada: %d\n", cpf_entrada);

        // abre o arquivo binario em read
        FILE *login;
        login = fopen ("usuario.bin", "rb");
        // verifica se teve erro ao abrir
        if (login == NULL) {
            limpa();
            printf("Erro ao abrir o arquivo\n");
            return 1;
        }
        // le a primeira informacao e guarda no cpf_usuario e fecha o arquivo
        fread(&cpf_usuario, sizeof(cpf_usuario), 1, login);
        fclose(login);
        // verifica se o cpf que ele digitou for igual ao cpf que tem no arquivo
        if (cpf_entrada == cpf_usuario){
            limpa();
            printf("CPF aprovado\n");
            // printf("O que ele pegou do arquivo: %d", cpf_usuario);
            *ptr_aprovacao = 1;
        }else{
            limpa();
            printf("CPF invalido, tente novamente.\n\n");
        }
    } while (*ptr_aprovacao == 0);
    return 0;
}
// Funcao que faz o login da senha -----------------------------------------------------------------------------------------------
int Login_senha (){
    // define inteiros e ponteiros para variaveis
    int senha_entrada, senha_usuario, resultado_scan, lixo;
    int aprovacao_senha = 0;
    int *ptr_aprovacao;
    ptr_aprovacao = &aprovacao_senha;
    limpa();
    // faz uma repeticao para ficar pedindo o cpf
    do {
        // Teste para ver qual o valor de ptr antes da repeticao
        // printf("valor de ptr_aprovacao antes: %d\n", *ptr_aprovacao);

        // faz um looping até o usuario digitar um numero valido
        do {
            // pede o cpf e coloca na var cpf_entrada
            printf("Digite sua senha: \n");
            resultado_scan = scanf("%d", &senha_entrada);

            // se digitar um numero o scan sai com o numero 1, caso contrario sai como 0
            if (resultado_scan != 1) {
                limpa();
                printf("Entrada invalida, digite um numero.\n\n");

                // limpa o buffer de entrada
                while (getchar() != '\n');
            }

        } while (resultado_scan != 1);
        // abre o arquivo binario em read
        FILE *login;
        login = fopen ("usuario.bin", "rb");
        // verifica se teve erro ao abrir
        if (login == NULL) {
            limpa();
            printf("Erro ao abrir o arquivo\n");
            return 1;
        }
        // le a primeira informacao e guarda no senha_usuario e fecha o arquivo
        fread(&lixo, sizeof(senha_usuario), 1, login);
        fread(&senha_usuario, sizeof(senha_usuario), 1, login);
        fclose(login);
        // verifica se a senha que ele digitou é igual a senha que tem no arquivo
        if (senha_entrada == senha_usuario){
            limpa();
            printf("Senha aprovada\n");
            *ptr_aprovacao = 1;
        }else{
            limpa();
            printf("Senha invalida, tente novamente.\n\n");
        }
    } while (*ptr_aprovacao == 0);
    return 0;
}
// funcao para aparecer o console de opcoes -------------------------------------------------------------
int mostrar_console(){
    char entrada[10];  // Buffer para armazenar a entrada do usuário
    int opcao;

    do {
        limpa();
        printf("Bem vindo ao Projeto 1 - Exchange de criptomoedas!\n\n");
        printf("1. Consultar saldo.\n");
        printf("2. Consultar extrato.\n");
        printf("3. Depositar reais.\n");
        printf("4. Sacar reais.\n");
        printf("5. Comprar criptomoedas.\n");
        printf("6. Vender criptomoedas.\n");
        printf("7. Sair\n\n");
        printf("Digite a opcao desejada (1-7): ");

        // Captura a entrada como uma string
        fgets(entrada, sizeof(entrada), stdin);

        // Verifica se o usuario apertou apenas Enter
        if (entrada[0] == '\n') {
            limpa();
            printf("Entrada vazia! Por favor, insira uma opcao valida.\n");
            Sleep(2000);
            continue;
        }

        // Converte a string para um numero
        if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 1 || opcao > 7) {
            limpa();
            printf("Opcao invalida! Por favor, escolha um numero entre 1 e 6.\n");
            Sleep(2000);
        }
    } while (opcao < 1 || opcao > 7);

    return opcao;
}
// funcao para consultar saldo -------------------------------------------------------
int consultar_saldo(){
    limpa();
    printf("Reais: \n");
    printf("\nAperte enter para voltar.");

    char lixo[1];
    fgets(lixo, sizeof(lixo), stdin);  // Lê qualquer coisa que o usuário digitar

    return 1;
}

int main(){
    int cpf = 123;
    int senha = 321;
    int real = 10;
    add_usuario(cpf, senha, real);

    Login_cpf();
    Login_senha();
    int caso = 0;
    do{
        if (caso == 0){
            limpar_buffer();
            caso = mostrar_console();
        }else{
            switch ( caso ){
            case 1 :
                consultar_saldo();
            break;
            
            case 2 :
                printf ("Segunda\n");
                caso = 7;
            break;
            
            default :
                limpa();
                printf ("Por favor, digite uma entrada valida!\n");
                Sleep(2000);
            }
            if (caso != 7){
                caso = 0;
            }
        }
    } while ( caso != 7);
    return 0;
}