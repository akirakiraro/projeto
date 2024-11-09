#include "../Arquivos/common.h"

int main() {
  
  char CPF_logado[12];
  do{
    int logado = 0;
    do{
      Menu_inicial_usuario ();
      switch (escolher_operacao(0,1,"a opcao")){
        case 0:
          encerrar_programa ();

        case 1:
          if (login_usuario(CPF_logado) == 1) {
            logado = 1;
          }
          break;
      }
    } while (logado == 0);


    int sair = 0;
    do{
      Menu_usuario();
      switch (escolher_operacao(0,7,"a opcao")){
        case 0:
          encerrar_programa ();
        case 1:
          // consultar saldo
          consultar_saldo(CPF_logado);
          break;
        case 2:
          // consultar extrato
          break;
        case 3:
          // depositar reais
          depositar_real(CPF_logado);
          break;
        case 4:
          // sacar reais
          sacar_real(CPF_logado);
          break;
        case 5:
          // comprar criptomoedas
          break;
        case 6:
          // vender criptomoedas
          break;
        case 7:
          // atualizar cotacao
          break;
      }
    } while (sair == 0);
  } while (true);
  return 0;
}