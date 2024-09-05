#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int add_usuario (int cpf, int senha){
    char pasta[255] = "usuario.txt";
    FILE *login = fopen (pasta, "w");

    fprintf(login, "cpf: %d\
    fclose(login);

}


int main(){
    add_usuario(123, 123);
    



    return 0;
}


