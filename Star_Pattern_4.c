#include <stdio.h>

int main(){

    int num = 0;
    
    printf("Enter number of * Rows you want: ");
    scanf("%d", &num);

    for(int i = 0; i < num; i++){
        for(int j = 0; j < num; j++){
            if(j >= i){
                printf("*");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }

}