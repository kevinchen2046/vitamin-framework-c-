#include <stdio.h>
#include <windows.h>
#include <string.h>

enum Color{
    red,
    green,
    blue
};

int main()
{
    printf("Hello World\n");

    char a[]="12121";

    printf(strcat(a,"\n"));
    system("pause");
    return 0;
}