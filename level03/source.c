#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void decrypt(unsigned int key) {
    unsigned int len;
    unsigned int i;
    char *str = "Q}|u`sfg~sf{}|a3";

    len = strlen(str);

    for (i=0; i<len; i++)
        str[i] ^= key;

    if (!strcmp(str, "Congratulations!"))
        system("/bin/sh");
    else
        printf("\nInvalid Password!\n");
}

void test(unsigned int input, unsigned int secret) {
    int res;

    res = secret - input;
    switch(res)
    {
        case 0x1:
            decrypt(res);
            break;
        case 0x2:
            decrypt(res);
            break;
        case 0x3:
            decrypt(res);
            break;
        case 0x4:
            decrypt(res);
            break;
        case 0x5:
            decrypt(res);
            break;
        case 0x6:
            decrypt(res);
            break;
        case 0x7:
            decrypt(res);
            break;
        case 0x8:
            decrypt(res);
            break;
        case 0x9:
            decrypt(res);
            break;
        case 0xA:
            decrypt(res);
            break;
        case 0xB:
            decrypt(res);
            break;
        case 0xC:
            decrypt(res);
            break;
        case 0xD:
            decrypt(res);
            break;
        case 0xE:
            decrypt(res);
            break;
        case 0xF:
            decrypt(res);
            break;
        case 0x10:
            decrypt(res);
            break;
        case 0x11:
            decrypt(res);
            break;
        case 0x12:
            decrypt(res);
            break;
        case 0x13:
            decrypt(res);
            break;
        case 0x14:
            decrypt(res);
            break;
        case 0x15:
            decrypt(res);
            break;
        default:
            decrypt(rand());
    }
}

int main(void) {
    int input;

    srand(time(NULL));
    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");
    printf("\nPassword:");
    scanf("%d", &input);

    test(input, 0x1337d00d);

    return 0;
}