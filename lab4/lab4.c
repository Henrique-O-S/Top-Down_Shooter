#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "mouse.h"
#include "mouse_macros.h"

extern int bytes_counter;
extern uint8_t packet_mouse[3];

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
    int r, ipc_status;
    message msg;
    uint8_t mouse_irq_bit = 2;
    int mouse_id = 2;
    
    if(mouse_subscribe_int(mouse_irq_bit, &mouse_id)) return 1;
    
    mouse_enable_data_reporting();
    
    while(cnt > 0){
      if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
        printf("driver_receive failed with %d", r);
        continue;
      }
        
      if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: /* hardware interrupt notification */
            if (msg.m_notify.interrupts & BIT(mouse_irq_bit)) {
              mouse_ih();

              if(bytes_counter == 3){
                cnt--;
                struct packet p = mouse_parse_packet(packet_mouse);
                mouse_print_packet(&p);
              }
            }
            break;
            
          default:
            break; /* no other notifications expected: do nothing */
              /* no standart message expected: do nothing */
        }
      }
    }

    

    if(mouse_unsubscribe_int(&mouse_id)) return 1;
    
    return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}
