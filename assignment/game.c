#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "pacer.h"
#include "navswitch.h"
#include "snake.h"
#include "apple.h"

#define PACER_RATE 500



static uint8_t snake_x = 0;
static uint8_t snake_y = 0;

static uint8_t apple_x = 0;
static uint8_t apple_y = 0;

static uint8_t* snake_pos= {0};
static uint8_t* apple_pos= {0};


int main (void)
{
    //Initialize
    system_init ();
    pacer_init(PACER_RATE);
    navswitch_init();

    apple_init();



    render_init();
    snake_init();
    //AppleCom_t ptr = apple_init();
    //Temporary count to manage the movement
    uint16_t count = 0;
    while (1)
    {
        pacer_wait();
        //Update switch
        navswitch_update();
        //Change direction and grow snake
        button_chang();
        //Move once per second
        apple_display();
        //the move speed could be changed by ..
        if (count % 500 == 0) {
            count = 0;
            snake_move();

        }



        snake_update();
        render_display();//keep same brightness
        snake_pos = update_snake_pos();
        snake_x = snake_pos[0];
        snake_y = snake_pos[1];

        apple_pos = update_apple_pos();
        apple_x = apple_pos[0];
        apple_y = apple_pos[1];



        if (snake_x == apple_x && snake_y == apple_y) {
            snake_grow();
            apple_move();
            snake_move();
        }
        count++;
	}
}
