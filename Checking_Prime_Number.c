#include <stdio.h>
#include <math.h>

int main(){

    int n = 0 ;
    int  isPrime = 1;

    printf("Enter the number to check if it's Prime or Composite: ");
    scanf("%d", &n);

    if(n == 1){
        printf("1 is nor Prime nor Composite!");
        return 0;
    }

    for(int i=2; i <= (sqrt(n)); i++){
        if(n % i == 0){
            isPrime = 0;
        }
    }

    if(isPrime){
        printf("The %d number is Prime!", n);
    }
    else{
        printf("The %d number is Composite!", n);
    }

    return 0;
}