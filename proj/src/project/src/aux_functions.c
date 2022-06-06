#include <lcom/lcf.h>

#include "aux_functions.h"

int (menu_init)(){
  vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MENU_BACKGROUND_COLOR);

  vg_draw_rectangle(get_XRes() / 2 - (350 / 2), 1 * (get_YRes() / 6) , 350, get_YRes() / 7 , MENU_OPTION_COLOR);
  vg_draw_rectangle(get_XRes() / 2 - (350 / 2), 3 * (get_YRes() / 6) , 350, get_YRes() / 7 , MENU_OPTION_COLOR);
  
  pixmap_drawer(get_XRes() / 2 - (350 / 2) + (350 / 7), 1 * (get_YRes() / 6) + ((get_YRes() / 7) / 4), PLAY);

  pixmap_drawer(get_XRes() / 2 - (350 / 2) + (350 / 4), 3 * (get_YRes() / 6) + ((get_YRes() / 7) / 4), EXIT);

  //Dimensions used should probably be macros

  return 0;
}
