#include "common.h"

// Funcao para depositar reais
int depositar_real(char cpf[12]) {
  float valor_depositado;
  int aprovado = 0;

  do {
    limpa_tela();
    printf("Digite 0 para voltar ao menu principal.\n");
    printf("Digite o valor do deposito: \n");

    if (scanf("%f", &valor_depositado) != 1 || valor_depositado <= 0) {
      if (valor_depositado == 0) {
        return 0;
      } else {
        limpa_tela();
        printf("Digite um valor valido e positivo.\n");
        delay(1500);
        aprovado = 0;
        while(getchar() != '\n');
      }
    } else { aprovado = 1;}
  } while (aprovado == 0);

  FILE *arquivo = abrir_arquivo("Storage/Usuarios.bin", "rb+");

  Usuario usuario;

  while (fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
    if (strcmp(usuario.cpf, cpf) == 0) {
      usuario.real += valor_depositado;

      fseek(arquivo, -sizeof(Usuario), SEEK_CUR);
      fwrite(&usuario, sizeof(Usuario), 1, arquivo);

      limpa_tela();
      printf("Deposito no valor de %.2f feito com sucesso!\n", valor_depositado);
      printf("Saldo atual: %.2f", usuario.real);
      delay(2000);
      break;
    } else {
      limpa_tela();
      printf("Nao existe o CPF no arquivo de usuarios.\n");
      delay(1500);
      return -1;
    }
  }
  escrever_extrato(cpf, 1, valor_depositado, "Real", time(NULL), 0, 0);
  fclose(arquivo);
  return 1;
}

// funcao para sacar reais
int sacar_real(char cpf[12]) {
  float valor_sacado, valor_disponivel;
  int aprovado = 0;

  if (verifica_saque(cpf, &valor_disponivel) == 0) {
    limpa_tela();
    printf("Voce nao possui saldo para sacar.\n");
    delay(2000);
    return 0;
  }

  do{
    limpa_tela();
    
    printf("Saldo atual: %.2f\n\n", valor_disponivel);
    printf("Digite 0 para voltar ao menu principal.\n");
    printf("Digite o valor para sacar: ");

    if (scanf("%f", &valor_sacado) != 1) {
      limpa_tela();
      printf("Digite um valor valido e positivo para sacar.\n");
      delay(2000);
      while(getchar() != '\n');
      aprovado = 0;
    } else {
      if (valor_sacado == 0) {
        return 0;
      } else if (valor_sacado <= valor_disponivel && valor_sacado > 0){
        aprovado = 1;
      } else {
        limpa_tela();
        printf("O valor deve ser positivo e nao pode exceder o seu saldo.\n");
        delay(2000);
        aprovado = 0;
      }
    }
  } while (aprovado == 0);

  FILE *arquivo = abrir_arquivo("Storage/Usuarios.bin", "rb+");

  Usuario usuario;

  while(fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
    if (strcmp(usuario.cpf, cpf) == 0) {
      usuario.real -= valor_sacado;

      fseek(arquivo, -sizeof(Usuario), SEEK_CUR);
      fwrite(&usuario, sizeof(Usuario), 1, arquivo);

      limpa_tela();
      printf("Saque no valor de %.2f feito com sucesso!\n", valor_sacado);
      printf("Saldo atual: %.2f", usuario.real);
      delay(2000);
      break;
    }
  }
  fclose(arquivo);
  escrever_extrato(cpf, 0, valor_sacado, "Real", time(NULL), 0, 0);
  return 1;
}

int verifica_saque (char cpf[12], float *valor_disponivel) {

  FILE *arquivo = abrir_arquivo("Storage/Usuarios.bin","rb");

  Usuario usuario;

  while (fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
    if (strcmp(usuario.cpf, cpf) == 0) {
      if (usuario.real > 0) {
        *valor_disponivel = usuario.real;
        fclose(arquivo);
        return 1;
      } else {
        fclose(arquivo);
        return 0;
      }
    } else {
      limpa_tela();
      printf("CPF nao encontrado para verificacao.\n");
      delay(1500);
      fclose(arquivo);
      return -1;
    }
  }
}

int consultar_saldo (char cpf[12]) {
  float Saldo_reais;

  FILE *arquivo = abrir_arquivo("Storage/Usuarios.bin", "rb");

  Usuario usuario;
  
  while(fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
    if (strcmp(usuario.cpf, cpf) == 0) {
      Saldo_reais = usuario.real;
      break;
    }
  }
  char cpf_formatado[15];
  formatar_cpf(cpf, cpf_formatado);

  limpa_tela();
  printf("CONSULTAR SALDO\n\n");
  printf("CPF: %s\n", cpf_formatado);
  printf("Saldo: R$ %.2f\n\n", Saldo_reais);

  if (consultar_criptomoedas(cpf) == -1) {
    printf("Nao possui nenhuma Criptomoeda.\n");
  }

  printf("\nAperte enter para voltar ao menu.\n");
  getchar();
  return 1;
}

int consultar_criptomoedas (char cpf[12]){
  FILE *arquivo_criptomoeda = abrir_arquivo("Storage/Saldo_Criptomoedas.bin", "rb");
  if (arquivo_criptomoeda == NULL) {
    return -1;
  }

  Moeda_usuario cripto;
  int encontrado = 0;
  printf("Criptomoedas:\n\n");

  while(fread(&cripto, sizeof(Moeda_usuario), 1, arquivo_criptomoeda) == 1) {
    if (strcmp(cripto.cpf, cpf) == 0) {
      encontrado = 1;
      printf("%s: %.3f\n", cripto.criptomoeda, cripto.quantidade);
    }
  }

  fclose(arquivo_criptomoeda);

  if (encontrado == 0) {
    return -1;
  } else {
    return 1;
  }
  
}

int consultar_saldo_adm () {
  char cpf_consultado[12];
  limpa_tela();
  if (pede_CPF(cpf_consultado) == -1) {
    return -1;
  }

  consultar_saldo(cpf_consultado);
  return 1;
}
