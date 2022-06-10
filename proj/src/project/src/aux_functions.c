#include <lcom/lcf.h>

#include "aux_functions.h"
#include "mouse.h"

static keys_t key;

void update_key_press(void) {
  if(keyboard_get_size() == 1) {
    switch (get_scancode()[0]) {
      case W_MAKE: key.w_pressed = 1; break;
      case W_BREAK: key.w_pressed = 0; break;
      case A_MAKE: key.a_pressed = 1; break;
      case A_BREAK: key.a_pressed = 0; break;
      case S_MAKE: key.s_pressed = 1; break;
      case S_BREAK: key.s_pressed = 0; break;
      case D_MAKE: key.d_pressed = 1; break;
      case D_BREAK: key.d_pressed = 0; break;
    default:
      break;
    }
  }
}

keys_t* (get_key_press)(void) {
    return &key;
}

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
  uint16_t x1_box = x_box + 350;
  uint16_t y_box =  (get_YRes() / 6) - 15;
  uint16_t y1_box =  y_box + get_YRes() / 7;
  uint16_t y_box_exit =  3 * (get_YRes() / 6);
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
  
int (map1_init)() {
  vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MENU_BACKGROUND_COLOR);

  return 0;
}

void (map1_background)(void) {


  switch (no_interrupts/(60)) // each 5 secs changes color
  {
  case 0: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL0); break;
  case 1: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL1); break;
  case 2: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL2); break;
  case 3: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL3); break;
  case 4: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL4); break;
  case 5: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL5); break;
  case 6: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL6); break;
  case 7: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL7); break;
  case 8: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL8); break;
  case 9: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL9); break;
  case 10: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL10); break;
  case 11: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL11); break;
  case 12: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL12); break;
  default: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL13); break;
  }
  
}
