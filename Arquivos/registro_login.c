#include "common.h"

//================================
//        REGISTRO ADM
//================================
int adicionar_administrador() {
  char CPF[12], senha[7];
  criar_arquivo_binario("Storage/Administradores.bin", "wb");

  if (registro_cpf(CPF) == -1) {
    return -1;
  }
  pede_senha(senha);

  FILE *arquivo = abrir_arquivo("Storage/Administradores.bin", "ab");
  Usuario novo_usuario;
  snprintf(novo_usuario.cpf, sizeof(novo_usuario.cpf), "%s", CPF);
  snprintf(novo_usuario.senha, sizeof(novo_usuario.senha), "%s", senha);
  fwrite(&novo_usuario, sizeof(Usuario), 1, arquivo);

  fclose(arquivo);
  return 1;
}

int registro_cpf(char *CPF_digitado) {
  int CPF_aprovado;

  do {
    
    if (pede_CPF(CPF_digitado) == -1) {
      return -1;
    }

    // Verifica se ja existe um CPF igual
    FILE *arquivo = abrir_arquivo("Storage/Administradores.bin", "rb");

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

//================================
//           LOGIN ADM
//================================

int logar_administrador(char *CPF_logado) {
  char CPF[12], senha[7];
  
  if (verifica_arquivo_adm() == -1) {
    return -1;
  }

  if (logar_cpf(CPF) == -1) {
    return -1;
  }
  logar_senha(CPF);
  strcpy(CPF_logado, CPF);
  return 1;
}

int logar_cpf (char *CPF_digitado) {
  int CPF_aprovado = 0;

  do {
    
    if (pede_CPF(CPF_digitado) == -1) {
      return -1;
    }

    // Verifica se ja existe o CPF
    FILE *arquivo = abrir_arquivo("Storage/Administradores.bin", "rb");

    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
      if (strcmp(usuario.cpf, CPF_digitado) == 0) {
        CPF_aprovado = 1;
        return 1;
      }
    }

    fclose(arquivo);

  } while (CPF_aprovado == 0);
  return -1;
}

int logar_senha (char *CPF_usuario) {
  int senha_aprovada = 0;
  char senha_digitada[7];

  do {
    
    pede_senha(senha_digitada);

    FILE *arquivo = abrir_arquivo("Storage/Administradores.bin", "rb");
    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
      if (strcmp(usuario.cpf, CPF_usuario) == 0) {
        if (strcmp(usuario.senha, senha_digitada) == 0) {
          printf("Senha aprovada.\n");
          senha_aprovada = 1;
          return 1;
        } else {
          limpa_tela();
          printf("Senha incorreta.\n");
          delay(1500);
          break;
        }
      }
    }
  } while (senha_aprovada == 0);

  return 0;
}

int verifica_arquivo_adm() {
  FILE *arquivo = fopen("Storage/Administradores.bin", "rb");
  if (arquivo == NULL) {
    return -1;
  }

  Usuario usuario;
  int existe_cpf = 0;

  while (fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
    if (usuario.cpf[0] != '\0') {
      return 1;
    }
  }

  fclose(arquivo);
  return -1;
}

