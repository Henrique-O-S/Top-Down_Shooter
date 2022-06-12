#ifndef AUX_FUNCTIONS_H_INCLUDED
#define AUX_FUNCTIONS_H_INCLUDED

/**
 * @defgroup aux_functions aux_functions
 * @ingroup proj
 *
 * @{
 */

#include "libraries.h"

struct keys {
    int w_pressed;
    int a_pressed;
    int s_pressed;
    int d_pressed;
    int lb_pressed;
};

typedef struct keys keys_t;

struct text{
    sprite_t *numbers;
    int16_t x, y;
    int16_t pos2, pos1, pos0;
};

typedef struct text text_t;

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


text_t*(text_ctor)(int16_t x, int16_t y);

void (text_set_number)(text_t *t, int16_t pos2, int16_t pos1, int16_t pos0);

void update_key_press(void);

void update_mouse_press(struct packet pp);

keys_t* (get_key_press)(void);

int (menu_draw)();

void(set_hud)();

void(draw_hud)(int h, int k, int t);

void (set_highscore)(int k);

void (start_highscore)();

void (draw_highscore)();

void(draw_end_game)(int k, int t);

void (set_menu)();

uint16_t (mouse_on_top)();

void (draw_menu)();

uint16_t (mouse_in_box)();

int (process_mouse)(struct packet *p, int in_game);

date_t*(date_ctor)(int16_t x, int16_t y);

void (date_set_number)(date_t *t,int16_t pos2,  int16_t pos1, int16_t pos0);
void (date_draw)(date_t *t);

/**
 * @}
 */
int (map1_init)();

void (map1_background)(void);

#endif //AUX_FUNCTIONS_H_INCLUDED
