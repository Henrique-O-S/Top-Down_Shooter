#include <lcom/lcf.h>

typedef struct{
    int x;
    int y;
    int xspeed;
    int yspeed;
    xpm_image_t img;

}player;

int build_player(int startx, int starty, xpm_map_t sprite);

void draw_player();

void update_pos();
