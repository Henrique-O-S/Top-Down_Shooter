#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "kbd.h"
#include "kbc.h"
#include "i8042.h"
#include "timer.h"

extern uint8_t scancode[2];
extern uint8_t keycode;
extern uint32_t sys_inb_counter;
extern uint32_t no_interrupts;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  int r, ipc_status;
  message msg;
  uint8_t kbc_irq_bit = 1;
  int kbc_id = 0;
  int kbc_irq = BIT(kbc_irq_bit);

  if(kbd_subscribe_int(kbc_irq_bit,&kbc_id)) return 1;



  int processing = 1;
  while(processing) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with %d", r);
            continue;
    }
        
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */
          if (msg.m_notify.interrupts & kbc_irq) { //KBD int?
            kbc_ih();

            if (keycode == ESC_BREAK_CODE) { 
              processing = 0;
            }
          }
          break;
          
        default:
          break; /* no other notifications expected: do nothing */
            /* no standart message expected: do nothing */
      }
    }
  }
  
  
  if(kbd_unsubscribe_int(&kbc_id)) return 1;

  if(kbd_print_no_sysinb(sys_inb_counter)) return 1;

  return 0;
}

int(kbd_test_poll)(){
  
  while(!(scancode_sz == 1 && scancode[0] == ESC_BREAK_CODE)){
    
    if(scancode[scancode_sz - 1] & BREAK_CODE_BIT){
            kbd_print_scancode(false, scancode_sz, scancode);
    }
    else return 1;
    
  }
  
  if(kbc_restore_keyboard()) return 1;

  if(kbd_print_no_sysinb(sys_inb_counter)) return 1;

  return 1;
  
}

int(kbd_test_timed_scan)(uint8_t n) {
  int r, ipc_status;
  message msg;
  uint8_t kbc_irq_bit = 1;  
  int kbc_id = 1;
  int kbc_irq = BIT(kbc_irq_bit);

  if(kbd_subscribe_int(kbc_irq_bit, &kbc_id)) return 1;

  uint8_t timer_id = 0;
  int seconds_passed = 0;
  uint8_t timer_irq = BIT(timer_id);

  if(timer_subscribe_int(&timer_id)) return 1;

  int processing = 1;

  while(processing) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with %d", r);
            continue;
    }
        
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */
          if(msg.m_notify.interrupts & timer_irq){
            timer_int_handler();

            if(no_interrupts % 60 == 0){
              seconds_passed++;
            }
          }

          if (msg.m_notify.interrupts & kbc_irq) { //KBD int?
            kbc_ih();

            seconds_passed = 0;
            no_interrupts = 0;

            if (keycode == ESC_BREAK_CODE) { 
              processing = 0;
            }
          }
          break;

        default:
          break; /* no other notifications expected: do nothing */
            /* no standart message expected: do nothing */
      }
    }
  }
  
  if(kbd_unsubscribe_int(&kbc_id)) return 1;

  if(timer_unsubscribe_int()) return 1;

  if(kbd_print_no_sysinb(sys_inb_counter)) return 1;

  return 0;
}
