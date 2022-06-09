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

uint16_t (mouse_in_box)(){
  uint16_t select = 0;

  uint16_t mouse_x = get_mouse_X();
  uint16_t mouse_y = get_mouse_Y();

  uint16_t x_box = get_XRes() / 2 - (350 / 2);
  uint16_t x1_box = get_XRes() / 2 - (350 / 2) + 350;
  uint16_t y_box =  (get_YRes() / 6)- 15;
  uint16_t y1_box =  y_box + get_YRes() / 7;
  uint16_t y_box_exit =  3 * (get_YRes() / 6)-15;
  uint16_t y1_box_exit = y_box_exit + get_YRes() / 7;

  if(mouse_x >= x_box && mouse_x <= x1_box && mouse_y >= y_box && mouse_y <= y1_box){
      select = 1;
  }else if (mouse_x >= x_box && mouse_x <= x1_box && mouse_y >= y_box_exit && mouse_y <= y1_box_exit){
      select = 2;
  }
  return select;
}

int (process_mouse)(struct packet *p){
  uint16_t selected = mouse_in_box();
  if(p->lb){
    return selected;
  }
  return 0;
}
