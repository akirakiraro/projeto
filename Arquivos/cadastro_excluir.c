#include "common.h"

//================================
//       CRIAR INVESTIDOR
//================================

int criar_investidor () {
    char CPF[12], senha[7];

    if (CPF_novo_investidor (CPF) == -1) {
        return -1;
    }
    senha_novo_investidor (senha);

    FILE *arquivo = abrir_arquivo("Storage/Usuarios.bin", "ab");
    Usuario novo_usuario;
    snprintf(novo_usuario.cpf, sizeof(novo_usuario.cpf), "%s", CPF);
    snprintf(novo_usuario.senha, sizeof(novo_usuario.senha), "%s", senha);
    fwrite(&novo_usuario, sizeof(Usuario), 1, arquivo);

    fclose(arquivo);
    return 1;
}

int CPF_novo_investidor (char *CPF_digitado) {
    int CPF_aprovado = 0;
    do {
    limpa_tela();
    printf("NOVO INVESTIDOR\n\n");
    printf("> Digite o CPF do novo investidor (sem pontos e traco): ");
    fgets(CPF_digitado, 12, stdin);
    verificar_buffer(CPF_digitado);

    if (strcmp(CPF_digitado, "0") == 0) {
      return -1;
    }

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

int senha_novo_investidor (char *senha_digitada) {
    int senha_aprovada = 0;

    do {
        limpa_tela();
        printf("> Digite a senha do novo usuario (6 digitos): ");
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
    printf("> Digite o CPF do usuario a ser excluido (sem pontos e traco): ");
    fgets(CPF_digitado, 12, stdin);
    verificar_buffer(CPF_digitado);

    if (strcmp(CPF_digitado, "0") == 0) {
      return -1;
    }

    // Verifica se o usuario digitou 11 numeros
    if (strlen(CPF_digitado) != 11 || !verifica_numero(CPF_digitado)) {
      limpa_tela();
      printf("Digite um CPF valido.\n");
      delay(1500);
      continue;
    }

    // Verifica se ja existe um CPF igual
    FILE *arquivo = abrir_arquivo("Storage/Usuarios.bin", "rb");

    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
      if (strcmp(usuario.cpf, CPF_digitado) == 0) {
        CPF_aprovado = 1;
        limpa_tela();
        printf("CPF ja cadastrado.\n");
        delay(1500);
        return 1;
      }
    }

    fclose(arquivo);

  } while (CPF_aprovado == 0);
  return -1;
}

int excluir_usuario (const char *cpf_excluir) {
    FILE *arquivo = fopen("Storage/Usuarios.bin", "rb");
    if (arquivo == NULL) {
        printf("Arquivo nao encontrado.\n");
        return -1;
    }

    FILE *temp = fopen("Storage/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(arquivo);
        return -1;
    }

    Usuario usuario;
    int cpf_encontrado = 0;

    while (fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
        if (strcmp(usuario.cpf, cpf_excluir) != 0) {
            fwrite(&usuario, sizeof(Usuario), 1, temp);
        } else {
            cpf_encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (cpf_encontrado) {
        if (remove("Storage/Usuarios.bin") != 0) {
            perror("Erro ao remover o arquivo original");
            delay(2000);
            return -1;
        }
        if (rename("Storage/temp.bin", "Storage/Usuarios.bin") != 0) {
            perror("Erro ao renomear o arquivo temporário para o original");
            delay(2000);
            return -1;
        }
        printf("Usuário com CPF %s excluído com sucesso.\n", cpf_excluir);
        delay(2000);
    } else {
        // Remove o arquivo temporário, pois o CPF não foi encontrado
        if (remove("Storage/temp.bin") != 0) {
            perror("Erro ao remover o arquivo temporário");
            delay(2000);
        }
        printf("CPF %s não encontrado.\n", cpf_excluir);
        delay(2000);
    }

    return cpf_encontrado;
}



