#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int create_FIFO_read()
{
    int fd;
    while ((fd = open("/tmp/fifo_teste", O_RDONLY)) == -1)
    {
        if (mkfifo("/tmp/fifo_teste", 0666) != 0)
        {
            printf("problem creating the fifo\n");
            exit(-1);
        }
        else
        {
            printf("fifo created\n");
        }
    }
    printf("fifo just opened\n");
    return fd;
}

int create_FIFO_write()
{
    int fd;
    while ((fd = open("/tmp/fifo_teste2", O_WRONLY)) == -1)
    {
        if (mkfifo("/tmp/fifo_teste2", 0666) != 0)
        {
            printf("problem creating the fifo\n");
            exit(-1);
        }
        else
        {
            printf("fifo created\n");
        }
    }
    printf("fifo just opened for writing\n");
    return fd;
}

int main()
{
    int fd_write = create_FIFO_write();
    int fd_read = create_FIFO_read();
    char str[20];
    int n;
    char result[100];
    while (1)
    {
        printf("write a string:");
        fgets(str, 20, stdin);
        write(fd_write, str, 20);
        

        n = read(fd_read, result, 100);
		if(n<=0){
			perror("read ");
			exit(-1);
		}
        printf("%s", result);
    }
}
