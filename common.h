#ifndef common_h
#define common_h

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// struct para extrato
typedef struct {
  char CPF[12];  // CPF do usuario
  int tipo;      // 1 para positivo e 0 para negativo
  float valor;   // valor da transacao
  int moeda;     // 0 para real, 1 para bitcoin, 2 para ethereum, 3 para ripple
  time_t data;   // data e hora da transacao
  int taxa;      // taxa da transacao
  float cotacao; // cotacao da criptomoeda na hora da transacao
} Extrato;

// struct para criptomoedas
typedef struct {
  float bitcoin_cotacao;
  float ethereum_cotacao;
  float ripple_cotacao;
} Criptomoedas;

// struct para definir o usuario
typedef struct {
  char cpf[12];
  int senha;
  float reais;
  float bitcoin;
  float ethereum;
  float ripple;
} Usuario;

// FUNCOES.C
void delay(int tempo_ms);
void limpar_buffer();
void formatar_cpf(const char *cpf_original, char *cpf_formatado);



#endif