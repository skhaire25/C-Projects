#include <stdio.h>
#include <string.h>

int main(){

    char s[100];
    char temp;
    int len = 0;

    printf("Enter a String: ");
    fgets(s, sizeof(s), stdin);
    s[strlen(s) - 1] = '\0';


    while(s[len] != '\0'){
        len ++;
    }

    printf("The length of string is %d\n", len);

    for(int i = 0; i < (len-1)/2; i++){
        temp = s[i];
        s[i] = s[len-1-i];
        s[len-1-i] = temp;
    }

    printf("The Reversed String is %s", s);

    return 0;
}