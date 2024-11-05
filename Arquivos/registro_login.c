#include "common.h"

int adicionar_administrador() {
  char CPF[12], senha[7];
  criar_arquivo_binario("Storage/Usuarios.bin", "wb");

  registro_cpf(CPF);
  registro_senha(senha);

  FILE *arquivo = abrir_arquivo("Storage/Usuarios.bin", "ab");
  Usuario novo_usuario;
  snprintf(novo_usuario.cpf, sizeof(novo_usuario.cpf), "%s", CPF);
  snprintf(novo_usuario.senha, sizeof(novo_usuario.senha), "%s", senha);
  fwrite(&novo_usuario, sizeof(Usuario), 1, arquivo);

  fclose(arquivo);
  return 1;
}

int registro_cpf(char *CPF_digitado) {
  int CPF_aprovado = 0;

  do {
    limpa_tela();
    printf("> Digite seu CPF sem pontos e traco: ");
    fgets(CPF_digitado, 12, stdin);
    verificar_buffer(CPF_digitado);

    // Verifica se o usuario digitou 11 numeros
    if (strlen(CPF_digitado) != 11 || !verifica_numero(CPF_digitado)) {
      limpa_tela();
      printf("Digite um CPF valido.\n");
      delay(1500);
      continue;
    }

    // Verifica se ja existe um CPF igual
    FILE *arquivo = abrir_arquivo("Storage/Usuarios.bin", "rb");

    CPF_aprovado = 1;
    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
      if (strcmp(usuario.cpf, CPF_digitado) == 0) {
        CPF_aprovado = 0;
        limpa_tela();
        printf("CPF ja cadastrado.\n");
        delay(1500);
        break;
      }
    }

    fclose(arquivo);

  } while (CPF_aprovado == 0);
  return 1;
}

int registro_senha(char *senha_digitada) {
  int senha_aprovada = 0;

  do {
    limpa_tela();
    printf("> Digite sua senha de 6 digitos: ");
    fgets(senha_digitada, 7, stdin);
    verificar_buffer(senha_digitada);

    if (strlen(senha_digitada) != 6 || !verifica_numero(senha_digitada)) {
      limpa_tela();
      printf("Digite uma senha valida.\n");
      senha_aprovada = 0;
      delay(1500);
      continue;
    } else {
      senha_aprovada = 1;
    }
  } while (senha_aprovada == 0);
  return 1;
}



