#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/prctl.h>
#include <sys/wait.h>

int main(void)
{
    char buffer[128] = {0};
    int syscall = 0;
    int status = 0;
    pid_t child = fork();

    if(child == 0)
    {
        prctl(1, 1);
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        puts("Give me some shellcode, k");
        gets(buffer);
    }
    else
    {
        while(1)
        {
            wait(&status);
            if (WIFEXITED(status) || WIFSIGNALED(status)) {
                puts("child is exiting...");
                break;
            }

            syscall = ptrace(PTRACE_PEEKUSER, child, 44, 0);
            if(syscall == 11)
            {
                puts("no exec() for you");
                kill(child, 9);
                break;
            }
        }
    }

    return 0;
}