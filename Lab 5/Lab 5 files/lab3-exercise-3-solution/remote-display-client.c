#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <zmq.h>
#include <assert.h>

#define WINDOW_SIZE 15

typedef struct ch_info_t
{
    int ch;
    int pos_x, pos_y;
} ch_info_t;

int main()
{
    ch_info_t char_data[100];
    remote_char_t m;
    m.msg_type = 2;
    char sub_topic[50];
    int n_chars = 0;
    int fd;
    void *context = zmq_ctx_new();
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://localhost:5555");

    zmq_send(requester, &m, sizeof(remote_char_t), 0);
    zmq_recv(requester, sub_topic, sizeof(sub_topic), 0);
    
    zmq_connect(subscriber, "tcp://localhost:5556");
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, sub_topic, 50);
    

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    /* creates a window and draws a border */
    WINDOW *my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
    box(my_win, 0, 0);
    wrefresh(my_win);

    int ch;
    int pos_x;
    int pos_y;

    direction_t direction;
    char type[4];
    char_data[0].ch = 0;
    while (1)
    {
        if (zmq_recv(subscriber, &type, 5, 0) == -1)
            exit(0);

        // Clear the window
        for (int i = 0; i < 100; i++)
        {
            if (char_data[i].ch == 0)
                break;

            wmove(my_win, char_data[i].pos_x, char_data[i].pos_y);
            waddch(my_win, ' ');
        }

        if (zmq_recv(subscriber, &char_data, sizeof(ch_info_t) * 100, 0) == -1)
            exit(0);

        for (int i = 0; i < 100; i++)
        {
            if (char_data[i].ch == 0)
                break;

            wmove(my_win, char_data[i].pos_x, char_data[i].pos_y);
            waddch(my_win, char_data[i].ch | A_BOLD);
        }

        wrefresh(my_win);
    }
    endwin();
    zmq_close(requester);
    zmq_close(subscriber);
    zmq_ctx_destroy(context);
    return 0;
}