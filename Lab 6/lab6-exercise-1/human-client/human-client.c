#include <ncurses.h>
#include "../remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <ctype.h> 
#include <stdlib.h>
#include "../balls.pb-c.h"
 
#include <zmq.h>
#include "zhelpers.h"

int main()
{
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    int rc = zmq_connect (requester, "tcp://localhost:55555");
    if (rc!=0){
        printf("error connecting REQ socket");
        exit(-1);
    }
	printf("socket connected\n");

    char ch;
    do{
        printf("what is your character(a..z)?: ");
        ch = getchar();
        ch = tolower(ch);  
    }while(!isalpha(ch));



    int msg_type = 0;
    zmq_send(requester, &msg_type, sizeof(msg_type), ZMQ_SNDMORE);

    // TODO 7 - create and fill a message of type client_connection_req   
    //           and send the packed message to the server
    ClientConnectionReq ccr = CLIENT_CONNECTION_REQ__INIT;
    ccr.client_id = &ch;
    int msg_len = client_connection_req__get_packed_size(&ccr);
    char * msg_buf = malloc(msg_len);
    client_connection_req__pack(&ccr, msg_buf);
    zmq_send (requester, msg_buf, msg_len, 0);
    free(msg_buf);
    // TODO 7

    char * str = s_recv(requester);
    free(str);   


	initscr();			/* Start curses mode 		*/
	cbreak();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    int n = 0;

    MovementReq mov_msg = MOVEMENT_REQ__INIT;
    mov_msg.client_id = &ch;
    
    int key;
    do
    {
    	key = getch();		
        n++;
        switch (key)
        {
        case KEY_LEFT:
            mvprintw(0,0,"%d Left arrow is pressed", n);
            mov_msg.direction = LEFT;
            break;
        case KEY_RIGHT:
            mvprintw(0,0,"%d Right arrow is pressed", n);
            mov_msg.direction = RIGHT;
            break;
        case KEY_DOWN:
            mvprintw(0,0,"%d Down arrow is pressed", n);
            mov_msg.direction = DOWN;
            break;
        case KEY_UP:
            mvprintw(0,0,"%d :Up arrow is pressed", n);
            mov_msg.direction = UP;
            break;

        default:
            key = 'x'; 
            break;
        }

         if (key != 'x'){
            int msg_type = 1;
            zmq_send(requester, &msg_type, sizeof(msg_type), ZMQ_SNDMORE);

            // TODO 10 - create and fill a message of type  movement_req  
            //           and send the packed message to the server
            int msg_len = movement_req__get_packed_size(&mov_msg);
            char * msg_buf = malloc(msg_len);
            movement_req__pack(&mov_msg, msg_buf);
            zmq_send(requester, msg_buf, msg_len, 0);
            free(msg_buf);
            // TODO 10


            char * str = s_recv(requester);
            free(str);   
        }
        refresh();			/* Print it on to the real screen */
    }while(key != 27);
    
    
  	endwin();			/* End curses mode		  */

	return 0;
}