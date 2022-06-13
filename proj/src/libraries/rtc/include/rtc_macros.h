#ifndef _RTC_MACROS_H_
#define _RTC_MACROS_H_

/** @defgroup rtc_macros.h rtc_macros.h
 * @ingroup libraries
 * @{
 *
 * Basic functions to operate via polling mode on the Real-Time Clock (RTC).
 */

#include <lcom/lcf.h>

// RTC IRQ Line

#define RTC_IRQ   8

/* Access to RTC */

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71

/* REGISTER */
#define REG_A 10
#define REG_B 11

/* INPUTS */
#define DAY   7
#define MONTH 8
#define YEAR  9
#define MILLENIUM 2000

#define HOURS   4
#define MINUTES 2
#define SECONDS 0

/* FLAGS */
#define REG_A_UIP BIT(7)
#define REG_B_BIN BIT(2)

/**
 * @}
 */

#endif //RTC_MACROS_H_INCLUDED
