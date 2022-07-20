/*----------Identificação----------*/

// - Nome: Bruno Pinto
// - Nº de aluno: 2021129642


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// tabuleiros 3x3
typedef struct galo galo, *pgalo;
struct galo
{
  char player;
  char t[3][3];
};

// histórico de jogadas
typedef struct historico historico, *phist;
struct historico
{
  int x, y; // coordenadas
  int p; // jogador

  phist prox; // ponteiro para o próximo item da lista
};



// print do campo de jogo
void board(pgalo g, int *index);

// print do campo pela 1ª vez
void firstboard();

// inserir um valor no tabuleiro
pgalo insere(pgalo g, int x, int y, int *p,int *index, char sym, int *tam);

// mostra as jogadas anteriores
void jogadasAnt(phist h, int htotal);

// guardar jogada no histórico
phist guardarJogada(phist h, int x, int y, int p, int *htotal);

// guardar jogo - Meio
void guardarMid(pgalo g, int *index, int *p, int *tam);

// guardar tabuleiro - Fim
void guardarTab(pgalo g, char *fn, int venc);

// guardar jogo - Fim
void guardar(phist p, char *fn, int venc);

// carregar jogo
pgalo carregar(int *index, int *p, int *tam);



// print do campo de jogo
void board(pgalo g, int *index){

  if(g == NULL){
    firstboard();
    return;
  }


  int i = 0;
  int idx, idy;
  idx = 0;    idy = 0;

  printf("   1 2 3   4 5 6   7 8 9\n");

  for(int y = 1; y <= 9; y++, idy++){
    for(int x = 1; x <= 9; x++, idx++){

      i = indexgalo(x,y);

      if(x == 1)
        printf("%d  ",y);

      // cor de fundo do campo jogável
      if(i == *index)
        printf("\033[100m");

      if(((g + (i-1))->t[idx][idy] == 'X' || (g + (i-1))->t[idx][idy] == 'O') || (g + (i-1))->t[idx][idy] == '_'){

        // caso seja um jogo ganho pelo P1
        if((g + (i-1))->player == 'X')
          printf("\033[44m");
        // caso seja um jogo ganho pelo P2
        if((g + (i-1))->player == 'O')
          printf("\033[43m");

        printf("%c \033[0m",(g + (i-1))->t[idx][idy]);

      } else
        printf("_ \033[0m");

      if(x == 3 || x == 6){
        printf("| ");
        idx = -1;
      }
      if(x == 9){
        printf("\n");
        idx = -1;
      }

    }

    if(idy == 2){
      idy = 0;
    }

    if(y == 3 || y == 6){
      printf("   ------+-------+------\n");
      idy = -1;
      idx = 0;
    }

  }

  return;

}

// print do campo pela 1ª vez
void firstboard(){

  printf("   1 2 3   4 5 6   7 8 9\n");
  printf("1  _ _ _ | _ _ _ | _ _ _\n2  _ _ _ | _ _ _ | _ _ _\n3  _ _ _ | _ _ _ | _ _ _\n   ------+-------+------\n");
  printf("4  _ _ _ | _ _ _ | _ _ _\n5  _ _ _ | _ _ _ | _ _ _\n6  _ _ _ | _ _ _ | _ _ _\n   ------+-------+------\n");
  printf("7  _ _ _ | _ _ _ | _ _ _\n8  _ _ _ | _ _ _ | _ _ _\n9  _ _ _ | _ _ _ | _ _ _\n");

}



// inserir um valor no tabuleiro
pgalo insere(pgalo g, int x, int y, int *p,int *index, char sym, int *tam){

  system("cls");

  int i = indexgalo(x,y);
  pgalo novo = NULL;

  // caso os valores de x e de y sejam inválidos
  if((i != *index && g != NULL) || x < 1 || x > 9 || y < 1 || y > 9){
    printf("\n\033[31mERRO - Valor de \033[4mx\033[0m\033[31m ou de \033[4my\033[0m\033[31m invalido.\033[0m\n\n");
    if(*p == 1)
      *p = 2;
    else
      *p = 1;
    return g;
  }

  int z, k, idx, idy;

  // caso o local de inserção seja maior que à array
  if(*tam < i){
    novo = realloc(g,i*sizeof(galo));
    *tam = i;

    if(novo == NULL){
      printf("\n\033[31mERRO - Array não foi alocada.\033[0m\n");
      return g;
    }

  }else if(*tam >= i){ // caso o local de inserção seja menor ou igual à array
    novo = realloc(g,(*tam)*sizeof(galo));
    if(novo == NULL){
      printf("\n\033[31mERRO - Array não foi alocada.\033[0m\n");
      return g;
    }

  }


  // caso o tabuleiro esteja terminado
  if((novo + (i-1))->player == 'X' || (novo + (i-1))->player == 'O'){
    printf("\nTabuleiro Terminado\nA reposicionar...\n");

    int random;

    do{
      // função para gerar um valor aleatório para a próxima jogada
      srand( (unsigned)time(NULL) );
      random = 1+rand()%9;
    }while((random == *index && (novo + (random-1))->player == 'X') || (novo + (random-1))->player == 'O');

    *index = random;

    return novo;
  }


  // inserção do valor na posição
  for(z=1, idy = 0; z<=9; z++, idy++){
    for(k=1, idx = 0; k<=9; k++, idx++){


      // insere o valor na array
      if(k == x && z == y){

        // verifica se já existe algo na posição pretendida para inserção
        if((novo + (i-1))->t[idx][idy] == 'X' || (novo + (i-1))->t[idx][idy] == 'O'){
          printf("\n\033[31mERRO - A posição já está preenchida.\033[0m\n\n");

          if(*p == 1)
            *p = 2;
          else
            *p = 1;

          return g;

        }

        // insere o valor na posição
        (novo + (i-1))->t[idx][idy] = sym;
        (novo + (i-1))->player = 'N';

        *index = indexgalo_small(idx+1,idy+1);

      }

      if(idx == 2)
        idx = -1;

    }
    if(idy == 2)
      idy = -1;

  }

  // verifica se existe vencedor no tabuleiro
  verfsmall(novo);

  // caso o tabuleiro esteja terminado
  if((novo + ((*index)-1))->player == 'X' || (novo + ((*index)-1))->player == 'O'){
    printf("\nTabuleiro Terminado\nA reposicionar...\n");

    int random;

    do{
      // função para gerar um valor aleatório para a próxima jogada
      srand( (unsigned)time(NULL) );
      random = 1+rand()%9;
    }while(random == *index || (novo + (random-1))->player == 'X' || (novo + (random-1))->player == 'O');

    *index = random;

  }

  return novo;

}



// mostra as jogadas anteriores
void jogadasAnt(phist h, int htotal){

  int k;
  phist aux;

  do{
    printf("\nQuantas jogadas quer visualizar? ");
    scanf("%d",&k);
  }while(k < 0 || k > 10);

  system("cls");

  if(k == 0)
    return;

  aux = h;

  // move o apontador para mostrar as últimas k jogadas
  if(htotal > k){
    for(int i = 0; i <=  htotal-k; i++)
      aux = aux->prox;
  }

  // mostra as últimas k jogadas
  for(k = k; k >= 0 && aux != NULL; k--){
    printf("\nP%d - (x,y) = (%d,%d)", aux->p, aux->x, aux->y);
    aux = aux->prox;
  }
  printf("\n");

  return;

}



// guardar jogada no histórico
phist guardarJogada(phist h, int x, int y, int p, int *htotal){

  phist novo, aux = NULL;

  novo = malloc(sizeof(historico));
  if(novo == NULL){
    printf("\n\033[31mERRO - Estrutura não foi alocada.\033[0m\n");
    return h;
  }

    (*htotal)++;

    novo->x = x;
    novo->y = y;
    novo->p = p;
    novo->prox = NULL;

  // caso seja o 1º a ser inserido
  if(h == NULL)
    return novo;


  aux = h;

  while(aux->prox != NULL)
    aux = aux->prox;


  aux->prox = novo;

  return h;

}



// guardar jogo - Meio
void guardarMid(pgalo g, int *index, int *p, int *tam){

  FILE * dados = fopen("jogo.bin","wb");
  if(dados == NULL){
    printf("\n\033[31mERRO ao abrir o ficheiro\033[0m\n");
    return;
  }

  int i = *index, pl = *p, t = *tam;

  // informação necessária para o jogo
  fwrite(&i, sizeof(int), 1, dados);
  fwrite(&pl, sizeof(int), 1, dados);
  fwrite(&t, sizeof(int), 1, dados);

  // tabuleiro completo
  fwrite(g, sizeof(galo), *tam, dados);

  fclose(dados);

}



// guardar tabuleiro - Fim
void guardarTab(pgalo g, char *fn, int venc){

  char str[55] = "T";
  strcat(str,fn);

  FILE * dados = fopen(str,"w");

  if(dados == NULL){
    printf("\n\033[31mERRO ao abrir o ficheiro %s\033[0m\n",fn);
    return;
  }

  int i = 0;
  int idx, idy;
  idx = 0;    idy = 0;

  fprintf(dados,"       ! P%d GANHOU !\n\n   1 2 3   4 5 6   7 8 9\n",venc);

  for(int y = 1; y <= 9; y++, idy++){
    for(int x = 1; x <= 9; x++, idx++){

      i = indexgalo(x,y);

      if(x == 1)
        fprintf(dados,"%d  ",y);

      if(((g + (i-1))->t[idx][idy] == 'X' || (g + (i-1))->t[idx][idy] == 'O') || (g + (i-1))->t[idx][idy] == '_'){
        fprintf(dados,"%c ",(g + (i-1))->t[idx][idy]);

      } else
        fprintf(dados,"_ ");



      if(x == 3 || x == 6){
        fprintf(dados,"| ");
        idx = -1;
      }
      if(x == 9){
        fprintf(dados,"\n");
        idx = -1;
      }

    }

    if(idy == 2){
      idy = 0;
    }

    if(y == 3 || y == 6){
      fprintf(dados,"   ------+-------+------\n");
      idy = -1;
      idx = 0;
    }

  }

  fclose(dados);

}



// guardar jogo - Fim
void guardar(phist p, char *fn, int venc){

  FILE * dados = fopen(fn,"w");
  if(dados == NULL){
    printf("\n\033[31mERRO ao abrir o ficheiro %s\033[0m\n",fn);
    return;
  }

  phist aux = p;

  while(aux->prox != NULL){
    fprintf(dados, "\nP%d - (x,y) = (%d,%d)", aux->p, aux->x, aux->y);
    aux = aux->prox;
  }

  fclose(dados);

}



// carregar jogo
pgalo carregar(int *index, int *p, int *tam){

  FILE * dados = fopen("jogo.bin","rb");
  if(dados == NULL){
    printf("\n\033[31mERRO ao abrir o ficheiro\033[0m\n");
    return;
  }

  pgalo g;
  int i, pl, t;

  // informação necessária para o jogo
  fread(&i, sizeof(int), 1, dados);   *index = i;
  fread(&pl, sizeof(int), 1, dados);  *p = pl;
  fread(&t, sizeof(int), 1, dados);   *tam = t;

  g = realloc(g,t*sizeof(galo));

  // tabuleiro completo
  fread(g, sizeof(galo), t, dados);

  fclose(dados);

  return g;

}
