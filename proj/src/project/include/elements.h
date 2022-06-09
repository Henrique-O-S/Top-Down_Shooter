#ifndef ELEMENTS_H_INCLUDED
#define ELEMENTS_H_INCLUDED

#include "libraries.h"

//structs

struct player{
    sprite_t *player_idle;
    sprite_t *player_shooting;
    int x;
    int y;
    int xspeed;
    int yspeed;
    int alive;

};

/**
 * @brief Player.
 */
typedef struct player player_t;

player_t p;

struct enemy{
    int id;
    sprite_t *enemy_idle;
    sprite_t *enemy_attacking;
    int x;
    int y;
    int xspeed;
    int yspeed;
    int alive;

};

/**
 * @brief Enemy.
 */
typedef struct enemy enemy_t;

int n_enemies;
struct enemy enemies[10]; //enemy size got to be equal to n_enemies

struct bullet{
    int id;
    sprite_t *bullet_sprite;
    int x;
    int y;
    int xspeed;
    int yspeed;
    int fired;
};

/**
 * @brief Bullet.
 */
typedef struct bullet bullet_t;

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

int (build_player)(int start_x, int start_y,  basic_sprite_t **idle,  basic_sprite_t **shooting);

void (draw_player)();

void (update_player_pos)();

int (collision_player_monster)(struct enemy enemy, struct player player);

int (collision_player_wall)(struct map map, struct player player);

//Monsters

int (build_monsters)(int start_x, int start_y,  basic_sprite_t **idle,  basic_sprite_t **attacking);

void (draw_monsters)();

void (update_monster_pos)();

int (collision_monster_wall)(struct map map, struct enemy enemy);

//Bullet

int (build_bullets)(int startx, int starty,  basic_sprite_t **sprite);

void (draw_bullets)();

void (update_bullet_pos)();

int (collision_bullet_wall)(struct map map, struct bullet bullet);

int (collision_bullet_monster)(struct enemy enemy, struct bullet bullet);

//Walls

int (wall_collision)(struct map map, int x, int y);



#endif //ELEMENTS_H_INCLUDED
