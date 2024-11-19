#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "funcs-ex5.h"

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
    char func[20], str[20], result[100];
    int n, arg;
    while (1)
    {
        printf("Write a function:");
        fgets(func, 20, stdin);

        printf("Write which type of function you want to execute (0 - No args; 1 - An integer arg;):");
        fgets(str, 20, stdin);
        sscanf(str, " %d", &n);
        
        if (n == 1)
        {
            
            printf("Write an integer:");
            fgets(str, 20, stdin);
            sscanf(str, "%d", &arg);
        }
        
        message_type msg;
        msg.funct_type = n;
        strcpy(msg.f_name, func);
        msg.arg = arg;

        write(fd_write, &msg, sizeof(msg));
        
        n = read(fd_read, result, 100);
		if(n<=0){
			perror("read ");
			exit(-1);
		}
        printf("%s", result);
    }
}
