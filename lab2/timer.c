#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  
  if(timer < 0 || timer > 2){
    printf("Invalid timer!\n");
    return 1;
  }

  uint16_t val = TIMER_FREQ / freq;

  uint8_t lsb;
  util_get_LSB(val, &lsb);

  uint8_t msb;
  util_get_MSB(val, &msb);

  uint8_t readback;
  if(timer_get_conf(timer, readback)){
    printf("Failed while getting conf\n");
    return 1;
  }

  uint8_t timer_reg = TIMER_0 | timer;
  uint8_t timer_sel = (timer << 6);
  
  
  
  return 0;
}


int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {

  if(st == NULL) return 1;

  if(timer < 0 || timer > 2){
    printf("Invalid timer!\n");
    return 1;
  }

  uint8_t readback = 0 | TIMER_RB_SEL(timer) | TIMER_RB_COUNT_ | TIMER_RB_CMD;

  if(sys_outb(TIMER_CTRL, readback)) return 1;

  int port = TIMER_0 | timer;

  return util_sys_inb(port, st);
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  /* To be implemented by the students */
  

  uint8_t aux = 0x30;
  uint8_t init_mode;
  union timer_status_field_val conf;
  
  switch(field) {
    case tsf_all:
      conf.byte = st; /* Displays status byte */
      break;
    case tsf_initial:
      init_mode = (st & aux) >> 4;
      switch (init_mode)
      {
      case 0:
        conf.in_mode = INVAL_val;
        break;
      case 1:
        conf.in_mode = LSB_only;
        break;
      case 2:
        conf.in_mode = MSB_only;
        break;
      case 3:
        conf.in_mode = MSB_after_LSB;
        break;
      
      default:
        break;
      }
    
      break;

    aux = 0x0e;
    case tsf_mode:
      conf.count_mode = (st & aux) >> 1;
      if(conf.count_mode > 5) conf.count_mode -= 4;
      break;
    case tsf_base:
      break;
    
  }

  if(timer_print_config(timer, field, conf)) return 1;

  return 0;
  
}
