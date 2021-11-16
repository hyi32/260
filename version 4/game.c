/** @File   game.c
    @Author Moses Wescombe (@mwe50) & Heng Yin (hyi32) Group_107
    @Date   18 OCT 2021
    @Descr:  A Snake game for the ENCE260 assignmnent.

			The game will end when the snake eats itself.
            There are 3 level of difficulties the player can choose.
            Different level of difficulties paired with different background sounds.
*/

/* Course-provided modules. */
#include <string.h>
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "pacer.h"
#include "navswitch.h"

/* Student-created modules. */
#include "apple.h"
#include "snake.h"
#include "score.h"
#include "beep.h"

/* ------- Definitions  -------*/
//Default text
#define WELCOME_MESSAGE "SNAKE"
#define SCORE_MESSAGE "SCORE:"

//Define rates
#define PACER_RATE 350
#define MESSAGE_RATE 20
#define SETTING_DISPLAY_TIME 2

//Maximum apples
#define MAX_APPLES 5
#define APPLE_FLASH_RATE 10

//Difficulty
#define MAX_LEVEL 4
#define MIN_LEVEL 1

//Helpful functions
#define MAX(a,b) (((a) > (b))? (a) : (b))
#define MIN(a,b) (((a) < (b))? (a) : (b))


/* ------- Difficulty controls ------- */
//Updates per second (*2 to avoid float values)
typedef enum {
    EASY = 2, //1 a second
    MEDIUM = 3, //1.5 a second
    HARD = 4, //2 a second
    INSANE = 4
} SETTING_T;

//Difficulty selection
SETTING_T difficulties[4] = {EASY, MEDIUM, HARD, INSANE};

//Difficulty index and display value
static uint8_t difficulty = 1;


/* ------- Other Variables ------- */
//Number of apples to render
static uint8_t apple_count = 1;

//sound frequency selection
static uint16_t sound_fre[4] = {1000,200,50,25};


/**
 * Convert to a number, up to 3 digits long
 * @param number Number to convert
 * @return Pointer to char array
 */
char* convert_to_string(uint8_t number) {
    char* number_text = calloc(4, sizeof (char));
    //100s
    number_text[0] = ('0' + (number / 100));
    number = number % 100;
    //10s
    number_text[1] = '0' + (number / 10);
    number = number % 10;
    //1s
    number_text[2] = '0' + (number / 1);

    return number_text;
}

/**
 * Update difficulty text in menu
 */
void update_settings_text(bool* display_settings, uint8_t* setting, uint16_t* counter) {
    char* setting_text = convert_to_string(*setting);

    //Set tinygl
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    tinygl_text(setting_text + 2);
    free(setting_text);

    //Toggle display bool
    *display_settings = true;
    *counter = 0;
}

/**
 * Menu to display welcome message and handle difficulty changes
 */
void menu(void) {
    //Setup tinygl
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(WELCOME_MESSAGE);

    //Timing controls
    uint16_t count = 0;
    bool display_settings = false;

    while (1)
    {
        //Pace
        pacer_wait();
        //Update switch
        navswitch_update();

        //Controls
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            return;
        } else if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            //Increment level
            difficulty = MIN(difficulty + 1, MAX_LEVEL);
            update_settings_text(&display_settings, &difficulty, &count);
        } else if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            //Decrement level
            difficulty = MAX(difficulty - 1, MIN_LEVEL);
            update_settings_text(&display_settings, &difficulty, &count);
        } else if (navswitch_push_event_p(NAVSWITCH_EAST)) {
            //Increment apple count
            apple_count = MIN(apple_count + 1, MAX_APPLES);
            update_settings_text(&display_settings, &apple_count, &count);
        } else if (navswitch_push_event_p(NAVSWITCH_WEST)) {
            //Decrement apple count
            apple_count = MAX(apple_count - 1, 1);
            update_settings_text(&display_settings, &apple_count, &count);
        }

        //Reset settings screen
        if (count == PACER_RATE * SETTING_DISPLAY_TIME && display_settings) {
            //Set back to message
            tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
            tinygl_text(WELCOME_MESSAGE);
            display_settings = false;
            count = 0;
        }

        //Update
        tinygl_update();
        count++;
    }
}

/**
 * Final score screen after losing
 */
void score_screen(void) {
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    //Set score
    char* score_string = SCORE_MESSAGE;
    char* score_value = convert_to_string(get_score());
    tinygl_text(strcat(score_string, score_value));
    free(score_value);

    while (1)
    {
        //Pace
        pacer_wait();
        //Update switch
        navswitch_update();

        //Controls
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            return;
        }

        //Update
        tinygl_update();
    }
}

/**
 * Core game loop, manages the game
 */
void game_loop(void) {
    //Temporary countS to manage the movement timing and apple flash rate
    uint16_t move_count = 0;
    uint16_t apple_flash_count = 0;
    uint8_t cur_col = 1;
    uint8_t prev_col = cur_col;

    //Snake
    snake_init();
    snake_update();

    //Array of apples
    Apple_t* apples[apple_count];
    bool display_apples = true;

    //Generate the first apple
    for (uint8_t i=0; i < apple_count; i++) {
        apples[i] = apple_init();
    }

    while (1)
    {
        //Pace
        pacer_wait();
        //Update switch
        navswitch_update();
        //Change direction and grow snake
        if (navswitch_push_event_p(NAVSWITCH_EAST)) {
            change_direction(EAST);
        } else if (navswitch_push_event_p(NAVSWITCH_WEST)) {
            change_direction(WEST);
        } else if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            change_direction(NORTH);
        } else if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            change_direction(SOUTH);
        }

        //Update movement
        if (move_count == (PACER_RATE * 2) / difficulties[difficulty - 1]) {
            move_count = 0;
            //Move snake and Exit game on collision
            if (snake_move(difficulty)) {
                for (uint8_t i=0; i<apple_count; i++) {
                    free_apple(apples[i]);
                }
                clear_bitmap();
                return; //Exit
            }
            //Check collision with apple
            int8_t index = check_apple_collision(apples, apple_count);
            if (index != -1) {
                snake_grow();
                free_apple(apples[index]);
                apples[index] = apple_init();
            }
        }

        //Toggle apples
        if (apple_flash_count == PACER_RATE/APPLE_FLASH_RATE) {
            display_apples = !display_apples;
            apple_flash_count = 0;
        }

        //Update display
        clear_bitmap();
        if (display_apples) {
            apple_update(apples, apple_count);
        }
        snake_update();

        prev_col = display_column(prev_col, cur_col);
        cur_col = (cur_col+1) > 5? 1 : (cur_col+1);

        //  generate BGM
        if (move_count % sound_fre[difficulty-1] == 0) {
            beep();
        }
        //Increment counters
        apple_flash_count++;
        move_count++;
    }
}

/**
 * Main loop to run application
 * @return Exit
 */
int main (void)
{
    //Initialize
    system_init();
    pacer_init(PACER_RATE);
    beep_init();


    //Setup tinygl
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    render_init();

    //Main loop
    while (1) {
        //1. Display start menu
        menu();

        //2. Play game
        game_loop();

        //3. Display score screen
        score_screen();

        //4. Reset
        reset_score();
        clear_snake();
    }
}
