#include <stdlib.h>
#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "fifo.h"

#define WINDOW_SIZE 15

direction_t random_direction()
{
    return random() % 4;
}
void new_position(int *x, int *y, direction_t direction)
{
    switch (direction)
    {
    case UP:
        (*x)--;
        if (*x == 0)
            *x = 2;
        break;
    case DOWN:
        (*x)++;
        if (*x == WINDOW_SIZE - 1)
            *x = WINDOW_SIZE - 3;
        break;
    case LEFT:
        (*y)--;
        if (*y == 0)
            *y = 2;
        break;
    case RIGHT:
        (*y)++;
        if (*y == WINDOW_SIZE - 1)
            *y = WINDOW_SIZE - 3;
        break;
    default:
        break;
    }
}

void receive_message(int fd, msg_fifo *m)
{
    if (read(fd, m, sizeof(msg_fifo)) <= 0)
    {
        perror("read ");
        exit(-1);
    }
}

char_info* search_player(char_info players[], int n_players, char character)
{
    for (int i = 0; i < n_players; i++)
    {
        if (players[i].character == character)
        {
            return &players[i];
        }
    }
    endwin();
    exit(-1);
}

int main()
{

    // TODO_3
    // create and open the FIFO for reading
    int fd = create_FIFO_read(FIFO_LOCATION);

    // ncurses initialization
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    /* creates a window and draws a border */
    WINDOW *my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
    box(my_win, 0, 0);
    wrefresh(my_win);

    /* information about the character */
    char_info players[6];
    int n_players = 0;


    direction_t direction;
    msg_fifo m;
    char_info* data_player;
    while (1)
    {
        // TODO_7
        // receive message from the clients
        receive_message(fd, &m);
        // TODO_8
        //  process connection messages
        if (m.msg_type == CONNECTION)
        {
            data_player = &players[n_players];
            (*data_player).character = m.character;
            (*data_player).x = WINDOW_SIZE / 2;
            (*data_player).y = WINDOW_SIZE / 2;
            n_players++;
        }

        // TODO_11
        // process the movement message
        else if(m.msg_type == MOVEMENT)
        {
            data_player = search_player(players, n_players, m.character);
            direction = m.direction;
            wmove(my_win, (*data_player).x, (*data_player).y);
            waddch(my_win, ' ');
            new_position(&(*data_player).x, &((*data_player).y), direction);
        }
        
        /* draw mark on new position */
        wmove(my_win, (*data_player).x, (*data_player).y);
        waddch(my_win, (*data_player).character | A_BOLD);
        wrefresh(my_win);
    }
    endwin(); /* End curses mode		  */

    return 0;
}