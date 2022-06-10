#include <lcom/lcf.h>

#include "elements.h"
#include <stdio.h>
#include <math.h>

//Player

int (build_player)(int start_x, int start_y,  basic_sprite_t **idle,  basic_sprite_t **shooting){
    p.x = start_x;
    p.y = start_y;
    p.xMov = 0;
    p.yMov = 0;
    p.speed = PLAYER_SPEED;
    p.alive = 1;
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
        //int x = p.x;
        //int y = p.y;
        p.x = p.x + (p.speed * p.xMov);
        p.y = p.y + (p.speed * p.yMov);
        /*
        if(collision_player_wall(p)){
            p.x = x;
            p.y = y;
        }
        for(int j = 0; j < n_enemies; j++){
            enemy_t enemy = enemies[j];
            if(enemy.alive && collision_player_monster(enemy, p)){
                p.alive = 0;
                break;
            }
        } */
    }   
}

void (shoot)(){
    spawn_bullet(p.x, p.y, get_mouse_angle(p.player_idle));
}

int (collision_player_monster)(enemy_t enemy, player_t player) {
    double player_radius = fmax(sprite_get_w(player.player_idle), sprite_get_h(player.player_idle))/2.0;
    double monster_radius = fmax(sprite_get_w(enemy.enemy_idle), sprite_get_h(enemy.enemy_idle))/2.0;
    double distance_x = enemy.x - player.x;
    double distance_y = enemy.y - player.y;
    double distance = sqrt(distance_x * distance_x + distance_y * distance_y);
    return distance <= monster_radius + player_radius;
}

int (collision_player_wall)(player_t player){
    double radius = fmax(sprite_get_w(player.player_idle), sprite_get_h(player.player_idle))/2.0;
    for (double x = -radius; x <= radius; x += 1) {
        double y_pos = sqrt(radius*radius - x*x);
        double y_neg = -y_pos;
        if (wall_collision(player.x + x, player.y + y_pos) || wall_collision(player.x + x, player.y + y_neg)) return 1;
    }
    return 0;
}

//Enemy

int n_enemies = 4;

int (build_monsters)(int start_x, int start_y,  basic_sprite_t **idle,  basic_sprite_t **attacking) {
    for(int i = 0; i < n_enemies; i++){
        enemy_t m;
        m.id = i;
        m.x = start_x;
        m.y = start_y;
        m.xspeed = 0;
        m.yspeed = 0;
        m.alive = 1;
        m.enemy_idle = sprite_ctor(idle, 20);
        m.enemy_attacking = sprite_ctor(attacking, 15);
        enemies[i] = m;
    }
    return 0; 
}

void (draw_monsters)() {
    for(int i = 0; i < n_enemies; i++){
        enemy_t enemy = enemies[i];
        if(enemy.alive){
            sprite_set_pos(enemy.enemy_attacking, enemy.x + i* 100+100, enemy.y);
            sprite_set_angle(enemy.enemy_attacking, sprite_angle_of_two(p.player_idle, enemy.enemy_attacking));
            sprite_set_pos(enemy.enemy_idle, enemy.x + i, enemy.y+i*100);
            sprite_set_angle(enemy.enemy_idle, get_mouse_angle(enemy.enemy_idle));
            sprite_set_angle(enemy.enemy_idle, sprite_angle_of_two(p.player_idle, enemy.enemy_idle));
            sprite_draw(enemy.enemy_idle);
            sprite_draw(enemy.enemy_attacking);
            sprite_update_animation(enemy.enemy_idle);
            sprite_update_animation(enemy.enemy_attacking);
        }
    }
}

void (update_monster_pos)(struct map map){
    for(int i = 0; i < n_enemies; i++){
        enemy_t enemy = enemies[i];
        if(enemy.alive){
            int rand_x = rand() % 3;
            int rand_y = rand() % 3;
            if(rand_x == 2) rand_x = -1;
            if(rand_y == 2) rand_y = -1;
            int x = enemy.x;
            int y = enemy.y;
            enemy.x = enemy.x + enemy.xspeed * rand() % 3;
            enemy.y = enemy.y + enemy.yspeed * rand() % 3;
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
            }
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

int n_bullets = 10;
int current_bullet = 0;

int (build_bullets)(basic_sprite_t **sprite){
    for(int i = 0; i < n_bullets; i++){
        struct bullet b;
        b.id = i;
        b.x = 0;
        b.y = 0;
        b.angle = 0;
        b.xspeed = 0;
        b.yspeed = 0;
        b.fired = 0;
        b.bullet_sprite = sprite_ctor(sprite, 3);
        bullets[i] = b;
    }
    return 0; 
}

void (spawn_bullet)(int x, int y, double angle){
    struct bullet bullet = bullets[current_bullet];

    if(!bullet.fired){
        bullet.x = x;
        bullet.y = y;
        bullet.angle = angle;
        bullet.xspeed = BULLET_SPEED * fm_cos(angle);
        bullet.yspeed = BULLET_SPEED * fm_sin(angle);
        bullet.fired = true;
    }

    current_bullet++;

    if(current_bullet >= n_bullets){
        current_bullet = 0;
    }
}

void (draw_bullets)(){
    for(int i = 0; i < n_bullets; i++){
        struct bullet bullet = bullets[i];
        if(bullet.fired){
            sprite_set_pos(bullet.bullet_sprite, bullet.x, bullet.y);
            sprite_set_angle(bullet.bullet_sprite, bullet.angle);
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
        if (wall_collision(bullet.x + x, bullet.y + y_pos) || wall_collision(bullet.x + x, bullet.y + y_neg)) {
            return 1;
        }
    }
    return 0;
}

int (collision_bullet_monster)(enemy_t enemy, struct bullet bullet) {
    double bullet_radius = fmax(sprite_get_w(bullet.bullet_sprite), sprite_get_h(bullet.bullet_sprite))/2.0;
    double monster_radius = fmax(sprite_get_w(enemy.enemy_idle), sprite_get_h(enemy.enemy_idle))/2.0;
    double distance_x = enemy.x - bullet.x;
    double distance_y = enemy.y - bullet.y;
    double distance = sqrt(distance_x * distance_x + distance_y * distance_y);

    if(distance <= monster_radius + bullet_radius){
        return 1;
    }
    
    return 0;
}

//Wall

int (wall_collision)(int x, int y){
    const int w = sprite_get_w(map.background), h = sprite_get_h(map.background);
    if(x < 0 || w <= x || y < 0 || h <= y) return 0;
    int32_t pos = x + y * w;
    if(0 <= pos && pos < w * h) return map.walls[pos];
    else return 0;
}
