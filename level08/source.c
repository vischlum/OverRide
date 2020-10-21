#include <stdio.h>
#include <stdlib.h>

void log_wrapper(FILE *logFD, char *str, char *filename)
{
    char *buff;

    strcpy(buff, str);
    snprintf(buff + strlen(buff), 254 - strlen(buff), filename);
    buff[strcspn(buff, "\n")] = "\0";
    fprintf(logFD, "LOG: %s\n", buff);
}

int main(int argc, char **argv)
{
    FILE *logFD, *argvFD;
    char *buff;
    int fileToSave;
    char chk;

    if (argc != 2)
        printf("Usage: %s filename\n", argv[0]);

    logFD = fopen("./backups/.log", "w");
    if (logFD == NULL) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }
    log_wrapper(logFD, "Starting back up: ", argv[1]);

    argvFD = fopen(argv[1], "r");
    if (argvFD == NULL) {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
    }

    strcpy(buff, "./backups/");
    strncat(buff, argv[1], 99 - strlen(buff));
    fileToSave = open(buff, O_CREAT | O_EXCL | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fileToSave < 0) {
        printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
        exit(1); 
    }
    while( (chk = fgetc(argvFD)) != EOF)
        write(fileToSave, &chk, 1); 
    log_wrapper(logFD, "Finished back up ", argv[1]);

    fclose(argvFD);
    close(fileToSave);

    return 0;
}