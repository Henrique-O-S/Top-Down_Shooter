// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include "proj.h"
#include "player.h"
#include "crosshair.h"

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

  if(vbe_get_mode_information(mode)) return 1;

  if(map_vram()) return 1;

  if(set_vbe_mode(mode)) return 1;

  /// MENU
  if(menu_init()) return 1;

  /// SPRITES
  bsp_player = get_player(); if(bsp_player == NULL) printf("failed to get player\n");
  sp_player = sprite_ctor(bsp_player);
  bsp_crosshair = get_crosshair(); if(bsp_crosshair == NULL) printf("failed to get player\n");
  sp_crosshair = sprite_ctor(bsp_crosshair);
  sprite_set_pos(sp_crosshair, 270, 100);
  sprite_draw(sp_crosshair);

  int ipc_status, r;
  message msg;
  int good = true;
  int x = 0, y = 0;


  while(good) { /* You may want to use a different condition */
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
                    if(no_interrupts % 3 == 0){ // the second 60 corresponds to the refresh rate
                      //swapBuffer();
                      clear_screen();
                      menu_init();
                    
                      //menu switch case here
                      //menu update here
                      sprite_set_pos(sp_crosshair, get_mouse_X(), get_mouse_Y());
                      sprite_draw(sp_crosshair);
                      draw_double_buffer();
                      no_interrupts = 1;
                    }
                 }
                 if(msg.m_notify.interrupts & get_irq(KBC_IRQ)){
  
                    kbc_ih();
                    if(got_error_keyboard == 1){
                      good = 0;
                    }
                    if(get_scancode()[0] == 0x81){ //ESC scancode, can probably done in key process in kbd
                      good = 0;
                    }

                 }
                 if(msg.m_notify.interrupts & get_irq(MOUSE_IRQ)){
                    mouse_ih();
                    if(get_mouse_ih_counter() >= 3){
                      x++;
                      y++;
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
