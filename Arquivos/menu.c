#include "common.h"

void Menu_inicial_usuario () {
  limpa();
  printf("Bem vindo ao Projeto 1 - Exchange de criptomoedas!\n\n");
  printf("1. Login.");
  printf("0. Sair.");
}

void Menu_usuario () {
  limpa();
  printf("Bem vindo ====nome===== \n\n");
  printf("1. Consultar saldo.\n");
  printf("2. Consultar extrato.\n");
  printf("3. Depositar reais.\n");
  printf("4. Sacar reais.\n");
  printf("5. Comprar criptomoedas.\n");
  printf("6. Vender criptomoedas.\n");
  printf("7. Atualizar cotacao de criptomoedas.\n");
  printf("0. Sair\n\n");
}

// ===================================
//            Administrador
// ===================================

void Menu_Adm () {
  limpa();
  printf("Bem vindo ====nome===== \n\n");
  printf("1. Cadastrar novo investidor.\n");
  printf("2. Excluir investidor.\n");
  printf("3. Cadastrar criptomoeda.\n");
  printf("4. Excluir criptomoeda.\n");
  printf("5. Consultar saldo do investidor.\n");
  printf("6. Consultar extrato do investidor.\n");
  printf("7. Atualizar cotacao da criptomoeda.\n");
  printf("0. Sair\n\n");
}

void Menu_inicial_adm () {
  limpa();
  printf("Bem vindo ao Projeto 1 - Exchange de criptomoedas!\n\n");
  printf("1. Login.");
  printf("2. Registro.");
  printf("0. Sair.");
}













