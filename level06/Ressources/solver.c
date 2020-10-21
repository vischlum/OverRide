#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *login = "level06";
    int len;
    uint bin;
    int i;

    len = strnlen(login, 32);
    bin = (login[3] ^ 0x1337U) + 0x5eeded;
    for (i = 0; i < len; i++) {
        if (login[i] < 32 || login[i] > 127)
            return 1;
        bin += (login[i] ^ bin) % 1337;
    }

    printf("With login = %s, serial must be = %u\n", login, bin);
    return 0;
}