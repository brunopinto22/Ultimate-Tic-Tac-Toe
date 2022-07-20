/*----------Identificação----------*/

// - Nome: Bruno Pinto
// - Nº de aluno: 2021129642


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



// verfica o índice do jogo onde estamos a inserir o novo elemento
int indexgalo(int x, int y);

// verifica o índice na 'tabela' pequena
int indexgalo_small(int x, int y);

// verifica se existe vencedor em algum dos tabuleiros
void verfsmall(pgalo g);

// verifica se existe vencedor do jogo
int verf(pgalo g);



// verfica o índice do jogo onde estamos a inserir o novo elemento
int indexgalo(int x, int y){

  int z,i;

  // índice em x
  if(x >= 1 && x<=3)
    z = 1;
  else if(x >= 4 && x<=6)
    z = 2;
  else if(x >= 7 && x<=9)
    z = 3;

  // índice em y
  if(y >= 1 && y<=3)
    i = 1;
  else if(y >= 4 && y<=6)
    i = 2;
  else if(y >= 7 && y<=9)
    i = 3;


  // índice na 'tabela'
  if(z == 1 && i == 1)
    return 1;   // 1ª coluna 1ª linha
  else if(z == 2 && i == 1)
    return 2;   // 2ª coluna 1ª linha
  else if(z == 3 && i == 1)
    return 3;   // 3ª coluna 1ª linha

  if(z == 1 && i == 2)
    return 4;   // 1ª coluna 2ª linha
  else if(z == 2 && i == 2)
    return 5;   // 2ª coluna 2ª linha
  else if(z == 3 && i == 2)
    return 6;   // 3ª coluna 2ª linha

  if(z == 1 && i == 3)
    return 7;   // 1ª coluna 3ª linha
  else if(z == 2 && i == 3)
    return 8;   // 2ª coluna 3ª linha
  else if(z == 3 && i == 3)
    return 9;   // 3ª coluna 3ª linha

}

// verifica o índice na 'tabela' pequena
int indexgalo_small(int x, int y){

  if(x == 1 && y == 1)
    return 1;
  if(x == 2 && y == 1)
    return 2;
  if(x == 3 && y == 1)
    return 3;

  if(x == 1 && y == 2)
    return 4;
  if(x == 2 && y == 2)
    return 5;
  if(x == 3 && y == 2)
    return 6;

  if(x == 1 && y == 3)
    return 7;
  if(x == 2 && y == 3)
    return 8;
  if(x == 3 && y == 3)
    return 9;

}

// verifica se existe vencedor em algum dos tabuleiros
void verfsmall(pgalo g){

  for(int i = 0; i<9; i++){

    // horizontais:
    if((g + i)->t[0][0] == (g + i)->t[1][0] && (g + i)->t[0][0] == (g + i)->t[2][0] && (g + i)->player == 'N' && ((g + i)->t[0][0] == 'X' || (g + i)->t[0][0] == 'O')){
      (g + i)->player = (g + i)->t[0][0];

      (g + i)->t[0][0] = (g + i)->player;
      (g + i)->t[1][0] = (g + i)->player;
      (g + i)->t[2][0] = (g + i)->player;

      (g + i)->t[0][1] = '_';
      (g + i)->t[1][1] = '_';
      (g + i)->t[2][1] = '_';

      (g + i)->t[0][2] = '_';
      (g + i)->t[1][2] = '_';
      (g + i)->t[2][2] = '_';

    }
    if((g + i)->t[0][1] == (g + i)->t[1][1] && (g + i)->t[0][1] == (g + i)->t[2][1] && (g + i)->player == 'N' && ((g + i)->t[0][1] == 'X' || (g + i)->t[0][1] == 'O')){
      (g + i)->player = (g + i)->t[0][1];

      (g + i)->t[0][0] = '_';
      (g + i)->t[1][0] = '_';
      (g + i)->t[2][0] = '_';

      (g + i)->t[0][1] = (g + i)->player;
      (g + i)->t[1][1] = (g + i)->player;
      (g + i)->t[2][1] = (g + i)->player;

      (g + i)->t[0][2] = '_';
      (g + i)->t[1][2] = '_';
      (g + i)->t[2][2] = '_';

    }
    if((g + i)->t[0][2] == (g + i)->t[1][2] && (g + i)->t[0][2] == (g + i)->t[2][2] && (g + i)->player == 'N' && ((g + i)->t[0][2] == 'X' || (g + i)->t[0][2] == 'O')){
      (g + i)->player = (g + i)->t[0][2];

      (g + i)->t[0][0] = '_';
      (g + i)->t[1][0] = '_';
      (g + i)->t[2][0] = '_';

      (g + i)->t[0][1] = '_';
      (g + i)->t[1][1] = '_';
      (g + i)->t[2][1] = '_';

      (g + i)->t[0][2] = (g + i)->player;
      (g + i)->t[1][2] = (g + i)->player;
      (g + i)->t[2][2] = (g + i)->player;

    }

    // verticais:
    if((g + i)->t[0][0] == (g + i)->t[0][1] && (g + i)->t[0][0] == (g + i)->t[0][2] && (g + i)->player == 'N' && ((g + i)->t[0][0] == 'X' || (g + i)->t[0][0] == 'O')){
      (g + i)->player = (g + i)->t[0][0];

      (g + i)->t[0][0] = (g + i)->player;
      (g + i)->t[1][0] = '_';
      (g + i)->t[2][0] = '_';

      (g + i)->t[0][1] = (g + i)->player;
      (g + i)->t[1][1] = '_';
      (g + i)->t[2][1] = '_';

      (g + i)->t[0][2] = (g + i)->player;
      (g + i)->t[1][2] = '_';
      (g + i)->t[2][2] = '_';
    }
    if((g + i)->t[1][0] == (g + i)->t[1][1] && (g + i)->t[1][0] == (g + i)->t[1][2] && (g + i)->player == 'N' && ((g + i)->t[1][0] == 'X' || (g + i)->t[1][0] == 'O')){
      (g + i)->player = (g + i)->t[1][0];

      (g + i)->t[0][0] = '_';
      (g + i)->t[1][0] = (g + i)->player;
      (g + i)->t[2][0] = '_';

      (g + i)->t[0][1] = '_';
      (g + i)->t[1][1] = (g + i)->player;
      (g + i)->t[2][1] = '_';

      (g + i)->t[0][2] = '_';
      (g + i)->t[1][2] = (g + i)->player;
      (g + i)->t[2][2] = '_';
    }
    if((g + i)->t[2][0] == (g + i)->t[2][1] && (g + i)->t[2][0] == (g + i)->t[2][2] && (g + i)->player == 'N' && ((g + i)->t[2][0] == 'X' || (g + i)->t[2][0] == 'O')){
      (g + i)->player = (g + i)->t[2][0];

      (g + i)->t[0][0] = '_';
      (g + i)->t[1][0] = '_';
      (g + i)->t[2][0] = (g + i)->player;

      (g + i)->t[0][1] = '_';
      (g + i)->t[1][1] = '_';
      (g + i)->t[2][1] = (g + i)->player;

      (g + i)->t[0][2] = '_';
      (g + i)->t[1][2] = '_';
      (g + i)->t[2][2] = (g + i)->player;
    }

    // diagonais:
    if((g + i)->t[0][0] == (g + i)->t[1][1] && (g + i)->t[0][0] == (g + i)->t[2][2] && (g + i)->player == 'N' && ((g + i)->t[0][0] == 'X' || (g + i)->t[0][0] == 'O')){
      (g + i)->player = (g + i)->t[0][0];

      (g + i)->t[0][0] = (g + i)->player;
      (g + i)->t[1][0] = '_';
      (g + i)->t[2][0] = '_';

      (g + i)->t[0][1] = '_';
      (g + i)->t[1][1] = (g + i)->player;
      (g + i)->t[2][1] = '_';

      (g + i)->t[0][2] = '_';
      (g + i)->t[1][2] = '_';
      (g + i)->t[2][2] = (g + i)->player;
    }
    if((g + i)->t[2][0] == (g + i)->t[1][1] && (g + i)->t[2][0] == (g + i)->t[0][2] && (g + i)->player == 'N' && ((g + i)->t[2][0] == 'X' || (g + i)->t[2][0] == 'O')){
      (g + i)->player = (g + i)->t[2][0];

      (g + i)->t[0][0] = '_';
      (g + i)->t[1][0] = '_';
      (g + i)->t[2][0] = (g + i)->player;

      (g + i)->t[0][1] = '_';
      (g + i)->t[1][1] = (g + i)->player;
      (g + i)->t[2][1] = '_';

      (g + i)->t[0][2] = (g + i)->player;
      (g + i)->t[1][2] = '_';
      (g + i)->t[2][2] = '_';
    }

  }

}


// verifica se existe vencedor do jogo
int verf(pgalo g){

  char t1 = g->player;
  char t2 = (g + 1)->player;
  char t3 = (g + 2)->player;

  char t4 = (g + 3)->player;
  char t5 = (g + 4)->player;
  char t6 = (g + 5)->player;

  char t7 = (g + 6)->player;
  char t8 = (g + 7)->player;
  char t9 = (g + 8)->player;


  // horizontais:
  if(t1 == t2 && t1 == t3){
    if(t1 == 'X')
      return 1;
    if(t1 == 'O')
      return 2;
  }
  if(t4 == t5 && t4 == t6){
    if(t4 == 'X')
      return 1;
    if(t4 == 'O')
      return 2;
  }
  if(t7 == t8 && t7 == t9){
    if(t7 == 'X')
      return 1;
    if(t7 == 'O')
      return 2;
  }

  // verticais:
  if(t1 == t4 && t1 == t7){
    if(t1 == 'X')
      return 1;
    if(t1 == 'O')
      return 2;
  }
  if(t2 == t5 && t2 == t8){
    if(t2 == 'X')
      return 1;
    if(t2 == 'O')
      return 2;
  }
  if(t3 == t6 && t3 == t9){
    if(t3 == 'X')
      return 1;
    if(t3 == 'O')
      return 2;
  }

  // diagonais:
  if(t1 == t5 && t1 == t9){
    if(t1 == 'X')
      return 1;
    if(t1 == 'O')
      return 2;
  }
  if(t3 == t5 && t3 == t7){
    if(t3 == 'X')
      return 1;
    if(t3 == 'O')
      return 2;
  }

  return 0;

}
