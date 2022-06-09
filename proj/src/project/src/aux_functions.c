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
