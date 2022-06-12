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

/**
 * @brief Updates keyboard press
 */
void update_key_press(void);

/**
 * @brief Updates mouse press
 */
void update_mouse_press(struct packet pp);

/**
 * @brief Gets pressd key
 * @return Returns pressed key
 */
keys_t* (get_key_press)(void);

/**
 * @brief Draws the whole menu and it's options
 * @return Returns 0 if succeded, non 0 other wise;
 */
int (menu_draw)();

/**
 * @brief Checks if mouse pointer is inside any menu options
 * @return Returns selected option or 0 in case of nothing selected
 */
uint16_t (mouse_in_box)();

/**
 * @brief Procecess a mouse click
 * @return Returns 0 if succeded, non 0 other wise;
 */
int (process_mouse)(struct packet *p, int in_game);

/**
 * @}
 */
/**
 * @brief Initiates map draw on screen
 * @return Returns 0 if succeded, non 0 other wise;
 */
int (map1_init)();

/**
 * @brief Draws map backround color
 */
void (map1_background)(void);

#endif //AUX_FUNCTIONS_H_INCLUDED
