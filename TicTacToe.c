#include <stdio.h>

char positions[10] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9'};

void board();
int win();

int main(){

    int player = 1;
    int choice = 0;
    int i = 0;
    char mark = {'\0'};

    do{
        board();
        player = (player % 2) ? 1 : 2;
        printf("Player %d enter your move: ", player);
        scanf("%d", &choice);
        mark = (player == 1) ? 'X' : 'O';

        if(choice == 1 && positions[1] == '1'){
            positions[1] = mark;
        }   
        else if(choice == 2 && positions[2] == '2'){
            positions[2] = mark;
        }    
        else if(choice == 3 && positions[3] == '3'){
            positions[3] = mark;
        }    
        else if(choice == 4 && positions[4] == '4'){
            positions[4] = mark;
        }
        else if(choice == 5 && positions[5] == '5'){
            positions[5] = mark;
        }
        else if(choice == 6 && positions[6] == '6'){
            positions[6] = mark;
        }

        else if(choice == 7 && positions[7] == '7'){
            positions[7] = mark;
            }
            
        else if(choice == 8 && positions[8] == '8'){
            positions[8] = mark;
        }         
        else if(choice == 9 && positions[9] == '9'){
            positions[9] = mark;
        }
        else{
            printf("Invalid Choice!\n");
            player--;
        }     

        i = win();
        player++;
        
    }while( i == -1);

    board();

    if(i == 1){
        player--;
        printf("Player %d is the WINNER!", player);
    }
    else{
        printf("GAME DRAW!");
    }

    return 0;
}

void board(){

    printf("\n*** TIC TAC TOE ***\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c   \n", positions[1], positions[2], positions[3]);
    printf("     |     |     \n");
    printf("-----|-----|-----\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c   \n", positions[4], positions[5], positions[6]);
    printf("     |     |     \n");
    printf("-----|-----|-----\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c   \n", positions[7], positions[8], positions[9]);
    printf("     |     |     \n");

    return;

}

int win(){

    if(positions[1] == positions[2] && positions[2] == positions[3]){
        return 1;
    }
    else if(positions[4] == positions[5] && positions[5] == positions[6]){
        return 1;
    }
     else if(positions[7] == positions[8] && positions[8] == positions[9]){
        return 1;
    }
    else if(positions[1] == positions[4] && positions[4] == positions[7]){
        return 1;
    }
    else if(positions[2] == positions[5] && positions[5] == positions[8]){
        return 1;
    }
    else if(positions[3] == positions[6] && positions[6] == positions[9]){
        return 1;
    }
    else if(positions[1] == positions[5] && positions[5] == positions[9]){
        return 1;
    }
    else if(positions[3] == positions[5] && positions[5] == positions[7]){
        return 1;
    }
    else if(positions[1] != '1' && positions[2] != '2' && positions[3] != '3' && positions[4] != '4' && positions[5] != '5' &&
            positions[6] != '6' && positions[7] != '7' && positions[8] != '8' && positions[9] != '9'){
        return 0;
    }
    else{
        return -1;
    }

}