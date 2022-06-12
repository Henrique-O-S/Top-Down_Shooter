#include <lcom/lcf.h>

#include "aux_functions.h"
#include "mouse.h"
#include "numbers.h"
#include "menu.h"
#include "hud.h"


static keys_t key;

text_t*(text_ctor)(int16_t x, int16_t y) {
  text_t *t = malloc(sizeof(text_t));
  t->numbers = NULL;
  t->numbers = sprite_ctor(get_number(), 10);
  sprite_set_pos(t->numbers,x, y);
  t->x = x;
  t->y = y;
  t->pos2 = 0;
  t->pos1 = 0;
  t->pos0 = 0;

  return t;
}

void (text_set_number)(text_t *t, int16_t pos2, int16_t pos1, int16_t pos0) {
  t->pos2 = pos2;
  t->pos1 = pos1;
  t->pos0 = pos0;
}

date_t*(date_ctor)(int16_t x, int16_t y) {
  date_t *t = malloc(sizeof(date_t));
  t->numbers = NULL;
  t->numbers = sprite_ctor(get_number(), 10);
  t->slash = sprite_ctor(get_slash(), 1);
  sprite_set_pos(t->numbers,x, y);
  t->x = x;
  t->y = y;
  t->score = 0;
  t->pos9 = 0;
  t->pos8 = 0;
  t->pos7 = 0;
  t->pos6 = 0;
  t->pos5 = 0;
  t->pos4 = 0;
  t->pos3 = 0;
  t->pos2 = 0;
  t->pos1 = 0;
  t->pos0 = 0;
  t->s_pos2 = 0;
  t->s_pos1 = 0;
  t->s_pos0 = 0;
  return t;
}

void (date_set_number)(date_t *t,int16_t pos2,  int16_t pos1, int16_t pos0) {
  t->s_pos2 = pos2;
  t->s_pos1 = pos1;
  t->s_pos0 = pos0;
}

void (date_draw)(date_t *t) {
  sprite_set_pos(t->numbers, t->x , t->y + 50);
  sprite_choose_animation(t->numbers, t->pos9);
  sprite_draw(t->numbers);

  sprite_set_pos(t->numbers, t->x + 20 , t->y + 50);
  sprite_choose_animation(t->numbers, t->pos8);
  sprite_draw(t->numbers);

  sprite_set_pos(t->slash, t->x + 40, t->y + 50);
  sprite_draw(t->slash);

  sprite_set_pos(t->numbers, t->x + 60, t->y + 50);
  sprite_choose_animation(t->numbers, t->pos6);
  sprite_draw(t->numbers);

  sprite_set_pos(t->numbers, t->x + 80 , t->y + 50);
  sprite_choose_animation(t->numbers, t->pos5);
  sprite_draw(t->numbers);

  sprite_set_pos(t->slash, t->x + 100, t->y + 50);
  sprite_draw(t->slash);

  sprite_set_pos(t->numbers, t->x + 120, t->y + 50);
  sprite_choose_animation(t->numbers, t->pos3);
  sprite_draw(t->numbers);

  sprite_set_pos(t->numbers, t->x + 140 , t->y + 50);
  sprite_choose_animation(t->numbers, t->pos2);
  sprite_draw(t->numbers);

  sprite_set_pos(t->numbers, t->x + 160, t->y + 50);
  sprite_choose_animation(t->numbers, t->pos1);
  sprite_draw(t->numbers);

  sprite_set_pos(t->numbers, t->x + 180 , t->y + 50);
  sprite_choose_animation(t->numbers, t->pos0);
  sprite_draw(t->numbers);

  if(!t->s_pos2) {
      if(!t->s_pos1) {
        sprite_set_pos(t->numbers, t->x, t->y);
        sprite_choose_animation(t->numbers, t->s_pos0);
        sprite_draw(t->numbers);
      }
      else {
        sprite_set_pos(t->numbers, t->x , t->y);
        sprite_choose_animation(t->numbers, t->s_pos1);
        sprite_draw(t->numbers);
    
        sprite_set_pos(t->numbers, t->x + 20, t->y);
        sprite_choose_animation(t->numbers, t->s_pos0);
        sprite_draw(t->numbers);
      }
    }
    else {

        sprite_set_pos(t->numbers, t->x , t->y);
        sprite_choose_animation(t->numbers, t->s_pos2);
        sprite_draw(t->numbers);

        sprite_set_pos(t->numbers, t->x + 20 , t->y);
        sprite_choose_animation(t->numbers, t->s_pos1);
        sprite_draw(t->numbers);
    
        sprite_set_pos(t->numbers, t->x + 40, t->y);
        sprite_choose_animation(t->numbers, t->s_pos0);
        sprite_draw(t->numbers);
    }

    sprite_set_pos(t->numbers, t->x, t->y);
}

void (text_draw)(text_t *t) {
    int x = sprite_get_X(t->numbers);
    int y = sprite_get_Y(t->numbers);


    if(!t->pos2) {
      if(!t->pos1) {
        sprite_set_pos(t->numbers, t->x, t->y);
        sprite_choose_animation(t->numbers, t->pos0);
        sprite_draw(t->numbers);
      }
      else {
        sprite_set_pos(t->numbers, t->x , t->y);
        sprite_choose_animation(t->numbers, t->pos1);
        sprite_draw(t->numbers);
    
        sprite_set_pos(t->numbers, t->x + 20, t->y);
        sprite_choose_animation(t->numbers, t->pos0);
        sprite_draw(t->numbers);
      }
    }
    else {

        sprite_set_pos(t->numbers, t->x , t->y);
        sprite_choose_animation(t->numbers, t->pos2);
        sprite_draw(t->numbers);

        sprite_set_pos(t->numbers, t->x + 20 , t->y);
        sprite_choose_animation(t->numbers, t->pos1);
        sprite_draw(t->numbers);
    
        sprite_set_pos(t->numbers, t->x + 40, t->y);
        sprite_choose_animation(t->numbers, t->pos0);
        sprite_draw(t->numbers);
    }

    sprite_set_pos(t->numbers, x, y);
}

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
  
void (set_hud)() {
  bsp_hud = get_hud();
  sp_hud = sprite_ctor(bsp_hud, 1);
  bsp_numbers = get_number();
  sp_numbers = sprite_ctor(bsp_numbers, 10);
  p_health = text_ctor(290, 20);
  p_kills = text_ctor(650, 20);
  game_timer = text_ctor(460, 20);
  end_p_kills = text_ctor(770, 335);;
  end_game_timer = text_ctor(770, 425);;
}

void(draw_hud)(int h, int k, int t) {
  int pos0h, pos1h, pos2h;
  int pos0k, pos1k, pos2k;
  int pos0t, pos1t, pos2t;
  if(t < 0) t = 0;
  pos0h = h % 10;  h /=10;
  if(!h) pos1h = 0;
  else  pos1h = h % 10;  h /=10;
  if(!h) pos2h = 0;
  else  pos2h = h % 10;  h /=10;

  pos0k = k % 10;  k /=10;
  if(!k) pos1k = 0;
  else  pos1k = k % 10;  k /=10;
  if(!k) pos2k = 0;
  else  pos2k = k % 10;  k /=10;

  pos0t = t % 10;  t /=10;
  if(!t) pos1t = 0;
  else  pos1t = t % 10;  t /=10;
  if(!t) pos2t = 0;
  else  pos2t = t % 10;  t /=10;
  

  sprite_draw(sp_hud);
  text_set_number(p_health, pos2h, pos1h, pos0h);
  text_set_number(p_kills, pos2k, pos1k, pos0k);
  text_set_number(game_timer, pos2t, pos1t, pos0t);
  text_draw(p_health);
  text_draw(p_kills);
  text_draw(game_timer);
}

void (start_highscore)() {
  bsp_slash = get_slash();
  sp_slash = sprite_ctor(bsp_slash, 1);
  date1 = date_ctor(620, 270);
  date2 = date_ctor(620, 385);
  date3 = date_ctor(620, 500);

}

void (set_highscore)(int k){
  int l = k;
  int16_t pos2k, pos1k, pos0k;
  pos0k = k % 10;  k /=10;
  if(!k) pos1k = 0;
  else  pos1k = k % 10;  k /=10;
  if(!k) pos2k = 0;
  else  pos2k = k % 10;  k /=10;

  uint8_t y, m, d;
  getDate(&y, &m, &d);
  int pos = 0;
  if(date1->score <= date2->score && date1->score <= date3->score ) pos = 1;
  else if(date2->score <= date1->score && date2->score <= date3->score ) pos = 2;
  else pos = 3;

  switch (pos)
  {
  case 1:
    date1->score = l;
    date1->pos8 = d%10;
    d /= 10;
    date1->pos9 = d%10;
    date1->pos5 = m%10;
    m /= 10;
    date1->pos6 = m%10;
    date1->pos0 = y%10;
    y /= 10;
    date1->pos1 = y%10;
    date1->pos2 = 0;
    date1->pos3 = 2;
    date_set_number(date1, pos2k, pos1k, pos0k);
    break;
  case 2:
    date2->score = l;
    date2->pos8 = d%10;
    d /= 10;
    date2->pos9 = d%10;
    date2->pos5 = m%10;
    m /= 10;
    date2->pos6 = m%10;
    date2->pos0 = y%10;
    y /= 10;
    date2->pos1 = y%10;
    date2->pos2 = 0;
    date2->pos3 = 2;
    date_set_number(date2, pos2k, pos1k, pos0k);
    break;
  case 3:
    date3->score = l;
    date3->pos8 = d%10;
    d /= 10;
    date3->pos9 = d%10;
    date3->pos5 = m%10;
    m /= 10;
    date3->pos6 = m%10;
    date3->pos0 = y%10;
    y /= 10;
    date3->pos1 = y%10;
    date3->pos2 = 0;
    date3->pos3 = 2;
    date_set_number(date3, pos2k, pos1k, pos0k);
    break;
  
  default:
    break;
  }

}

void (draw_highscore)(){
  date_draw(date1);
  date_draw(date2);
  date_draw(date3);

}

void(draw_end_game)(int k, int t) {

  int pos0k, pos1k, pos2k;
  int pos0t, pos1t, pos2t;

  pos0k = k % 10;  k /=10;
  if(!k) pos1k = 0;
  else  pos1k = k % 10;  k /=10;
  if(!k) pos2k = 0;
  else  pos2k = k % 10;  k /=10;

  pos0t = t % 10;  t /=10;
  if(!t) pos1t = 0;
  else  pos1t = t % 10;  t /=10;
  if(!t) pos2t = 0;
  else  pos2t = t % 10;  t /=10;
  

  text_set_number(end_p_kills, pos2k, pos1k, pos0k);
  text_set_number(end_game_timer, pos2t, pos1t, pos0t);
  text_draw(end_p_kills);
  text_draw(end_game_timer);
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
