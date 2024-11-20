#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include "fifo.h"
#include "remote-char.h"

int main()
{

    // TODO_4
    //  create and open the FIFO for writing
    int fd = create_FIFO_write(FIFO_LOCATION);

    // TODO_5
    //  read the character from the user
    char character;
    do
    {
    printf("Choose a character to control:");
    } while (scanf(" %c", &character) != 1);

    // TODO_6
    // send connection message
    msg_fifo m;
    m.character = character;
    m.msg_type = CONNECTION;
    write(fd, &m, sizeof(msg_fifo));

    initscr();            /* Start curses mode 		*/
    cbreak();             /* Line buffering disabled	*/
    keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
    noecho();             /* Don't echo() while we do getch */

    int ch;
    do
    {
        ch = getch();
        m.msg_type = MOVEMENT;
        switch (ch)
        {
        case KEY_LEFT:
            mvprintw(0, 0, "Left arrow is pressed");
            m.direction = LEFT;
            break;
        case KEY_RIGHT:
            mvprintw(0, 0, "Right arrow is pressed");
            m.direction = RIGHT;
            break;
        case KEY_DOWN:
            mvprintw(0, 0, "Down arrow is pressed");
            m.direction = DOWN;
            break;
        case KEY_UP:
            mvprintw(0, 0, "Up arrow is pressed");
            m.direction = UP;
            break;
        default:
            ch = 'x';
            m.msg_type = NO_MOVEMENT;
            break;
        }
        refresh(); /* Print it on to the real screen */
        // TODO_9
        //  prepare the movement message
        //Done in the switch statement          
        

        // TODO_10
        // send the movement message
        write(fd, &m, sizeof(msg_fifo));

    } while (ch != 27);

    endwin(); /* End curses mode		  */

    return 0;
}