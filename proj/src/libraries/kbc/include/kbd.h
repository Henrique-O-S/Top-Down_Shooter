#ifndef KBD_H_INCLUDED
#define KBD_H_INCLUDED

/**
 * @defgroup kbd kbd
 * @ingroup libraries
 *
 * @{
 */

#include <lcom/lcf.h>

/**
 * @brief Subscribes Keyboard Interrupts
 * @param interrupt_bit Bit of Interrupt Vector that will be set when Keyboard Interrupt is pending
 * @param interrupt_id Keyboard Interrupt ID to specify the Keyboard Interrupt in other calls
 * @return 0 if successful, 1 otherwise
 */
int (subscribe_kbc_interrupt)(uint8_t interrupt_bit, int *interrupt_id);

uint8_t scancode[2];
int done;
int sz;
int got_error_keyboard;

/**
 * @brief KBC interrupt handler
 */
void (kbc_ih)(void);

/**
 * @brief Poll keyboard for scancodes
 * @param   bytes   Array to put read bytes
 * @param   size    Number of ready bytes
 * @return  0 if successful, 1 otherwise
 */
int (keyboard_poll)(uint8_t bytes[], uint8_t *size);

/**
 * @brief Get scancode read from keyboard
 * @return  Pointer to begin of scancode array
 */
const uint8_t* (get_scancode)();

/**
 * @brief Get state of reading (done)
 * @return  1 if done, 0 otherwise
 */
int keyboard_get_done(void);

/**
 * @brief Get size of read scancode
 * @return Size of scancode
 */
int keyboard_get_size(void);

/**
 * @brief Checks if keyboard interrupt handler had errors while running
 * @return  1 if had any errors, 0 otherwise
 */
int keyboard_get_error(void);

#endif //KBD_H_INCLUDED
