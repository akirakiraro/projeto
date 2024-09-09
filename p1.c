#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int add_usuario (int cpf, int senha){
    char pasta[255] = "usuario.txt";
    FILE *login = fopen (pasta, "w");

<<<<<<< Updated upstream
    fprintf(login, "cpf: %d\
    fclose(login);
=======
    FILE *login;                                                // define que login  eh um arquivo
    login = fopen ("usuario.bin", "wb");                        // abre o arquivo em modo de "write binario"
    fwrite(&cpf, sizeof(int), 1, login);                        // escreve no arquivo o cpf
    fwrite(&senha, sizeof(int), 1, login);                      // escreve no arquivo a senha
    fclose(login);                                              // fecha o arquivo
}

// Funcao que faz o login do usuario ---------------------------------------------------------------------------------------
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
>>>>>>> Stashed changes

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
            *ptr_aprovacao = 1;
        }else{
            limpa();
            printf("CPF invalido, tente novamente.\n\n");
        }
    } while (*ptr_aprovacao == 0);
    return 0;
}


int main(){
<<<<<<< Updated upstream
    add_usuario(123, 123);
    
=======
    // int cpf = 123;
    // int senha = 321;
    // add_usuario(cpf, senha);
>>>>>>> Stashed changes


<<<<<<< Updated upstream
=======
    Login_cpf();
>>>>>>> Stashed changes

    return 0;
}


