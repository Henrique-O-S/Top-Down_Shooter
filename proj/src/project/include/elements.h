#ifndef ELEMENTS_H_INCLUDED
#define ELEMENTS_H_INCLUDED

/**
 * @defgroup elements elements
 * @ingroup proj
 *
 * @{
 */

#include "libraries.h"
#include "aux_functions.h"

//game macros
#define PLAYER_SPEED    5
#define MONSTER_SPEED   3
#define BULLET_SPEED    10
#define BORDER_OFFSET   25
#define DISTANCE_THRESHOLD   175
//structs

struct ret_pair{
    int x;
    int y;
};

typedef struct ret_pair ret_pair_t;

struct player{
    sprite_t *player_idle;
    sprite_t *player_shooting;
    int x;
    int y;
    int xMov; //can be -1, 0 or 1
    int yMov; //can be -1, 0 or 1
    int speed;
    int alive, health;
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
    int wait, wait_threshold;
};

/**
 * @brief Enemy.
 */
typedef struct enemy enemy_t;

int n_enemies;
enemy_t enemies[10]; //enemy size got to be equal to n_enemies

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

struct map map;

//Aux functions

ret_pair_t (is_border)(int x, int y);

ret_pair_t (path_to_take)(int x, int y);

//Elements functions

void (build_map)();

void (draw_map)();

//Player

int (build_player)(int start_x, int start_y,  basic_sprite_t **idle,  basic_sprite_t **shooting);

void (draw_player)();

void (set_player_pos)(keys_t *keys);

void (update_player_pos)();

int (get_player_status)();

int (collision_player_monster)(enemy_t enemy, player_t player);

int (collision_player_wall)(player_t player, int threshold);

int (in_range_of_player)(enemy_t enemy);

//Monsters

int (build_monsters)(int start_x, int start_y,  basic_sprite_t **idle,  basic_sprite_t **attacking);

void (draw_monsters)();

void (spawn_monsters)(void);

void (update_monster_pos)();

int (collision_monster_wall)(enemy_t enemy);

//Bullet

int (build_bullets)(int startx, int starty,  basic_sprite_t **sprite);

void (draw_bullets)();

void (update_bullet_pos)();

int (collision_bullet_wall)(struct bullet bullet);

int (collision_bullet_monster)(enemy_t enemy, struct bullet bullet);

//Walls

int (wall_collision)(int x, int y);

/**
 * @}
 */



#endif //ELEMENTS_H_INCLUDED
