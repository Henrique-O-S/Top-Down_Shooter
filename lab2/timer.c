#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"
#include "error.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  
  if(freq > TIMER_FREQ || freq < TIMER_MIN_FREQ) {
    printf("Frequency out of range\n");
    return FREQ_ERROR;
  }
  if(timer < 0 || timer > 2) {
    printf("Timer out of range\n");
    return TIMER_ERROR;
  }
  
  uint8_t lsb;
  uint8_t msb;
  uint16_t val = (uint16_t) (TIMER_FREQ / freq);
  if(util_get_LSB(val, &lsb)) return 1;
  if(util_get_MSB(val, &msb)) return 1;

  uint8_t control_word;
  if(timer_get_conf(timer, &control_word)){
    printf("Failed while getting conf\n");
    return 1;
  }

  /* Qual a funcionalidade disto?? */
  //timer_reg é semelhante a port em timer_get_conf, tem o port do timer
  //timer_sel é para selecionar o timer com control word que se passa ao sys_outb
  uint8_t timer_reg = TIMER_0 | timer;
  uint8_t timer_sel = (timer << 6);

  //Bits 0 a 3 ficam com valor que tinham anteriormente, 
  //bits 4 e 5 a 1 por causa de TIMER_LSB_MSB
  //bits 6 e 7 dependem de timer_sel
  control_word = (control_word & 0x0F) | TIMER_LSB_MSB | timer_sel;

  if(sys_outb(TIMER_CTRL, control_word) ||
    sys_outb(timer_reg, lsb) || sys_outb(timer_reg, msb)){
    printf("Failed in sys_out of timer_set_frequency\n");
    return 1;
  }
  
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

  if(sys_outb(TIMER_CTRL, readback)) {
    printf("Failed in sys_out of timer_get_conf\n");
    return 1;
  }

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
      init_mode = (st & aux) >> 0x04;
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
        return 1;
      }
      break;
    case tsf_mode:
      aux = 0x0e;
      conf.count_mode = (st & aux) >> 0x01;
      if(conf.count_mode > 0x05) conf.count_mode -= 0x04;
      break;
    case tsf_base:
      conf.bcd = (st & 0x01);
      break;
    
  }

  if(timer_print_config(timer, field, conf)) return 1;

  return 0;
  
}
