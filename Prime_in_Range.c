#include <stdio.h>
#include <math.h>

int isPrime(int n){
    for(int i=2; i <= (sqrt(n)); i++){
        if(n % i == 0){
            return 0;       
        }
    }
    return 1;
}

int main(){

    int n1=0, n2=0;
    
    printf("Enter the Range is which you wanna find Prime Numbers\n");

    printf("Enter the first number: ");
    scanf("%d", &n1);

    printf("Enter the second number: ");
    scanf("%d", &n2);

    printf("Prime number between %d and %d: ", n1, n2);

    for(int i=n1; i <= n2; i++){
        if(isPrime(i)){
            printf(" %d", i);
        }
    }

    return 0;
}