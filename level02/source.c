#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *fd = NULL;
    int readRet = 0;
    char *filePassword;
    char *login;
    char *userPassword;

    fd = fopen("/home/users/level03/.pass", "r");
    if (fd == NULL) {
        fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
        exit(1);
    }

    readRet = fread(filePassword, 1, 41, fd);
    filePassword[strcspn(filePassword, "\n")] = '\0';
    if (readRet != 41) {
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        exit(1);
    }
    fclose(fd);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");

    printf("--[ Username: ");
    fgets(login, 100, stdin);
    login[strcspn(login, "\n")] = '\0';
    printf("--[ Password: ");
    fgets(userPassword, 100, stdin);
    userPassword[strcspn(userPassword, "\n")] = '\0';
    puts("*****************************************");

    if (!strncmp(filePassword, userPassword, 41)) {
        printf("Greetings, %s!\n", login, login);
        system("/bin/sh");
        return 0;
    }
    printf(login);
    puts(" does not have access!");
    exit(1);
}