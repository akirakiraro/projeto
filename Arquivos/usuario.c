#include "common.h"

int adicionar_administrador () {
  char CPF[12];
  FILE *arquivo = abrir_arquivo ("Storage/Usuarios","ab");
  registro_cpf (CPF);
  

  fclose(arquivo);
  return 1;
}

int registro_cpf (char *CPF_digitado){
  int CPF_aprovado = 0;

  do{
    limpa_tela ();
    printf("> Digite seu CPF sem pontos e traco: ");
    fgets(CPF_digitado, 12, stdin);
    verificar_buffer(CPF_digitado);

    // verifica se o usuario digitou 11 numeros
    if (strlen(CPF_digitado) != 11 || !verifica_cpf(CPF_digitado)) {
      limpa_tela();
      printf("Digite um CPF valido.");
      CPF_aprovado = 0;
      delay(1500);
      continue;
    }

    // verifica se ja existe um cpf igual
    FILE *arquivo = abrir_arquivo ("Storage/Usuarios","rb");
    CPF_aprovado = 1;
    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
      if (strcmp(usuario.cpf, CPF_digitado) == 0){
        fclose(arquivo);
        CPF_aprovado = 0;
        limpa_tela ();
        printf("CPF ja cadastrado.\n");
        delay(1500);
        break;
      }
    }

    fclose(arquivo);
  
  } while (CPF_aprovado == 0);
  return 1;
}

int registro_senha (){

}



