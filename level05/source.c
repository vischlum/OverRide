#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void)
{
    char buff[100];
    int  i = 0;
    int  len = 0;

    fgets(buff, 100, stdin);

    len = strlen(buff);
    while (i < len) { //Convert to lowercase
        if ('@' < buff[i] && buff[i] < '[' )
            buff[i] = buff[i] ^ 0x20;
        i++;
    }

    printf(buff);

    exit(0);
}