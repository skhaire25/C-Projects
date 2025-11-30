#include <stdio.h>

int main(){

    int n, sum = 0;

    printf("Enter the last natural number you wanna sum: ");
    scanf("%d", &n);

    //for(int i = 1; i <= n; i++){
    //    sum += i;
    //}

    sum = (n*n + n)/2;

    printf("The Sum of Natural numbers: %d", sum);

    return 0;
}