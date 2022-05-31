#include <lcom/lcf.h>

#include "libraries/graphics/include/graphics.h"
#include "libraries/graphics/include/sprite.h"
#include "player.h"

static player p;

int build_player(int start_x, int start_y, xpm_map_t sprite){
    p.x = start_x;
    p.y = start_y;
    p.xspeed = 0;
    p.yspeed = 0;
    xpm_image_t img;
    xpm_load(sprite, XPM_8_8_8, &img);
    p.img = img;

    return 0; 
}

void draw_player(){

}

void update_pos(){
    
}
