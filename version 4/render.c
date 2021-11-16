//
// Created by moses on 15/10/21.
//
#include <stdlib.h>
#include <stdint.h>
#include "system.h"
#include "pio.h"
#include "ledmat.h"

//PIO rows
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

//PIO cols
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

//Display bitmap (grid)
static uint8_t bitmap[] =
{
    0b0000000, 0b0000000, 0b0000000, 0b0000000, 0b0000000
};

uint8_t get_bitmap_pattern(uint8_t index) {
    return bitmap[index];
}

void render_init(void) {
    for (int i=0; i < 5; i++) {
        pio_config_set(cols[i], PIO_OUTPUT_HIGH);
    }

    for (int i=0; i < 7; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }
}

void clear_display(void) {
    for (int i=0; i < 5; i++) {
        pio_output_high(cols[i]);
    }

    for (int i=0; i < 7; i++) {
        pio_output_high(rows[i]);
    }
}

void clear_bitmap(void) {
    for (uint8_t i=0; i < 5; i++) {
        bitmap[i] = 0b0000000;
    }
}

uint8_t display_column (uint8_t previous_column, uint8_t current_column)
{
    uint8_t row_pattern = bitmap[current_column - 1];
    pio_output_high(cols[previous_column - 1]);

    for (uint8_t current_row=0; current_row < 7; current_row++) {
        if ((row_pattern) & (1 << current_row))
        {
            pio_output_low(rows[current_row]);
        }
        else
        {
            pio_output_high(rows[current_row]);
        }
    }

    pio_output_low(cols[current_column - 1]);
    return current_column;
}

void set_point(int x, int y) {
    uint8_t* pattern = &bitmap[x - 1];
    *pattern |= 1 << (y - 1);
}
