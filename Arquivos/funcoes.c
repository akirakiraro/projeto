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
  printf("Feito por: Rodrigo Akira e Gustavo Nomura.\n\n");
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

int pede_CPF (char *CPF) {
  int aprovado = 0;
  do {
    printf("> Digite o CPF ou 0 para voltar.\n");
    printf("> CPF: ");
    fgets(CPF, 12, stdin);
    verificar_buffer(CPF);

    if (strcmp(CPF, "0") == 0) {
      return -1;
    }

    // Verifica se o usuario digitou 11 numeros
    if (strlen(CPF) != 11 || !verifica_numero(CPF)) {
      limpa_tela();
      printf("Digite um CPF valido.\n");
      delay(1500);
      continue;
    }

    aprovado = 1;
  } while (aprovado == 0);
  return 1;
}

int pede_senha (char *senha) {
  int senha_aprovada = 0;

  do {
    printf("> Digite a senha de 6 digitos.\n");
    printf("> Senha: ");
    fgets(senha, 7, stdin);
    verificar_buffer(senha);

    if (strlen(senha) != 6 || !verifica_numero(senha)) {
      limpa_tela();
      printf("Digite uma senha valida.\n");
      senha_aprovada = 0;
      delay(1500);
      continue;
    } else {
      senha_aprovada = 1;
    }
  } while (senha_aprovada == 0);
  return 1;
}

int iniciar_programa (int usuario) {
  // verifica arquivo de usuarios ou adm
  if (usuario == 1) {
    // verifica_arq de usuarios
    FILE *arq_usuarios = abrir_arquivo("Storage/Usuarios.bin","rb");
    if (arq_usuarios == NULL) {
      arq_usuarios = abrir_arquivo("Storage/Usuarios.bin","wb");
      fclose(arq_usuarios);
    }
  } else {
    // verifica_arq de adm
    FILE *arq_usuarios = abrir_arquivo("Storage/Administradores.bin","rb");
    if (arq_usuarios == NULL) {
      arq_usuarios = abrir_arquivo("Storage/Administradores.bin","wb");
      fclose(arq_usuarios);
    }
  }

  // verifica arq extrato
  FILE *arq_extrato = abrir_arquivo("Storage/Extrato.bin","rb");
  if (arq_extrato == NULL) {
    arq_extrato = abrir_arquivo("Storage/Extrato.bin","wb");
    fclose(arq_extrato);
  }
  
  // verifica arq saldo_criptomoedas
  FILE *arq_saldo_criptomoedas = abrir_arquivo("Storage/Saldo_Criptomoedas.bin","rb");
  if (arq_saldo_criptomoedas == NULL) {
    arq_saldo_criptomoedas = abrir_arquivo("Storage/Saldo_Criptomoedas.bin","wb");
    fclose(arq_saldo_criptomoedas);
  }

  // verifica arq Criptomoedas
  FILE *arq_Criptomoedas = abrir_arquivo("Storage/Criptomoedas.bin","rb");
  if (arq_Criptomoedas == NULL) {
    criar_cripto_basicas ();
  }

  return 1;
}

int criar_cripto_basicas () {
  FILE *arq_Criptomoedas = abrir_arquivo("Storage/Criptomoedas.bin","wb");

  Criptomoedas cripto;

  snprintf(cripto.Nome_Cripto, sizeof(cripto.Nome_Cripto), "%s", "Bitcoin");
  cripto.taxa_compra = 2;
  cripto.taxa_venda = 3;
  cripto.cotacao = 520000;

  fwrite(&cripto, sizeof(Criptomoedas), 1, arq_Criptomoedas);

  snprintf(cripto.Nome_Cripto, sizeof(cripto.Nome_Cripto), "%s", "Ethereun");
  cripto.taxa_compra = 1;
  cripto.taxa_venda = 2;
  cripto.cotacao = 18000;

  fwrite(&cripto, sizeof(Criptomoedas), 1, arq_Criptomoedas);

  snprintf(cripto.Nome_Cripto, sizeof(cripto.Nome_Cripto), "%s", "Ripple");
  cripto.taxa_compra = 1;
  cripto.taxa_venda = 1;
  cripto.cotacao = 6;

  fwrite(&cripto, sizeof(Criptomoedas), 1, arq_Criptomoedas);
  fclose(arq_Criptomoedas);

  return 1;
}







