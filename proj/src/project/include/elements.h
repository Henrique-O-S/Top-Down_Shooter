#ifndef ELEMENTS_H_INCLUDED
#define ELEMENTS_H_INCLUDED

/**
 * @defgroup elements elements
 * @ingroup proj
 *
 * @{
 */

#include "libraries.h"

//game macros
#define PLAYER_SPEED    5;
#define MONSTER_SPEED   3;
#define BULLET_SPEED    10;
#define SHOT_COOLDOWN   0.25;

//structs

struct player{
    sprite_t *player_sprite;
    int x;
    int y;
    int xMov; //can be -1, 0 or 1
    int yMov; //can be -1, 0 or 1
    int speed;
    float shot_cooldown;
    int alive;
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
};

int n_bullets;
struct bullet bullets[1]; //bullets size got to be equal to n_bullets

//is in single bullet mode which means only one bullet can be shot at a time
//bullet limits can be changed by increasing n_bullets

struct map{
    sprite_t *background;
    uint8_t *walls;
};

struct map map;

//Elements functions

//Player

int (build_player)(int start_x, int start_y, const basic_sprite_t *sprite);

void (draw_player)();

void (update_player_pos)();

void (update_dir)(int val, int dir);

void (shoot)();

int (collision_player_monster)(struct monster monster, struct player player);

int (collision_player_wall)(struct player player);

//Monsters

int (build_monsters)(int start_x, int start_y, const basic_sprite_t *sprite);

void (draw_monsters)();

void (update_monster_pos)();

int (collision_monster_wall)(struct monster monster);

//Bullet

int (build_bullets)(int startx, int starty, const basic_sprite_t *sprite);

void (draw_bullets)();

void (update_bullet_pos)();

int (collision_bullet_wall)(struct bullet bullet);

int (collision_bullet_monster)(struct monster monster, struct bullet bullet);

//Walls

int (wall_collision)(int x, int y);

/**
 * @}
 */

#endif //ELEMENTS_H_INCLUDED
