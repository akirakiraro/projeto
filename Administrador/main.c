#include "../Arquivos/common.h"

// Versao para ADM

int main() {
  

  int logado = 0;
  do{
    Menu_inicial_adm ();
    switch (escolher_operacao(0,3,"a opcao")){
      case 0:
        encerrar_programa ();
      case 1:
        break;
      case 2:
        break;
    }
  } while (logado != 0);
  
  

  return 0;
}