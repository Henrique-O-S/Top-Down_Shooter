#include <lcom/lcf.h>

#include "game.h"
#include "proj.h"

int finished = false;

int(game_display)(keys_t *keys) {
  map1_background();
  // sprite_draw(sp_map);
  draw_map();
  spawn_monsters();
  update_monster_pos();

  set_player_pos(keys);

  draw_player();
  draw_monsters();

  update_bullet_pos();
  draw_bullets();

  sprite_set_pos(sp_crosshair, get_mouse_X(), get_mouse_Y());
  sprite_draw(sp_crosshair);

  draw_double_buffer();

  if (!get_player_status()) return 1;

  return 0;
}
