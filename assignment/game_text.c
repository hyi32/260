#include "system.h"
#include "simplefont.h"
#include "pacer.h"
#include "ledmat.h"



char message[] = "HI !!";
    uint8_t col = 0;
    uint8_t index = 0;
    uint8_t tick = 0;

    system_init ();
    ledmat_init ();

    pacer_init (LOOP_RATE);

    /* Paced loop.  */
    while (1)
    {
        /* Wait for next tick.  */
        pacer_wait ();

        ledmat_display_column (font[(message[index] - ' ') * 5 + col],
                               col);

        col++;
        if (col > 4)
            col = 0;

        /* Advance message.  */
        tick++;
        if (tick >= LOOP_RATE / MESSAGE_RATE)
        {
            tick = 0;
            index++;
            if (!message[index])
                index = 0;
        }
    }
