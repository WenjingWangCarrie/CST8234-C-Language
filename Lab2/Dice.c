#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define WON 0
#define LOSE 1

int rollDice(void);
int playGame(void);

int rollDice(void) {

    return ((rand() % 6) + 1);
}

int playGame(void) {
    char c;
    int games = 0;
    int dice_1 = 0, dice_2 = 0;
    int sum = 0, point = 0;
    int rollNum, result;
    int wins = 0, losses = 0;
    time_t t;

    srand(time(NULL));
    
    do {
   
        printf("               ROLL THE DICE WITH [ENTER]\n");
        fgetc(stdin);        

        dice_1 = rollDice();
        dice_2 = rollDice();
        sum = dice_1 + dice_2;
        point = sum;
        
        printf("-------------------------------------------------------\n");
        printf("ROLL NUM  DICE #1  DICE #2  TOTAL ROLL  POINT MATCH \n"); 
        printf("-------------------------------------------------------\n");
        printf(" %5d  %5d  %5d  %7d  %9d\n",rollNum, dice_1, dice_2, sum,point); 

        switch (sum) {
            case 7:
            case 11:
            result = WON;
            wins++;
            printf("Congratulations you roll %d and WON at your first try!!!\n", sum);
            break;

            case 2:
            case 3:
            case 12:
            result = LOSE;
            losses++;
            printf("Sorry, you roll %d and you lose!!!\n", sum);
            break;

            default:
            result = WON;
            wins++;
            printf("Congratulations you roll %d and WON\n", sum);
            break;
        }

        while(result = WON) {
            dice_1 = rollDice();
            dice_2 = rollDice();
            sum = dice_1 + dice_2;
            point = sum;
            printf("-------------------------------------------------------\n");
            printf("ROLL NUM  DICE #1  DICE #2  TOTAL ROLL  POINT MATCH \n"); 
            printf("-------------------------------------------------------\n");
            printf(" %5d  %5d  %5d  %7d  %9d\n",rollNum, dice_1, dice_2, sum,point); 
        
            if (sum == 7) {
            result = WON;
         
            } else if (sum == point) { 
            result = WON;   
            
            } 
        }
   
        printf("Another Game? [ Y / N ]\n");
        scanf("%c", &c);
    } while(c == 'y' || c == 'Y'); 
  
    if (c =='n' || c =='N') {
        ;             
    }      
  
    printf("You won %d games and lost %d games!\n", wins, losses);  
    
    return 0;
}


int main(void) {
        
    int result = playGame();

    switch(result) {
        case WON:
        printf("Thank you for playing\n");
        printf("What a winner!\n");
        break;

        case LOSE:
        printf("Thank you for playing\n");
                printf("Better luck next time!\n");
        break;

    }

    return EXIT_SUCCESS;
}
