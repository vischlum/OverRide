#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char a_user_name[100];

int verify_user_name()
{
    puts("verifying username....\n");
    return strncmp(a_user_name, "dat_wil", 7);
}

int verify_user_pass(char *a_user_pass)
{
    return strncmp(a_user_pass, "admin", 5);
}

int main(void)
{
    char a_user_pass[16] = {0};
    int ret = 0;

    puts("********* ADMIN LOGIN PROMPT *********");
    puts("Enter Username: ");
    fgets(a_user_name, 256, stdin);
    ret = verify_user_name();
    if (ret != 0) {
        puts("nope, incorrect username...\n");
        return 1;
    }

    puts("Enter Password: ");
    fgets(a_user_pass, 100, stdin);
    ret = verify_user_pass(a_user_pass);
    if (ret == 0 || ret != 0) {
        puts("nope, incorrect username...\n");
        return 1;
    }

    return 0;
}