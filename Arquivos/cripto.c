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
    int aprovado = 0;


    do{
        limpa_tela();
        if (mostrar_criptomoedas() == -1) {
            limpa_tela();
            printf("Nao ha Criptomoedas disponiveis para compra.\n");
            printf("Por favor entre em contato com um Administrador.\n");
            delay(3000);
            return -1;
        }
        printf("> Digite 0 para voltar ou o nome da Criptomoeda que deseja comprar.\n");
        printf("> Saldo atual: R$ %.2f\n", saldo_reais);
        printf("> Nome: ");
        fgets(nome_criptomoeda, 20, stdin);
        verificar_buffer(nome_criptomoeda);

        if (strcmp(nome_criptomoeda, "0") == 0) {
            return -1;
        }

        if (verificar_nome_cripto(nome_criptomoeda) == -1) {
            aprovado = 1;
        } else {
            limpa_tela();
            printf("Nao existe uma criptomoeda com esse nome.\n");
            delay(1500);
            aprovado = 0;
        }

    } while (aprovado == 0);

    float valor_minimo_compra, valor_minimo_sem_taxa;

    FILE *arquivo_criptomoedas = abrir_arquivo("Storage/Criptomoedas.bin","rb");
    Criptomoedas criptomoeda;

    while(fread(&criptomoeda, sizeof(Criptomoedas), 1, arquivo_criptomoedas) == 1) {
        if (strcmp(criptomoeda.Nome_Cripto, nome_criptomoeda) == 0) {
            valor_minimo_sem_taxa = 0.001 * criptomoeda.cotacao;
            valor_minimo_compra = valor_minimo_sem_taxa + ((valor_minimo_sem_taxa / 100) * criptomoeda.taxa_compra);
            if (saldo_reais < valor_minimo_compra) {
                limpa_tela();
                printf("> Voce nao possui o saldo minimo para comprar essa criptomoeda.\n");
                printf("> Valor minimo de compra: R$ %.2f\n", valor_minimo_compra);
                delay(2000);
                fclose(arquivo_criptomoedas);
                return 0;
            }
            break;
        }
    }
    fclose(arquivo_criptomoedas);

    FILE *arquivo_Saldo_Criptomoedas = abrir_arquivo("Storage/Saldo_Criptomoedas.bin","rb");
    Moeda_usuario saldo;

    int cripto_encontrada = 0;

    while(fread(&saldo, sizeof(Moeda_usuario), 1, arquivo_Saldo_Criptomoedas) == 1) {
        if (strcmp(saldo.cpf, cpf) == 0) {
            if (strcmp(saldo.criptomoeda, criptomoeda.Nome_Cripto) == 0) {
                cripto_encontrada = 1;
                break;
            }
        }
    }

    if (cripto_encontrada == 0) {
        saldo.quantidade = 0;
    }

    fclose(arquivo_Saldo_Criptomoedas);

    float quantidade_comprada;
    aprovado = 0;
    do {        
        limpa_tela();
        printf("Criptomoeda: %s\n", criptomoeda.Nome_Cripto);
        printf("Taxa de Venda: %02d %%\n", criptomoeda.taxa_venda);
        printf("Taxa de Compra: %02d %%\n", criptomoeda.taxa_compra);
        printf("Cotacao atual: R$ %.2f\n\n", criptomoeda.cotacao);

        printf("Saldo atual: R$ %.2f\n", saldo_reais);
        printf("Saldo de criptomoeda atual: %.3f\n", saldo.quantidade);
        if (valor_minimo_compra < 0.009) {
            printf("\n");
        } else {
            printf("Valor minimo de investimento: %.2f\n\n", valor_minimo_compra);
        }
        
        printf("Digite a quantidade de %s que deseja comprar.\n", criptomoeda.Nome_Cripto);
        printf("Quantidade: ");
        if (scanf("%f", &quantidade_comprada) != 1) {
            limpa_tela();
            printf("Digite um numero valido.\n");
            delay(1500);
            limpa_tela();
            aprovado = 0;
            while(getchar() != '\n');
        } else if (quantidade_comprada == 0) {
            return 0;
        } else if (quantidade_comprada < 0.001) {
            limpa_tela();
            printf("Digite uma quantidade acima de 0.001 %s.\n", criptomoeda.Nome_Cripto);
            delay(1500);
            limpa_tela();
            aprovado = 0;
            while(getchar() != '\n');
        } else {
            aprovado = 1;
        }

    } while (aprovado == 0);

    float valor_comprado_sem_taxa, valor_comprado;

    valor_comprado_sem_taxa =  (quantidade_comprada * criptomoeda.cotacao);
    valor_comprado = valor_comprado_sem_taxa + ((valor_comprado_sem_taxa / 100) * criptomoeda.taxa_compra);

    arquivo_usuarios = abrir_arquivo("Storage/Usuarios.bin","rb+");
    Usuario usuario2;
    while(fread(&usuario2, sizeof(Usuario), 1, arquivo_usuarios) == 1) {
        if (strcmp(usuario2.cpf, cpf) == 0) {
            usuario2.real -= valor_comprado;

            fseek(arquivo_usuarios, -sizeof(Usuario), SEEK_CUR);
            fwrite(&usuario2, sizeof(Usuario), 1, arquivo_usuarios);
            fclose(arquivo_usuarios);
            break; 
        }
    }


    arquivo_Saldo_Criptomoedas = abrir_arquivo("Storage/Saldo_Criptomoedas.bin","rb+");
    Moeda_usuario saldo_cripto;

    aprovado = 0;

    while(fread(&saldo_cripto, sizeof(Moeda_usuario), 1, arquivo_Saldo_Criptomoedas) == 1) {
        if (strcmp(saldo_cripto.cpf, cpf) == 0) {
            if (strcmp(saldo_cripto.criptomoeda, criptomoeda.Nome_Cripto) == 0) {
                saldo_cripto.quantidade += quantidade_comprada;
                aprovado = 1;

                fseek(arquivo_Saldo_Criptomoedas, -sizeof(Moeda_usuario), SEEK_CUR);
                fwrite(&saldo_cripto, sizeof(Moeda_usuario), 1, arquivo_Saldo_Criptomoedas);
                break;
            }
        }
    }

    fclose(arquivo_Saldo_Criptomoedas);
    
    if (aprovado == 0) {
        arquivo_Saldo_Criptomoedas = abrir_arquivo("Storage/Saldo_Criptomoedas.bin","ab");
        strcpy(saldo_cripto.cpf, cpf);
        strcpy(saldo_cripto.criptomoeda, criptomoeda.Nome_Cripto);
        saldo_cripto.quantidade = quantidade_comprada;
        fwrite(&saldo_cripto, sizeof(Moeda_usuario), 1, arquivo_Saldo_Criptomoedas);
        fclose(arquivo_Saldo_Criptomoedas);
    }

    limpa_tela();
    printf("A sua compra de %.3f de %s foi realizada com sucesso.\n", quantidade_comprada, criptomoeda.Nome_Cripto);
    delay(1500);
    escrever_extrato(cpf, 1, quantidade_comprada, saldo_cripto.criptomoeda, time(NULL), criptomoeda.taxa_compra, criptomoeda.cotacao);
    return 1;
}

int vender_criptomoeda (char cpf[12]) {
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
    int aprovado = 0;

    do{
        limpa_tela();
        if (mostrar_criptomoedas_possuidas(cpf) == -1) {
            limpa_tela();
            printf("Voce nao possui Criptomoedas.\n");
            delay(2000);
            return -1;
        }
        printf("> Digite 0 para voltar ou o nome da Criptomoeda que deseja vender.\n");
        printf("> Nome: ");
        fgets(nome_criptomoeda, 20, stdin);
        verificar_buffer(nome_criptomoeda);

        if (strcmp(nome_criptomoeda, "0") == 0) {
            return -1;
        }

        if (verificar_nome_cripto(nome_criptomoeda) == -1) {
            aprovado = 1;
        } else {
            limpa_tela();
            printf("Nao existe uma criptomoeda com esse nome.\n");
            delay(1500);
            aprovado = 0;
        }

    } while (aprovado == 0);

    FILE *arquivo_Saldo_Criptomoedas = abrir_arquivo("Storage/Saldo_Criptomoedas.bin","rb");
    Moeda_usuario saldo;

    int cripto_encontrada = 0;

    while(fread(&saldo, sizeof(Moeda_usuario), 1, arquivo_Saldo_Criptomoedas) == 1) {
        if (strcmp(saldo.cpf, cpf) == 0) {
            if (strcmp(saldo.criptomoeda, nome_criptomoeda) == 0) {
                cripto_encontrada = 1;
                break;
            }
        }
    }

    fclose(arquivo_Saldo_Criptomoedas);

    FILE *arquivo_criptomoedas = abrir_arquivo("Storage/Criptomoedas.bin","rb");
    Criptomoedas criptomoeda;

    while(fread(&criptomoeda, sizeof(Criptomoedas), 1, arquivo_criptomoedas) == 1) {
        if (strcmp(criptomoeda.Nome_Cripto, nome_criptomoeda) == 0) {
            break;
        }
    }

    float quantidade_vendida;
    aprovado = 0;
    do {        
        limpa_tela();
        printf("Criptomoeda: %s\n", criptomoeda.Nome_Cripto);
        printf("Taxa de Venda: %02d %%\n", criptomoeda.taxa_venda);
        printf("Taxa de Compra: %02d %%\n", criptomoeda.taxa_compra);
        printf("Cotacao atual: R$ %.2f\n\n", criptomoeda.cotacao);

        printf("Saldo atual: R$ %.2f\n", saldo_reais);
        printf("Saldo de criptomoeda atual: %.3f\n", saldo.quantidade);
        
        printf("Digite a quantidade de %s que deseja vender.\n", criptomoeda.Nome_Cripto);
        printf("Quantidade: ");
        if (scanf("%f", &quantidade_vendida) != 1) {
            limpa_tela();
            printf("Digite um numero valido.\n");
            delay(1500);
            aprovado = 0;
            while(getchar() != '\n');
        } else if (quantidade_vendida == 0) {
            return 0;
        } else if (quantidade_vendida <= 0.001) {
            limpa_tela();
            printf("Digite uma quantidade acima de 0.001 %s.\n", criptomoeda.Nome_Cripto);
            delay(1500);
            aprovado = 0;
            while(getchar() != '\n');
        } else if (quantidade_vendida > saldo.quantidade) {
            limpa_tela();
            printf("Saldo de %s indisponivel.\n", saldo.quantidade);
            aprovado = 0;
            while(getchar() != '\n');
            delay(1500);
        } else {
            aprovado = 1;
        }

    } while (aprovado == 0);

    float valor_vendido_sem_taxa, valor_vendido;

    valor_vendido_sem_taxa =  (quantidade_vendida * criptomoeda.cotacao);
    valor_vendido = valor_vendido_sem_taxa - ((valor_vendido_sem_taxa / 100) * criptomoeda.taxa_venda);

    arquivo_usuarios = abrir_arquivo("Storage/Usuarios.bin","rb+");
    Usuario usuario2;
    while(fread(&usuario2, sizeof(Usuario), 1, arquivo_usuarios) == 1) {
        if (strcmp(usuario2.cpf, cpf) == 0) {
            usuario2.real += valor_vendido;

            fseek(arquivo_usuarios, -sizeof(Usuario), SEEK_CUR);
            fwrite(&usuario2, sizeof(Usuario), 1, arquivo_usuarios);
            fclose(arquivo_usuarios);
            break; 
        }
    }


    arquivo_Saldo_Criptomoedas = abrir_arquivo("Storage/Saldo_Criptomoedas.bin","rb+");
    Moeda_usuario saldo_cripto;


    while(fread(&saldo_cripto, sizeof(Moeda_usuario), 1, arquivo_Saldo_Criptomoedas) == 1) {
        if (strcmp(saldo_cripto.cpf, cpf) == 0) {
            if (strcmp(saldo_cripto.criptomoeda, criptomoeda.Nome_Cripto) == 0) {
                saldo_cripto.quantidade -= quantidade_vendida;

                fseek(arquivo_Saldo_Criptomoedas, -sizeof(Moeda_usuario), SEEK_CUR);
                fwrite(&saldo_cripto, sizeof(Moeda_usuario), 1, arquivo_Saldo_Criptomoedas);
                break;
            }
        }
    }

    fclose(arquivo_Saldo_Criptomoedas);

    limpa_tela();
    printf("A sua venda de %.3f de %s foi realizada com sucesso.\n", quantidade_vendida, criptomoeda.Nome_Cripto);
    delay(1500);
    escrever_extrato(cpf, 0, quantidade_vendida, saldo_cripto.criptomoeda, time(NULL), criptomoeda.taxa_compra, criptomoeda.cotacao);
    return 1;
}

int atualizar_cripto_usuario () {
    char nome_cripto_anterior[20];
    float variacao, cotacao_antes, aleatorio;
    srand(time(NULL));

    FILE *arquivo_cripto = abrir_arquivo("Storage/Criptomoedas.bin","rb+");
    Criptomoedas cripto;
    int encontrada = 0;

    while(fread(&cripto, sizeof(Criptomoedas), 1, arquivo_cripto) == 1) {
        encontrada = 1;
        if (strcmp(cripto.Nome_Cripto, nome_cripto_anterior) == 0) {
            break;
        } else {
            strcpy(nome_cripto_anterior, cripto.Nome_Cripto);
        }

        aleatorio = -5.0 + ((rand() % 101) / 10.0);
        variacao = ((int) (aleatorio * 10) / 10.0);
        cotacao_antes = cripto.cotacao;
        cripto.cotacao = cotacao_antes * (100 - variacao) / 100;
        if (cripto.cotacao < 0) {
            cripto.cotacao = 0;
        }

        fseek(arquivo_cripto, -sizeof(Criptomoedas), SEEK_CUR);
        fwrite(&cripto, sizeof(Criptomoedas), 1, arquivo_cripto);
    }

    fclose(arquivo_cripto);

    if (encontrada == 0) {
        limpa_tela();
        printf("Nao ha criptomoedas disponiveis.\n");
        printf("Fale com um administrador.\n");
        delay(2000);
        return -1;
    }

    limpa_tela();
    printf("Todas as Criptomoedas foram atualizadas.\n");
    delay(2000);
    return 1;
}







