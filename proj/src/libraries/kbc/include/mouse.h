#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

/**
 * @defgroup mouse mouse
 * @ingroup libraries
 *
 * @{
 */

#include <stdint.h>

#include "sprite.h"

int bytes_counter;
uint8_t packet_mouse[3];

/**
 * @brief Subscribes Mouse Interrupts
 * @param interrupt_bit Bit of Interrupt Vector that will be set when Mouse Interrupt is pending
 * @param interrupt_id Mouse Interrupt ID to specify the Mouse Interrupt in other calls
 * @return 0 if successful, 1 otherwise
 */
int (mouse_subscribe_int)(uint8_t interrupt_bit, int *interrupt_id);

/**
 * @brief Unsubscribes Mouse Interrupts
 * @param interrupt_id Mouse Interrupt ID to specify the Mouse Interrupt in other calls
 * @return 0 if successful, 1 otherwise
 */
int (mouse_unsubscribe_int)(int *interrupt_id);

/**
 * @brief Mouse interrupt handler
 */
void (mouse_ih)();

/**
 * @brief Number of mouse bytes received
 * @return  Number of bytes
 */
int (get_mouse_ih_counter)();

/**
 * @brief   Parse 3 bytes and returns it as a parsed, struct packet
 * @param   packet  Pointer to packet to store the information
 * @return  0 successful, 1 otherwise
 */
int (mouse_parse_packet)(struct packet *packet);

/**
 * @brief   Updates mouse position
 * @param   p  Pointer to packet to store the information.
 */
void (update_mouse)(struct packet *p);

/**
 * @brief   Gets mouse horizontal position
 * @return  Mouse horizontal position
 */
int16_t get_mouse_X(void);

/**
 * @brief   Gets mouse vertical position
 * @return  Mouse vertical position
 */
int16_t get_mouse_Y(void);

/**
 * @brief   Gets mouse angle relative to player position
 * @param   p  Pointer to player sprite
 * @return  Mouse angle relative to player position
 */
double get_mouse_angle(const sprite_t *p);

/**
 * @brief Converts 9-bit number to 16-bit with sign extension
 * @param sign_bit  Sign bit identifiying the signal of the number
 * @param byte      Least significant byte that will be extended
 * @return Extended 9-bit number
 */
int16_t (sign_extend_byte)(uint8_t sign_bit, uint8_t byte);

/**
 * @brief Issues command to mouse
 * @param cmd Command to be issued
 * @return 0 if successful, 1 otherwise
 */
int (mouse_issue_cmd)(uint8_t cmd);

/**
 * @brief Sets data report mode for mouse
 * @param   on  zero to disable data report, any other value to enable data report
 * @return  0 if successful, 1 otherwise
 */
int (mouse_set_data_report)(int on);

/**
 * @brief Reads byte from mouse
 * @param byte Pointer to variable where byte read from mouse will be stored
 * @return 0 if successful, 1 otherwise
 */
int (mouse_read_byte)(uint8_t *byte);

/**@}*/

#endif //MOUSE_H_INCLUDED
