#include <lcom/lcf.h>

#include "game.h"
#include "proj.h"


int finished = false;

static int player_kills;
static int end_game_time;

void(game_place_everything)() {
  set_hud();
  start_highscore();
}

int(game_display)(keys_t *keys) {
  tick_cooldown();
  map1_background();
  // sprite_draw(sp_map);
  draw_map();
  if(get_no_interupts()/60 <= 60) spawn_monsters();
  update_monster_pos();

  set_player_pos(keys);

  draw_player();
  draw_monsters();

  update_bullet_pos();
  draw_bullets();

  draw_hud(player_get_health(), player_get_kills(), 60-get_no_interupts()/60);

  sprite_set_pos(sp_crosshair, get_mouse_X(), get_mouse_Y());
  sprite_draw(sp_crosshair);

  draw_double_buffer();

  if (!get_player_status()) return 1;
  if (!get_game_status() && get_no_interupts()/60 > 60) return 1;

  return 0;
}

void(game_dispawn_everyting()) {
  player_kills = player_get_kills();
  end_game_time = get_no_interupts()/60;
  dispawn_monsters();
  dispawn_player();
  dispawn_bullets();
  set_highscore(player_kills);
}

void(display_score)() {
  draw_end_game(player_kills, end_game_time);
}
