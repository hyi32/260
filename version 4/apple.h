/** @File:   apple.h
    @Author: Moses Wescombe (@mwe50) & Heng Yin (hyi32) Group_107
    @Date:   18 OCT 2021
    @Descr:  apple module for game.c
*/

#ifndef APPLE_H
#define APPLE_H

/* Course-provided modules. */
#include <stdlib.h>
#include "system.h"

typedef struct {
    uint8_t x;
    uint8_t y;
} Apple_t;

/**
 * Initialize the apple at a random spot
 * @return pointer to the apple
 */
Apple_t* apple_init(void);

/**
 * Free the memory storing an apple
 * @param apple Pointer to the apple
 */
void free_apple(Apple_t* apple);

/**
 * Update the renderer with the positions of the apples
 * @param apples List of apples to update
 * @param size Size of list
 */
void apple_update(Apple_t* apples[], uint8_t size);

#endif
