#include <stdio.h>

int factorial(int num){

    if(num == 0 || num == 1){
        return 1;
    }
    else{
        return num * factorial(num - 1);
    }
}

int main(){

    int num = 0;
    int fact = 0;

    printf("Enter the number you want the Factorial of: ");
    scanf("%d", &num);

    fact = factorial(num);

    printf("\nThe Factorial of %d = %d", num, fact);

    return 0;
}