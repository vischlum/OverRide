#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_stdin(void)
{
    char c;

    while(c != -1) {
        c = getchar();
        if (c == '\n')
            return;
    }

    return;
}

int get_unum(void)
{
    int unum = 0;

    fflush(stdout);
    scanf("%d", &unum);
    clear_stdin();

    return unum;    
}

int read_number(int number[100])
{
    int index;

    printf(" Index: ");
    index = get_unum();
    printf(" Number at data[%u] is %u\n", index, number[index]);
    
    return 0;
}

int store_number(int number[100])
{
    int input, index, ret;

    printf(" Number: ");
    input = get_unum();
    printf(" Index: ");
    index = get_unum();

    if ((index % 3 == 0) || (input >> 24 == 183)) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        ret = 1;
    } else {
        *(index * 4 + number) = input;
        ret = 0;
    }

    return ret;
}

int main(int argc, char **argv, char **env)
{
    int ret = 0;
    char *command;
    int number[100];

    while (*argv) {
        memset(*argv, 0, strlen(*argv));
        argv++;
    }
    while (*env) {
        memset(*env, 0, strlen(*env));
        env++;
    }

    puts("----------------------------------------------------\n");
    puts("  Welcome to wil's crappy number storage service!\n");
    puts("----------------------------------------------------\n");
    puts(" Commands:\n");
    puts("    store - store a number into the data storage\n");
    puts("    read  - read a number from the data storage\n");
    puts("    quit  - exit the program\n");
    puts("----------------------------------------------------\n");
    puts("   wil has reserved some storage :>\n");\
    puts("----------------------------------------------------\n");

    while(1) {
        printf("Input command: ");
        ret = 1;

        fgets(command, 20, stdin);
        command[strlen(command) - 1] = '\0';

        if (!strncmp(command, "store", 5))
            ret = store_number(number);
        else if (!strncmp(command, "read", 4))
            ret = read_number(number);
        else if (!strncmp(command, "quit", 4))
            break;
        
        if (ret == 0)
            printf(" Completed %s command successfully\n", command);
        else
            printf(" Failed to do %s command\n", command);

        memset(command, 0, 20);
    }

    return 0;
}