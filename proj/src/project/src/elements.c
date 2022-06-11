#include <lcom/lcf.h>

#include "elements.h"
#include "walls.h"
#include "map.h"
#include <stdio.h>
#include <math.h>


void (build_map)() {
    map.background = sprite_ctor(get_map(), 1);
    uint16_t w = sprite_get_w(map.background), h = sprite_get_h(map.background);
    map.walls = malloc(sizeof(uint8_t) * w * h);

    basic_sprite_t *aux = get_wall();
    const uint8_t *m = basic_sprite_get_map(aux);

    for(int i = 0; i < w*h; i++) {
        map.walls[i] =  (m[4*i+3] < ALPHA_THRESHOLD ? 1 : 0);
    }
    basic_sprite_dtor(aux);
    sprite_set_pos(map.background, 0, 75);
}

void (draw_map)() {
    sprite_draw(map.background);
}

//Player

int (build_player)(int start_x, int start_y,  basic_sprite_t **idle,  basic_sprite_t **shooting){
    p.x = start_x;
    p.y = start_y;
    p.xMov = 0;
    p.yMov = 0;
    p.speed = PLAYER_SPEED;
    p.alive = 1;
    p.health = 3;
    p.player_idle = sprite_ctor(idle, 20);
    p.player_shooting = sprite_ctor(shooting, 3);
    return 0; 
}

void (draw_player)(){
    if(p.alive){
        sprite_set_pos(p.player_idle, p.x, p.y);
        sprite_set_angle(p.player_idle, get_mouse_angle(p.player_idle));
        sprite_draw(p.player_idle);
        sprite_update_animation(p.player_idle);
    }
}

void (set_player_pos)(keys_t *keys) {
    p.yMov = keys->s_pressed - keys->w_pressed;
    p.xMov = keys->d_pressed - keys->a_pressed;
    update_player_pos();
}

void (update_player_pos)(){
    if(p.alive){
        //player inputs
        int x0 = p.x, y0 = p.y;
        int x = p.x + (p.speed * p.xMov);
        int y = p.y + (p.speed * p.yMov);
        if(collision_player_wall(p, 0)){
            p.x = x;
            p.y = y;
            if(collision_player_wall(p, -PLAYER_SPEED)) {
                p.x = x0;
                p.y = y0;
            }
            
        } 
        
        else {
            if(x <= BORDER_OFFSET || x >= ((int)get_XRes() - BORDER_OFFSET)) {
                ;
            }
            else {
                p.x = x;
            }
            if(y <= BORDER_OFFSET || y >= ((int)get_YRes() - BORDER_OFFSET)) {
                ;
            }
            else {
                p.y = y;
            }
        } 
        
    
        
        for(int i = 0; i < n_enemies; i++){
            if(enemies[i].alive && collision_player_monster(enemies[i], p) && enemies[i].wait == 7){
                p.health--;
                if (!p.health)
                    p.alive = 0;
            }
        } 
    }   
}

int (get_player_status)() {
    return p.alive;
}

int (collision_player_monster)(enemy_t enemy, player_t player) {
    double player_radius = fmax(sprite_get_w(player.player_idle), sprite_get_h(player.player_idle))/2.0;
    double monster_radius = fmax(sprite_get_w(enemy.enemy_idle), sprite_get_h(enemy.enemy_idle))/2.0;
    double distance_x = enemy.x - player.x;
    double distance_y = enemy.y - player.y;
    double distance = sqrt(distance_x * distance_x + distance_y * distance_y);
    return distance <= monster_radius + player_radius;
}

int (collision_player_wall)(player_t player, int threshold){
    double radius = fmax(sprite_get_w(player.player_idle), sprite_get_h(player.player_idle))/6.0;
    radius += threshold;
    for (double x = -radius; x <= radius; x += 1) {
        double y_pos = sqrt(radius*radius - x*x);
        double y_neg = -y_pos;
        if (wall_collision(player.x + x, player.y + y_pos) || wall_collision(player.x + x, player.y + y_neg)) return 1;
    }
    return 0;
}


ret_pair_t (is_border)(int x, int y) {
    ret_pair_t ret;
    if(x <= BORDER_OFFSET || x >= ((int)get_XRes() - BORDER_OFFSET)) {
        ret.x = 0;
    }
    else {
        ret.x = 1;
    }
    if(y <= BORDER_OFFSET || y >= ((int)get_YRes() - BORDER_OFFSET)) {
        ret.y = 0;
    }
    else {
        ret.y = 1;
    }
    return ret;
}

ret_pair_t (path_to_take)(int x, int y) {
    ret_pair_t ret;

    ret.x = (x - p.x < 0)? 1 : -1 ;
    ret.y = (y - p.y < 0)? 1 : -1 ;

    return ret;
}

int (in_range_of_player)(enemy_t enemy) {
    int x = abs(enemy.x - p.x);
    int y = abs(enemy.y - p.y);

    int ret = sqrt(x*x +y*y);
    return (ret < DISTANCE_THRESHOLD);
}

//Enemy

int n_enemies = 4;

int (build_monsters)(int start_x, int start_y,  basic_sprite_t **idle,  basic_sprite_t **attacking) {
    for(int i = 0; i < n_enemies; i++){
        enemy_t m;
        m.id = i;
        m.x = start_x;
        m.y = start_y;
        m.xspeed = 2;
        m.yspeed = 2;
        m.alive = 1;
        m.enemy_idle = sprite_ctor(idle, 20);
        m.enemy_attacking = sprite_ctor(attacking, 15);
        m.wait = 0;
        m.wait_threshold = 15;
        enemies[i] = m;

    }
    return 0; 
}

void (draw_monsters)() {
    for(int i = 0; i < n_enemies; i++){
        if(enemies[i].alive){
            
        
            if(enemies[i].wait > 0) {
                enemies[i].wait--;
                sprite_set_pos(enemies[i].enemy_attacking, enemies[i].x, enemies[i].y);
                sprite_set_angle(enemies[i].enemy_attacking, sprite_angle_of_two(p.player_idle, enemies[i].enemy_attacking));
                sprite_draw(enemies[i].enemy_attacking);
                sprite_update_animation(enemies[i].enemy_attacking);
            }
            else {
                sprite_set_pos(enemies[i].enemy_idle, enemies[i].x, enemies[i].y);
                sprite_set_angle(enemies[i].enemy_idle, sprite_angle_of_two(p.player_idle, enemies[i].enemy_idle));
                sprite_draw(enemies[i].enemy_idle);
                sprite_update_animation(enemies[i].enemy_idle);
            }
            
        }
    }
}

void (spawn_monsters)(void) {
    enemies[0].x = 90;
    enemies[0].y = 100;
    enemies[1].x = 50;
    enemies[1].y = 500;
    enemies[2].x = 950;
    enemies[2].y = 50;
    enemies[3].x = 950;
    enemies[3].y = 600;
}

void (update_monster_pos)(){
    for(int i = 0; i < n_enemies; i++){
        if(enemies[i].alive){

            if(in_range_of_player(enemies[i])) {
                
                ret_pair_t r = path_to_take(enemies[i].x, enemies[i].y);
                int x = enemies[i].x + enemies[i].xspeed*r.x;
                int y = enemies[i].y + enemies[i].yspeed*r.y;
                ret_pair_t r2 = is_border(x, y);
                if(r2.x) enemies[i].x = x;
                if(r2.y) enemies[i].y = y;

                // for animation
                if(!enemies[i].wait) enemies[i].wait = enemies[i].wait_threshold;
            }
            else {
                int rand_x = rand() % 3 -1;
                int rand_y = rand() % 3 -1;
                int x = enemies[i].x + enemies[i].xspeed*rand_x;
                int y = enemies[i].y + enemies[i].yspeed*rand_y;
                ret_pair_t r = is_border(x, y);
                if(r.x) enemies[i].x = x;
                if(r.y) enemies[i].y = y;
            }

            /*
            if(collision_monster_wall(enemy)){
                enemy.x = x;
                enemy.y = y;
            }
            for(int j = 0; j < n_bullets; i++){
                struct bullet bullet = bullets[j];
                if(bullet.fired && collision_bullet_monster(enemy, bullet)){
                    bullet.fired = 0;
                    enemy.alive = 0;
                    break;
                }
            } */
        }
    }
}

int (collision_monster_wall)( enemy_t enemy) {
    double radius = fmax(sprite_get_w(enemy.enemy_idle), sprite_get_h(enemy.enemy_idle))/2.0;
    for (double x = -radius; x <= radius; x += 1) {
        double y_pos = sqrt(radius*radius - x*x);
        double y_neg = -y_pos;
        if (wall_collision(enemy.x + x, enemy.y + y_pos) || wall_collision(enemy.x + x, enemy.y + y_neg)) return 1;
    }
    return 0;
}

//Bullet

int n_bullets = 1;

int (build_bullets)(int start_x, int start_y, basic_sprite_t **sprite){
    for(int i = 0; i < n_bullets; i++){
        struct bullet b;
        b.id = i;
        b.x = start_x;
        b.y = start_y;
        b.xspeed = 0;
        b.yspeed = 0;
        b.fired = 0;
        b.bullet_sprite = sprite_ctor(sprite, 3);
        bullets[i] = b;
    }
    return 0; 
}

void (draw_bullets)(){
    for(int i = 0; i < n_bullets; i++){
        struct bullet bullet = bullets[i];
        if(bullet.fired != -1){
            sprite_set_pos(bullet.bullet_sprite, bullet.x, bullet.y);
            sprite_draw(bullet.bullet_sprite);
            sprite_update_animation(bullet.bullet_sprite);
        }
    }

}

void (update_bullet_pos)(){
    for(int i = 0; i < n_bullets; i++){
        struct bullet bullet = bullets[i];
        if(bullet.fired){
            //bullet direction should be worked out here
            int x = bullet.x;
            int y = bullet.y;
            bullet.x = bullet.x + bullet.xspeed; // * angle, probably
            bullet.y = bullet.y + bullet.yspeed; // * angle, probably
            if(collision_bullet_wall(bullet)){
                bullet.x = x;
                bullet.y = y;
                bullet.fired = 0;
            }
            for(int j = 0; j < n_enemies; i++){
                enemy_t enemy = enemies[j];
                if(enemy.alive && collision_bullet_monster(enemy, bullet)){
                    bullet.fired = 0;
                    enemy.alive = 0;
                    break;
                }
            }
        }
    }
}

int (collision_bullet_wall)(struct bullet bullet) {
    double radius = fmax(sprite_get_w(bullet.bullet_sprite), sprite_get_h(bullet.bullet_sprite))/2.0;
    for (double x = -radius; x <= radius; x += 1) {
        double y_pos = sqrt(radius*radius - x*x);
        double y_neg = -y_pos;
        if (wall_collision(bullet.x + x, bullet.y + y_pos) || wall_collision(bullet.x + x, bullet.y + y_neg)) return 1;
    }
    return 0;
}

int (collision_bullet_monster)(enemy_t enemy, struct bullet bullet) {
    double bullet_radius = fmax(sprite_get_w(bullet.bullet_sprite), sprite_get_h(bullet.bullet_sprite))/2.0;
    double monster_radius = fmax(sprite_get_w(enemy.enemy_idle), sprite_get_h(enemy.enemy_idle))/2.0;
    double distance_x = enemy.x - bullet.x;
    double distance_y = enemy.y - bullet.y;
    double distance = sqrt(distance_x * distance_x + distance_y * distance_y);
    return distance <= monster_radius + bullet_radius;
}

//Wall

int (wall_collision)(int x, int y){
    const int w = sprite_get_w(map.background), h = sprite_get_h(map.background);
    if(x < 0 || w <= x || y < 0 || h <= y) return 0;
    int32_t pos = x + y * w;
    if(0 <= pos && pos < w * h) return map.walls[pos];
    else return 0;
}

