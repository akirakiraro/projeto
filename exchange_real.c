#include "common.h"

// Funcao para depositar reais
int depositar_real(char cpf[12]) {
  float valor_depositado;
  int deposito_aprovado = 0, resultado_scan = 0, aprov = 0;
  // faz um loop pro usuario digitar o valor valido
  limpa();
  do {
    printf("Digite 0 para voltar ao menu principal.\n");
    printf("Digite o valor do deposito: \n");
    resultado_scan = scanf("%f", &valor_depositado);

    if (resultado_scan != 1) {
      limpa();
      printf("Entrada invalida, digite um numero.\n\n");
      // limpa o buffer de entrada
      while (getchar() != '\n')
        ;
      continue;
    } else if (valor_depositado < 0) {
      limpa();
      printf("Por favor digite um numero positivo.\n\n");
      continue;
    } else if (valor_depositado == 0) {
      return 0;
    } else {
      aprov = 1;
    }
  } while (aprov != 1);

  // abre o arquivo binario em read e escrita
  FILE *login = fopen("usuario.bin", "r+b");
  if (!login) {
    perror("nao foi possivel abrir o arquivo");
    return -1;
  }

  Usuario usuario;

  // percorre o arquivo para encontrar o CPF correspondente
  while (fread(&usuario, sizeof(Usuario), 1, login)) {
    if (strcmp(usuario.cpf, cpf) == 0) {
      // Atualiza o valor dos reais
      usuario.reais += valor_depositado;
      fseek(login, -sizeof(Usuario), SEEK_CUR); // volta para a posicao anterior
      fwrite(&usuario, sizeof(Usuario), 1, login); // grava a atualizacao
      break;
    }
  }
  fclose(login);
  escrever_extrato(cpf, 1, valor_depositado, 0, time(NULL), 0, 0);
  limpa();
  printf("Deposito aprovado no valor de R$ %.2f\n", valor_depositado);
  printf("\nAperte enter para voltar.");
  limpar_buffer();
  char lixo[1];
  fgets(lixo, sizeof(lixo), stdin);
  return 1;
}
// funcao para sacar reais
int sacar_real(char cpf[12]) {
  float valor_sacado, valor_disponivel;
  int saque_aprovado = 0, resultado_scan = 0, aprovacao_valor = 0, aprov = 0;
  // faz um loop pro usuario digitar o valor valido
  limpa();
  do {
    printf("Digite 0 para voltar ao menu principal.\n");
    printf("Digite o valor do saque: \n");
    resultado_scan = scanf("%f", &valor_sacado);

    if (resultado_scan != 1) {
      limpa();
      printf("Entrada invalida, digite um numero.\n\n");
      // limpa o buffer de entrada
      while (getchar() != '\n')
        ;
      continue;
    } else if (valor_sacado < 0) {
      limpa();
      printf("Por favor digite um numero positivo.\n\n");
      continue;
    } else if (valor_sacado == 0) {
      return 0;
    }

    FILE *login = fopen("usuario.bin", "rb");
    if (!login) {
      perror("nao foi possivel abrir o arquivo");
      return -1;
    }

    Usuario usuario;

    while (fread(&usuario, sizeof(Usuario), 1, login)) {
      if (strcmp(usuario.cpf, cpf) == 0) {
        valor_disponivel = usuario.reais;
        if (valor_sacado > valor_disponivel) {
          limpa();
          printf("Valor para saque nao disponivel.\n\n");
          resultado_scan = 0, aprovacao_valor = 0;

        } else {
          aprovacao_valor = 1;
        }
      }
    }
    fclose(login);
    if (aprovacao_valor == 1) {
      Login_senha(cpf);
      aprov = 1;
    }
  } while (aprov != 1);

  // abre o arquivo binario em read e escrita
  FILE *login = fopen("usuario.bin", "r+b");
  if (!login) {
    perror("nao foi possivel abrir o arquivo");
    return -1;
  }

  Usuario usuario;

  // percorre o arquivo para encontrar o CPF correspondente
  while (fread(&usuario, sizeof(Usuario), 1, login)) {
    if (strcmp(usuario.cpf, cpf) == 0) {
      // Atualiza o valor dos reais
      usuario.reais -= valor_sacado;
      fseek(login, -sizeof(Usuario), SEEK_CUR); // volta para a posicao anterior
      fwrite(&usuario, sizeof(Usuario), 1, login); // grava a atualizacao
      break;
    }
  }
  fclose(login);
  escrever_extrato(cpf, 0, valor_sacado, 0, time(NULL), 0, 0);
  limpa();
  printf("Saque aprovado no valor de R$ %.2f\n", valor_sacado);
  printf("\nAperte enter para voltar.");
  limpar_buffer();
  char lixo[1];
  fgets(lixo, sizeof(lixo), stdin);
  return 1;
}

