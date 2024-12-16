#include <ncurses.h>
#include "../remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <zmq.h>
#include "zhelpers.h"
#include "../balls.pb-c.h"

#define WINDOW_SIZE 15

// STEP 1
typedef struct ch_info_t
{
    int ch;
    int pos_x, pos_y;
} ch_info_t;



BallDrawDisplayMsg  * zmq_read_BallDrawDisplayMsg(void * subscriber){

        zmq_msg_t msg_raw;
        zmq_msg_init (&msg_raw);
        int n_bytes = zmq_recvmsg(subscriber, &msg_raw, 0);
        char *pb_msg = zmq_msg_data (&msg_raw);

        BallDrawDisplayMsg  * ret_value =
                ball_draw_display_msg__unpack(NULL, n_bytes, pb_msg);
        zmq_msg_close (&msg_raw);
        return ret_value;
}

int main()
{

    char cc_str[100];
    char client_name[100];

    printf("you is your name: ");
    fgets(client_name, 100, stdin);
    printf("you is your credit_card_name: ");
    fgets(cc_str, 100, stdin);


    ch_info_t char_data[100];
    int n_chars = 0;



    void *context = zmq_ctx_new ();

    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:55555");


    int msg_type = 2;
    zmq_send(requester, &msg_type, sizeof(msg_type), ZMQ_SNDMORE);


    // TODO 2 - send the name and credit card to the server using protocol buffers
    //         create a C structure of type PayperviewReq + PAYPERVIEW_RESP__INIT
    //         fill the C structure with the datapayperview_req__get_packed_size)
    //         create a buffer
    //         pack the C structure (payperview_req__pack) into the buffer

    // TODO 2
    PayperviewReq pay_m_stuct = PAYPERVIEW_REQ__INIT;
    pay_m_stuct.client_name = client_name;
    pay_m_stuct.credit_card_number = cc_str;

    int msg_len = payperview_req__get_packed_size(&pay_m_stuct);
    char * msg_buf = malloc(msg_len);
    payperview_req__pack(&pay_m_stuct, msg_buf);
    zmq_send(requester, msg_buf, msg_len, 0);
    free(msg_buf);

    // TODO 5 -  read and process the payperview_resp message
    zmq_msg_t zmq_msg;
    zmq_msg_init (&zmq_msg);

    int msg_len_resp = zmq_recvmsg (requester, &zmq_msg, 0);
    void * msg_data = zmq_msg_data (&zmq_msg);
    PayperviewResp * resp_m = payperview_resp__unpack(NULL, msg_len_resp, msg_data);
    // TODO 5


    //Convert resp_m->code to string
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    zmq_connect (subscriber, "tcp://localhost:55556");
    zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, &resp_m->code, sizeof(resp_m->code));


	initscr();
	cbreak();
    keypad(stdscr, TRUE);
	noecho();

    /* creates a window and draws a border */
    WINDOW * my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
    box(my_win, 0 , 0);
	wrefresh(my_win);

    int ch;
    int pos_x;
    int pos_y;


    int random_secret;
    remote_display_m m;
    BallDrawDisplayMsg  * pb_m_stuct;
    while (1)
    {

        zmq_recv(subscriber, &random_secret, sizeof(random_secret), 0);

        pb_m_stuct = zmq_read_BallDrawDisplayMsg(subscriber);

        pos_x = pb_m_stuct->x;
        pos_y = pb_m_stuct->y;
        ch = (char) pb_m_stuct->ch.data[0];


       // free(pb_msg);
       // zmq_msg_close (&msg_raw);

        /* draw mark on new position */
        wmove(my_win, pos_x, pos_y);
        waddch(my_win,ch| A_BOLD);
        wrefresh(my_win);

    }
  	endwin();			/* End curses mode		  */

	return 0;
}