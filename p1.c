#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void limpa(){
    system("cls");                                              // da um clear no terminal
}

// funcao pra futuramente add um usuario e tem que colocar no maximo 10 usuarios
int add_usuario (int cpf, int senha){

    FILE *login;                                                // define que login  eh um arquivo
    login = fopen ("usuario.bin", "wb");                        // abre o arquivo em modo de "write binario"
    fwrite(&cpf, sizeof(int), 1, login);                        // escreve no arquivo o cpf
    fwrite(&senha, sizeof(int), 1, login);                      // escreve no arquivo a senha
    fclose(login);                                              // fecha o arquivo
}

int Login_cpf (){                                               // Funcao que faz o login do usuario -------------------------------------------------------------

    int cpf_entrada;                                            // define um int para cpf_entrada
    int aprovacao_cpf = 0;
    int *ptr_aprovacao; 
    ptr_aprovacao = &aprovacao_cpf;
    printf("%d", *ptr_aprovacao);
    while (*ptr_aprovacao == 0){
        limpa();
        printf("Digite seu cpf: \n");                               // fala pra ele digitar o cpf_entrada
        scanf("%d", &cpf_entrada);                                  // pega o cpf que ele digitar
    }
    
    limpa();

    int cpf_usuario;                                            // define um cpf_usuario
    FILE *login;                                                // define que login eh arquivo
    login = fopen ("usuario.bin", "rb");                        // abri o arquivo em read binario
    fread(&cpf_usuario, sizeof(cpf_usuario), 1, login);         // le o arquivo, armazena na variavel "&cpf_usuario"
    fclose(login);                                              // fecha o arquivo
    if (cpf_entrada == cpf_usuario){                            // verifica se o cpf que ele digitou for igual ao cpf que tem no arquivo
        printf("Verdade\n");
        *ptr_aprovacao = 1;
    }else{
        printf("Falso\n");
    }

}


int main(){
    int cpf = 123;
    int senha = 321;
    add_usuario(cpf, senha);

    // Comeca os codigos certos a partir daqui.

    Login_cpf();

    printf("entrou!!\n");

    return 0;
}


