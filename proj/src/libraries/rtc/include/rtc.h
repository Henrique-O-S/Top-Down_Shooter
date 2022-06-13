#ifndef _RTC_H_
#define _RTC_H_

/** @defgroup rtc rtc
 * @ingroup libraries
 * @{
 *
 * Basic functions to operate via polling mode on the Real-Time Clock (RTC).
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "rtc_macros.h"

/**
 * @brief Subscribes RTC Interrupts
 * 
 * @return 0 if successful, 1 otherwise
 */
int (subscribe_rtc_interrupt)(uint8_t interrupt_bit, int *interrupt_id);

/**
 * @brief Enables/Disables interrupts on update.
 * 
 * @return  0 if successful, 1 otherwise
 */
int (rtc_set_updates)(int on);

/**
 * @brief Checks if RTC is updating
 *
 * @return 1 if RTC updating, 0 otherwise
 */
int isRTCUpdating();


/**
 * @brief Checks if the data read from RTC is in BCD
 *
 * @return 1 if BCD, 0 if binary
 */
int isBCD();


/**
 * @brief Converts a byte in BCD to binary
 *
 * @param bcd a pointer to the byte in BCD form
 *
 * @return the binary form of the given BCD byte
 */
uint8_t BCDtoBin(uint8_t* bcd);


/**
 * @brief Reads date from RTC
 *
 * @param year a pointer to a byte to store the year
 * @param month a pointer to a byte to store the month
 * @param day a pointer to a byte to store the day
 */
void getDate(uint8_t *year, uint8_t *month, uint8_t *day);


/**
 * @brief Reads time from RTC
 *
 * @param hour a pointer to a byte to store the hour
 * @param minutes a pointer to a byte to store the minutes
 * @param seconds a pointer to a byte to store the seconds
 */
void getHour(uint8_t *hours, uint8_t *minutes, uint8_t *seconds);

/**
 * @}
 */

#endif //RTC_H_INCLUDED
