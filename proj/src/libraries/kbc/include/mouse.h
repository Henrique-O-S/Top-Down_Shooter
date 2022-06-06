#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

/**
 * @defgroup mouse mouse
 * @ingroup libraries
 *
 * @{
 */

#include <stdint.h>

int bytes_counter;
uint8_t packet_mouse[3];

int (mouse_subscribe_int)(uint8_t interrupt_bit, int *interrupt_id);

int (mouse_unsubscribe_int)(int *interrupt_id);

void (mouse_ih)();

int (mouse_parse_packet)(struct packet *packet);

int16_t (sign_extend_byte)(uint8_t sign_bit, uint8_t byte);

/**@}*/

#endif //MOUSE_H_INCLUDED
