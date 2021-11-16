/** @File:   score.h
    @Author: Moses Wescombe (@mwe50) Group_107
    @Date:   15 OCT 2021
    @Descr:  A score module for the game.c

*/

#ifndef GROUP_107_RENDER_H
#define GROUP_107_RENDER_H
#include <stdint.h>
#include "system.h"
#include "pio.h"
#include "ledmat.h"

/**
 * Get bit pattern for given column
 * @param index Index of the column (0-4)
 * @return Bit pattern of column
 */
uint8_t get_bitmap_pattern(uint8_t index);

/**
 * Initialize the renderer
 */
void render_init(void);

/**
 * Clear the display
 */
void clear_display(void);

/**
 * Clear the points in the bitmap
 */
void clear_bitmap(void);

/**
 * Render a column
 */
uint8_t display_column (uint8_t previous_column, uint8_t current_column);

/**
 * Set a single point in the bitmap
 * @param x X co-ordinate
 * @param y Y co-ordinate
 */
void set_point(int x, int y);

#endif //GROUP_107_RENDER_H
