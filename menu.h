/*----------Identificação----------*/

// - Nome: Bruno Pinto
// - Nº de aluno: 2021129642


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// print do menu principal
int criarmenu();

// print do "manual de instruções"
void help();

// delay de funções
void delay(float sec);



// print do menu principal
int criarmenu(){

    int esc=0;

    do{
        //clear do ecrã
        system("cls");
        printf("---------- Jogo do Galo ----------\n\n\t1 - P1 vs P2\n\t2 - P1 vs CPU\n\t3 - Ajuda\n\t0 - Sair\n\n----------------------------------\n>>>  ");
        scanf("%d",&esc);

        if(esc == 4){
            help();
        }

    }while(esc > 3 || esc < 0);

    return esc;

}


// print do "manual de instruções"
void help(){
    int i;
    system("cls");
    printf("--------------- Ajuda ---------------\n\n Durante o Jogo:\n\n\t0 <= x <= 9\n\t0 <= y <= 9\n\t-1 -> Sair do Jogo e Guardar\n\n--------------------------------------\nInsira um valor qualquer para sair >>>  ");
    scanf("%d",&i);
}


// delay de funções
void delay(float sec)
{
    float milli = 1000 * sec;

    clock_t start_time = clock();

    while (clock() < start_time + milli);
}

