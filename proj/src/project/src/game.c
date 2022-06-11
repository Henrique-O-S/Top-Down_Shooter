#include <lcom/lcf.h>

#include "game.h"
#include "player0.h"
#include "enemy.h"
#include "bullet.h"
#include "map.h"
#include "proj.h"

int finished = false;

int (game_loop)(){

  /// SPRITES

  //bsp_player = get_player(); if(bsp_player == NULL) printf("failed to get player\n");
  //sp_player = sprite_ctor(bsp_player, 20);

  bsp_player_idle = get_player_idle();
  bsp_player_shooting = get_player_shooting();

  bsp_enemy_idle = get_enemy_idle();
  bsp_enemy_attacking = get_enemy_attacking();

  bsp_bullet = get_bullet();

  bsp_map = get_map();
  sp_map = sprite_ctor(bsp_map, 1);
  sprite_set_pos(sp_map, 0, 75);

  build_map();
  build_player(500, 500, bsp_player_idle, bsp_player_shooting); 
  build_monsters(0, 0, bsp_enemy_idle, bsp_enemy_attacking);
  build_bullets(170, 80, bsp_bullet);

  //bsp_enemy = get_enemy(); if(bsp_enemy == NULL) printf("failed to get player\n");
  //sp_enemy = sprite_ctor(bsp_enemy, 15);
  printf("got enemy\n");

  build_player(100, 100, bsp_player_idle, bsp_player_shooting); 
  build_monsters(500, 500, bsp_enemy_idle, bsp_enemy_attacking);
  build_bullets(250, 250, bsp_bullet);

  keys_t *keys = get_key_press();
  spawn_monsters();

  //sprite_set_pos(sp_player, 450, 450);
  //sprite_set_pos(sp_enemy, 150, 150);
  
  int ipc_status, r;
  message msg;

  while(!finished) { /* You may want to use a different condition */
     /* Get a request message. */
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
         continue;
     }
     if (is_ipc_notify(ipc_status)) { /* received notification */
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */       
                  if(msg.m_notify.interrupts & get_irq(timer_id)){
                      timer_int_handler();
                      if(get_no_interupts() % 3 == 0){ // the second 60 corresponds to the refresh rate
                        clear_screen();
                    
                        map1_background();
                        //sprite_draw(sp_map);
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
                        if(!get_player_status()) finished = 0;
                        set_no_interupts(0);
                      }
                  }
                 if(msg.m_notify.interrupts & get_irq(kbc_id)){
                    kbc_ih();
                    if(keyboard_get_error() == 1){
                      finished = true;
                    }
                    //calls to key processing functions here, functions to be implemented in kbd
                    if(get_scancode()[0] == ESC_BREAK_CODE){
                      finished = true;
                    }
                    update_player_pos();
                 }
                 if(msg.m_notify.interrupts & get_irq(mouse_id)){
                    mouse_ih();
                    struct packet pp;
                    mouse_parse_packet(&pp);
                    if(pp.lb){
                      finished = true;
                    }
                    //mouse function calls here
                 }
                 break;
             default:
                 break; /* no other notifications expected: do nothing */ 
         }
     } else { /* received a standard message, not a notification */
         /* no standard messages expected: do nothing */
     }
  }
    return 0;
}
