#ifndef APPLE_H
#define APPLE_H

#include "system.h"
#include "pio.h"
#include "render.h"
#include <stdlib.h>


typedef struct AppleCom_s AppleCom_t;
struct AppleCom_s {
    uint8_t x;
    uint8_t y;
    AppleCom_t* next; };


// Apple linked_list
typedef struct {
    AppleCom_t* head;
} Apple_t;


void  apple_init(void);


void  apple_display(void);

void apple_move(void);



int8_t* update_apple_pos(void);

#endif
