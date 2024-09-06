#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int add_usuario (int *cpf, int *senha){

    FILE *login;
    login = fopen ("usuario.bin", "wb");

    fwrite(cpf, sizeof(int), 1, login);
    fwrite(senha, sizeof(int), 1, login);
    fclose(login);
}

int le_usuario (int *cpf, int *senha){
    int i = 0;
    FILE *login;
    login = fopen ("usuario.bin", "rb");

    fread(cpf, sizeof(int), 1, login);
    
    for(i = 0; i < 1; i++)
    {
        printf("%d\n", cpf[i]);
    }

    for(i = 0; i < 1; i++)
    {
        printf("%d\n", senha[i]);
    }
}

int main(){

    int cpf [1] = {123};
    int senha [1] = {321};
    add_usuario(cpf, senha);
    le_usuario(cpf, senha);

    int cpf_entrada;

    printf("Digite seu cpf: ");
    scanf("%d", &cpf_entrada);
    printf("entrada: %d", cpf_entrada);

    return 0;
}


