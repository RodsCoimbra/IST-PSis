#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include "funcs.h"

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

char *read_FIFO(char* func_name, int fd)
{
    // read function name from fifo
    int n;
    char str[20];
    int count;
    n = read(fd, str, 20);
    if (n <= 0)
    {
        perror("read");
        exit(-1);
    }
    count = 0;

    // Trim the string
    for (int i = 0; str[i] != '\n'; i++)
    {
        count++;
    }

    func_name = (char *)malloc(count * sizeof(char));

    for (int i = 0; i < count; i++)
    {
        func_name[i] = str[i];
    }
    return func_name;
}

int main()
{
    int fd_read = create_FIFO_read();
    int fd_write = create_FIFO_write();
    void *handle;
    handle = dlopen("./funcs.so", RTLD_LAZY);

    
    char *func_name = NULL;
    
    while (1)
    {

        func_name = read_FIFO(func_name, fd_read);

        // Call the function
        int (*pfunc)();
        pfunc = dlsym(handle, func_name);

        if (pfunc == NULL)
        {
            write(fd_write, "Function not found\n", 100);
            continue;
        }

        char result[100];
        sprintf(result, "Function %s -> Result = %d\n", func_name, pfunc());
        write(fd_write, result, 100);

        free(func_name);
    }

    dlclose(handle);
}
