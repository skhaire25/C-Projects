#include <stdio.h>

int reverse(int num){
    int rem =0, rev = 0;
    
    while(num != 0){
        rem = num % 10;
        rev = rev * 10 + rem;
        num = num/10;
    }

    return rev;
}

int main(){

    int num = 0;
    int rev = 0;

    printf("Enter the number you wanna Reverse: ");
    scanf("%d", &num);

    rev = reverse(num);

    printf("\nReverse of %d --> %d", num, rev);

    return 0;
}