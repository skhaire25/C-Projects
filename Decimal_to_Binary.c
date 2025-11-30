#include <stdio.h>

int main(){

    int n = 0;
    int rem;
    int arr[10];
    int i = 0;

    printf("Enter number you wanna convert to Binary: ");
    scanf("%d", &n);
    int num = n;

    if(n == 0){
        printf("0");
        return 0;
    }

    while(n != 0){
        rem = n % 2;
        n = n/2;
        arr[i] = rem;
        i++;
    }

    printf("Binary of %d --> ", num);
    for(int j=i-1; j >= 0; j--){
        printf("%d", arr[j]);
    }

    return 0;
}