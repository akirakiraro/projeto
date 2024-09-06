#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int add_usuario (int cpf, int senha){

    FILE *login;
    login = fopen ("usuario.bin", "wb");

    fwrite(&cpf, sizeof(int), 1, login);
    fwrite(&senha, sizeof(int), 1, login);
    fclose(login);
}

int Login_cpf (int cpf_entrada){
    int cpf_usuario;

    FILE *login;
    login = fopen ("usuario.bin", "rb");
    fread(&cpf_usuario, sizeof(cpf_usuario), 1, login);
    fclose(login);
    if (cpf_entrada == cpf_usuario){
        printf("Verdade\n");
    }else{
        printf("Falso\n");
    }

}

int main(){

    int cpf = 123;
    int senha = 321;
    add_usuario(cpf, senha);

    int cpf_entrada;

    printf("Digite seu cpf: \n");
    scanf("%d", &cpf_entrada);

    Login_cpf(cpf_entrada);

    printf("entrada: %d\n", cpf_entrada);

    return 0;
}


