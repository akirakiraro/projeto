#include "common.h"

void Menu_inicial_usuario () {
  limpa_tela();
  printf("Bem vindo ao Projeto 1 - Exchange de criptomoedas!\n\n");
  printf("1. Login.\n");
  printf("0. Sair.\n\n");
}

void Menu_usuario () {
  limpa_tela();
  printf("   BEM-VINDO     \n\n");
  printf("1. Consultar saldo.\n");
  printf("2. Consultar extrato.\n");
  printf("3. Depositar reais.\n");
  printf("4. Sacar reais.\n");
  printf("5. Comprar criptomoedas.\n");
  printf("6. Vender criptomoedas.\n");
  printf("7. Atualizar cotacao de criptomoedas.\n");
  printf("0. Sair\n\n");
}

void mostrar_criptomoedas () {
  FILE *arquivo_criptomoedas = abrir_arquivo("Storage/Criptomoedas.bin","rb");

  Criptomoedas criptomoeda;

  printf("|----------------------------------------------------------------|\n");
  printf("|                    CRIPTOMOEDAS DISPONIVEIS                    |\n");
  printf("|----------------------------------------------------------------|\n");
  printf("| Nome             taxa venda    taxa compra    cotacao atual    |\n");
  printf("|----------------------------------------------------------------|\n");


  while(fread(&criptomoeda, sizeof(Criptomoedas), 1, arquivo_criptomoedas) == 1) {
    printf("| %-20s %02d %%          %02d %%       R$ %-13.2f |\n", 
    criptomoeda.Nome_Cripto, 
    criptomoeda.taxa_venda, 
    criptomoeda.taxa_compra, 
    criptomoeda.cotacao);
  }

  printf("|----------------------------------------------------------------|\n\n");

  fclose(arquivo_criptomoedas);
}

// ===================================
//            Administrador
// ===================================

void Menu_Adm () {
  limpa_tela();
  printf("   BEM-VINDO     \n\n");
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
  limpa_tela();
  printf("Bem vindo ao Projeto 1 - Exchange de criptomoedas!\n\n");
  printf("1. Login.\n");
  printf("2. Registro.\n");
  printf("0. Sair.\n\n");
}













