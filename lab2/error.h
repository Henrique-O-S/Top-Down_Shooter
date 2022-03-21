#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

/** @brief Error Codes */
enum errors {
    SUCCESS = 0,        /** @brief Sucessful */
    NULL_PTR,           /** @brief Null Pointer Error */
    FREQ_ERROR,         /** @brief Frequency Out of Range */
    TIMER_ERROR,        /** @brief Timer Out of Range */
};

#endif //ERROR_H_INCLUDED