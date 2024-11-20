#include "remote-char.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "fifo.h"

int main()
{
    // TODO_4
    int fd = create_FIFO_write(FIFO_LOCATION);

    // TODO_5
    char character;
    do
    {
        printf("Choose a character to control:");
    } while (scanf(" %c", &character) != 1);

    // TODO_6
    msg_fifo m;
    m.character = character;
    m.msg_type = CONNECTION;
    write(fd, &m, sizeof(msg_fifo));

    int sleep_delay;
    direction_t direction;
    m.msg_type = MOVEMENT;
    while (1)
    {
        sleep_delay = random() % 700000;
        usleep(sleep_delay);
        direction = random() % 4;
        
        // TODO_9
        m.direction = direction;

        // TODO_10
        write(fd, &m, sizeof(msg_fifo));
    }

    return 0;
}