#include "common.h"


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

// funcao para comprar criptomoedas
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





















