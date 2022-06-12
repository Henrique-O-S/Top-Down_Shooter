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
#define BULLET_SPEED    30
#define SHOT_COOLDOWN   10
#define BORDER_OFFSET   25
#define DISTANCE_THRESHOLD 375
#define ATTACK_THRESHOLD   175
#define PLAYER_SPAWN_X   500
#define PLAYER_SPAWN_Y   500
//structs


/**
 * @brief Calculates if given position is border
 */
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
    //Shot cooldown is number of frames between shooting and when the player can shoot again
    int shot_cooldown, cur_cooldown;
    int alive, health;
    int wait, wait_threshold;
};

/**
 * @brief Player.
 */
typedef struct player player_t;

player_t p;

struct enemy{
    int id;
    int spawn_point, in_house, in_house2;
    sprite_t *enemy_idle;
    sprite_t *enemy_attacking;
    double x, y, c, s, angle;
    int speed, x_entrance, y_entrance;
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
    double x, y;
    double speed, angle;
    double c, s;
    int fired;
    int wait, wait_threshold;
};

/**
 * @brief Bullet.
 */
typedef struct bullet bullet_t;

int n_bullets;
bullet_t bullets[5]; //bullets size got to be equal to n_bullets

//is in single bullet mode which means only one bullet can be shot at a time
//bullet limits can be changed by increasing n_bullets

struct map{
    sprite_t *background;
    uint8_t *walls;
};

struct map map;

//Aux functions
/**
 * @brief Calculates if given position is border
 * @return Returns 1 if border, 0 other wise
 */
ret_pair_t (is_border)(int x, int y);

ret_pair_t (path_to_take)(int x, int y);

/**
 * @brief Calculates angle of e's position from his entrance point
 * @return Returns angle
 */
double get_angle(enemy_t e);

/**
 * @brief Calculates angle between to given points
 * @return Returns angle
 */
double get_angle_two_points(int x, int y, int x1, int y1);

/**
 * @brief Calculates angle between enemy and player
 * @return Returns angle
 */
double get_angle_to_player(enemy_t e);

/**
 * @brief Calculates distance from enemy to player
 * @return Returns distance
 */
int get_distance(enemy_t e);

//Elements functions

/**
 * @brief Builds map and its configurations
 */
void (build_map)();

/**
 * @brief Draws loaded map on screen
 */
void (draw_map)();

//Player

/**
 * @brief Builds a plyer and his configurations
 * @return Returns 0 if succeded, non 0 other wise;
 */
int (build_player)(int start_x, int start_y,  basic_sprite_t **idle,  basic_sprite_t **shooting);

/**
 * @brief Erases player
 */
void (dispawn_player)(void);

/**
 * @brief Draws previously loaded player
 */
void (draw_player)();

/**
 * @brief Sets player's position to given one
 */
void (set_player_pos)(keys_t *keys);

/**
 * @brief Visually updates player position
 */
void (update_player_pos)();

/**
 * @brief Checks if player is still alive
 */
int (get_player_status)();

/**
 * @brief Calculates distance from player radius to enemy radius to check for collisions
 * @return Returns distance from enemy to player
 */
int (collision_player_monster)(enemy_t enemy, player_t player);

/**
 * @brief Calculates distance from player radius to wall to check for collisions
 * @return Returns distance from wall to player
 */
int (collision_player_wall)(player_t player, int threshold);

/**
 * @brief Checks if player is in range of enemy
 * @return Returns distance from enemy to player
 */
int (in_range_of_player)(enemy_t enemy);

/**
 * @brief Ticks the shot cooldown
 */
void (tick_cooldown)();

//Monsters

/**
 * @brief Builds an enemy and his configurations
 * @return Returns 0 if succeded, non 0 other wise;
 */
int (build_monsters)(basic_sprite_t **idle,  basic_sprite_t **attacking);

/**
 * @brief Draws the enemy on screen
 */
void (draw_monsters)();

/**
 * @brief Spawns the enemys
 */
void (spawn_monsters)(void);

/**
 * @brief Dispawns the enemys
 */
void (dispawn_monsters)(void);

/**
 * @brief Updates enemys positions
 */
void (update_monster_pos)();

/**
 * @brief Resets enemy's animation
 */
void (enemy_reset)(enemy_t *enemy);

/**
 * @brief Checks if enemy is able to atack player
 * @return Returns 0 if succeded, non 0 other wise;
 */
int (in_sight_of_player)(enemy_t enemy);

/**
 * @brief Checks if enemy collides with wall
 * @return Returns 0 if succeded, non 0 other wise;
 */
int (collision_monster_wall)(enemy_t enemy, int threshold);

//Bullet

/**
 * @brief Builds a bullet and his configurations
 * @return Returns 0 if succeded, non 0 other wise;
 */
int (build_bullets)(int startx, int starty,  basic_sprite_t **sprite);

/**
 * @brief Spawns bullets
 */
void (spawn_bullets)();

/**
 * @brief Dispawns the bullets
 */
void dispawn_bullets(void);

/**
 * @brief Draws the bullets on screen
 */
void (draw_bullets)();

/**
 * @brief Updates bullets positions
 */
void (update_bullet_pos)();

/**
 * @brief Checks if bullet collides with wall
 * @return Returns 0 if succeded, non 0 other wise;
 */
int (collision_bullet_wall)(struct bullet bullet);

/**
 * @brief Checks if bullet collides with enemy
 * @return Returns 0 if succeded, non 0 other wise;
 */
int (collision_bullet_monster)(enemy_t enemy, struct bullet bullet);

//Walls

/**
 * @brief Checks for wall collisions
 */
int (wall_collision)(int x, int y);

/**
 * @}
 */

#endif //ELEMENTS_H_INCLUDED
