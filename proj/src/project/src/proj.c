// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include "proj.h"
#include "player0.h"
#include "enemy.h"
#include "bullet.h"
#include "map.h"
#include "crosshair.h"
#include "game.h"

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(proj_main_loop)(int argc, char* argv[]) {
  (void)argc; (void)argv;

  if (subscribe_all()) return 1;

  uint16_t mode = 0x118;

  if(vbe_get_mode_information(mode))  {
    unsubscribe_all();
    return 1;
  }

  if(map_vram()) {
    unsubscribe_all();
    return 1;
  }

  if(set_vbe_mode(mode)) {
    unsubscribe_all();
    free_memory_map();
    return 1;
  }

  /// SPRITES

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


  keys_t *keys = get_key_press();

  /// MENU
  if(menu_draw()) return 1;

  bsp_crosshair = get_crosshair(); if(bsp_crosshair == NULL) printf("failed to get crosshair\n");
  printf("got crosshair\n");
  sp_crosshair = sprite_ctor(bsp_crosshair, 1);
  printf("after crosshair\n");

  int ipc_status, r;
  message msg;
  int finished = false;
  //For the program to know if the game_loop should be entered
  int game_enter = false;

  while(!finished) { /* You may want to use a different condition */
     /* Get a request message. */
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
         continue;
     }
     if (is_ipc_notify(ipc_status)) { /* received notification */
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */       
                 if(msg.m_notify.interrupts & get_irq(TIMER0_IRQ)){
                    timer_int_handler();
                    if(get_no_interupts() % 3 == 0){ // the second 60 corresponds to the refresh rate
                      clear_screen();

                      if(game_enter){
                        if(game_display(keys)) finished = true;
                      }
                      else{
                        if(menu_draw()) finished = true;
                      }

                      sprite_set_pos(sp_crosshair, get_mouse_X(), get_mouse_Y());
                      sprite_draw(sp_crosshair);
                      
                      draw_double_buffer();

                      set_no_interupts(1);
                    }
                 }
                 if(msg.m_notify.interrupts & get_irq(KBC_IRQ)){
                    kbc_ih();
                    if(got_error_keyboard == 1){
                      finished = true;
                    }
                    if(get_scancode()[0] == 0x81){ //ESC scancode, can probably done in key process in kbd
                      if(game_enter) {
                        game_dispawn_everyting();
                        game_enter = false;
                      }
                      else finished = true;
                    }

                    if(game_enter){
                      update_player_pos();
                    }
                 }
                 if(msg.m_notify.interrupts & get_irq(MOUSE_IRQ)){
                    mouse_ih();
                    if(get_mouse_ih_counter() >= 3){
                      struct packet pp;
                      mouse_parse_packet(&pp);
                      update_mouse_press(pp);
                      int option = process_mouse(&pp, game_enter);

                      if(option == 1){
                        game_enter = true;
                      }

                      else if(option == 2){
                        finished = true;
                      }
                      update_mouse(&pp);
                    
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

  if (unsubscribe_all()){
    vg_exit();
    free_memory_map();
    printf("%s: failed to unsubscribe drivers.\n", __func__);
    return 1;
  }

  if(vg_exit()) {
    free_memory_map();
    return 1;
  }

  if (free_memory_map()) return 1;

  return 0;
}
