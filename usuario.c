#include "common.h"

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

// nao vai existir mais
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



