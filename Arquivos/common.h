#ifndef common_h
#define common_h

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>

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
  char senha[7];
  float real;
} Usuario;

typedef struct {
  char cpf[12];
  char criptomoeda[20];
  float quantidade;
} Moeda_usuario;


// CADASTRO_EXCLUIR.C
int criar_investidor ();
int CPF_novo_investidor (char *CPF_digitado);
int excluir_investidor ();
int CPF_excluir_investidor (char *CPF_digitado);
int excluir_usuario (const char *cpf_excluir);
int verifica_arquivo_usuarios();

// FUNCOES.C
void delay(int tempo_ms);
void verificar_buffer(char *entrada);
void limpar_buffer();
void limpa_tela ();
void formatar_cpf(const char *cpf_original, char *cpf_formatado);
int escolher_operacao(int min_op, int max_op, char *texto);
void encerrar_programa ();
FILE* abrir_arquivo(const char* nome_arquivo, const char* modo_abertura);
int criar_arquivo_binario(const char* nome_arquivo, const char* modo_abertura);
int verifica_numero (const char *cpf);
int pede_CPF (char *CPF);
int pede_senha (char *senha);

// MENU.C
void Menu_usuario ();
void Menu_inicial_usuario ();
void Menu_Adm ();
void Menu_inicial_adm ();

// REGISTRO_LOGIN.C
int adicionar_administrador ();
int registro_cpf (char *CPF_digitado);
int logar_administrador(char *CPF_logado);
int logar_cpf (char *CPF_digitado);
int logar_senha (char *CPF_usuario);
int verifica_arquivo_adm();
int login_usuario (char *CPF_logado);
int logar_cpf_usuarios (char *CPF_digitado);
int logar_senha_usuarios (char *CPF_usuario);

// CRIPTO.C
int verificar_nome_cripto (char *nome);
int criar_criptomoeda();
int excluir_criptomoeda();
int atualizar_cripto ();

// EXCHANGE_REAL.C
int depositar_real(char cpf[12]);
int sacar_real(char cpf[12]);
int verifica_saque (char cpf[12], float *valor_disponivel);
int consultar_saldo (char cpf[12]);

#endif