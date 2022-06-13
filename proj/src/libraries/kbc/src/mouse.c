#include <lcom/lcf.h>

#include <math.h>
#include "mouse.h"
#include "mouse_macros.h"
#include "kbc_macros.h"
#include "kbc.h"
#include "graphics.h"
#include "utils.h"
#include "sprite.h"

int (mouse_subscribe_int)(uint8_t interrupt_bit, int *interrupt_id){
    if (interrupt_id == NULL) return 1;
    *interrupt_id = interrupt_bit;
    if(sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, interrupt_id)) return 1;
    return 0;
}

int (mouse_unsubscribe_int)(int *interrupt_id){
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

int (get_mouse_ih_counter)() {
    return bytes_counter;
}

static int16_t mouse_x = 0, mouse_y = 0;
void (update_mouse)(struct packet *p) {
    bytes_counter = 0;
    mouse_x = max(0, mouse_x + p->delta_x);
    mouse_x = min(mouse_x, (int16_t)get_XRes() - 1);

    mouse_y = max(0, mouse_y - p->delta_y);
    mouse_y = min(mouse_y, (int16_t)get_YRes() - 1);

}
int16_t (get_mouse_X)(void) { 
    return mouse_x; 
}
int16_t (get_mouse_Y)(void) { 
    return mouse_y;
}

double (get_mouse_angle)(const sprite_t *p) {
    return atan2(sprite_get_Y(p) - mouse_y, mouse_x - sprite_get_X(p));
}

int (mouse_parse_packet)(struct packet *p){
    p->bytes[0] = packet_mouse[0];
    p->bytes[1] = packet_mouse[1];
    p->bytes[2] = packet_mouse[2];
    p->rb = p->bytes[0] & RIGHT_BUTTON;
    p->mb = p->bytes[0] & MIDDLE_BUTTON;
    p->lb = p->bytes[0] & LEFT_BUTTON;
    p->delta_x = sign_extend_byte((p->bytes[0] & MSB_X_DELTA) != 0, p->bytes[1]);
    p->delta_y = sign_extend_byte((p->bytes[0] & MSB_Y_DELTA) != 0, p->bytes[2]);
    p->x_ov = p->bytes[0] & X_OVERFLOW;
    p->y_ov = p->bytes[0] & Y_OVERFLOW;

    return 0;
}

int (mouse_set_data_report)(int on){
    if(on) 
        return mouse_issue_cmd(ENABLE_DATA_REP);
    else 
        return mouse_issue_cmd(DIS_DATA_REP);
}

int (mouse_issue_cmd)(uint8_t cmd) {
    int ret;
    uint8_t ack = 0;
    for (unsigned int i = 0; i < KBC_NUM_TRIES; i++) {
        if ((ret = kbc_issue_cmd(MOUSE_WRITE_B))) return ret;
        if ((ret = kbc_issue_arg(cmd))) return ret;
        if ((ret = mouse_read_byte(&ack))) return ret;

        if (ack == ACK_OK) return 0;
        if (ack == ACK_ERROR) return 1;
        tickdelay(micros_to_ticks(DELAY));
    }
    return 0;
}

int16_t (sign_extend_byte)(uint8_t sign_bit, uint8_t byte){
  return (int16_t)(((0xFF * sign_bit)<<8) | byte);
}

int (mouse_read_byte)(uint8_t *byte) {
    int ret = 0;
    uint8_t stat;
    for(int i = 0; i < KBC_NUM_TRIES; ++i){
        if((ret = util_sys_inb(STATUS_REG, &stat))) return ret;
        if((stat & OUT_BUF_FUL) && (stat & AUX_MOUSE)) {
            if(stat & (PARITY_ERROR | TIME_OUT_REC)) return 1;
            if((ret = util_sys_inb(OUTPUT_BUF, byte))) return ret;
            else return 0;
        }
        tickdelay(micros_to_ticks(DELAY));
    }
    return 1;
}
