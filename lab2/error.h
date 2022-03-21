#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

/** @brief Error Codes */
enum errors {
    SUCCESS = 0,        /** @brief Sucessful */
    FREQ_ERROR,         /** @brief Frequency Out of Range */
    TIMER_ERROR,        /** @brief Timer Out of Range */
    NULL_PTR,           /** @brief Null Pointer */
};

#endif /* ERROR_H_INCLUDED */
