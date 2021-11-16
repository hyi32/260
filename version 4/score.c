/** @File:   score.c
    @Author: Moses Wescombe (@mwe50) Group_107
    @Date:   18 OCT 2021
    @Descr:  A score module for the game.c

*/

#include <stdint.h>

//Score
static uint8_t score = 0;

void increment_score(void) {
    score++;
}

void reset_score(void) {
    score = 0;
}

uint8_t get_score(void) {
    return score;
}
