#include "common.h"

void delay(int tempo_ms) {
    #ifdef _WIN32
    Sleep(tempo_ms);
    #else
    usleep(tempo_ms * 1000);
    #endif
}

void verificar_buffer(char *entrada) {
    size_t len = strlen(entrada);

    if (len > 0 && entrada[len - 1] == '\n') {
        entrada[len - 1] = '\0';
    } else {
        limpar_buffer();
    }
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

FILE *abrir_arquivo(const char *nome_arquivo, const char *modo) {
  FILE *arquivo = fopen(nome_arquivo, modo);

  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
  }

  return arquivo;
}


int criar_arquivo_binario(const char* nome_arquivo, const char* modo_abertura) {
  FILE *teste_arquivo = fopen(nome_arquivo, "rb");
  if (teste_arquivo != NULL) {
    fclose(teste_arquivo);
    printf("O arquivo '%s' já existe.\n", nome_arquivo);
    return -1;
  }

  FILE *ponteiro_arquivo = fopen(nome_arquivo, modo_abertura);
  if (ponteiro_arquivo == NULL) {
    printf("Erro ao criar arquivo: %s\n", strerror(errno));
    delay(3000);
    return -1;
  }

  fclose(ponteiro_arquivo);
  return 0;
}

int verifica_numero (const char *cpf) {
  while (*cpf) {
    if (!isdigit(*cpf)) {
      return 0;
    }
    cpf++;
  }
  return 1;
}















