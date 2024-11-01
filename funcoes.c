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

void formatar_cpf(const char *cpf_original, char *cpf_formatado) {
  // formata o CPF = XXX.XXX.XXX-XX
  snprintf(cpf_formatado, 15, "%c%c%c.%c%c%c.%c%c%c-%c%c", cpf_original[0],
           cpf_original[1], cpf_original[2], cpf_original[3], cpf_original[4],
           cpf_original[5], cpf_original[6], cpf_original[7], cpf_original[8],
           cpf_original[9], cpf_original[10]);
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
























