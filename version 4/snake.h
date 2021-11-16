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

/**
 * Initialize the snake. creating a head peice
 */
void snake_init(void);

/**
 * Clean up the snake and remove from memory
 */
void clear_snake(void);

/**
 * Update the snakes position
 */
void snake_update(void);

/**
 * Move the snake, if the difficulty is above 3 the game is over when the player hits the borders
 * Else teleport
 *
 * @param difficulty The current difficulty setting of the game
 * @return Bool true if a collision has occured, false otherwise
 */
bool snake_move(uint8_t difficulty);

/**
 * Chang the direction of the snake, with either NORTH, EAST, SOUTH, WEST
 */
void change_direction(Direction_t direction);

/**
 * Increase the size of the snake from the tail
 */
void snake_grow(void);

/**
 * Check for collision between the apples and the snake head.
 * @param apples List of apples to check against
 * @param size Size of apple list
 * @return Index of apple, -1 if no collision
 */
int8_t check_apple_collision(Apple_t* apples[], uint8_t size);

#endif
