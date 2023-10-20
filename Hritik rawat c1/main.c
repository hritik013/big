#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"

int main(){
    int option=1;
    while(option!=6){
        char *a=(char*)malloc(1000*sizeof(char));
        char *b=(char*)malloc(1000*sizeof(char));

        printf("Controls :\n");
        printf("1 : add two numbers\n");
        printf("2 : Subtract two numbers\n");
        printf("3 : Multiply two numbers\n");
        printf("4 : Divide two numbers\n");
        printf("5 : Get remainder\n");    
        printf("6 : Exit\n");

        scanf("%d",&option);
        getchar();

        if(option==6) break;

        printf("Enter first number : ");
        fgets(a,1000,stdin);
    
        printf("Enter second number : ");
        fgets(b,1000,stdin);

        node *ans=NULL;

        switch(option){
            case 1 :  ans=AddbigInt(a,b);
            break;
            case 2 :  ans=Subtract_bigInt(a,b);
            break;
            case 3 :  ans=Multiply_bigInt(a,b);
            break;
            case 4 :  ans=Divide_bigInt(a,b,4);
            break;
            case 5 :  ans=Divide_bigInt(a,b,5);
            break;
        }
        printf("Answer : ");
        print(ans);
    }
}

//  gcc main.c functions.c -o main
//  ./main