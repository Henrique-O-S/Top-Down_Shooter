#ifndef INSTRUCTIONS_H_INCLUDED
#define INSTRUCTIONS_H_INCLUDED

#include "graphics.h"
#include "instructions.xpm"

static basic_sprite_t** get_instructions(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 1);
    ret[0] = basic_sprite_ctor((const char *const *)instructions_xpm, 0, 0);

    return ret;
}

#endif //INSTRUCTIONS_H_INCLUDED
