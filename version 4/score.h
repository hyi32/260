#ifndef SCORE_H
#define SCORE_H
#include <stdint.h>

/**
 * Incrememnt score by one
 */
void increment_score(void);

/**
 * Reset the score to 0
 */
void reset_score(void);

/**
 * Get the current score
 * @return current score uint8_t
 */
uint8_t get_score(void);

#endif