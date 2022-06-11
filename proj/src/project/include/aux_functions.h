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

void update_key_press(void);

void update_mouse_press(struct packet pp);

keys_t* (get_key_press)(void);

int (menu_draw)();

uint16_t (mouse_in_box)();

int (process_mouse)(struct packet *p, int in_game);

/**
 * @}
 */
int (map1_init)();

void (map1_background)(void);

#endif //AUX_FUNCTIONS_H_INCLUDED
