#include "common.h"

// funcao para escrever no arquivo de extrato
void escrever_extrato(char CPF[12], int tipo, float valor, const char *moeda, time_t data, int taxa, float cotacao) {
  Extrato novo_extrato;

  // coloca todos os dados no novo extrato
  strncpy(novo_extrato.CPF, CPF, sizeof(novo_extrato.CPF) - 1);
  novo_extrato.CPF[sizeof(novo_extrato.CPF) - 1] = '\0';
  novo_extrato.tipo = tipo;
  novo_extrato.valor = valor;
  strncpy(novo_extrato.moeda, moeda, sizeof(novo_extrato.moeda) - 1);
  novo_extrato.moeda[sizeof(novo_extrato.moeda) - 1] = '\0';
  novo_extrato.data = data;
  novo_extrato.taxa = taxa;
  novo_extrato.cotacao = cotacao;

  // abre o arquivo em modo append para so add o novo extrato
  FILE *arquivo_extrato = fopen("Storage/Extrato.bin", "ab");
  if (!arquivo_extrato) {
    perror("Erro ao abrir o arquivo.\n");
    return;
  }
  fwrite(&novo_extrato, sizeof(Extrato), 1, arquivo_extrato);
  fclose(arquivo_extrato);
}

// funcao para ler o arquivo de extrato
void ler_extrato(char cpf[12]) {
  // abre o arquivo para ler o extrato
  FILE *arquivo_extrato = fopen("Storage/Extrato.bin", "rb");
  if (!arquivo_extrato) {
    perror("Nao ha nenhuma transacao cadastrada.");
    return;
  }
  // vai armazenar cada registro
  Extrato extratos[100]; // Array para armazenar os extratos
  int total_extratos = 0;

  // le todos os extratos do arquivo
  while (fread(&extratos[total_extratos], sizeof(Extrato), 1, arquivo_extrato) && total_extratos < 100) {
    total_extratos++;
  }

  fclose(arquivo_extrato);

  int transacoes_encontradas = 0;

  // vai deixar tudo na verrtical e bonitao
  limpa_tela();
  printf("%s\n", "---------------------------------------------------------------------------------------------");
  printf("%-15s %-15s %-20s %-20s %-10s %-10s\n", "CPF", "Valor", "Moeda", "Data", "Taxa", "Cotacao");
  printf("%s\n", "---------------------------------------------------------------------------------------------");

  // pega cada extrato e printa em ordem reversa para ficar bunitu
  for (int i = total_extratos - 1; i >= 0; i--) {
    if (strcmp(extratos[i].CPF, cpf) == 0 && transacoes_encontradas < 100) {
      transacoes_encontradas++;
      char buffer[26];
      strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&extratos[i].data));

      float valor_formatado = (extratos[i].tipo == 1) ? extratos[i].valor : -extratos[i].valor; // sinal positivo ou negativo
      
      char cpf_formatado[15];
      formatar_cpf(extratos[i].CPF, cpf_formatado);
      printf("%-15s %-15.2f %-20s %-20s %-10d %-10.2f\n", cpf_formatado, valor_formatado, extratos[i].moeda, buffer, extratos[i].taxa, extratos[i].cotacao);
    }
  }

  if (transacoes_encontradas == 0) {
    limpa_tela();
    printf("Nenhuma transacao encontrada para o CPF: %s\n", cpf);
  }

  printf("\nPressione enter para voltar.\n");
  getchar();
}

int consultar_extrato_adm () {
  char cpf_consultado[12];
  limpa_tela();
  if (pede_CPF(cpf_consultado) == -1) {
    return -1;
  }

  ler_extrato(cpf_consultado);
  return 1;
}














