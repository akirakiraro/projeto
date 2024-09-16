#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h> // Usar esse daqui no replit
#include <Windows.h> // usar esse daqui no vscode
// quando ir pro windows tem que trocar todos os usleep por Sleep
// e trocar tbm o clear  por cls

// limpa o terminal
void limpa() { system("cls"); }
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

int add_usuario(char cpf[12], int senha) {
  int valor0 = 0;
  FILE *login; // define que login  eh um arquivo
  login =
      fopen("usuario.bin", "ab"); // abre o arquivo em modo de "write binario"
  fwrite(&cpf, sizeof(int), 1, login);   // escreve no arquivo o cpf
  fwrite(&senha, sizeof(int), 1, login); // escreve no arquivo a senha
  // como eu preciso ter um valor nessas variaveis e a conta é nova ele nao tem
  // q comecar com dinheiros
  fwrite(&valor0, sizeof(int), 1, login); // reais
  fwrite(&valor0, sizeof(int), 1, login); // bitcoin
  fwrite(&valor0, sizeof(int), 1, login); // ethereum
  fwrite(&valor0, sizeof(int), 1, login); // ripple
  fclose(login);                          // fecha o arquivo
}

// struct para definir o usuario
typedef struct {
  char cpf[12]; // CPF como string (11 dígitos + terminador nulo)
  int senha;    // Senha como int
  int reais;
  int bitcoin;
  int ethereum;
  int ripple;
} Usuario;
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
    Sleep(1000);

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
          printf("CPF inválido, deve conter apenas números.\n\n");
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
  char entrada[10]; // Buffer para armazenar a entrada do usuário
  int opcao;

  do {
    limpa();
    printf("Bem vindo ao Projeto 1 - Exchange de criptomoedas!\n\n");
    printf("1. Consultar saldo. (FEITO)\n");
    printf("2. Consultar extrato. (Nao feito)\n");
    printf("3. Depositar reais. (Nao feito, proximo a fazer)\n");
    printf("4. Sacar reais. (Nao feito)\n");
    printf("5. Comprar criptomoedas. (Nao feito)\n");
    printf("6. Vender criptomoedas. (Nao feito)\n");
    printf("7. Sair\n\n");
    printf("Digite a opcao desejada (1-7): ");

    // Captura a entrada como uma string
    fgets(entrada, sizeof(entrada), stdin);

    // Verifica se o usuario apertou apenas Enter
    if (entrada[0] == '\n') {
      limpa();
      printf("Entrada vazia! Por favor, insira uma opcao valida.\n");
      Sleep(2000);
      continue;
    }

    // Converte a string para um numero
    if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 1 || opcao > 7) {
      limpa();
      printf("Opcao invalida! Por favor, escolha um numero entre 1 e 6.\n");
      Sleep(2000);
    }
  } while (opcao < 1 || opcao > 7);

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
    printf("Reais: %d\n", usuario.reais);
    printf("Bitcoin: %d\n", usuario.bitcoin);
    printf("Ethereum: %d\n", usuario.ethereum);
    printf("Ripple: %d\n", usuario.ripple);
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
int depositar_real() {
  float valor_depositado;
  int deposito_aprovado = 0, resultado_scan = 0;
  // faz um loop pro usuario digitar o valor valido
  limpa();
  do {
    printf("Digite o valor do deposito: \n");
    resultado_scan = scanf("%f", &valor_depositado);

    if (resultado_scan != 1) {
      limpa();
      printf("Entrada invalida, digite um numero.\n\n");

      // limpa o buffer de entrada
      while (getchar() != '\n')
        ;
    }
    if (valor_depositado < 0) {
      limpa();
      printf("Por favor digite um numero positivo.\n\n");
      continue; // volta para inicio do loop para pedir a senha dnv
    }
  } while (resultado_scan != 1);

  

  limpa();
  printf("Deposito aprovado no valor de R$ %.2f\n", valor_depositado);
  printf("\nAperte enter para voltar.");
  limpar_buffer();
  char lixo[1];
  fgets(lixo, sizeof(lixo), stdin);
  return 1;
}
int main() {
  long long cpf_main;
  char cpf_char[12];
  // verifica se tem os dados do ADM no arquivo bin
  ADM();
  limpa();
  cpf_main = Login_cpf();
  sprintf(cpf_char, "%lld", cpf_main);
  Login_senha(cpf_char);
  int caso = 0;
  do {
    if (caso == 0) {
      limpar_buffer();
      caso = mostrar_console();
    } else {
      switch (caso) {
      case 1:
        consultar_saldo(cpf_char);
        break;

      case 2:
        printf("Segunda\n");
        caso = 7;
        break;

      case 3:
        depositar_real();
        break;

      default:
        limpa();
        printf("Por favor, digite uma entrada valida!\n");
        caso = 0;
        Sleep(2000);
        break;
      }
      if (caso != 7) {
        caso = 0;
      }
    }
  } while (caso != 7);
  return 0;
}