#ifndef AUX_FUNCTIONS_H_INCLUDED
#define AUX_FUNCTIONS_H_INCLUDED

/**
 * @defgroup aux_functions aux_functions
 * @ingroup project
 *
 * @{
 */

#include "libraries.h"

/**
 * @brief Struct that refers if a given key was/was not pressed
 * @param w_pressed 1 if w key was pressed, 0 otherwise 
 * @param a_pressed 1 if a key was pressed, 0 otherwise 
 * @param s_pressed 1 if s key was pressed, 0 otherwise 
 * @param d_pressed 1 if d key was pressed, 0 otherwise 
 * @param lb_pressed 1 if left mouse button was pressed, 0 otherwise 
 */
struct keys {
    int w_pressed;
    int a_pressed;
    int s_pressed;
    int d_pressed;
    int lb_pressed;
};

typedef struct keys keys_t;

/**
 * @brief Struct that can draw in screen numbers from 0 to 999
 * @param numbers Sprite that contains basic sprites for all numbers
 * @param x horizontal position
 * @param y vertical position
 * @param pos2 Most significant position
 * @param pos1 Middle position
 * @param pos0 Less significant position
 */
struct text{
    sprite_t *numbers;
    int16_t x, y;
    int16_t pos2, pos1, pos0;
};

typedef struct text text_t;

/**
 * @brief Struct that can draw dates from 00-00-2000 to 31-12-2099
 * @param score given score value
 * @param numbers Sprite that contains basic sprites for all numbers
 * @param slash Sprite that contains a basic sprite for a slash
 * @param x horizontal position
 * @param y vertical position
 * @param s_pos2 Most significant position for score
 * @param s_pos1 Middle position for score
 * @param s_pos0 Less significant position for score
 * @param pos9 Position 9 for date
 * @param pos8 Position 8 for date
 * @param pos7 Position 7 for date
 * @param pos6 Position 6 for date
 * @param pos5 Position 5 for date
 * @param pos4 Position 4 for date
 * @param pos3 Position 3 for date
 * @param pos2 Position 2 for date
 * @param pos1 Position 1 for date
 * @param pos0 Position 0 for date
 */
struct date{
    uint16_t score;
    sprite_t *numbers;
    sprite_t *slash;
    int16_t x, y;
    int16_t s_pos2, s_pos1, s_pos0;
    int16_t pos9, pos8, pos7, pos6, pos5, pos4, pos3, pos2, pos1, pos0;
};

typedef struct date date_t;

basic_sprite_t **bsp_play;
sprite_t *sp_play;

basic_sprite_t **bsp_exit;
sprite_t *sp_exit;

basic_sprite_t **bsp_instructions;
sprite_t *sp_instructions;

basic_sprite_t **bsp_highscore;
sprite_t *sp_highscore;

basic_sprite_t **bsp_numbers;
sprite_t *sp_numbers;

basic_sprite_t **bsp_hud;
sprite_t *sp_hud;

basic_sprite_t **bsp_slash;
sprite_t *sp_slash;

text_t *p_health;
text_t *p_kills;
text_t *game_timer;

text_t *end_p_kills;
text_t *end_game_timer;

date_t *date1;
date_t *date2;
date_t *date3;


/**
 * @brief Text constructor that loads numbers and default position in screen
 * @param x horizontal position
 * @param y vertical position
 * @return constructed Text
 */
text_t*(text_ctor)(int16_t x, int16_t y);

/**
 * @brief Sets number for 3 positions
 * @param t Text struct
 * @param pos2 Most significant position
 * @param pos1 Middle position
 * @param pos0 Less significant position
 */
void (text_set_number)(text_t *t, int16_t pos2, int16_t pos1, int16_t pos0);

/**
 * @brief Updates mouse pressed into the global keys
 */
void update_key_press(void);

/**
 * @brief Updates mouse pressed into the global keys
 * @param pp mouse packet with latest updates
 */
void update_mouse_press(struct packet pp);

/**
 * @brief Gets global key struct
 * @return global key struct
 */
keys_t* (get_key_press)(void);


/**
 * @brief Sets default HUD components
 */
void(set_hud)();

/**
 * @brief Draws HUD with new values
 * @param h new health value
 * @param k new kills value
 * @param t new time value
 */
void(draw_hud)(int h, int k, int t);

/**
 * @brief Sets Highscore with new kills value
 * @param k new kills value
 */
void (set_highscore)(int k);

/**
 * @brief Sets default highscore components
 */
void (start_highscore)();

/**
 * @brief Draws High score
 */
void (draw_highscore)();

/**
 * @brief Draws end game screen
 * @param k kills value
 * @param t time survived
 */
void(draw_end_game)(int k, int t);

/**
 * @brief Set menu components
 */
void (set_menu)();

/**
 * @brief Gets value if its on top of a menu item
 * @return 1 to 4 if selected Play, HighScore, Instructions or Exit, respectively
 */
uint16_t (mouse_on_top)();

/**
 * @brief Draws Main Menu
 * 
 */
void (draw_menu)();

uint16_t (mouse_in_box)();

/**
 * @brief Processes mouse position in screen for a given scenario
 * @param in_game if not in game
 */
int (process_mouse)(struct packet *p, int in_game);

/**
 * @brief Date constructor
 * @param x horizontal position
 * @param y vertical position
 * @return date
 */
date_t*(date_ctor)(int16_t x, int16_t y);

/**
 * @brief Sets new score into date
 * @param t date struct
 * @param pos2 Most significant position
 * @param pos1 Middle position
 * @param pos0 Less significant position
 */
void (date_set_number)(date_t *t,int16_t pos2,  int16_t pos1, int16_t pos0);

/**
 * @brief Draws a given date
 * @param t date to be drawn
 * 
 */
void (date_draw)(date_t *t);

int (map1_init)();

void (map1_background)(void);

/**
 * @}
 */

#endif //AUX_FUNCTIONS_H_INCLUDED
