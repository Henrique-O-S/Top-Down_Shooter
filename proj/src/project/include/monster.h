#include <lcom/lcf.h>

struct monster{
    int id;
    sprite_t *monster_sprite;
    int x;
    int y;
    int xspeed;
    int yspeed;
    int alive;
    xpm_image_t img;

};

struct map{
    sprite_t *background;
};

int n_monsters;
struct monster monsters[10];

int build_monster(int startx, int starty, xpm_map_t sprite);

void draw_player();

void update_pos();

int collision_monster_wall(struct map map, struct monster monster);

int wall_collision(struct map map, int x, int y);
