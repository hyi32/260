#include <stdlib.h>
#include <stdint.h>
#include "render.h"
#include "apple.h"
#include "navswitch.h"
#include "snake.h"
//Direction multipliers
static int8_t x_direction= 0;
static int8_t y_direction = 1;

//Directions

//Snake object
static Snake_t snake;


//Initialize
void snake_init(void) {
    //Create a new component
    SnakeComponent_t* component = calloc(1, sizeof(SnakeComponent_t));
    component->x = 3;
    component->y = 4;
    component->next = NULL;

    //Set as head
    snake.head = component;
}




//Render the
void snake_update(void) {
    SnakeComponent_t* current_comp = snake.head;

    //Loop through all components and set_point on their co-ordinates
    while (current_comp != NULL) {
        render_display();
        set_point(current_comp->x, current_comp->y);
        current_comp = current_comp->next;
    }

    //return box;
}

//Move the snake in the current direction
void snake_move(void) {
    SnakeComponent_t* current_comp = snake.head;

    //Previous position
    uint8_t prev_x = current_comp->x;
    uint8_t prev_y = current_comp->y;

    //Move the head
    if (current_comp->x ==  5 && x_direction == 1) {
        current_comp->x = 1;
    } else if (current_comp->x ==  1 && x_direction == -1) {
        current_comp->x = 5;
    } else if (current_comp->y ==1 && y_direction == 1) {
        current_comp-> y = 7;
    } else if (current_comp->y == 7 && y_direction == -1) {
        current_comp-> y = 1;
/*

    } else if (current_comp->x == 1 && current_comp->y == 2  ) {
        apple_move();
        current_comp->x = current_comp->x + x_direction;
        current_comp->y = current_comp->y - y_direction;

*/


    }  else {
        current_comp->x = current_comp->x + x_direction;
        current_comp->y = current_comp->y - y_direction;
    }


    current_comp =  current_comp->next;

    //Move the body
    while (current_comp != NULL) {
        //Save the current position
        uint8_t temp_x = current_comp->x;
        uint8_t temp_y = current_comp->y;

        //Update the current position to parents previous position
        current_comp->x = prev_x;
        current_comp->y = prev_y;

        //Set previous position
        prev_x = temp_x;
        prev_y = temp_y;
        current_comp = current_comp->next;
    }


}

//Change the direction of movement
void change_direction(Direction_t direction) {
    switch (direction) {
        case NORTH:
            x_direction = 0;
            y_direction = 1;
            break;
        case SOUTH:
            x_direction = 0;
            y_direction = -1;
            break;
        case EAST:
            x_direction = 1;
            y_direction = 0 ;
            break;
        case WEST:
            x_direction = -1;
            y_direction = 0;
            break;
    }
}

//Add another component to the tail
void snake_grow(void) {
    SnakeComponent_t* current_comp = snake.head;

    //Get to the end of the snake
    while (current_comp->next != NULL) {
        current_comp = current_comp->next;
    }

    //Create a new component
    SnakeComponent_t* newComponent = calloc(1, sizeof(SnakeComponent_t));
    newComponent->x = current_comp->x;
    newComponent->y = current_comp->y;
    newComponent->next = NULL;

    //Set as end of the snake
    current_comp->next = newComponent;
}


void button_chang(void)
{
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        snake_grow();
    } else if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        change_direction(EAST);
    } else if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        change_direction(WEST);
    } else if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        change_direction(NORTH);
    } else if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        change_direction(SOUTH);
    }

}

uint8_t* update_snake_pos(void)
{
    SnakeComponent_t* current_comp = snake.head;
//    current_comp->x;
    return current_comp;
}
