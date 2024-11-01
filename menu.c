#include "common.h"

// funcao para aparecer o console de opcoes
int mostrar_console() {
  char entrada[255]; // Buffer para armazenar a entrada do usuário
  int opcao;

  do {
    limpa();
    printf("Bem vindo ao Projeto 1 - Exchange de criptomoedas!\n\n");
    printf("1. Consultar saldo.\n");
    printf("2. Consultar extrato.\n");
    printf("3. Depositar reais.\n");
    printf("4. Sacar reais.\n");
    printf("5. Comprar criptomoedas.\n");
    printf("6. Vender criptomoedas.\n");
    printf("7. Atualizar criptomoedas.\n");
    printf("8. Adicionar usuario.\n");
    printf("9. Remover usuario.\n");
    printf("0. Sair\n\n");
    printf("Digite a opcao desejada (0-9): ");

    // Captura a entrada como uma string
    fgets(entrada, sizeof(entrada), stdin);

    // Verifica se o usuario apertou apenas Enter
    if (entrada[0] == '\n') {
      limpa();
      printf("Entrada vazia! Por favor, insira uma opcao valida.\n");
      sleep(1);
      limpar_buffer();
      continue;
    }

    // Converte a string para um numero
    if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 0 || opcao > 9) {
      limpa();
      printf("Opcao invalida! Por favor, escolha um numero entre 0 e 9.\n");
      sleep(1);
    }
  } while (opcao < 0 || opcao > 9);

  return opcao;
}

// funcao para consultar saldo
int consultar_saldo(char *cpf_usuario) {
  // define variaveis
  Usuario usuario;
  int encontrado = 0;

  // abre o arquivo binario em read
  FILE *login = fopen("usuario.bin", "rb");
  if (login == NULL) {
    limpa();
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }
  // le o arquivo e busca o usuario do CPF
  while (fread(&usuario, sizeof(Usuario), 1, login)) {
    if (strcmp(usuario.cpf, cpf_usuario) == 0) {
      encontrado = 1;
      break; // Encerra o loop se o CPF for encontrado
    }
  }
  fclose(login);

  if (encontrado) {
    char cpf_formatado[15];
    formatar_cpf(usuario.cpf, cpf_formatado);

    limpa();
    printf("CONSULTAR SALDO\n");
    printf("CPF: %s\n\n", cpf_formatado);
    printf("Reais: %.2f\n", usuario.reais);
    printf("Bitcoin: %.3f\n", usuario.bitcoin);
    printf("Ethereum: %.3f\n", usuario.ethereum);
    printf("Ripple: %.3f\n", usuario.ripple);
    printf("\nAperte enter para voltar.");

    char lixo[1];
    fgets(lixo, sizeof(lixo), stdin); // le qualquer coisa que o usuario digitar
  } else {
    limpa();
    printf("Usuário não encontrado.\n");
  }
  return 1;
}









