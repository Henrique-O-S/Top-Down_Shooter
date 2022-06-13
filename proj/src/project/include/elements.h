#ifndef ELEMENTS_H_INCLUDED
#define ELEMENTS_H_INCLUDED

/**
 * @defgroup elements elements
 * @ingroup project
 *
 * @{
 */

#include "libraries.h"
#include "aux_functions.h"

//game macros
#define PLAYER_SPEED    5
#define ENEMY_SPEED   4
#define BULLET_SPEED    30
#define SHOT_COOLDOWN   10
#define BORDER_OFFSET   25
#define DISTANCE_THRESHOLD 500
#define ATTACK_THRESHOLD   175
#define PLAYER_SPAWN_X   500
#define PLAYER_SPAWN_Y   500
//structs



struct ret_pair{
    int x;
    int y;
};

/**
 * @brief Pair defining if a position is beyond a border.
 * @details This pair contains a x and a y argument, each taking the value of 1 if a position is beyond a border and 0 if it's inside
 */
typedef struct ret_pair ret_pair_t;

struct player{
    sprite_t *player_idle;
    sprite_t *player_shooting;
    int kills;
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
 * @brief Player struct.
 * @details This struct contains all information relevant to the player, including its sprites, position, speed and direction its moving, number of kills, cooldown between shots, health and if it's alive or not, and time the player stays in the shooting animation
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
 * @brief Enemy struct.
 * @details This struct contains all information relevant to the enemy, including its sprites, position, speed and direction its moving, spawn point, where it will try to enter the house, if it's alive or not, and time the enemy stays in the stabbing animation
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
 * @brief Bullet struct.
 * @details This struct contains all information relevant to the bullet, including sprite, position, speed, firing angle, if it is spawned in currently and time it stays spawned in if it doesn't hit anything
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

/**
 * @brief Map where the game takes place.
 * @details This struct contains information to draw the map where the game takes place and which parts of it are walls so they have collisions
 */
struct map map;

//Aux functions

/**
 * @brief Function that checks if a position is beyond a border, returning a ret_pair_t with 1 in a parameter if it's beyond the border in that direction and 0 if it isn't
 */
ret_pair_t (is_border)(int x, int y);

/**
 * @brief Returns the angle between the enemy and the position it enters the house
 */
double get_angle(enemy_t e);

/**
 * @brief Returns the angle between two points
 */
double get_angle_two_points(int x, int y, int x1, int y1);

/**
 * @brief Returns the angle between an enemy and the player
 */
double get_angle_to_player(enemy_t e);

/**
 * @brief Returns 1 if the enemy is in a position it should enter the house and 0 if it isn't
 */
int get_distance(enemy_t e);

//Elements functions

/**
 * @brief Builds the map struct where the game takes place
 */
void (build_map)();

/**
 * @brief Draws the map on the screen
 */
void (draw_map)();

//Player

/**
 * @brief Builds the player struct with the values it has at the start of the game
 */
int (build_player)(int start_x, int start_y,  basic_sprite_t **idle,  basic_sprite_t **shooting);

/**
 * @brief Despawns the player from the game, resetting its values when the game ends
 */
void (despawn_player)(void);

/**
 * @brief Draws the player on the screen
 */
void (draw_player)();

/**
 * @brief Updates the state of the player based on keys pressed
 */
void (update_player)(keys_t *keys);

/**
 * @brief Updates the position of the player
 */
void (update_player_pos)();

/**
 * @brief Returns if the player is alive or not
 */
int (get_player_status)();

/**
 * @brief Returns how many enemies are currently alive
 */
int (get_enemies_alive)();

/**
 * @brief Checks if there are collisions between the player and an enemy
 */
int (collision_player_enemy)(enemy_t enemy, player_t player);

/**
 * @brief Checks if there are collisions between the player and a wall
 */
int (collision_player_wall)(player_t player, int threshold);

/**
 * @brief Returns how many kills the player got
 */
int (player_get_kills)(void);

/**
 * @brief Returns how much health the player has
 */
int (player_get_health)(void);

/**
 * @brief Returns distance between an enemy and player
 */
int (in_range_of_player)(enemy_t enemy);

/**
 * @brief Advances the shot cooldown 1 tick
 */
void (tick_cooldown)();

//Monsters

/**
 * @brief Builds the enemy structs with the values they should have at the start of the game
 */
int (build_enemies)(basic_sprite_t **idle,  basic_sprite_t **attacking);

/**
 * @brief Draws the enemies on the screen
 */
void (draw_enemies)();

/**
 * @brief Spawns the enemies on the game
 */
void (spawn_enemies)(void);

/**
 * @brief Despawns the enemies at the end of the game, resetting their values
 */
void (despawn_enemies)(void);

/**
 * @brief Updates the positions of enemies, moving them
 */
void (update_enemy_pos)();

/**
 * @brief Returns 1 if the enemy has the player on its sight
 */
int (in_sight_of_player)(enemy_t enemy);

/**
 * @brief Checks if there's a collision between the enemy and a wall
 */
int (collision_enemy_wall)(enemy_t enemy, int threshold);

//Bullet

/**
 * @brief Builds the bullet structs with the values they should have at the start of the game
 */
int (build_bullets)(int startx, int starty,  basic_sprite_t **sprite);

/**
 * @brief Spawns a bullet when it is shot with the right direction and position
 */
void (spawn_bullet)();

/**
 * @brief Despawns all bullets at the end of the game, resetting their values
 */
void despawn_bullets(void);

/**
 * @brief Draws all bullets on the screen
 */
void (draw_bullets)();

/**
 * @brief Updates the position of the bullets, moving them
 */
void (update_bullet_pos)();

/**
 * @brief Checks if there's a collision between the bullet and a wall
 */
int (collision_bullet_wall)(struct bullet bullet);

/**
 * @brief Checks if there's a collision between the bullet and an enemy
 */
int (collision_bullet_enemy)(enemy_t enemy, struct bullet bullet);

//Walls

/**
 * @brief Checks if there's a collision between object in (x, y) position with the wall
 */
int (wall_collision)(int x, int y);

/**
 * @}
 */

#endif //ELEMENTS_H_INCLUDED
