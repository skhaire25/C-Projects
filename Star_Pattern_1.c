#include <stdio.h>

int main(){

    int num = 0;
    
    printf("Enter number of * Rows you want: ");
    scanf("%d", &num);

    for(int i = 0; i < num; i++){
        for(int j = 0; j < i+1; j++){
            printf("*");
        }
        printf("\n");
    }

    return 0;
}