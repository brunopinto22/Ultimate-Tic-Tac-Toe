/*----------Identificao----------*/

// - Nome: Bruno Pinto
// - N de aluno: 2021129642


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "galo.h"
#include "menu.h"
#include "verf.h"


int main(void) {

  pgalo g = NULL;       // array dinâmica
  phist h = NULL;       // ponteiro para a lista
  FILE * dados = NULL;  // ponteiro para ficheiro

  int esc, i, p = 1, x, y, index, tam = 0, htotal = 0;
  char sym = 'X', fn[54];

  do{

    // Menu Principal
    esc = criarmenu();
    system("cls");


    // Jogo
    switch(esc){

      // sair
      case 0:
        printf("Adeus ;)");
        return 0;
      break;



      // P VS P
      case 1:

        // verifica se existe algum jogo inacabado
        dados = fopen("jogo.bin","rb");
        if(dados != NULL){
          printf("Tem um jogo inacabado.\nPretende continuar?\n1 - S\t0 - N\n>>> ");
          scanf("%d",&i);
          system("cls");

          // caso o utilizador queira carregar o jogo
          if(i == 1)
            g = carregar(&index, &p, &tam);
        }
        fclose(dados);

        printf("\n---------- P1 VS P2 ----------\n     \033[44m P1 - X \033[0m\t\033[43m P2 - O \033[0m\n\n");

        do{

          if(tam > 0){
            jogadasAnt(h, htotal);  // mostra as jogadas anteriores
            printf("\n\033[100m Tabuleiro a jogar %d \033[0m\n\n",index);
          }

          board(g, &index);

          if(p == 1)
            printf("\033[44m");
          if(p == 2)
            printf("\033[43m");

          printf("\n P%d \033[0m - coordenadas (x,y): ", p);
          scanf("%d %d", &x, &y);

          i = p;
          // insere o valor no taburleiro
          g = insere(g, x, y, &p, &index, sym, &tam);


          if(p == 1){
            p++;
            sym = 'O';
          } else if(p == 2){
            p--;
            sym = 'X';
          }

          if(i != p)
            h = guardarJogada(h, x, y, i, &htotal);  // guarda a jogada no historico


          fflush(stdin);

          // caso haja vencedor
          if(verf(g) != 0){
            system("cls");

            if(verf(g) == 1)
              printf("     \033[44m  ! P%d GANHOU !  \033[0m\n\n",verf(g));
            if(verf(g) == 2)
              printf("     \033[43m  ! P%d GANHOU !  \033[0m\n\n",verf(g));

            board(g, &index);

            fflush(stdin);
            printf("Insira o nome pelo qual quer guardar o jogo\n>>> ");
            scanf("%49[^\n]",fn);

            strcat(fn,".txt");
            // guarda o jogo
            guardar(h, fn, verf(g));

            // guarda o tabuleiro
            guardarTab(g, fn, verf(g));

            break;
          }

          // sair a meio do jogo
          if(x == -1 || y == -1){
            system("cls");

            // guarda o jogo
            guardarMid(g, &index, &p, &tam);

            break;
          }

        }while(x != -1 || y != -1);

      break;



      // P VS CPU
      case 2:

        // verifica se existe algum jogo inacabado
        dados = fopen("jogo.bin","rb");
        if(dados != NULL){
          printf("Tem um jogo inacabado.\nPretende continuar?\n1 - S\t0 - N\n>>> ");
          scanf("%d",&i);
          system("cls");

          // caso o utilizador queira carregar o jogo
          if(i == 1)
            g = carregar(&index, &p, &tam);
        }
        fclose(dados);

        printf("\n---------- P1 VS CPU ----------\n     \033[44m P1 - X \033[0m\t\033[43m CPU - O \033[0m\n\n");

        do{

          if(p == 1){

            if(tam > 0)
              jogadasAnt(h, htotal);  // mostra as jogadas anteriores

            printf("\n\033[100m Tabuleiro a jogar %d \033[0m\n\n",index);
            board(g, &index);
            printf("\n\033[44m P%d \033[0m - coordenadas (x,y): ", p);
            scanf("%d %d", &x, &y);
          }
          if(p == 2){

            system("cls");
            int i = 1;
            do{
              // funcao para gerar um valor aleatorio para a joagado da CPU
              srand( (unsigned)time(NULL) );
              x = 1+rand()%9;
              y = 1+rand()%9;

              if(i == 1)
                printf("Pensando.");
              if(i == 2)
                printf("Pensando..");
              if(i == 3){
                printf("Pensando...");
                i = 0;
              }

              delay(0.7);
              system("cls");

              i++;
            }while(indexgalo(x,y) != index);
          }

          i = p;
          g = insere(g, x, y, &p, &index, sym, &tam);

          if(p == 1){
            p++;
            sym = 'O';
          } else if(p == 2){
            p--;
            sym = 'X';
          }

          if(i != p)
            h = guardarJogada(h, x, y, i, &htotal);  // guarda a jogada no historico

          fflush(stdin);

          // caso haja vencedor
          if(verf(g) != 0){
            system("cls");

            if(verf(g) == 1)
              printf("     \033[44m  ! P%d GANHOU !  \033[0m\n\n",verf(g));
            if(verf(g) == 2)
              printf("     \033[43m  ! P%d GANHOU !  \033[0m\n\n",verf(g));

            board(g, &index);

            fflush(stdin);
            printf("Insira o nome pelo qual quer guardar o jogo\n>>> ");
            scanf("%49[^\n]",fn);

            strcat(fn,".txt");
            // guarda o jogo
            guardar(h, fn, verf(g));

            // guarda o tabuleiro
            guardarTab(g, fn, verf(g));

            free(g);

            break;
          }

          // sair a meio do jogo
          if(x == -1 || y == -1){
            system("cls");

            // guarda o jogo
            guardarMid(g, &index, &p, &tam);

            break;
          }

        }while(x != -1 || y != -1);

      break;


      case 3:
        help();
      break;

    }
  }while(esc != 0);

  free(g);

}
