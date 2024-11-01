#include "common.h"

int main() {
  long long cpf_main;
  char cpf_char[12];
  // verifica se tem os dados do ADM no arquivo bin
  ADM();
  limpa();
  // verifica se tem o arquivo de criptomoedas.bin
  arq_cripto();
  limpa();
  // Pede o CPF para login
  cpf_main = Login_cpf();
  // converte o cpf para numero (long long)
  sprintf(cpf_char, "%lld", cpf_main);
  // pede a senha para o login
  Login_senha(cpf_char);
  int caso = -1;
  do {
    if (caso == -1) {
      limpar_buffer();
      caso = mostrar_console();
    } else {
      switch (caso) {
      case 1:
        consultar_saldo(cpf_char);
        break;

      case 2:
        ler_extrato(cpf_char);
        break;

      case 3:
        depositar_real(cpf_char);
        break;

      case 4:
        sacar_real(cpf_char);
        break;

      case 5:
        limpa();
        comprar_cripto(cpf_char);
        break;

      case 6:
        limpa();
        vender_cripto(cpf_char);
        break;

      case 7:
        limpa();
        atualizar_cotacao();
        break;

      case 8:
        limpa();
        add_usuario();
        break;

      case 9:
        limpa();
        remover_usuario();
        break;

      case 0:
        limpa();
        caso = -2;
        break;

      default:
        limpa();
        printf("Por favor, digite uma entrada valida!\n");
        caso = -1;
        sleep(1);
        break;
      }
      if (caso != -2) {
        caso = -1;
      }
    }
  } while (caso != -2);
  limpa();
  printf("Obrigado por utilizar os servicos de Exchange de criptomoedas!\n\n");
  printf("Made by: Akira e Guga\n\n");
  return 0;
}