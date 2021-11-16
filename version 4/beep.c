//refrence beep1 (/ucfk4/apps/beep1)

#include "system.h"
#include "pio.h"

/* Connect piezo tweeter to pins 6 and 8 of UCFK4 P1 connector
   for push-pull operation.  */
#define PIEZO1_PIO PIO_DEFINE (PORT_D, 4)
#define PIEZO2_PIO PIO_DEFINE (PORT_D, 6)


void beep_init(void) // this function into main
{
    pio_config_set (PIEZO1_PIO, PIO_OUTPUT_LOW);
    pio_config_set (PIEZO2_PIO, PIO_OUTPUT_HIGH);

}


void beep (void)
{
    pio_output_toggle (PIEZO1_PIO);
    pio_output_toggle (PIEZO2_PIO);
}
// into the while [if need change sound_quecny] add [if] define const FRE
