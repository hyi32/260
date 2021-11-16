/** @File:   snaek.c
    @Author: Moses Wescombe (@mwe50) Group_107
    @Date:   18 OCT 2021
    @Descr:  A Snake module for the game.c

*/

/* Course-provided modules. */
#include <stdlib.h>
#include <stdbool.h>

/* Student-created modules. */
#include "score.h"
#include "render.h"
#include "apple.h"

//Direction multipliers
static int8_t x_direction= 0;
static int8_t y_direction = 1;

static bool command_made = false;

//Directions
typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction_t;

//Snake component
typedef struct SnakeComponent_s SnakeComponent_t;
struct SnakeComponent_s {
    uint8_t x;
    uint8_t y;
    SnakeComponent_t* next;
    SnakeComponent_t* prev;
};

//Snake linked_list
typedef struct {
    SnakeComponent_t* head;
    SnakeComponent_t* tail;
} Snake_t;

//Snake object
static Snake_t snake;

//Initialize
void snake_init(void) {
    //Create a new component
    SnakeComponent_t* component = calloc(1, sizeof(SnakeComponent_t));
    component->x = 3;
    component->y = 4;
    component->next = NULL;
    component->prev = NULL;

    //Set as head
    snake.head = component;
    snake.tail = component;
}

//Clear the snakes memory
void clear_snake(void) {
    SnakeComponent_t* tail = snake.tail;
    SnakeComponent_t* next;

    //Erase memory
    while (tail != NULL) {
        next = tail->prev;
        free(tail);
        tail = next;
    }
}

//Render the snake
void snake_update(void) {
    SnakeComponent_t* current_comp = snake.head;

    //Loop through all components and set_point on their co-ordinates
    while (current_comp != NULL) {
        set_point(current_comp->x, current_comp->y);
        current_comp = current_comp->next;
    }
}

//Check for a self-collision
bool check_collision(const uint8_t x, const uint8_t y) {
    SnakeComponent_t* comp = snake.head;

    //Make sure there is at least two points
    if (comp->next == NULL) {
        return false;
    } else {
        comp = comp->next;
    }

    //Loop up until the second to last point
    while (comp->next != NULL && comp != snake.tail) {
        //check for collision with co-ordinates
        if (comp->x == x && comp->y == y) {
            return true;
        }
        comp = comp->next;
    }

    return false;
}

//Check for collision with the apples
int8_t check_apple_collision(Apple_t* apples[], uint8_t size) {
    //Go through apples and check collision with snake head
    for (uint8_t i=0; i < size; i++) {
        if (apples[i]->x == snake.head->x && apples[i]->y == snake.head->y) {
            return i;
        }
    }

    return -1;
}

//Move the snake in the current direction
bool snake_move(uint8_t difficulty) {
    SnakeComponent_t* current_comp = snake.head;
    bool game_over = false;

    //Previous position
    uint8_t prev_x = current_comp->x;
    uint8_t prev_y = current_comp->y;

    //Move the head and teleport across border
    if (current_comp->x ==  5 && x_direction == 1) {
        current_comp->x = 1;
        game_over = difficulty >= 4;
    } else if (current_comp->x ==  1 && x_direction == -1) {
        current_comp->x = 5;
        game_over = difficulty >= 4;
    } else if (current_comp->y ==1 && y_direction == 1) {
        current_comp-> y = 7;
        game_over = difficulty >= 4;
    } else if (current_comp->y == 7 && y_direction == -1) {
        current_comp-> y = 1;
        game_over = difficulty >= 4;
    } else {
        current_comp->x = current_comp->x + x_direction;
        current_comp->y = current_comp->y - y_direction;
    }

    //Check for collision with head
    if (check_collision(current_comp->x, current_comp->y)) {
        game_over = true;
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

    command_made = false;

    //Exit on failure
    if (game_over) {
        //Reset
        clear_snake();
        return true;
    }

    return false;
}

//Change the direction of movement
void change_direction(Direction_t direction) {
    if (command_made) {
        return;
    }

    switch (direction) {
        case NORTH:
            if (-y_direction != 1) {
                x_direction = 0;
                y_direction = 1;
                command_made = true;
            }
            break;
        case SOUTH:
            if (-y_direction != -1) {
                x_direction = 0;
                y_direction = -1;
                command_made = true;
            }
            break;
        case EAST:
            if (-x_direction != 1) {
                x_direction = 1;
                y_direction = 0;
                command_made = true;
            }
            break;
        case WEST:
            if (-x_direction != -1) {
                x_direction = -1;
                y_direction = 0;
                command_made = true;
            }
            break;
    }
}

//Add another component to the tail
void snake_grow(void) {
    SnakeComponent_t* current_comp = snake.tail;

    //Create a new component
    SnakeComponent_t* newComponent = calloc(1, sizeof(SnakeComponent_t));
    newComponent->x = current_comp->x;
    newComponent->y = current_comp->y;
    newComponent->next = NULL;
    newComponent->prev = current_comp;

    //Set as end of the snake
    current_comp->next = newComponent;
    snake.tail = newComponent;

    //Add to the score
    increment_score();
}
