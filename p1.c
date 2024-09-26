#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // Usar esse daqui no replit
// #include <Windows.h> // usar esse daqui no vscode

// Quando trocar de windows pro replit tem que trocar os include e o cls por
// clear e o sleep

// limpa o terminal
void limpa() { system("clear"); } // troca esse daqui se for mudar de plataforma
// limpa o buffer
void limpar_buffer() {
  int c;
  // Lê e descarta todos os caracteres até encontrar um Enter ('\n') ou EOF
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void formatar_cpf(const char *cpf_original, char *cpf_formatado) {
  // formata o CPF = XXX.XXX.XXX-XX
  snprintf(cpf_formatado, 15, "%c%c%c.%c%c%c.%c%c%c-%c%c", cpf_original[0],
           cpf_original[1], cpf_original[2], cpf_original[3], cpf_original[4],
           cpf_original[5], cpf_original[6], cpf_original[7], cpf_original[8],
           cpf_original[9], cpf_original[10]);
}
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
// funcao para escrever no arquivo de extrato
// -------------------------------------------------------------------------------------
void escrever_extrato(char CPF[12], int tipo, float valor, int moeda,
                      time_t data, int taxa, float cotacao) {
  Extrato novo_extrato;

  // coloca todos os dados no novo extrato
  strncpy(novo_extrato.CPF, CPF, sizeof(novo_extrato.CPF) - 1);
  novo_extrato.CPF[sizeof(novo_extrato.CPF) - 1] = '\0';
  novo_extrato.tipo = tipo;
  novo_extrato.valor = valor;
  novo_extrato.moeda = moeda;
  novo_extrato.data = data;
  novo_extrato.taxa = taxa;
  novo_extrato.cotacao = cotacao;
  // abre o arquivo em modo append para so add o novo extrato
  FILE *arquivo_extrato = fopen("Extrato.bin", "ab");
  if (!arquivo_extrato) {
    perror("Erro ao abrir o arquivo");
    return;
  }
  fwrite(&novo_extrato, sizeof(Extrato), 1, arquivo_extrato);
  fclose(arquivo_extrato);
}
// Função para converter moeda para string
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
// funcao para ler o arquivo de extrato
// -------------------------------------------------------------------------------------------
void ler_extrato(char cpf[12]) {
  // abre o arquivo para ler o extrato
  FILE *arquivo_extrato = fopen("Extrato.bin", "rb");
  if (!arquivo_extrato) {
    perror("Nao ha nenhuma transacao cadastrada.");
    return;
  }
  // vai armazenar cada registro
  Extrato extratos[100]; // Array para armazenar os extratos
  int total_extratos = 0;

  // le todos os extratos do arquivo
  while (
      fread(&extratos[total_extratos], sizeof(Extrato), 1, arquivo_extrato) &&
      total_extratos < 100) {
    total_extratos++;
  }

  fclose(arquivo_extrato);

  int transacoes_encontradas = 0;

  // vai deixar tudo na verrtical e bonitao
  limpa();
  printf("%s\n", "-------------------------------------------------------------"
                 "----------------------");
  printf("%-15s %-15s %-10s %-20s %-10s %-10s\n", "CPF", "Valor", "Moeda",
         "Data", "Taxa", "Cotacao");
  printf("%s\n", "-------------------------------------------------------------"
                 "----------------------");

  // pega cada extrato e printa em ordem reversa para ficar bunitu
  for (int i = total_extratos - 1; i >= 0; i--) {
    if (strcmp(extratos[i].CPF, cpf) == 0 && transacoes_encontradas < 100) {
      transacoes_encontradas++;
      char buffer[26];
      strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S",
               localtime(&extratos[i].data));

      float valor_formatado =
          (extratos[i].tipo == 1)
              ? extratos[i].valor
              : -extratos[i].valor; // sinal positivo ou negativo
      char cpf_formatado[15];
      formatar_cpf(extratos[i].CPF, cpf_formatado);
      printf("%-15s %-15.2f %-10s %-20s ", cpf_formatado, valor_formatado,
             moeda_to_string(extratos[i].moeda), buffer);

      // printa se a moeda for o real
      if (extratos[i].moeda != 0) {
        printf("%-10d %-10.2f\n", extratos[i].taxa, extratos[i].cotacao);
      } else {
        printf("N/A         N/A       \n");
      }
    }
  }

  if (transacoes_encontradas == 0) {
    limpa();
    printf("Nenhuma transacao encontrada para o CPF: %s\n", cpf);
  }

  printf("\nPressione enter para voltar.\n");
}
// funcao para criar criptomoedas se precisar
int arq_cripto() {

  // tenta abrir o arquivo, caso nn tenha o arquivo ele cria um.
  FILE *criptomoedas;
  criptomoedas = fopen("criptomoedas.bin", "rb");
  if (criptomoedas == NULL) {
    printf("Criando arquivo de criptomoedas...\n\n");
    fflush(stdout); // Força a saída do buffer para o console

    sleep(1);
    limpa();
    criptomoedas = fopen("criptomoedas.bin", "wb");
    if (criptomoedas == NULL) {
      printf("Erro ao abrir o arquivo para escrita.\n");
      return 1;
    }
    // base para as cotacoes caso nao tiver o arquivo de criptomoedas
    Criptomoedas Base;
    Base.bitcoin_cotacao = 300000000.00;
    Base.ethereum_cotacao = 13000.00;
    Base.ripple_cotacao = 3.20;
    // escreve os items acima no arquivo
    fwrite(&Base, sizeof(Criptomoedas), 1, criptomoedas);
    fclose(criptomoedas);
    return 0;
  }
  return 0;
}
// struct para definir o usuario
typedef struct {
  char cpf[12]; // CPF como string (11 dígitos + terminador nulo)
  int senha;    // Senha como int
  float reais;
  float bitcoin;
  float ethereum;
  float ripple;
} Usuario;
// funcao para criacao de usuario
int add_usuario() {
  int aprovado = 0;
  // verifica se o arquivo de usuario tem mais de 10 usuario + ADM
  FILE *arquivo_cripto = fopen("usuario.bin", "rb");
  if (arquivo_cripto == NULL) {
    perror("Erro ao abrir o arquivo.");
    return 0;
  }

  // coloca o tamanho de cada usuario
  size_t tamanho_usuario = sizeof(Usuario);

  // vai para o final do arq
  fseek(arquivo_cripto, 0, SEEK_END);
  long tamanho_arquivo = ftell(arquivo_cripto);

  // calcula o numero de usuarios
  int num_usuarios = tamanho_arquivo / tamanho_usuario;

  // verifica se o numero de usuarios chegou no limite
  if (num_usuarios >= 11) {
    aprovado = 0;
  } else {
    aprovado = 1;
  }

  fclose(arquivo_cripto);

  if (aprovado != 1) {
    limpa();
    printf("Nao foi possivel adicionar o usuario. Limite de usuarios "
           "atingido.\n\n");
    printf("Aperte enter para voltar.\n");

    char lixo[1];
    fgets(lixo, sizeof(lixo), stdin);
    return 0;
  }

  char cpf_novo_usuario[12];
  int senha_novo_usuario, aprov_cpf = 0, aprov_senha = 0, resultado_scan;
  // pede para o ADM digitar o CPF do novo usuario.
  limpa();
  do {
    aprov_cpf = 0;
    printf("Digite 0 para cancelar.\n");
    printf("Digite o CPF do novo usuario (11 digitos sem ponto e traco): ");
    resultado_scan = scanf("%s", cpf_novo_usuario);
    // vai verificando se o cpf e valido
    if (resultado_scan != 1) {
      limpa();
      printf("Entrada invalida, digite um CPF valido.\n\n");
      limpar_buffer();
      continue;
    } else if (strcmp(cpf_novo_usuario, "0") == 0) {
      return 0;
    } else if (strlen(cpf_novo_usuario) != 11) {
      limpa();
      printf("CPF digitado deve conter 11 digitos.\n\n");
      limpar_buffer();
      continue;
    }
    // Verifica se o CPF digitado contem apenas digitos
    for (int i = 0; cpf_novo_usuario[i] != '\0'; i++) {
      if (cpf_novo_usuario[i] < '0' || cpf_novo_usuario[i] > '9') {
        limpa();
        printf("CPF invalido, deve conter apenas numeros.\n\n");
        limpar_buffer();
        break;
      }
    }

    FILE *arquivo_usuarios = fopen("usuario.bin", "rb");
    if (!arquivo_usuarios) {
      perror("Erro ao abrir o arquivo.");
      return 1;
    }

    Usuario usuario;

    while (fread(&usuario, sizeof(Usuario), 1, arquivo_usuarios)) {
      if (strcmp(usuario.cpf, cpf_novo_usuario) == 0) {
        aprov_cpf = 2;
      }
    }
    fclose(arquivo_usuarios);
    if (aprov_cpf == 2) {
      limpa();
      limpar_buffer();
      printf("\nJa existe um usuario com este CPF.\n\n");
      printf("Aperte enter para voltar.\n");
      getchar();
      limpa();
      continue;
    } else {
      aprov_cpf = 1;
    }
  } while (aprov_cpf != 1);
  limpa();
  // pede para o ADM digitar a senha do novo usuario.
  do {
    printf("Digite a senha de 6 digitos do novo usuario: ");
    resultado_scan = scanf("%d", &senha_novo_usuario);
    if (resultado_scan != 1) {
      limpa();
      printf("Entrada invalida, digite uma senha valida.\n\n");
      limpar_buffer();
      continue;
    } else if (senha_novo_usuario < 100000 || senha_novo_usuario > 999999) {
      limpa();
      printf("Sua senha deve conter 6 digitos.\n\n");
      limpar_buffer();
      break;
    } else {
      aprov_senha = 1;
    }
  } while (aprov_senha != 1);

  // abre o arquivo para escrita e verifica se teve erro ao abrir
  FILE *login;
  login = fopen("usuario.bin", "a");
  if (login == NULL) {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return 1;
  }
  // cria um struct para novo usuario
  Usuario novo_usuario;
  strcpy(novo_usuario.cpf, cpf_novo_usuario);
  novo_usuario.senha = senha_novo_usuario;
  novo_usuario.reais = 0;
  novo_usuario.bitcoin = 0;
  novo_usuario.ethereum = 0;
  novo_usuario.ripple = 0;

  fwrite(&novo_usuario, sizeof(Usuario), 1, login);
  fclose(login);
  return 0;
}
// funcao para remover usuario especifico
int remover_usuario() {
  int aprov_cpf = 0, resultado_scan;
  char cpf_entrada[12];

  // verifica se tem algum usuario para ele remover, se caso nn tiver ele ja
  // avisa e volta
  limpa();
  Usuario usuario_1;
  FILE *arquivo_usuarios = fopen("usuario.bin", "rb");
  if (arquivo_usuarios == NULL) {
    limpa();
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }

  int contagem_verficacao = 0;
  while (fread(&usuario_1, sizeof(Usuario), 1, arquivo_usuarios)) {
    contagem_verficacao++;
  }
  fclose(arquivo_usuarios);
  if (contagem_verficacao == 1) {
    limpa();
    printf("Nao ha usuarios cadastrados.\n");
    printf("\nAperte enter para voltar.\n");
    return 1;
  }

  do {
    printf("Digite 0 para voltar ao menu.\n");
    printf("Digite 1 para abrir a lista de usuarios.\n\n");
    printf("Digite o CPF que deseja remover ou a opcao desejada: ");
    resultado_scan = scanf("%s", cpf_entrada);
    if (resultado_scan != 1) {
      limpa();
      printf("Entrada invalida, digite um CPF valido.\n\n");
      limpar_buffer();
      continue;
    }
    if (strcmp(cpf_entrada, "0") == 0) {
      return 0;
    } else if (strcmp(cpf_entrada, "1") == 0) {
      limpa();
      Usuario usuario;
      FILE *arquivo_usuarios = fopen("usuario.bin", "rb");
      if (arquivo_usuarios == NULL) {
        limpa();
        printf("Erro ao abrir o arquivo\n");
        return 1;
      }
      // nao le o ADM haha
      Usuario usuario_ignorado;
      fread(&usuario_ignorado, sizeof(Usuario), 1, arquivo_usuarios);
      int i = 0;
      while (fread(&usuario, sizeof(Usuario), 1, arquivo_usuarios)) {
        i++;
        char cpf_formatado[15];
        formatar_cpf(usuario.cpf, cpf_formatado);
        printf("CPF do usuario %d: %s\n", i, cpf_formatado);
      }
      fclose(arquivo_usuarios);
      if (i == 0) {
        limpa();
        printf("Nao ha usuarios cadastrados.\n");
      }
      printf("\nAperte enter para voltar.\n");
      limpar_buffer();
      getchar();
      limpa();
      continue;
    }
    // verifica se o comprimento é de 11 caracteres
    if (strlen(cpf_entrada) != 11) {
      limpa();
      printf("CPF digitado deve conter 11 digitos.\n\n");
      limpar_buffer();
      continue;
    }
    // Verifica se o CPF digitado contem apenas digitos
    for (int i = 0; cpf_entrada[i] != '\0'; i++) {
      if (cpf_entrada[i] < '0' || cpf_entrada[i] > '9') {
        limpa();
        printf("CPF invalido, deve conter apenas numeros.\n\n");
        limpar_buffer();
        break;
      } else {
        aprov_cpf = 1;
      }
    }

  } while (aprov_cpf != 1);

  int cpf_encontrado = 0, contador = 0;
  Usuario usuario[15];

  arquivo_usuarios = fopen("usuario.bin", "rb");
  if (arquivo_usuarios == NULL) {
    limpa();
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }

  // nao copia o ADM haha
  Usuario usuario_ignorado;
  fread(&usuario_ignorado, sizeof(Usuario), 1, arquivo_usuarios);

  while (fread(&usuario[contador], sizeof(Usuario), 1, arquivo_usuarios)) {
    if (strcmp(usuario[contador].cpf, cpf_entrada) == 0) {
      cpf_encontrado = 1;
    } else {
      contador++;
    }
  }
  fclose(arquivo_usuarios);

  if (!cpf_encontrado) {
    limpa();
    printf("CPF: %s nao encontrado.\n\n", cpf_entrada);
    printf("Aperte enter para voltar.\n");
    getchar();
    return 0;
  }

  FILE *arquivo_temp = fopen("usuario_temp.bin", "wb");
  if (arquivo_temp == NULL) {
    limpa();
    printf("Erro ao criar o arquivo temporário.\n");
    return 1;
  }

  fwrite(&usuario_ignorado, sizeof(Usuario), 1, arquivo_temp);

  fwrite(usuario, sizeof(Usuario), contador, arquivo_temp);
  fclose(arquivo_temp);

  // Substituir o arquivo original
  remove("usuario.bin");
  rename("usuario_temp.bin", "usuario.bin");

  printf("Usuario com CPF %s removido com sucesso.\n", cpf_entrada);
  return 0;
}
// funcao para fazer o adm master!!!
int ADM() {
  char cpf_ADM[] = "12312312312";
  int senha_ADM = 123123;

  FILE *login;
  login = fopen("usuario.bin", "rb");

  // Verifica se o arquivo existe; caso contrário, cria o arquivo com o usuário
  // ADM
  if (login == NULL) {
    limpa();
    printf("Criando arquivo binario...\n");
    sleep(1);

    login =
        fopen("usuario.bin", "wb"); // Abre o arquivo no modo "wb" para escrita
    if (login == NULL) {
      printf("Erro ao abrir o arquivo para escrita.\n");
      return 1;
    }

    Usuario adm;
    strcpy(adm.cpf, cpf_ADM);
    adm.senha = senha_ADM;
    adm.reais = 0;
    adm.bitcoin = 0;
    adm.ethereum = 0;
    adm.ripple = 0;

    fwrite(&adm, sizeof(Usuario), 1, login);
    fclose(login);
    return 0;
  }

  // Se o arquivo existe, lê o primeiro usuário para verificação
  Usuario temp;
  fread(&temp, sizeof(Usuario), 1, login);
  fclose(login);

  // Verifica se o CPF e a senha são iguais aos do ADM
  if (strcmp(temp.cpf, cpf_ADM) == 0 && temp.senha == senha_ADM) {
    printf("Arquivo aprovado.\n");
    return 1;
  } else {
    // Se não for, reescreve o arquivo com o usuário ADM no início e os outros
    // usuários
    login = fopen("usuario.bin", "rb");
    if (login == NULL) {
      printf("Erro ao abrir o arquivo para leitura.\n");
      return 1;
    }

    Usuario usuarios[11];
    int contador = 0;

    // Lê os usuários do arquivo
    while (fread(&usuarios[contador], sizeof(Usuario), 1, login)) {
      contador++;
    }
    fclose(login);
    limpa();
    printf("Número de usuários lidos: %d\n", contador);

    // Reabre o arquivo para escrita, substituindo o conteúdo
    login = fopen("usuario.bin", "wb");
    if (login == NULL) {
      printf("Erro ao abrir o arquivo para escrita.\n");
      return 1;
    }

    // Cria um novo usuário ADM
    Usuario novo_usuario;
    strcpy(novo_usuario.cpf, cpf_ADM);
    novo_usuario.senha = senha_ADM;
    novo_usuario.reais = 0;
    novo_usuario.bitcoin = 0;
    novo_usuario.ethereum = 0;
    novo_usuario.ripple = 0;

    // Escreve o novo usuário ADM no início do arquivo
    fwrite(&novo_usuario, sizeof(Usuario), 1, login);

    // Escreve os outros usuários no arquivo
    for (int i = 0; i < contador; i++) {
      fwrite(&usuarios[i], sizeof(Usuario), 1, login);
    }

    fclose(login);
    return 1;
  }
}
// Funcao que faz o login do cpf do usuario
// ---------------------------------------------------------------------------------------
long long Login_cpf() {
  // define inteiros e ponteiros para variaveis
  char cpf_entrada[12];
  int resultado_scan;
  int aprovacao_cpf = 0;
  int *ptr_aprovacao;
  ptr_aprovacao = &aprovacao_cpf;
  Usuario usuario;
  limpa();
  // faz uma repeticao para ficar pedindo o cpf
  do {
    // faz um looping até o usuario digitar um numero valido
    do {
      // Pede o CPF e coloca na var cpf_entrada
      printf("Digite seu CPF (sem ponto e traco): \n");
      resultado_scan = scanf("%s", cpf_entrada);

      // Limpa o buffer de entrada se necessário
      if (resultado_scan != 1) {
        limpa();
        printf("Entrada invalida, digite um CPF valido.\n\n");
        limpar_buffer();
        *ptr_aprovacao = 0;
        continue;
      }

      // verifica se o comprimento é de 11 caracteres
      if (strlen(cpf_entrada) != 11) {
        limpa();
        printf("CPF digitado deve conter 11 digitos.\n\n");
        *ptr_aprovacao = 0;
        limpar_buffer();
        continue;
      }

      // Verifica se o CPF digitado contem apenas digitos
      for (int i = 0; cpf_entrada[i] != '\0'; i++) {
        if (cpf_entrada[i] < '0' || cpf_entrada[i] > '9') {
          limpa();
          printf("CPF invalido, deve conter apenas numeros.\n\n");
          *ptr_aprovacao = 0;
          limpar_buffer();
          break;
        }
      }
      // se o cpf for invalido, continua pedindo
      if (*ptr_aprovacao == 0) {
        continue;
      }
    } while (resultado_scan != 1);

    // abre o arquivo binario em read
    FILE *login = fopen("usuario.bin", "rb");
    // verifica se teve erro ao abrir
    if (login == NULL) {
      limpa();
      printf("Erro ao abrir o arquivo\n");
      return 1;
    }
    // fica procurando até ele encontrar um usuario
    int encontrado = 0;
    while (fread(&usuario, sizeof(Usuario), 1, login)) {
      if (strcmp(usuario.cpf, cpf_entrada) == 0) {
        encontrado = 1;
        break; // encerra o loop se o CPF for encontrado
      }
    }
    fclose(login);

    // se o CPF foi encontrado ele aprova o login
    if (encontrado) {
      limpa();
      printf("CPF aprovado\n");
      *ptr_aprovacao = 1;
    } else {
      limpa();
      printf("CPF invalido, tente novamente.\n\n");
    }
  } while (*ptr_aprovacao == 0);

  // retornar o numero de cpf da pessoa
  long long cpf_num;
  char *endptr;
  cpf_num = strtoll(cpf_entrada, &endptr, 10);

  return cpf_num;
}
// Funcao que faz o login da senha
// ------------------------------------------------------------------------------------------------
int Login_senha(char *cpf_usuario) {
  // define inteiros e ponteiros para variaveis
  int senha_entrada, senha_usuario, resultado_scan;
  int aprovacao_senha = 0;
  int *ptr_aprovacao = &aprovacao_senha;
  limpa();
  // faz uma repeticao para ficar pedindo a senha
  do {
    // faz um looping até o usuario digitar uma senha valida
    do {
      printf("Digite sua senha de 6 digitos: \n");
      resultado_scan = scanf("%d", &senha_entrada);

      // se digitar um numero o scan sai com o numero 1, caso contrario sai como
      // 0
      if (resultado_scan != 1) {
        limpa();
        printf("Entrada invalida, digite um numero.\n\n");

        // limpa o buffer de entrada
        while (getchar() != '\n')
          ;
      }

    } while (resultado_scan != 1);

    if (senha_entrada < 100000 || senha_entrada > 999999) {
      limpa();
      printf("Senha invalida, por favor digite uma senha de 6 digitos.\n\n");
      continue; // volta para inicio do loop para pedir a senha dnv
    }

    // abre o arquivo binario em read
    FILE *login;
    login = fopen("usuario.bin", "rb");
    // verifica se teve erro ao abrir
    if (login == NULL) {
      limpa();
      printf("Erro ao abrir o arquivo\n");
      return 1;
    }
    // le e verifica cada registro até encontrar o CPF correspondente
    Usuario usuario;
    int cpf_encontrado = 0;

    while (fread(&usuario, sizeof(Usuario), 1, login)) {
      if (strcmp(usuario.cpf, cpf_usuario) == 0) {
        cpf_encontrado = 1;
        senha_usuario = usuario.senha;
        break;
      }
    }
    fclose(login);

    if (cpf_encontrado && senha_entrada == senha_usuario) {
      limpa();
      printf("Senha aprovada\n");
      *ptr_aprovacao = 1;
    } else {
      limpa();
      printf("Senha invalida, tente novamente.\n\n");
    }

  } while (*ptr_aprovacao == 0);
  return 0;
}
// funcao para aparecer o console de opcoes
// ---------------------------------------------------------------------------------------
int mostrar_console() {
  char entrada[255]; // Buffer para armazenar a entrada do usuário
  int opcao;

  do {
    limpa();
    printf("Bem vindo ao Projeto 1 - Exchange de criptomoedas!\n\n");
    printf("1. Consultar saldo.\n");
    printf("2. Consultar extrato.\n");
    printf("3. Depositar reais.\n");
    printf("4. Sacar reais.\n");
    printf("5. Comprar criptomoedas.\n");
    printf("6. Vender criptomoedas.\n");
    printf("7. Atualizar criptomoedas.\n");
    printf("8. Adicionar usuario.\n");
    printf("9. Remover usuario.\n");
    printf("0. Sair\n\n");
    printf("Digite a opcao desejada (0-9): ");

    // Captura a entrada como uma string
    fgets(entrada, sizeof(entrada), stdin);

    // Verifica se o usuario apertou apenas Enter
    if (entrada[0] == '\n') {
      limpa();
      printf("Entrada vazia! Por favor, insira uma opcao valida.\n");
      sleep(1);
      limpar_buffer();
      continue;
    }

    // Converte a string para um numero
    if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 0 || opcao > 9) {
      limpa();
      printf("Opcao invalida! Por favor, escolha um numero entre 0 e 9.\n");
      sleep(1);
    }
  } while (opcao < 0 || opcao > 9);

  return opcao;
}
// funcao para consultar saldo
// ----------------------------------------------------------------------------------------------------
int consultar_saldo(char *cpf_usuario) {
  // define variaveis
  Usuario usuario;
  int encontrado = 0;

  // abre o arquivo binario em read
  FILE *login = fopen("usuario.bin", "rb");
  if (login == NULL) {
    limpa();
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }
  // le o arquivo e busca o usuario do CPF
  while (fread(&usuario, sizeof(Usuario), 1, login)) {
    if (strcmp(usuario.cpf, cpf_usuario) == 0) {
      encontrado = 1;
      break; // Encerra o loop se o CPF for encontrado
    }
  }
  fclose(login);

  if (encontrado) {
    char cpf_formatado[15];
    formatar_cpf(usuario.cpf, cpf_formatado);

    limpa();
    printf("CONSULTAR SALDO\n");
    printf("CPF: %s\n\n", cpf_formatado);
    printf("Reais: %.2f\n", usuario.reais);
    printf("Bitcoin: %.3f\n", usuario.bitcoin);
    printf("Ethereum: %.3f\n", usuario.ethereum);
    printf("Ripple: %.3f\n", usuario.ripple);
    printf("\nAperte enter para voltar.");

    char lixo[1];
    fgets(lixo, sizeof(lixo), stdin); // le qualquer coisa que o usuario digitar
  } else {
    limpa();
    printf("Usuário não encontrado.\n");
  }
  return 1;
}
// Funcao para depositar reais
// ----------------------------------------------------------------------------------------------------
int depositar_real(char cpf[12]) {
  float valor_depositado;
  int deposito_aprovado = 0, resultado_scan = 0, aprov = 0;
  // faz um loop pro usuario digitar o valor valido
  limpa();
  do {
    printf("Digite 0 para voltar ao menu principal.\n");
    printf("Digite o valor do deposito: \n");
    resultado_scan = scanf("%f", &valor_depositado);

    if (resultado_scan != 1) {
      limpa();
      printf("Entrada invalida, digite um numero.\n\n");
      // limpa o buffer de entrada
      while (getchar() != '\n')
        ;
      continue;
    } else if (valor_depositado < 0) {
      limpa();
      printf("Por favor digite um numero positivo.\n\n");
      continue;
    } else if (valor_depositado == 0) {
      return 0;
    } else {
      aprov = 1;
    }
  } while (aprov != 1);

  // abre o arquivo binario em read e escrita
  FILE *login = fopen("usuario.bin", "r+b");
  if (!login) {
    perror("nao foi possivel abrir o arquivo");
    return -1;
  }

  Usuario usuario;

  // percorre o arquivo para encontrar o CPF correspondente
  while (fread(&usuario, sizeof(Usuario), 1, login)) {
    if (strcmp(usuario.cpf, cpf) == 0) {
      // Atualiza o valor dos reais
      usuario.reais += valor_depositado;
      fseek(login, -sizeof(Usuario), SEEK_CUR); // volta para a posicao anterior
      fwrite(&usuario, sizeof(Usuario), 1, login); // grava a atualizacao
      break;
    }
  }
  fclose(login);
  escrever_extrato(cpf, 1, valor_depositado, 0, time(NULL), 0, 0);
  limpa();
  printf("Deposito aprovado no valor de R$ %.2f\n", valor_depositado);
  printf("\nAperte enter para voltar.");
  limpar_buffer();
  char lixo[1];
  fgets(lixo, sizeof(lixo), stdin);
  return 1;
}
// funcao para sacar reais
// --------------------------------------------------------------------------------------------------------
int sacar_real(char cpf[12]) {
  float valor_sacado, valor_disponivel;
  int saque_aprovado = 0, resultado_scan = 0, aprovacao_valor = 0, aprov = 0;
  // faz um loop pro usuario digitar o valor valido
  limpa();
  do {
    printf("Digite 0 para voltar ao menu principal.\n");
    printf("Digite o valor do saque: \n");
    resultado_scan = scanf("%f", &valor_sacado);

    if (resultado_scan != 1) {
      limpa();
      printf("Entrada invalida, digite um numero.\n\n");
      // limpa o buffer de entrada
      while (getchar() != '\n')
        ;
      continue;
    } else if (valor_sacado < 0) {
      limpa();
      printf("Por favor digite um numero positivo.\n\n");
      continue;
    } else if (valor_sacado == 0) {
      return 0;
    }

    FILE *login = fopen("usuario.bin", "rb");
    if (!login) {
      perror("nao foi possivel abrir o arquivo");
      return -1;
    }

    Usuario usuario;

    while (fread(&usuario, sizeof(Usuario), 1, login)) {
      if (strcmp(usuario.cpf, cpf) == 0) {
        valor_disponivel = usuario.reais;
        if (valor_sacado > valor_disponivel) {
          limpa();
          printf("Valor para saque nao disponivel.\n\n");
          resultado_scan = 0, aprovacao_valor = 0;

        } else {
          aprovacao_valor = 1;
        }
      }
    }
    fclose(login);
    if (aprovacao_valor == 1) {
      Login_senha(cpf);
      aprov = 1;
    }
  } while (aprov != 1);

  // abre o arquivo binario em read e escrita
  FILE *login = fopen("usuario.bin", "r+b");
  if (!login) {
    perror("nao foi possivel abrir o arquivo");
    return -1;
  }

  Usuario usuario;

  // percorre o arquivo para encontrar o CPF correspondente
  while (fread(&usuario, sizeof(Usuario), 1, login)) {
    if (strcmp(usuario.cpf, cpf) == 0) {
      // Atualiza o valor dos reais
      usuario.reais -= valor_sacado;
      fseek(login, -sizeof(Usuario), SEEK_CUR); // volta para a posicao anterior
      fwrite(&usuario, sizeof(Usuario), 1, login); // grava a atualizacao
      break;
    }
  }
  fclose(login);
  escrever_extrato(cpf, 0, valor_sacado, 0, time(NULL), 0, 0);
  limpa();
  printf("Saque aprovado no valor de R$ %.2f\n", valor_sacado);
  printf("\nAperte enter para voltar.");
  limpar_buffer();
  char lixo[1];
  fgets(lixo, sizeof(lixo), stdin);
  return 1;
}
// funcao para comprar criptomoedas
// -----------------------------------------------------------------------------------------------
int comprar_cripto(char cpf[12]) {
  int opcao, resultado_scan, opcao_certa = 0;

  do {
    printf("Opcoes disponiveis para compra de criptomoedas:\n\n");
    printf("1. Bitcoin\n");
    printf("2. Ethereum\n");
    printf("3. Ripple\n\n");
    printf("Digite o numero da opcao desejada: ");
    resultado_scan = scanf("%d", &opcao);
    // se caso o valor digitado for diferente de um numero
    if (resultado_scan != 1) {
      limpa();
      printf("Entrada invalida, digite um numero.\n\n");
      // limpa o buffer de entrada
      while (getchar() != '\n')
        ;
    } else if (opcao < 1 || opcao > 3) {
      limpa();
      printf("Por favor digite um numero valido.\n\n");
    } else {
      opcao_certa = 1;
    }

  } while (opcao_certa != 1);

  Usuario usuario;
  // pega as variaveis de cotacao da cripto escolhida
  float possui_bitcoin, possui_ethereum, possui_ripple, carteira_reais;
  FILE *arquivo_usuario = fopen("usuario.bin", "rb");
  if (!arquivo_usuario) {
    limpa();
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }
  // le o arquivo e busca o usuario do CPF
  while (fread(&usuario, sizeof(Usuario), 1, arquivo_usuario)) {
    if (strcmp(usuario.cpf, cpf) == 0) {
      carteira_reais = usuario.reais;
      possui_bitcoin = usuario.bitcoin;
      possui_ethereum = usuario.ethereum;
      possui_ripple = usuario.ripple;
      break; // Encerra o loop se o CPF for encontrado
    }
  }
  fclose(arquivo_usuario);
  // pega as variaveis de cotacao
  Criptomoedas criptomoedas;
  FILE *arquivo_cripto = fopen("criptomoedas.bin", "rb");
  if (!arquivo_cripto) {
    limpa();
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }
  // le as variaveis para armazenar as cotacoes
  fread(&criptomoedas, sizeof(Criptomoedas), 1, arquivo_cripto);
  fclose(arquivo_cripto);

  char *cripto_maiusculo;
  char *cripto;
  float possui, cotacao;
  float valor_min;
  int taxa_compra;
  switch (opcao) {
  case 1:
    cripto_maiusculo = "BITCOIN";
    cripto = "Bitcoin";
    possui = possui_bitcoin;
    cotacao = criptomoedas.bitcoin_cotacao;
    taxa_compra = 2;
    break;

  case 2:
    cripto_maiusculo = "ETHEREUM";
    cripto = "Ethereum";
    possui = possui_ethereum;
    cotacao = criptomoedas.ethereum_cotacao;
    taxa_compra = 1;
    break;

  case 3:
    cripto_maiusculo = "RIPPLE";
    cripto = "Ripple";
    possui = possui_ripple;
    cotacao = criptomoedas.ripple_cotacao;
    taxa_compra = 1;
    break;
  }
  // ve se o usuario possui o valor minimo para poder comprar 0.001 criptomoeda,
  // caso nn tenha ele nn deixza comprar
  valor_min =
      roundf(((0.001 * cotacao) * ((taxa_compra / 100.0) + 1)) * 100) / 100;
  if (valor_min > carteira_reais) {
    limpa();
    printf("Valor minimo para comprar %s: R$ %.2f\n", cripto, valor_min);
    printf("Voce nao possui saldo suficiente para comprar %s.\n\n", cripto);
    printf("Aperte enter para voltar.");
    limpar_buffer();
    char lixo[1];
    fgets(lixo, sizeof(lixo), stdin); // le qualquer coisa que o usuario digitar

    return 0;
  }
  if (carteira_reais == 0) {
    limpa();
    printf("Voce nao possui saldo suficiente para comprar %s.\n\n", cripto);
    printf("Aperte enter para voltar.");
    limpar_buffer();
    char lixo[1];
    fgets(lixo, sizeof(lixo), stdin); // le qualquer coisa que o usuario digitar

    return 0;
  }
  // mostra a criptomoeda escolhida e variaveis
  int aprov = 0;
  float valor_investido;
  limpa();
  // loop para pedir o valor do investimento
  do {
    limpar_buffer();
    printf("COMPRAR %s\n\n", cripto_maiusculo);

    printf("Carteira: R$ %.2f\n", carteira_reais);
    printf("Possui: %.3f %s\n\n", possui, cripto);

    printf("Cotacao: R$ %.2f\n", cotacao);
    printf("Taxa de compra: %d%%\n\n", taxa_compra);

    if (valor_min != 0.00) {
      printf("Valor minimo para comprar 0.001 %s: R$ %.2f\n\n", cripto,
             valor_min);
    }
    // pede para digitar o valor em reais que o usuario quer comprar a
    // criptomoeda
    printf("Digite 0 para cancelar a compra\n");
    printf("Digite quantos reais deseja investir em %s: ", cripto);

    resultado_scan = scanf("%f", &valor_investido);
    if (!resultado_scan) {
      printf("Digite um numero.");
      limpar_buffer();
      continue;
    } else if (valor_investido == 0) {
      limpa();
      return 0;
    } else if (valor_investido < 0) {
      limpa();
      printf("digite um valor positivo.\n\n");
      sleep(1);
      limpa();
      continue;
    } else if (valor_investido < valor_min) {
      limpa();
      printf("Valor minimo para comprar 0.001 %s: R$ %.2f\n\n", cripto,
             valor_min);
      sleep(1);
      limpa();
      continue;
    } else if (valor_investido > carteira_reais) {
      limpa();
      printf("Voce nao tem saldo suficiente para investir R$ %.2f\n\n",
             valor_investido);
      sleep(1);
      limpa();
      continue;
    } else {
      Login_senha(cpf);
      aprov = 1;
    }

  } while (aprov == 0);

  // calcula o valor em cripto que o usuario comprou
  float valor_investido_criptomoeda, taxa_compra_arredondada;
  // calcula a taxa p/ subtrair do valor investido e arredonda p/ 2 casas
  // decimais
  taxa_compra_arredondada =
      roundf(((valor_investido / 100) * taxa_compra) * 100) / 100;
  // calcula o valor em cripto que o usuario comprou
  valor_investido_criptomoeda =
      roundf(((valor_investido - taxa_compra_arredondada) / cotacao) * 1000) /
      1000;
  limpa();
  printf("Investindo R$ %.2f voce comprou: %.3f %s\n\n", valor_investido,
         valor_investido_criptomoeda, cripto);
  printf("Aperte enter para voltar.\n");
  limpar_buffer();

  char lixo[1];
  fgets(lixo, sizeof(lixo), stdin); // le qualquer coisa que o usuario digitar
  // abre o arquivo para somar e subtrair os valores investidos
  arquivo_usuario = fopen("usuario.bin", "r+b");
  if (!arquivo_usuario) {
    limpa();
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }
  // percorre o arquivo para encontrar o CPF correspondente
  while (fread(&usuario, sizeof(Usuario), 1, arquivo_usuario)) {
    if (strcmp(usuario.cpf, cpf) == 0) {
      // Atualiza o valor dos reais
      usuario.reais -= valor_investido;
      if (opcao == 1) {
        usuario.bitcoin += valor_investido_criptomoeda;
        escrever_extrato(cpf, 1, valor_investido_criptomoeda, 1, time(NULL),
                         taxa_compra, cotacao);
      } else if (opcao == 2) {
        usuario.ethereum += valor_investido_criptomoeda;
        escrever_extrato(cpf, 1, valor_investido_criptomoeda, 2, time(NULL),
                         taxa_compra, cotacao);
      } else if (opcao == 3) {
        usuario.ripple += valor_investido_criptomoeda;
        escrever_extrato(cpf, 1, valor_investido_criptomoeda, 3, time(NULL),
                         taxa_compra, cotacao);
      }

      fseek(arquivo_usuario, -sizeof(Usuario),
            SEEK_CUR); // volta para a posicao anterior
      fwrite(&usuario, sizeof(Usuario), 1,
             arquivo_usuario); // grava a atualizacao
      break;
    }
  }
  fclose(arquivo_usuario);

  return 0;
}
// funcao para vender criptomoedas
// ------------------------------------------------------------------------------------------------
int vender_cripto(char cpf[12]) {
  int opcao, resultado_scan, opcao_certa = 0;

  do {
    printf("Opcoes para vender:\n\n");
    printf("1. Bitcoin\n");
    printf("2. Ethereum\n");
    printf("3. Ripple\n\n");
    printf("Digite o numero da opcao desejada: ");
    resultado_scan = scanf("%d", &opcao);
    // se caso o valor digitado for diferente de um numero
    if (resultado_scan != 1) {
      limpa();
      printf("Entrada invalida, digite um numero.\n\n");

      // limpa o buffer de entrada
      while (getchar() != '\n')
        ;
    } else if (opcao < 1 || opcao > 3) {
      limpa();
      printf("Por favor digite um numero valido.\n\n");
    } else {
      opcao_certa = 1;
    }

  } while (resultado_scan != 1 || opcao_certa != 1);

  Usuario usuario;
  // pega as variaveis de cotacao da cripto escolhida
  float possui_bitcoin, possui_ethereum, possui_ripple, carteira_reais;
  FILE *arquivo_usuario = fopen("usuario.bin", "rb");
  if (!arquivo_usuario) {
    limpa();
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }
  // le o arquivo e busca o usuario do CPF
  while (fread(&usuario, sizeof(Usuario), 1, arquivo_usuario)) {
    if (strcmp(usuario.cpf, cpf) == 0) {
      carteira_reais = usuario.reais;
      possui_bitcoin = usuario.bitcoin;
      possui_ethereum = usuario.ethereum;
      possui_ripple = usuario.ripple;
      break; // Encerra o loop se o CPF for encontrado
    }
  }
  fclose(arquivo_usuario);
  // pega as variaveis de cotacao
  Criptomoedas criptomoedas;
  FILE *arquivo_cripto = fopen("criptomoedas.bin", "rb");
  if (!arquivo_cripto) {
    limpa();
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }
  // le as variaveis para armazenar as cotacoes
  fread(&criptomoedas, sizeof(Criptomoedas), 1, arquivo_cripto);
  fclose(arquivo_cripto);

  char *cripto_maiusculo;
  char *cripto;
  float possui, cotacao;
  int taxa_venda;
  switch (opcao) {
  case 1:
    cripto_maiusculo = "BITCOIN";
    cripto = "Bitcoin";
    possui = possui_bitcoin;
    cotacao = criptomoedas.bitcoin_cotacao;
    taxa_venda = 3;
    break;

  case 2:
    cripto_maiusculo = "ETHEREUM";
    cripto = "Ethereum";
    possui = possui_ethereum;
    cotacao = criptomoedas.ethereum_cotacao;
    taxa_venda = 2;
    break;

  case 3:
    cripto_maiusculo = "RIPPLE";
    cripto = "Ripple";
    possui = possui_ripple;
    cotacao = criptomoedas.ripple_cotacao;
    taxa_venda = 1;
    break;
  }
  // ve se o usuario possui algum valor na criptomoeda
  if (possui == 0) {
    limpa();
    printf("Voce nao possui %s para vender.\n\n", cripto);
    printf("Aperte enter para voltar.");
    limpar_buffer();
    char lixo[1];
    fgets(lixo, sizeof(lixo), stdin); // le qualquer coisa que o usuario digitar
    return 0;
  }
  // mostra a criptomoeda escolhida e variaveis
  int aprov = 0, aceita = 0;
  float valor_vender, valor_sem_taxa, taxa, valor_final;
  limpa();
  // loop para pedir o valor
  do {
    printf("VENDER %s\n\n", cripto_maiusculo);

    printf("Carteira: R$ %.2f\n", carteira_reais);
    printf("Possui: %.3f %s\n\n", possui, cripto);

    printf("Cotacao: R$ %.2f\n", cotacao);
    printf("Taxa de venda: %d%%\n\n", taxa_venda);

    // pede para digitar o quanto ele deseja vender
    printf("Digite 0 para cancelar a venda\n");
    printf("Digite quantos %s deseja vender: ", cripto);

    resultado_scan = scanf("%f", &valor_vender);
    if (!resultado_scan) {
      limpa();
      printf("Digite um numero.\n\n");
      limpar_buffer();
      continue;
    }
    if (valor_vender == 0) {
      limpa();
      return 0;
    } else if (valor_vender < 0) {
      limpa();
      printf("digite um valor positivo.\n\n");
    } else if (valor_vender > possui) {
      limpa();
      printf("Voce nao tem %.3f %s de saldo suficiente\n\n", valor_vender,
             cripto);
    } else {
      // pega o o quanto ele deseja vender e multiplica pela cotacao para saber
      // o quanto ele vai receber sem a taxa
      valor_sem_taxa = roundf((valor_vender * cotacao) * 100) / 100;
      // calcula a taxa em relacao ao valor
      taxa = roundf(((valor_sem_taxa / 100) * taxa_venda) * 100) / 100;
      // aplica um taxa de no minimo 0.01 reais caso o valor seja menor que 0.01
      if (taxa < 0.01) {
        taxa = 0.01;
      }
      // calcula o valor final
      valor_final = valor_sem_taxa - taxa;
      // mostra os dados de quanto que ele vai receber
      limpa();
      printf("Valor a venda: %.3f %s\n", valor_vender, cripto);
      printf("Valor em reais da taxa: R$ %.2f\n", taxa);
      printf("Valor total para receber: R$ %.2f\n\n", valor_final);
      // confirma com o usuario se deseja aceitar
      printf("Digite 1 para prosseguir com a venda e 0 para voltar.\n");
      resultado_scan = scanf("%d", &aceita);
      // se o usuario digitou um ele confirma a venda caso escreva qualquer
      // outra coisa ele cancela a venda
      if (!resultado_scan || aceita == 0) {
        limpa();
        printf("Venda cancelada!");
        fflush(stdout);
        sleep(1);
        return 0;
      } else if (aceita == 1) {
        aprov = 1;
      }
    }
  } while (aprov == 0);

  // abre o arquivo para somar e subtrair os valores vendidos
  arquivo_usuario = fopen("usuario.bin", "r+b");
  if (!arquivo_usuario) {
    limpa();
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }
  // percorre o arquivo para encontrar o CPF correspondente
  while (fread(&usuario, sizeof(Usuario), 1, arquivo_usuario)) {
    if (strcmp(usuario.cpf, cpf) == 0) {
      // Atualiza o valor dos reais
      usuario.reais += valor_final;

      if (opcao == 1) {
        usuario.bitcoin -= valor_vender;
        escrever_extrato(cpf, 0, valor_vender, 1, time(NULL), taxa_venda,
                         cotacao);
      } else if (opcao == 2) {
        usuario.ethereum -= valor_vender;
        escrever_extrato(cpf, 0, valor_vender, 2, time(NULL), taxa_venda,
                         cotacao);
      } else if (opcao == 3) {
        usuario.ripple -= valor_vender;
        escrever_extrato(cpf, 0, valor_vender, 3, time(NULL), taxa_venda,
                         cotacao);
      }

      fseek(arquivo_usuario, -sizeof(Usuario),
            SEEK_CUR); // volta para a posicao anterior
      fwrite(&usuario, sizeof(Usuario), 1,
             arquivo_usuario); // grava a atualizacao
      break;
    }
  }
  fclose(arquivo_usuario);

  limpa();
  printf("vendido %.3f %s no valor de R$ %.2f \n\n", valor_vender, cripto,
         valor_final);
  printf("Aperte enter para voltar.\n");
  limpar_buffer();
  char lixo[1];
  fgets(lixo, sizeof(lixo), stdin); // le qualquer coisa que o usuario digitar

  return 0;
}
// funcao para atualizar a cotacao das criptomoedas
// -------------------------------------------------------------------------------
int atualizar_cotacao() {
  srand(time(NULL)); // faz com que pegue numeros aleatorios
  float cotacao;
  Criptomoedas criptomoedas;
  // gera um valor aleatorio entre -5% e 5%
  float variacao = (rand() % 11 - 5) / 100.0; // numero entre -0.05 e 0.05
  limpa();
  FILE *arquivo_cripto = fopen("criptomoedas.bin", "r+b");
  if (!arquivo_cripto) {
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }
  fread(&criptomoedas, sizeof(Criptomoedas), 1, arquivo_cripto);
  printf("Bitcoin pre ajuste: R$ %.2f\n", criptomoedas.bitcoin_cotacao);
  criptomoedas.bitcoin_cotacao += criptomoedas.bitcoin_cotacao * variacao;
  printf("Bitcoin pos ajuste: R$ %.2f\n\n", criptomoedas.bitcoin_cotacao);
  printf("Ethereum pre ajuste: R$ %.2f\n", criptomoedas.ethereum_cotacao);
  criptomoedas.ethereum_cotacao += criptomoedas.ethereum_cotacao * variacao;
  printf("Ethereum pos ajuste: R$ %.2f\n\n", criptomoedas.ethereum_cotacao);
  printf("Ripple pre ajuste: R$ %.2f\n", criptomoedas.ripple_cotacao);
  criptomoedas.ripple_cotacao += criptomoedas.ripple_cotacao * variacao;
  printf("Ripple pos ajuste: R$ %.2f\n\n", criptomoedas.ripple_cotacao);
  fseek(arquivo_cripto, -sizeof(Criptomoedas),
        SEEK_CUR); // volta para a posicao anterior
  fwrite(&criptomoedas, sizeof(Criptomoedas), 1,
         arquivo_cripto); // grava a atualizacao
  fclose(arquivo_cripto);

  // printa que foi atualizada

  printf("Cotacao atualizada com sucesso!\n\n");
  printf("Aperte enter para voltar.\n");

  char lixo[1];
  fgets(lixo, sizeof(lixo), stdin);

  return 1;
}

// MAIN ---------------------------
int main() {
  long long cpf_main;
  char cpf_char[12];
  // verifica se tem os dados do ADM no arquivo bin
  ADM();
  limpa();
  // verifica se tem o arquivo de criptomoedas.bin
  arq_cripto();
  limpa();
  // Pede o CPF para login
  cpf_main = Login_cpf();
  // converte o cpf para numero (long long)
  sprintf(cpf_char, "%lld", cpf_main);
  // pede a senha para o login
  Login_senha(cpf_char);
  int caso = -1;
  do {
    if (caso == -1) {
      limpar_buffer();
      caso = mostrar_console();
    } else {
      switch (caso) {
      case 1:
        consultar_saldo(cpf_char);
        break;

      case 2:
        ler_extrato(cpf_char);
        break;

      case 3:
        depositar_real(cpf_char);
        break;

      case 4:
        sacar_real(cpf_char);
        break;

      case 5:
        limpa();
        comprar_cripto(cpf_char);
        break;

      case 6:
        limpa();
        vender_cripto(cpf_char);
        break;

      case 7:
        limpa();
        atualizar_cotacao();
        break;

      case 8:
        limpa();
        add_usuario();
        break;

      case 9:
        limpa();
        remover_usuario();
        break;

      case 0:
        limpa();
        caso = -2;
        break;

      default:
        limpa();
        printf("Por favor, digite uma entrada valida!\n");
        caso = -1;
        sleep(1);
        break;
      }
      if (caso != -2) {
        caso = -1;
      }
    }
  } while (caso != -2);
  limpa();
  printf("Obrigado por utilizar os servicos de Exchange de criptomoedas!\n\n");
  printf("Made by: Akira e Guga\n\n");
  return 0;
}