#include "../Arquivos/common.h"

// Versao para ADM

int main() {
  
  char CPF_logado[12];
  do{
    int logado = 0;
    do{
      Menu_inicial_adm ();
      switch (escolher_operacao(0,3,"a opcao")){
        case 0:
          encerrar_programa ();

        case 1:
          if (logar_administrador(CPF_logado) == 1) {
            logado = 1;
          }
          break;

        case 2:
          adicionar_administrador();
          break;

      }
    } while (logado == 0);


    int sair = 0;
    do{
      Menu_Adm();
      switch (escolher_operacao(0,7,"a opcao")){
        case 0:
          encerrar_programa ();
        case 1:
          criar_investidor();
          break;
        case 2:
          excluir_investidor();
          break;
        case 3:
          criar_criptomoeda();
          break;
      }
    } while (sair == 0);
  } while (true);
  return 0;
}