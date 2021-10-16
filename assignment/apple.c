#include "system.h"
#include "pio.h"
#include <stdlib.h>
#include "render.h"
#include "apple.h"




static Apple_t apple;
/*
void  apple_init(void)
{
    set_point(3,4);
}


void  apple_display(uint8_t x, uint8_t y)
{
    set_point(x,y);
}

void apple_move(void);
{
    turn_off(x,y);

}

void update_apple_pos()
*/


void apple_init(void) {
    //Create a new component
    AppleCom_t* component = calloc(1, sizeof(AppleCom_t));
    component->x = 1;
    component->y = 2;
    component->next = NULL;
    apple.head = component;
}


void apple_display(void)
{
    AppleCom_t* current_com = apple.head;
    while (current_com != NULL) {
        render_display();
        set_point(current_com->x, current_com->y);
        current_com = current_com -> next;
    }
}


void apple_move(void)
{
        //render_display();
    AppleCom_t* current_com = apple.head;
    //uint8_t temp_x = current_com ->x;
    //uint8_t temp_y = current_com ->y;
    turn_off(current_com->x,current_com->y);
     current_com->x = current_com->y + 1;
     current_com->y  = current_com->x + 1;
     //current_com = current_com ->next;
    // free(current_com);
    // while (current_com != NULL) {
    //}
}



int8_t* update_apple_pos(void)
{
    AppleCom_t* current_com = apple.head;
    return current_com;
}
