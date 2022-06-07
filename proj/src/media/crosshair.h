#ifndef CROSSHAIR_H_INCLUDED
#define CROSSHAIR_H_INCLUDED

#include "graphics.h"
#include "crosshair.xpm"

static basic_sprite_t* get_crosshair(void) {
    return basic_sprite_ctor((const char *const *)crosshair, 0, 0);
}

#endif //CROSSHAIR_H_INCLUDED
