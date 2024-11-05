#ifndef common_h
#define common_h

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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
void verificar_buffer(char *entrada);
void limpar_buffer();
void limpa_tela ();
void formatar_cpf(const char *cpf_original, char *cpf_formatado);
int escolher_operacao(int min_op, int max_op, char *texto);
void encerrar_programa ();
FILE* abrir_arquivo(const char* nome_arquivo, const char* modo_abertura);
int criar_arquivo(const char* nome_arquivo);
int verifica_numero (const char *cpf);


// MENU.C
void Menu_usuario ();
void Menu_inicial_usuario ();
void Menu_Adm ();
void Menu_inicial_adm ();

// USUARIO.C
int adicionar_administrador ();
int registro_cpf (char *CPF_digitado);
int registro_senha (char *senha_digitada);



#endif