#ifndef WALLS_H_INCLUDED
#define WALLS_H_INCLUDED

#include "graphics.h"
#include "walls.xpm"

static basic_sprite_t* get_wall(void) {
    return basic_sprite_ctor((const char *const *)walls_xpm, 0, 0);;
}

#endif //BULLET_H_INCLUDED
