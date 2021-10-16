//
// Created by moses on 15/10/21.
//
#include <stdlib.h>
#include <stdint.h>
#include "system.h"
#include "pio.h"
#include "ledmat.h"

static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

void render_init(void) {
    for (int i=0; i < 5; i++) {
        pio_config_set(cols[i], PIO_OUTPUT_HIGH);
    }

    for (int i=0; i < 7; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }
}

void render_display (void) {
    for (int i=0; i < 5; i++) {
        pio_output_high(cols[i]);
    }

    for (int i=0; i < 7; i++) {
        pio_output_high(rows[i]);
    }
}

void set_point(int x, int y) {
    pio_output_low(rows[y - 1]);
    pio_output_low(cols[x - 1]);
}

void turn_off(int x,int y) {
    pio_output_high(rows[y - 1]);
    pio_output_high(cols[x - 1]);
}
