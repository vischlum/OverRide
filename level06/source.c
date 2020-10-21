#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>

int auth(char *login, uint serial)
{
    int len;
    uint bin;
    int i;

    login[strcspn(login, "\n")] = '\0';
    len = strnlen(login, 32);
    if (len < 6)
        return 1;
    
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
        puts("\x1b[32m.---------------------------.");
        puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
        puts("\x1b[32m\'---------------------------\'");
        return 1;
    }

    bin = (login[3] ^ 0x1337U) + 0x5eeded;
    for (i = 0; i < len; i++) {
        if (login[i] < 32 || login[i] > 127)
            return 1;
        bin += (login[i] ^ bin) % 1337;
    }

    if (serial != bin)
        return 1;
    
    return 0;
}

int main(void)
{
    char login[32];
    uint serial;
    int ret;

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");
    printf("-> Enter Login: ");
    fgets(login, 32, stdin);

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");
    scanf("%u", &serial);

    ret = auth(login, serial);
    if (ret == 0) {
        puts("Authenticated!");
        system("/bin/sh");
        return 0;
    }
    
    return 1;
}