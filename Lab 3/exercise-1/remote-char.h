#ifndef REMOTE_CHAR_H
#define REMOTE_CHAR_H
#include <ncurses.h>

// TODO_1 
// declaration the struct corresponding to the exchanged messages

typedef enum
{
    CONNECTION,
    MOVEMENT,
    NO_MOVEMENT
} type_msg;

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} direction_t;

typedef struct
{
    char character;
    int x;
    int y;
} char_info;


typedef struct{
    char character;
    type_msg msg_type;
    direction_t direction;
} msg_fifo;

// TODO_2
//declaration of the FIFO location
#define FIFO_LOCATION "/tmp/my_fifo"
#endif
