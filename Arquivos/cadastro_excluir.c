#include "common.h"

//================================
//       CRIAR INVESTIDOR
//================================

int criar_investidor () {
  char CPF[12], senha[7];

  if (verifica_arquivo_usuarios() == -1) {
    FILE *arquivo = abrir_arquivo("Storage/Usuarios.bin", "wb");
    fclose(arquivo);
  }

  if (CPF_novo_investidor(CPF) == -1) {
    return -1;
  }
  pede_senha(senha);

  FILE *arquivo = abrir_arquivo("Storage/Usuarios.bin", "ab");
  Usuario novo_usuario;
  snprintf(novo_usuario.cpf, sizeof(novo_usuario.cpf), "%s", CPF);
  snprintf(novo_usuario.senha, sizeof(novo_usuario.senha), "%s", senha);
  novo_usuario.real = 0;
  fwrite(&novo_usuario, sizeof(Usuario), 1, arquivo);

  fclose(arquivo);
  return 1;
}

int CPF_novo_investidor (char *CPF_digitado) {
    int CPF_aprovado = 0;
    do {
    limpa_tela();
    printf("  NOVO INVESTIDOR\n\n");
    if (pede_CPF(CPF_digitado) == -1) {
      return -1;
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

//================================
//      EXCLUIR INVESTIDOR
//================================

int excluir_investidor () {
    char CPF[12];

    CPF_excluir_investidor(CPF);

    excluir_usuario(CPF);

    return 1;
}

int CPF_excluir_investidor (char *CPF_digitado) {
    int CPF_aprovado = 0;
    do {
    limpa_tela();
    printf("EXCLUIR INVESTIDOR\n\n");
    if (pede_CPF(CPF_digitado) == -1){
      CPF_aprovado = 1;
      return -1;
    }

    // Verifica se ja existe o CPF
    FILE *arquivo = abrir_arquivo("Storage/Usuarios.bin", "rb");

    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
      if (strcmp(usuario.cpf, CPF_digitado) == 0) {
        return 1;
      }
    }

    fclose(arquivo);

  } while (CPF_aprovado == 0);
  return -1;
}

int excluir_usuario(const char *cpf_excluir) {
  FILE *arquivo = abrir_arquivo("Storage/Usuarios.bin", "rb");

  fseek(arquivo, 0, SEEK_END);
  long tamanho_arquivo = ftell(arquivo);
  int total_usuarios = tamanho_arquivo / sizeof(Usuario);
  fseek(arquivo, 0, SEEK_SET);

  Usuario *usuarios = (Usuario *)malloc(total_usuarios * sizeof(Usuario));
  if (usuarios == NULL) {
    printf("Erro de memoria.\n");
    fclose(arquivo);
    return -1;
  }

  fread(usuarios, sizeof(Usuario), total_usuarios, arquivo);
  fclose(arquivo);

  int cpf_encontrado = 0;
  int novo_total = 0;

  // remove o CPF 
  for (int i = 0; i < total_usuarios; i++) {
    if (strcmp(usuarios[i].cpf, cpf_excluir) == 0) {
      cpf_encontrado = 1;
    } else {
      usuarios[novo_total++] = usuarios[i];
    }
  }

  if (cpf_encontrado) {
    // Reescrever o arquivo com os usuários atualizados
    arquivo = abrir_arquivo("Storage/Usuarios.bin", "wb");
      

    fwrite(usuarios, sizeof(Usuario), novo_total, arquivo);
    fclose(arquivo);

    printf("Usuario com CPF %s excluido com sucesso.\n", cpf_excluir);
  } else {
    printf("CPF %s nao encontrado.\n", cpf_excluir);
  }

  free(usuarios);
  return cpf_encontrado;
}

int verifica_arquivo_usuarios() {
  FILE *arquivo = fopen("Storage/Usuarios.bin", "rb");
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

