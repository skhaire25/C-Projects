#include <stdio.h>

int main(){

    int num = 0;
    int power = 0;
    long long int value = 1;

    printf("Enter the number: ");
    scanf("%d", &num);

    printf("Enter the power: ");
    scanf("%d", &power);

    for(int i = 0; i < power; i++){
        value = value * num;
    }

    printf("The value of %d to the power %d is %lld", num, power, value);

    return 0;
}