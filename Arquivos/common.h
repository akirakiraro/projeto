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

typedef struct {
  char CPF[12];  // CPF do usuario
  int tipo;      // 1 para positivo e 0 para negativo
  float valor;   // valor da transacao
  int moeda;     // Qual moeda foi comprada ou vendida
  time_t data;   // data e hora da transacao
  int taxa;      // taxa da transacao
  float cotacao; // cotacao da criptomoeda na hora da transacao
} Extrato;

typedef struct {
  char Nome_Cripto[20];
  int taxa_compra;
  int taxa_venda;
  float cotacao;
} Criptomoedas;

typedef struct {
  char cpf[12];
  int senha;
} Usuario;

typedef struct {
  char cpf[12];
  char criptomoeda[20];
  float quantidade;
} Moeda_usuario;


// FUNCOES.C
void delay(int tempo_ms);
void limpar_buffer();
void formatar_cpf(const char *cpf_original, char *cpf_formatado);

// MENU.C
void Menu_usuario ();
void Menu_inicial_usuario ();


#endif