#include <lcom/lcf.h>

#include "game.h"

#include "proj.h"

int (game_loop)(){

    printf("player\n");
    build_player(100, 100, bsp_player_idle, bsp_player_shooting); 
    printf("monster\n");
    build_monsters(500, 500, bsp_enemy_idle, bsp_enemy_attacking);
    printf("bullet\n");
    build_bullets(250, 250, bsp_bullet);
    printf("after\n");
    
    int ipc_status, r;
    message msg;
    int good = true;

    while(good) { /* You may want to use a different condition */
        printf("in loop\n");
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
                      if(no_interrupts % 3 == 0){ // the second 60 corresponds to the refresh rate
                        clear_screen();
                    
                        map1_init();

                        sprite_set_pos(sp_crosshair, get_mouse_X(), get_mouse_Y());
                        sprite_draw(sp_crosshair);

                        draw_double_buffer();
                        no_interrupts = 0;
                      }
                  }
                  if(msg.m_notify.interrupts & get_irq(kbc_id)){
                      kbc_ih();
                      if(!keyboard_get_done()) break;
                      if(keyboard_get_error()){
                        good = 0;
                        break;
                      }
                      //calls to key processing functions here, functions to be implemented in kbd
                      if(get_scancode()[0] == 0x81){ //ESC scancode, can probably done in key process in kbd
                        good = 0;
                        break;
                      }

                  }
                  if(msg.m_notify.interrupts & get_irq(mouse_id)){
                      mouse_ih();
                      if(get_mouse_ih_counter() >= 3){
                        struct packet pp;
                        mouse_parse_packet(&pp);
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
    printf("im out\n");
    return 0;
}
