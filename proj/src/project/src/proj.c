// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include "proj.h"

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

  uint16_t mode = INDEXED_1024_768;

  if(vbe_get_mode_information(mode)) return 1;

  if(map_vram()) return 1;

  if(set_vbe_mode(mode)) return 1;

  if(menu_init()) return 1;

  int ipc_status, r;
  message msg;
  int good = true;

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
                    //printf("got to timer\n");
                    timer_int_handler();
                    //clear_screen();
                    //menu switch case here
                    //menu update here
                 }
                 if(msg.m_notify.interrupts & get_irq(KBC_IRQ)){
                    //printf("got to keyboard\n");
                    kbc_ih();
                    if(got_error_keyboard == 1){
                      good = 0;
                    }
                    if(get_scancode()[0] == 0x81){ //ESC scancode, can probably done in key process in kbd
                      good = 0;
                    }

                 }
                 if(msg.m_notify.interrupts & get_irq(MOUSE_IRQ)){
                   //printf("got to mouse\n");
                    mouse_ih();
                    if(bytes_counter == 3){
                      struct packet pp;
                      mouse_parse_packet(&pp);
                      if(pp.lb){
                        good = 0;
                      }
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
    printf("%s: failed to unsubscribe drivers.\n", __func__);
    return 1;
  }

  if(vg_exit()) return 1;

  if (free_memory_map()) return 1;

  return 0;
}
