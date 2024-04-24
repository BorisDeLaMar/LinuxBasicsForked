#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    int fd1, fd2;

    mkfifo("in1", 0644);
    mkfifo("in2", 0644);
    fd1 = open("in1", O_WRONLY);
    fd2 = open("in2", O_WRONLY);

    getchar();
    write(fd1, "10", 2);
    write(fd2, "20", 2);
    getchar();
    write(fd2, "4", 1);
    write(fd1, "1", 1);

    close(fd1);
    close(fd2);
    unlink("in1");
    unlink("in2");

    return 0;
}
