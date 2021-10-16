//
// Created by moses on 15/10/21.
//
#ifndef GROUP_107_RENDER_H
#define GROUP_107_RENDER_H

#include "system.h"
#include "pio.h"
#include "ledmat.h"


/**
 * Initialize the renderer
 */
void render_init(void);

/**
 * Clear the display
 */
void clear_display(void);

/**
 * Set a single point
 * @param x X co-ordinate
 * @param y Y co-ordinate
 */
void set_point(int x, int y);

void turn_off(int x,int y);

#endif //GROUP_107_RENDER_H
