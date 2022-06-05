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
struct monster monsters[10]; //monsters size got to be equal to n_monsters

struct bullet{
    int id;
    sprite_t *bullet_sprite;
    int x;
    int y;
    int xspeed;
    int yspeed;
    int fired;
    xpm_image_t img;

};

int n_bullets;
struct bullet bullets[1]; //bullets size got to be equal to n_bullets

//is in single bullet mode which means only one bullet can be shot at a time
//bullet limits can be changed by increasing n_bullets

struct map{
    sprite_t *background;
    uint8_t *walls;
};

//Elements functions

//Player

int (build_player)(int start_x, int start_y, xpm_map_t sprite);

void (draw_player)();

void (update_player_pos)();

int (collision_player_monster)(struct monster monster, struct player player);

int (collision_player_wall)(struct map map, struct player player);

//Monsters

int (build_monsters)(int start_x, int start_y, xpm_map_t sprite);

void (draw_monsters)();

void (update_monster_pos)();

int (collision_monster_wall)(struct map map, struct monster monster);

//Bullet

int (build_bullets)(int startx, int starty, xpm_map_t sprite);

void (draw_bullets)();

void (update_bullet_pos)();

int (collision_bullet_wall)(struct map map, struct bullet bullet);

int (collision_bullet_monster)(struct monster monster, struct bullet bullet);

//Walls

int (wall_collision)(struct map map, int x, int y);

#endif //ELEMENTS_H_INCLUDED
