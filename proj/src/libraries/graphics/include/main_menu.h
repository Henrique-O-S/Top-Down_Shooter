#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED

#include "font.h"

typedef struct main_menu main_menu_t;

menu_t* (menu_ctor)(const font_t *fnt);

void (menu_dtor)(main_menu *p);

int (menu_add_item)(main_menu *menu, const char *s);

int (menu_update_state)(main_menu *menu, int click);

void (menu_draw)(main_menu *menu);

/**
 * @}
 */

#endif //MAIN_MENU_H_INCLUDED
