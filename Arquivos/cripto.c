#include "common.h"

int criar_criptomoeda() {
    int aprovado;
    char nome_criptomoeda[20];
    int taxa_compra;

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

        aprovado = 1;
    } while (aprovado == 0);
    
    do{   
        printf("> Digite a taxa de compra da Criptomoeda.\n");
        printf("> Taxa de compra: ");
        if (scanf("%d", &taxa_compra) == 1) {
            aprovado = 1;
        } else {
            limpa_tela();
            printf("Digite um numero valido.\n");
            limpa_tela();
            delay(1500);
            aprovado = 0;
            while(getchar() != '\n');
        }
    } while (aprovado == 0);
    





    return 1;
}


















