#ifndef KBC_H_INCLUDED
#define KBC_H_INCLUDED

/**
 * @defgroup kbc kbc
 * @ingroup libraries
 *
 * @{
 */

/**

 * @brief High-level function that reads the command byte of the KBC
 * @param cmd Pointer to variable where command byte read from KBC will be stored
 * @return 0 if operation was successful, 1 otherwise
 */
int (kbc_read_cmd)(uint8_t *cmd);

/**
 * @brief High-level function that changes the command byte of the KBC
 * @param cmd New value for command byte of KBC
 * @return 0 if operation was successful, 1 otherwise
 */
int (kbc_change_cmd)(uint8_t cmd);

/**
 * @brief High-level function that restores KBC to normal state
 * High-level function that restores KBC to normal state, because lcf_start
 * changes the command byte of KBC. If this function is not used, there is a
 * chance that the keyboard and keyboard interrupts remain disabled.
 * @return 0 if operation was successful, 1 otherwise
 */
int (kbc_restore_keyboard)();

/**
 * @brief Low-level function to issue a command to keyboard
 * @param cmd command to be issued
 * @return 0 if operation was successful, 1 otherwise
 */
int (kbc_issue_cmd)(uint8_t cmd);

/**
 * @brief Low-level function to issue an argument of a command
 * @param cmd argument to be issued
 * @return 0 if operation was successful, 1 otherwise
 */
int (kbc_issue_arg)(uint8_t arg);

/**
 * @brief Low-level function for reading byte from keyboard
 * Low-level function for reading byte from keyboard. Waits until output buffer
 * is full
 * @param value Pointer to variable where byte read from keyboard will be stored
 * @return 0 if operation was successful, 1 otherwise
 */
int (kbc_read_byte)(uint8_t *byte);

/**@}*/

#endif //KBC_H_INCLUDED
