#ifndef ELEMENTS_H_INCLUDED
#define ELEMENTS_H_INCLUDED

#include "libraries.h"

//structs

struct player{
    sprite_t *player_sprite;
    int x;
    int y;
    int xspeed;
    int yspeed;
    int alive;
    xpm_image_t img;

};

struct player p;

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

int n_monsters;
struct monster monsters[10];

struct map{
    sprite_t *background;
};

//Elements functions

//Player

int build_player(int startx, int starty, xpm_map_t sprite);

void draw_player();

void update_player_pos();

int collision_player_wall(struct map map, struct player player);

//Monsters

int build_monsters(int startx, int starty, xpm_map_t sprite);

void draw_monsters();

void update_monster_pos();

int collision_monster_wall(struct map map, struct monster monster);

//Walls

int wall_collision(struct map map, int x, int y);

#endif //ELEMENTS_H_INCLUDED
