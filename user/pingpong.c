#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int fd[2];
    char *buf = (char*)0;

    if (pipe(fd) == -1)
    {
        fprintf(2, "Error: pipe(fd) error.\n");
        exit(1);
    }

    int pid = fork();

    if (pid < 0)
    {
        exit(1);
    }

    if (pid > 0)
    {
        *buf = '1';
        write(fd[1], buf, 1);
        close(fd[1]);
        read(fd[0], buf, 1);
        fprintf(2, "%d: received pong\n", getpid());
    }
    else
    {
        *buf = '1';
        read(fd[0], buf, 1);
        fprintf(2, "%d: received ping\n", getpid());
        close(fd[0]);
        write(fd[1], buf, 1);
        close(fd[1]);
    }

    exit(0);
}