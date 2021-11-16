/** @File:   apple.c
    @Author: Moses Wescombe (@mwe50) & Heng Yin (hyi32) Group_107
    @Date:   18 OCT 2021
    @Descr:  apple module for game.c 

*/

/* Course-provided modules */
#include <stdlib.h>
#include "system.h"

/* Student-created modules */
#include "render.h"

typedef struct {
    uint8_t x;
    uint8_t y;
} Apple_t;

Apple_t* apple_init(void) {
    Apple_t* apple = calloc(1, sizeof(Apple_t));
    //Generate random point
    uint8_t temp_x = (TCNT1 % 5);
    uint8_t temp_y = (TCNT1 % 7);

    uint8_t pattern = get_bitmap_pattern(temp_x);

    //Make sure its on an emtpy space
    while (pattern & (1 << temp_y)) {
        if (pattern == 0b01111111) {
            temp_x = (temp_x + 1) % 5;
            pattern = get_bitmap_pattern(temp_x);
        } else {
            temp_y = (temp_y + 1) % 7;
        }
    }

    //Set co-ordinates
    apple->x = temp_x + 1;
    apple->y = temp_y + 1;

    return apple;
}

void free_apple(Apple_t* apple) {
    free(apple);
}

void apple_update(Apple_t* apples[], uint8_t size) {
    //Update in bitmap
    for (uint8_t i=0; i < size; i++) {
        set_point(apples[i]->x, apples[i]->y);
    }
};
