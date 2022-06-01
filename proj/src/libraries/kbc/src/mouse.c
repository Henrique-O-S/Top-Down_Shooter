#include <lcom/lcf.h>

#include "mouse.h"
#include "mouse_macros.h"
#include "i8042.h"

int mouse_subscribe_int(uint8_t interrupt_bit, int *interrupt_id){
    if (interrupt_id == NULL) return 1;
    *interrupt_id = interrupt_bit;
    if(sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, interrupt_id)) return 1;
    return 0;
}

int mouse_unsubscribe_int(int *interrupt_id){
    if (interrupt_id == NULL) return 1;
    if(sys_irqrmpolicy(interrupt_id)) return 1;
    return 0;
}

int bytes_counter = 0;
uint8_t packet_mouse[3];

void (mouse_ih)(void) {
    uint8_t status = 0;

    if(bytes_counter >= 3){
        bytes_counter = 0;
    }

    if(util_sys_inb(STATUS_REG, &status)) {
        return;
    }

    if(status & (PARITY_ERROR & TIME_OUT_REC)){
        return;
    }

    if (((status & AUX_MOUSE) == 0) || ((status & OUT_BUF_FUL) == 0)) {
        return;
    }

    uint8_t byte = 0;

    if(util_sys_inb(OUTPUT_BUF, &byte)){
        return;
    }

    if((byte & FIRST_BYTE_ID) || bytes_counter){
        packet_mouse[bytes_counter++] = byte;
    }
}

struct packet (mouse_parse_packet)(const uint8_t *packet_bytes){
  struct packet p;
    p.bytes[0] = packet_bytes[0];
    p.bytes[1] = packet_bytes[1];
    p.bytes[2] = packet_bytes[2];
    p.rb = p.bytes[0] & RIGHT_BUTTON;
    p.mb = p.bytes[0] & MIDDLE_BUTTON;
    p.lb = p.bytes[0] & LEFT_BUTTON;
    p.delta_x = sign_extend_byte((packet_bytes[0] & MSB_X_DELTA) != 0, p.bytes[1]);
    p.delta_y = sign_extend_byte((packet_bytes[0] & MSB_Y_DELTA) != 0, p.bytes[2]);
    p.x_ov = p.bytes[0] & X_OVERFLOW;
    p.y_ov = p.bytes[0] & Y_OVERFLOW;
    return p;
}

int16_t (sign_extend_byte)(uint8_t sign_bit, uint8_t byte){
  return (int16_t)(((0xFF * sign_bit)<<8) | byte);
}
