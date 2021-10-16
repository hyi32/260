//
// Created by moses on 15/10/21.
//
#ifndef GROUP_107_SNAKE_H
#define GROUP_107_SNAKE_H
#include <stdlib.h>
#include <stdint.h>
#include "render.h"

/**
 * Direction enumeration
 */
typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction_t;

typedef struct SnakeComponent_s SnakeComponent_t;
struct SnakeComponent_s {
    uint8_t x;
    uint8_t y;
    SnakeComponent_t* next;
};

//Snake linked_list
typedef struct {
    SnakeComponent_t* head;
} Snake_t;

//Snake object



/**
 * Initialize the snake. creating a head peice
 */
void snake_init(void);

/**
 * Update the snakes position
 */
void snake_update(void);

/**
 * Move the snake
 */
void snake_move(void);

/**
 * Chang the direction of the snake, with either NORTH, EAST, SOUTH, WEST
 */
void change_direction(Direction_t direction);

/**
 * Increase the size of the snake from the tail
 */
void snake_grow(void);


void button_chang(void);




uint8_t* update_snake_pos(void);

#endif
