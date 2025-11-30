#include <stdio.h>

int returnMAX();

int main(){

    int arr[] = {1,2,3,4,5,6,7,8,9,0};
    int max = returnMAX(arr, 10);

    printf("The largest element in the array: %d", max);

    return 0;
}

int returnMAX(int array[], int n){
    int max = 0;
    for(int i = 0; i < n; i++){
        if(array[i]>max){
            max = array[i];
        }
    }
    return max;

}