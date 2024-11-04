#include "common.h"

void delay(int tempo_ms) {
    #ifdef _WIN32
    Sleep(tempo_ms);
    #else
    usleep(tempo_ms * 1000);
    #endif
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void limpa_tela () {
    #ifdef _WIN32
    system("cls"); // Para Windows
    #else
    system("clear"); // Para Unix/Linux (Replit)
    #endif
}

void formatar_cpf(const char *cpf_original, char *cpf_formatado) {
  // formata o CPF = XXX.XXX.XXX-XX
  snprintf(cpf_formatado, 15, "%c%c%c.%c%c%c.%c%c%c-%c%c", cpf_original[0],
           cpf_original[1], cpf_original[2], cpf_original[3], cpf_original[4],
           cpf_original[5], cpf_original[6], cpf_original[7], cpf_original[8],
           cpf_original[9], cpf_original[10]);
}

int escolher_operacao(int min_op, int max_op, char *texto) {
  int escolha;
  
  do {
    printf("> Escolha %s: ", texto);
    if (scanf("%d", &escolha) != 1 || (escolha < min_op || escolha > max_op) ) {
      printf("Escolha invalida.\n\n");
      escolha = -1;
    }
    limpar_buffer();
  }while (escolha == -1);

  return escolha;
}

void encerrar_programa () {
  limpa_tela ();
  printf("Programa encerrado com sucesso!\n");
  printf("Feito por: Rodrigo Akira e Gustavo Nomura.\n");
  exit(0);
}




// mudar funcao pq nn vai existir mais
const char *moeda_to_string(int moeda) {
  switch (moeda) {
  case 0:
    return "Real";
  case 1:
    return "Bitcoin";
  case 2:
    return "Ethereum";
  case 3:
    return "Ripple";
  default:
    return "Desconhecida";
  }
}
























