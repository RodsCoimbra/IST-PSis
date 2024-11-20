#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int create_FIFO_read(char *fifo_location)
{
    int fd;
    while ((fd = open(fifo_location, O_RDONLY)) == -1)
    {
        if (mkfifo(fifo_location, 0666) != 0)
            exit(-1);
    }
    return fd;
}

int create_FIFO_write(char *fifo_location)
{
    int fd;
    while ((fd = open(fifo_location, O_WRONLY)) == -1)
    {
        if (mkfifo(fifo_location, 0666) != 0)
            exit(-1);
    }
    return fd;
}