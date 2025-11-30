#include <stdio.h>

int main(){

    int num;
    
    printf("Enter the number for which you want the multiplication table: ");
    scanf("%d", &num);
    printf("\nThe multiplication table  of %d: \n", num);

    for(int i = 0; i < 10; i++){
        printf("%d X %d = %d\n", num, i+1, (i+1)*num);
    }

    return 0;
}