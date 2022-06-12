#include <lcom/lcf.h>

#include "aux_functions.h"
#include "mouse.h"

#include "menu.h"

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

void update_mouse_press(struct packet pp) {
  if(pp.lb) {
    key.lb_pressed = 1;
  }
  else key.lb_pressed = 0;
}

keys_t* (get_key_press)(void) {
    return &key;
}

int (menu_draw)(){
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
  uint16_t y_box =  (get_YRes() / 6);
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

int (process_mouse)(struct packet *p, int in_game){

  uint16_t selected = 0;

  if(!in_game){
    selected = mouse_on_top();
  }

  if(p->lb){
    return selected;
  }
  return 0;
}

void (set_menu)() {
  bsp_play = get_play();
  bsp_exit = get_exit();
  bsp_highscore = get_highscore();
  bsp_instructions = get_instructions();

  sp_play = sprite_ctor(bsp_play, 2);
  sp_exit = sprite_ctor(bsp_exit, 2);
  sp_highscore = sprite_ctor(bsp_highscore, 2);
  sp_instructions = sprite_ctor(bsp_instructions, 2);

  sprite_set_pos(sp_play, get_XRes()/2 - 60, get_YRes()*2/11);
  sprite_set_pos(sp_highscore, get_XRes()/2 - 130, get_YRes()*4/11);
  sprite_set_pos(sp_instructions, get_XRes()/2 - 180, get_YRes()*6/11);
  sprite_set_pos(sp_exit, get_XRes()/2 - 60, get_YRes()*8/11);
}

void (draw_menu)() {
  vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MENU_BACKGROUND_COLOR);

  uint16_t pos = mouse_on_top();
  switch (pos) {
    case 1: sprite_update_animation(sp_play, 0); break;
    case 2: sprite_update_animation(sp_highscore, 0);break;
    case 3: sprite_update_animation(sp_instructions, 0);break;
    case 4: sprite_update_animation(sp_exit, 0); break;
  default: break;
  }
  sprite_draw(sp_play);
  sprite_draw(sp_exit);
  sprite_draw(sp_highscore);
  sprite_draw(sp_instructions);
  switch (pos) {
    case 1: sprite_update_animation(sp_play, 0); break;
    case 2: sprite_update_animation(sp_highscore, 0);break;
    case 3: sprite_update_animation(sp_instructions, 0);break;
    case 4: sprite_update_animation(sp_exit, 0); break;
  default: break;
  }
}

uint16_t (mouse_on_top)(){
  uint16_t mouse_x = get_mouse_X(), mouse_y = get_mouse_Y();
  uint16_t x, y, w, h;
  x = sprite_get_X(sp_play); y = sprite_get_Y(sp_play); 
  w = sprite_get_w(sp_play); h = sprite_get_h(sp_play);
  if((x < mouse_x && mouse_x < (x + w)) && (y < mouse_y && mouse_y < (y + h)))
    return 1;
  
  x = sprite_get_X(sp_highscore); y = sprite_get_Y(sp_highscore); 
  w = sprite_get_w(sp_highscore); h = sprite_get_h(sp_highscore);
  if((x < mouse_x && mouse_x < (x + w)) && (y < mouse_y && mouse_y < (y + h)))
    return 2;

  x = sprite_get_X(sp_instructions); y = sprite_get_Y(sp_instructions); 
  w = sprite_get_w(sp_instructions); h = sprite_get_h(sp_instructions);
  if((x < mouse_x && mouse_x < (x + w)) && (y < mouse_y && mouse_y < (y + h)))
    return 3;

  x = sprite_get_X(sp_exit); y = sprite_get_Y(sp_exit); 
  w = sprite_get_w(sp_exit); h = sprite_get_h(sp_exit);
  if((x < mouse_x && mouse_x < (x + w)) && (y < mouse_y && mouse_y < (y + h)))
    return 4;

  return 0;
}
  
int (map1_init)() {
  vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MENU_BACKGROUND_COLOR);

  return 0;
}

void (map1_background)(void) {


  switch (no_interrupts/(60)) // each 5 secs changes color
  {
  case 0: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL01); break;
  case 1: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL02); break;
  case 2: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL03); break;
  case 3: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL04); break;
  case 4: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL05); break;
  case 5: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL06); break;
  case 6: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL07); break;
  case 7: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL08); break;
  case 8: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL09); break;
  case 9: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL10); break;
  case 10: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL11); break;
  case 11: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL12); break;
  case 12: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL13); break;
  case 13: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL14); break;
  case 14: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL15); break;
  case 15: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL16); break;
  case 16: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL17); break;
  case 17: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL18); break;
  case 18: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL19); break;
  case 19: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL20); break;
  case 20: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL21); break;
  case 21: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL22); break;
  case 22: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL23); break;
  case 23: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL24); break;
  case 24: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL25); break;
  case 25: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL26); break;
  case 26: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL27); break;
  case 27: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL28); break;
  case 28: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL29); break;
  case 29: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL30); break;
  case 30: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL31); break;
  case 31: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL32); break;
  case 32: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL33); break;
  case 33: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL34); break;
  case 34: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL35); break;
  case 35: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL36); break;
  case 36: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL37); break;
  case 37: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL38); break;
  case 38: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL39); break;
  case 39: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL40); break;
  case 40: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL41); break;
  case 41: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL42); break;
  case 42: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL43); break;
  case 43: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL44); break;
  case 44: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL45); break;
  case 45: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL46); break;
  case 46: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL47); break;
  case 47: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL48); break;
  case 48: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL49); break;
  case 49: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL50); break;
  case 50: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL51); break;
  case 51: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL52); break;
  case 52: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL53); break;
  case 53: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL54); break;
  case 54: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL55); break;
  case 55: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL56); break;
  case 56: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL57); break;
  case 57: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL58); break;
  case 58: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL59); break;
  case 59: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL60); break;
  default: vg_draw_rectangle(0, 0, get_XRes(), get_YRes(), MAP_COL60); break;
  }
  
}
