#include <stdio.h>
#include <string.h>
#include <math.h>

void DecToBin(int dec){
    
    int rem;
    int arr[10];
    int i = 0;
    int decimal = dec;

    if(dec == 0){
        printf("Binary of 0 --> 0");
        return ;
    }

    while(dec != 0){
        rem = dec % 2;
        dec = dec/2;
        arr[i] = rem;
        i++;
    }

    printf("Binary of %d --> ", decimal);
    for(int j=i-1; j >= 0; j--){
        printf("%d", arr[j]);
    }
}

int BinToDec(int bin){

    int power = 0, value = 0, rem = 0, decimal = 0;
    int binary = bin;

    while(bin!=0){
        rem = bin % 10;
        bin /= 10;

        if(rem == 1){
            value += rem*pow(2, power);
        }
        else if(rem==0){
            value += 0;
        }
        else{
            printf("It's not a Binary number!");
            return -1;
        }
        power++;
    }
    return value;
}

int OctToDec(int oct){

    int power = 0, value = 0, rem = 0, decimal = 0;
    int octal = oct;

    while(oct!=0){
        rem = oct % 10;
        oct /= 10;

        if(rem <= 7){
            value += rem*pow(8, power);
        }
        else{
            printf("It's not a Octal number!");
            return -1;
        }
        power++;
    }
    
    return value;

}

int HexToDec(char hex[]){

    int value=0;
    
    for(int i = 0; hex[i]!='\0'; i++){
        if(hex[i]>='0' && hex[i]<='9'){
            value = value * 16 + (hex[i]-'0');
        }
        else if(hex[i]>='A' && hex[i]<='F'){
            value = value * 16 + (hex[i]- 'A' + 10);
        }
        else if(hex[i]>='a' && hex[i]<='f'){
            value = value * 16 + (hex[i]- 'a' + 10);
        }
        else{
            printf("Invalid Hexadecimal Number!");
            return -1;
        }
    }
    
    return value;
}

int main()
{
    int input, output;
    int decValue = 0;
    int bin, oct;
    char hex[20];

    printf("Choose Input Number System\n");
    printf("1. Decimal\n2. Binary\n3. Octal\n4. Hexadecimal\n");
    printf("Enter choice: ");
    scanf("%d", &input);

    switch (input)
    {
    case 1:
        printf("Enter Decimal number: ");
        scanf("%d", &decValue);
        break;

    case 2:
        printf("Enter Binary number: ");
        scanf("%d", &bin);
        decValue = BinToDec(bin);
        break;

    case 3:
        printf("Enter Octal number: ");
        scanf("%d", &oct);
        decValue = OctToDec(oct);
        break;

    case 4:
        printf("Enter Hexadecimal number: ");
        scanf("%s", hex);
        decValue = HexToDec(hex);
        break;

    default:
        printf("Invalid Input Choice!\n");
        return 0;
    }

    if (decValue < 0)
        return 0;

    printf("\nConvert To\n");
    printf("1. Decimal\n2. Binary\n3. Octal\n4. Hexadecimal\n");
    printf("Enter choice: ");
    scanf("%d", &output);

    switch (output)
    {
    case 1:
        printf("Decimal: %d\n", decValue);
        break;

    case 2:
        DecToBin(decValue);
        break;

    case 3:
        printf("Octal: %o\n", decValue);
        break;

    case 4:
        printf("Hexadecimal: %X\n", decValue);
        break;

    default:
        printf("Invalid Output Choice!\n");
    }

    return 0;
}
