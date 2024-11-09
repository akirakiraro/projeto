#include "common.h"

int verificar_nome_cripto (char *nome) {
    FILE *arquivo = fopen("Storage/Criptomoedas.bin", "rb");
    if (arquivo == NULL) {
        fclose(arquivo);
        arquivo = fopen("Storage/Criptomoedas.bin", "wb");
        fclose(arquivo);
        return 0;
    }

    Criptomoedas criptomoeda;

    while (fread(&criptomoeda, sizeof(Criptomoedas), 1, arquivo) == 1) {
        if (strcmp(criptomoeda.Nome_Cripto, nome) == 0) {
            return -1;
        }
    }

    fclose(arquivo);
    return 1;

}

int criar_criptomoeda() {
    int aprovado;
    char nome_criptomoeda[20];
    int taxa_compra, taxa_venda;
    float cotacao_inicial;

    do {
        aprovado = 0;
        limpa_tela();
        printf("> Digite o nome da Criptomoeda.\n");
        printf("> Nome: ");
        fgets(nome_criptomoeda, 20, stdin);
        verificar_buffer(nome_criptomoeda);

        if (strcmp(nome_criptomoeda, "0") == 0) {
            return -1;
        }

        if (verificar_nome_cripto(nome_criptomoeda) == -1) {
            limpa_tela();
            printf("Ja existe uma criptomoeda com esse nome.\n");
            delay(1500);
            aprovado = 0;
        } else {
            aprovado = 1;
        }

    } while (aprovado == 0);
    
    do{   
        printf("> Digite a taxa de compra da Criptomoeda.\n");
        printf("> Taxa de compra: ");
        if (scanf("%d", &taxa_compra) == 1) {
            if (taxa_compra < 0 || taxa_compra > 99) {
                limpa_tela();
                printf("Digite um valor entre 0%% e 99%%.\n");
                delay(1500);
                limpa_tela();
                aprovado = 0;
            } else {
                aprovado = 1;
            }
        } else {
            limpa_tela();
            printf("Digite um numero valido.\n");
            delay(1500);
            limpa_tela();
            aprovado = 0;
            while(getchar() != '\n');
        }
    } while (aprovado == 0);
    
    do {
        printf("> Digite a taxa de venda da Criptomoeda.\n");
        printf("> Taxa de venda: ");
        if (scanf("%d", &taxa_venda) == 1) {
            if (taxa_venda < 0 || taxa_venda > 99) {
                limpa_tela();
                printf("Digite um valor entre 0%% e 99%%.\n");
                delay(1500);
                limpa_tela();
                aprovado = 0;
            } else {
                aprovado = 1;
            }
        } else {
            limpa_tela();
            printf("Digite um numero valido.\n");
            delay(1500);
            limpa_tela();
            aprovado = 0;
            while(getchar() != '\n');
        }
    } while (aprovado == 0);

    do{
        printf("> Digite a cotacao inicial da sua Criptomoeda.\n");
        printf("> Cotacao inicial: ");
        if (scanf("%f", &cotacao_inicial) == 1) {
            if (cotacao_inicial > 0) {
                aprovado = 1;
            } else {
                limpa_tela();
                printf("Digite um numero maior que 0.\n");
                delay(1500);
                limpa_tela();
                aprovado = 0;
            }
        } else {
            limpa_tela();
            printf("Digite um numero valido.\n");
            delay(1500);
            limpa_tela();
            aprovado = 0;
            while(getchar() != '\n');
        }
    } while (aprovado == 0);

    do{
        limpa_tela();
        printf("Nome: %s\n", nome_criptomoeda);
        printf("Taxa de compra: %d\n", taxa_compra);
        printf("Taxa de venda: %d\n", taxa_venda);
        printf("Cotacao inicial: %f\n\n", cotacao_inicial);
        printf("Para confirmar a nova criptomoeda digite 1, caso deseje cancelar digite 0.\n");
        printf("Confirmacao: ");
        if (scanf("%d", &aprovado) == 1) {
            if (aprovado == 1) {
                aprovado = 1;
            } else {
                return -1;
            }
        } else {
            limpa_tela();
            aprovado = 0;
        }

    }while (aprovado == 0);

    FILE *arquivo_cripto = abrir_arquivo("Storage/Criptomoedas.bin", "ab");

    Criptomoedas criptomoeda_nova;
    snprintf(criptomoeda_nova.Nome_Cripto, sizeof(criptomoeda_nova.Nome_Cripto), "%s", nome_criptomoeda);
    criptomoeda_nova.taxa_compra = taxa_compra;
    criptomoeda_nova.taxa_venda = taxa_venda;
    criptomoeda_nova.cotacao = cotacao_inicial;
    fwrite(&criptomoeda_nova, sizeof(Criptomoedas), 1, arquivo_cripto);
    fclose(arquivo_cripto);

    return 1;
}

int excluir_criptomoeda() {
    int aprovado;
    char nome_criptomoeda[20];
    
    do{
        limpa_tela();
        printf("Digite o nome da Criptomoeda que deseja excluir ou 0 para voltar.\n");
        printf("Nome: ");
        fgets(nome_criptomoeda, 20, stdin);
        verificar_buffer(nome_criptomoeda);

        if (strcmp(nome_criptomoeda, "0") == 0) {
            return -1;
        }

        if (verificar_nome_cripto(nome_criptomoeda) != -1) {
            limpa_tela();
            printf("Nao existe nenhuma criptomoeda com esse nome.\n");
            printf("Verifique as maiusculas e minusculas.\n");
            delay(1500);
            aprovado = 0;
        } else {
            FILE *arq = abrir_arquivo("Storage/Criptomoedas.bin", "rb");
            Criptomoedas criptomoeda_excluida;
            aprovado = 0;

            while (fread(&criptomoeda_excluida, sizeof(Criptomoedas), 1, arq) == 1) {
                if (strcmp(criptomoeda_excluida.Nome_Cripto, nome_criptomoeda) == 0) {
                    limpa_tela();
                    printf("Nome da Criptomoeda: %s\n", criptomoeda_excluida.Nome_Cripto);
                    printf("Taxa de compra: %d\n", criptomoeda_excluida.taxa_compra);
                    printf("Taxa de venda: %d\n", criptomoeda_excluida.taxa_venda);
                    printf("Cotacao: %.2f\n\n", criptomoeda_excluida.cotacao);
                    printf("Digite 1 para confirma a exclusao da criptomoeda.\n");
                    printf("Confirmacao: ");
                    if (scanf("%d", &aprovado) != 1 || aprovado != 1) {
                        fclose(arq);
                        printf("Operacao cancelada.\n");
                        delay(1500);
                        return -1;
                    }
                    break;
                }
            }
            fclose(arq);
            
            if (aprovado == 1) {
                FILE *arquivo_cripto = abrir_arquivo("Storage/Criptomoedas.bin", "rb");

                fseek(arquivo_cripto, 0, SEEK_END);
                long tamanho_arquivo = ftell(arquivo_cripto);
                int total_criptomoedas = tamanho_arquivo / sizeof(Criptomoedas);
                fseek(arquivo_cripto, 0, SEEK_SET);
                
                Criptomoedas *criptomoeda = (Criptomoedas *)malloc(total_criptomoedas * sizeof(Criptomoedas));
                if (criptomoeda == NULL) {
                    printf("Erro de memoria.\n");
                    fclose(arquivo_cripto);
                    return -1;
                }

                fread(criptomoeda, sizeof(Criptomoedas), total_criptomoedas, arquivo_cripto);
                fclose(arquivo_cripto);

                int encontrado = 0;
                int novo_total = 0;

                for (int i = 0; i < total_criptomoedas; i++) {
                    if (strcmp(criptomoeda[i].Nome_Cripto, nome_criptomoeda) == 0) {
                        encontrado = 1;
                    } else {
                        criptomoeda[novo_total++] = criptomoeda[i];
                    }
                }

                if (encontrado) {
                    arquivo_cripto = abrir_arquivo("Storage/Criptomoedas.bin", "wb");
                    

                    fwrite(criptomoeda, sizeof(Criptomoedas), novo_total, arquivo_cripto);
                    fclose(arquivo_cripto);

                    limpa_tela();
                    printf("Criptomoeda %s excluida com sucesso.\n", nome_criptomoeda);
                    delay(1500);

                }

                free(criptomoeda);
            }
        }
    } while (aprovado == 0);

    return 1;
}

int atualizar_cripto () {
    int aprovado;
    char nome_criptomoeda[20];

    do{
        limpa_tela();
        printf("Digite o nome da Criptomoeda que deseja atualizar.\n");
        printf("Nome: ");
        fgets(nome_criptomoeda, 20, stdin);
        verificar_buffer(nome_criptomoeda);

        if (strcmp(nome_criptomoeda, "0") == 0) {
            return -1;
        }

        if (verificar_nome_cripto(nome_criptomoeda) != -1) {
            limpa_tela();
            printf("Nao existe nenhuma criptomoeda com esse nome.\n");
            printf("Verifique as maiusculas e minusculas.\n");
            delay(1500);
            aprovado = 0;
        } else {
            FILE *arquivo_cripto = abrir_arquivo("Storage/Criptomoedas.bin", "rb+");

            Criptomoedas criptomoeda;

            while (fread(&criptomoeda, sizeof(Criptomoedas), 1, arquivo_cripto) == 1) {
                if (strcmp(criptomoeda.Nome_Cripto, nome_criptomoeda) == 0) {
                    printf("Cotacao atual: %.2f\n", criptomoeda.cotacao);
                    printf("Digite a nova cotacao: ");
                    if (scanf("%f", &criptomoeda.cotacao) != 1 || criptomoeda.cotacao <= 0) {
                        printf("Entrada invalida.\n");
                        fclose(arquivo_cripto);
                        return -1;
                    }

                    fseek(arquivo_cripto, -sizeof(Criptomoedas), SEEK_CUR);
                    fwrite(&criptomoeda, sizeof(Criptomoedas), 1, arquivo_cripto);
                    aprovado = 1;
                    break;
                }
            }
            fclose(arquivo_cripto);
        }
    } while (aprovado == 0);
    return 1;
}

// funcoes para usuairos

int comprar_criptomoeda (char cpf[12]) {
    float saldo_reais;
    limpa_tela();

    FILE *arquivo_usuarios = abrir_arquivo("Storage/Usuarios.bin","rb");

    Usuario usuario;

    while(fread(&usuario,sizeof(Usuario), 1, arquivo_usuarios) == 1) {
        if (strcmp(usuario.cpf, cpf) == 0) {
            saldo_reais = usuario.real;
        }
    }
    fclose(arquivo_usuarios);

    char nome_criptomoeda[20];

    mostrar_criptomoedas();


    printf("> Digite o nome da Criptomoeda que deseja comprar.\n");
    printf("> Nome: ");

    getchar();

    return 1;
}

void mostrar_criptomoedas () {
    FILE *arquivo_criptomoedas = abrir_arquivo("Storage/Criptomoedas.bin","rb");

    Criptomoedas criptomoeda;

    printf("|----------------------------------------------------------------|\n");
    printf("|                    CRIPTOMOEDAS DISPONIVEIS                    |\n");
    printf("|----------------------------------------------------------------|\n");
    printf("| Nome             taxa venda    taxa compra    cotacao atual    |\n");
    printf("|----------------------------------------------------------------|\n");


    while(fread(&criptomoeda, sizeof(Criptomoedas), 1, arquivo_criptomoedas) == 1) {
        printf("| %-20s %02d %%          %02d %%       R$ %-13.2f |\n", 
        criptomoeda.Nome_Cripto, 
        criptomoeda.taxa_venda, 
        criptomoeda.taxa_compra, 
        criptomoeda.cotacao);
    }

    printf("|----------------------------------------------------------------|\n\n");

    fclose(arquivo_criptomoedas);
}









