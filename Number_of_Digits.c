#include <stdio.h>

int main()
{
    int num = 0, counter = 0;

    printf("Enter the number: ");
    scanf("%d", &num);

    if (num == 0)
        printf("There is only 1 digit in your number.");
    else
    {
        while (num != 0)
        {
            num = num / 10; // n/=10
            counter++;
        }
        printf("There are %d digits in your number", counter);
    }
    return 0;
}