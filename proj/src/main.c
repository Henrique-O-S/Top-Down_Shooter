// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include "librarys/graphics/include/graphics.h"
#include "librarys/keyboard/include/kbc_macros.h"
#include "librarys/keyboard/include/kbd.h"
#include "librarys/keyboard/include/kbc.h"

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

  uint16_t mode = DIRECT_800_600;
  uint16_t width = 100, height = 100, x = 100, y = 100;
  uint32_t color = 0xFFFFFF;
        
  if(vbe_get_mode_information(mode)) {
    printf("%s: failed to get info for graphic mode %x.\n", __func__, mode);

    if (vg_exit()) {
      printf("%s: vg_exit failed to exit to text mode.\n", __func__);
    }

    return 1;
  }

  map_vram();

  if (set_vbe_mode(mode)) {
    printf("%s: failed to set graphic mode %x.\n", __func__, mode);

    if (vg_exit()) {
      printf("%s: vg_exit failed to exit to text mode.\n", __func__);
    }

    if (free_memory_map()) {
      printf("%s: lm_free failed\n", __func__);
    }
    
    return 1;
  };

  uint16_t w = (x + width > get_XRes()) ? (get_XRes() - x) : (width);
  uint16_t h = (y + height > get_YRes()) ? (get_YRes() - y) : (height);

  if (x < get_XRes() && y < get_YRes()) {
    if (vg_draw_rectangle(x, y, w, h, color)) {

      if (vg_exit()) {
        printf("%s: vg_exit failed to exit to text mode.\n", __func__);
      }

      if (free_memory_map()) {
        printf("%s: lm_free failed\n", __func__);
      }

      return 1;
    }
  }


  /// loop stuff
  int r;
  int ipc_status;
  message msg;
  /// Keyboard interrupt handling
  uint8_t kbc_irq_bit = KBC_IRQ;
  int kbc_id = 0;
  int kbc_irq = BIT(kbc_irq_bit);

  if (subscribe_kbc_interrupt(kbc_irq_bit, &kbc_id)) {
      
    if (vg_exit()) {
      printf("%s: vg_exit failed to exit to text mode.\n", __func__);
    }
        
    if (free_memory_map()) {
      printf("%s: lm_free failed\n", __func__);
    }
        
    return 1;
  }

  /// cycle
  int good = 1;
  while (good) {
  /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with %d", r);
      continue;
    }

        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & kbc_irq) { /* subscribed interrupt */
                        kbc_ih();
                        
                        if (get_scancode(0) == ESC_BREAK_CODE) 
                          good = 0;
                    }
                    break;

                default:
                    break; /* no other notifications expected: do nothing */
            }
        } else { /* received standart message, not a notification */
            /* no standart message expected: do nothing */
        }
    }

    if (unsubscribe_interrupt(&kbc_id)) {
        if (vg_exit()) {
            printf("%s: vg_exit failed to exit to text mode.\n", __func__);
        }
        if (free_memory_map()) {
            printf("%s: lm_free failed\n", __func__);
        }
        return 1;
    };


  if (vg_exit()) {
      printf("%s: vg_exit failed to exit to text mode.\n", __func__);
      if (free_memory_map()) printf("%s: lm_free failed\n", __func__);
      return 1;
  }

  if (free_memory_map()) {
      printf("%s: lm_free failed\n", __func__);
      return 1;
  }


  return 0;
}
