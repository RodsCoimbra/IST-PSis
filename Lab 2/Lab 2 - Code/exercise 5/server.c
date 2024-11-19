#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include "funcs-ex5.h"
#include <string.h>

int create_FIFO_read()
{
    int fd;
    while ((fd = open("/tmp/fifo_teste2", O_RDONLY)) == -1)
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
    printf("fifo just opened\n");
    return fd;
}

int create_FIFO_write()
{
    int fd;
    while ((fd = open("/tmp/fifo_teste", O_WRONLY)) == -1)
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
    printf("fifo just opened for writing\n");
    return fd;
}

char *trim_function(char *str)
{
    int count = 0;
    // Trim the string
    for (int i = 0; str[i] != '\n'; i++)
    {
        count++;
    }

    char *func_name = (char *)malloc(count * sizeof(char));

    for (int i = 0; i < count; i++)
    {
        func_name[i] = str[i];
    }
    return func_name;
}

message_type read_FIFO(int fd)
{
    // read function name from fifo
    int n;
    message_type msg;
    n = read(fd, &msg, sizeof(msg));
    if (n <= 0)
    {
        perror("read");
        exit(-1);
    }
    return msg;
}

int main()
{
    int fd_read = create_FIFO_read();
    int fd_write = create_FIFO_write();
    void *handle;
    handle = dlopen("./funcs-ex5.so", RTLD_LAZY);

    while (1)
    {

        message_type msg = read_FIFO(fd_read);
        char *func_name = trim_function(msg.f_name);
        int (*pfunc)();
        int (*pfunc2)(int);
        int return_value;
        switch (msg.funct_type)
        {
        case 0:
            pfunc = dlsym(handle, func_name);
            if (pfunc == NULL)
            {
                write(fd_write, "Function not found, case 0\n", 100);
                continue;
            }
            return_value = pfunc();
            break;

        case 1:
            pfunc2 = dlsym(handle, func_name);
            if (pfunc2 == NULL)
            {
                write(fd_write, "Function not found, case 1\n", 100);
                continue;
            }
            return_value = pfunc2(msg.arg);
            break;

        default:
            write(fd_write, "Invalid type\n", 100);
            continue;
        }

        char result[100];
        sprintf(result, "Function %s -> Result = %d\n", func_name, return_value);
        write(fd_write, result, 100);

        free(func_name);
    }

    dlclose(handle);
}
