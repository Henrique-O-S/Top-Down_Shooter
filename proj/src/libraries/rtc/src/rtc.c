#include <lcom/lcf.h>
#include <lcom/liblm.h>

#include "rtc.h"

int (subscribe_rtc_interrupt)(uint8_t interrupt_bit, int *interrupt_id) {
    if (interrupt_id == NULL) return 1;
    *interrupt_id = interrupt_bit;
    if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, interrupt_id)) return 1;
    return 0;
}

int (rtc_set_updates)(int on) {
    uint8_t data;
    if (on) {
        if ((util_sys_inb(REG_B, &data))) return 1;

        data |= REG_A_UIP;

        if ((sys_outb(REG_B, data))) return 1;

    }
    else {
        if ((util_sys_inb(REG_B, &data))) return 1;

        data &= ~REG_A_UIP;

        if ((sys_outb(REG_B, data))) return 1;
    }
    return 0;
}

int isRTCUpdating(){
  uint8_t reg_A;

  sys_outb(RTC_ADDR_REG, REG_A);
  util_sys_inb(RTC_DATA_REG, &reg_A);

  return (reg_A & REG_A_UIP);

}

int isBCD(){
  uint8_t reg_B;

  sys_outb(RTC_ADDR_REG, REG_B);
  util_sys_inb(RTC_DATA_REG, &reg_B);


  return (!(reg_B & REG_B_BIN));
}


uint8_t BCDtoBin(uint8_t* bcd){
  
  return (((*bcd) & 0xF0) / 16) * 10 + ((*bcd) & 0x0F);
}

void getDate(uint8_t *year, uint8_t *month, uint8_t *day){

  sys_outb(RTC_ADDR_REG, YEAR);
  util_sys_inb(RTC_DATA_REG, year);

  sys_outb(RTC_ADDR_REG, MONTH);
  util_sys_inb(RTC_DATA_REG, month);

  sys_outb(RTC_ADDR_REG, DAY);
  util_sys_inb(RTC_DATA_REG, day);

  if(isBCD()){
    (*year) = BCDtoBin(year);
    (*month) = BCDtoBin(month);
    (*day) = BCDtoBin(day);
  }
}

void getHour(uint8_t *hours, uint8_t *minutes, uint8_t *seconds){

  sys_outb(RTC_ADDR_REG, HOURS);
  util_sys_inb(RTC_DATA_REG, hours);

  sys_outb(RTC_ADDR_REG, MINUTES);
  util_sys_inb(RTC_DATA_REG, minutes);

  sys_outb(RTC_ADDR_REG, SECONDS);
  util_sys_inb(RTC_DATA_REG, seconds);

  if (isBCD()) {
    (*hours) = BCDtoBin(hours);
    (*minutes) = BCDtoBin(minutes);
    (*seconds) = BCDtoBin(seconds);
  }

}
