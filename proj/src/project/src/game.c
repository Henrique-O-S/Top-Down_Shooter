#include <lcom/lcf.h>

#include "game.h"

int finished = false;

int (game_loop)(){

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
                    if((no_interrupts * 60) % 60 == 0){ // the second 60 corresponds to the refresh rate
                      clear_screen();
                      draw_player();
                      draw_monsters();
                      //draw mouse here
                      no_interrupts = 0;
                    }
                 }
                 if(msg.m_notify.interrupts & get_irq(kbc_id)){
                    kbc_ih();
                    if(got_error_keyboard == 1){
                      finished = true;
                    }
                    //calls to key processing functions here, functions to be implemented in kbd
                    if(get_scancode()[0] == 0x81){ //ESC scancode, can probably done in key process in kbd
                      finished = true;
                    }

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

int (process_key)(uint8_t* scancode){
  switch (scancode[0])
  {
  case ESC_BREAK_CODE:
    finished = true;
    break;

  case A_MAKE:
    update_dir(-1, 0);
    break;

  case A_BREAK:
    update_dir(1, 0);
    break;

  case D_MAKE:
    update_dir(1, 0);
    break;

  case D_BREAK:
    update_dir(-1, 0);
    break;

  case W_MAKE:
    update_dir(-1, 1);
    break;
  
  case W_BREAK:
    update_dir(1, 1);
    break;

  case S_MAKE:
    update_dir(1, 1);
    break;

  case S_BREAK:
    update_dir(-1, 1);
    break;
  
  default:
    break;
  }

  return 0;
}
