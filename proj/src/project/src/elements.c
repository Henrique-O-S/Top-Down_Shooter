#include <lcom/lcf.h>

#include "elements.h"
#include <stdio.h>
#include <math.h>

//Player

int (build_player)(int start_x, int start_y,  basic_sprite_t **idle,  basic_sprite_t **shooting){
    p.x = start_x;
    p.y = start_y;
    p.xspeed = 0;
    p.yspeed = 0;
    p.alive = 1;
    p.player_idle = sprite_ctor(idle, 20);
    p.player_shooting = sprite_ctor(shooting, 3);
    return 0; 
}

void (draw_player)(){
    if(p.alive){
        sprite_set_pos(p.player_idle, p.x, p.y);
        sprite_draw(p.player_idle);
        sprite_update_animation(p.player_idle);
    }
}

void (update_player_pos)(struct map map){
    if(p.alive){
        //player inputs
        int x = p.x;
        int y = p.y;
        p.x = p.x + p.xspeed; // * angle, probably
        p.y = p.y + p.yspeed; // * angle, probably
        if(collision_player_wall(map, p)){
            p.x = x;
            p.y = y;
        }
        for(int j = 0; j < n_enemies; j++){
            struct enemy enemy = enemies[j];
            if(enemy.alive && collision_player_monster(enemy, p)){
                p.alive = 0;
                break;
            }
        }
    }
        
}

int (collision_player_monster)(struct enemy enemy, struct player player) {
    double player_radius = fmax(sprite_get_w(player.player_idle), sprite_get_h(player.player_idle))/2.0;
    double monster_radius = fmax(sprite_get_w(enemy.enemy_idle), sprite_get_h(enemy.enemy_idle))/2.0;
    double distance_x = enemy.x - player.x;
    double distance_y = enemy.y - player.y;
    double distance = sqrt(distance_x * distance_x + distance_y * distance_y);
    return distance <= monster_radius + player_radius;
}

int (collision_player_wall)(struct map map, struct player player){
    double radius = fmax(sprite_get_w(player.player_idle), sprite_get_h(player.player_idle))/2.0;
    for (double x = -radius; x <= radius; x += 1) {
        double y_pos = sqrt(radius*radius - x*x);
        double y_neg = -y_pos;
        if (wall_collision(map, player.x + x, player.y + y_pos) || wall_collision(map, player.x + x, player.y + y_neg)) return 1;
    }
    return 0;
}

//Enemy

int n_enemies = 4;

int (build_monsters)(int start_x, int start_y,  basic_sprite_t **idle,  basic_sprite_t **attacking) {
    for(int i = 0; i < n_enemies; i++){
        struct enemy m;
        m.id = i;
        m.x = start_x;
        m.y = start_y;
        m.xspeed = 0;
        m.yspeed = 0;
        m.alive = 1;
        m.enemy_idle = sprite_ctor(idle, 20);
        m.enemy_idle = sprite_ctor(attacking, 15);
        enemies[i] = m;
    }
    return 0; 
}

void (draw_monsters)(){
    for(int i = 0; i < n_enemies; i++){
        struct enemy enemy = enemies[i];
        if(enemy.alive){
            sprite_set_pos(enemy.enemy_idle, enemy.x + i*100, enemy.y+i*100);
            sprite_draw(enemy.enemy_idle);
            sprite_update_animation(enemy.enemy_idle);
        }
    }

}

void (update_monster_pos)(struct map map){
    for(int i = 0; i < n_enemies; i++){
        struct enemy enemy = enemies[i];
        if(enemy.alive){
            int rand_x = rand() % 3;
            int rand_y = rand() % 3;
            if(rand_x == 2) rand_x = -1;
            if(rand_y == 2) rand_y = -1;
            int x = enemy.x;
            int y = enemy.y;
            enemy.x = enemy.x + enemy.xspeed * rand() % 3;
            enemy.y = enemy.y + enemy.yspeed * rand() % 3;
            if(collision_monster_wall(map, enemy)){
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

int (collision_monster_wall)(struct map map, struct enemy enemy) {
    double radius = fmax(sprite_get_w(enemy.enemy_idle), sprite_get_h(enemy.enemy_idle))/2.0;
    for (double x = -radius; x <= radius; x += 1) {
        double y_pos = sqrt(radius*radius - x*x);
        double y_neg = -y_pos;
        if (wall_collision(map, enemy.x + x, enemy.y + y_pos) || wall_collision(map, enemy.x + x, enemy.y + y_neg)) return 1;
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

void (update_bullet_pos)(struct map map){
    for(int i = 0; i < n_bullets; i++){
        struct bullet bullet = bullets[i];
        if(bullet.fired){
            //bullet direction should be worked out here
            int x = bullet.x;
            int y = bullet.y;
            bullet.x = bullet.x + bullet.xspeed; // * angle, probably
            bullet.y = bullet.y + bullet.yspeed; // * angle, probably
            if(collision_bullet_wall(map, bullet)){
                bullet.x = x;
                bullet.y = y;
                bullet.fired = 0;
            }
            for(int j = 0; j < n_enemies; i++){
                struct enemy enemy = enemies[j];
                if(enemy.alive && collision_bullet_monster(enemy, bullet)){
                    bullet.fired = 0;
                    enemy.alive = 0;
                    break;
                }
            }
        }
    }
}

int (collision_bullet_wall)(struct map map, struct bullet bullet) {
    double radius = fmax(sprite_get_w(bullet.bullet_sprite), sprite_get_h(bullet.bullet_sprite))/2.0;
    for (double x = -radius; x <= radius; x += 1) {
        double y_pos = sqrt(radius*radius - x*x);
        double y_neg = -y_pos;
        if (wall_collision(map, bullet.x + x, bullet.y + y_pos) || wall_collision(map, bullet.x + x, bullet.y + y_neg)) return 1;
    }
    return 0;
}

int (collision_bullet_monster)(struct enemy enemy, struct bullet bullet) {
    double bullet_radius = fmax(sprite_get_w(bullet.bullet_sprite), sprite_get_h(bullet.bullet_sprite))/2.0;
    double monster_radius = fmax(sprite_get_w(enemy.enemy_idle), sprite_get_h(enemy.enemy_idle))/2.0;
    double distance_x = enemy.x - bullet.x;
    double distance_y = enemy.y - bullet.y;
    double distance = sqrt(distance_x * distance_x + distance_y * distance_y);
    return distance <= monster_radius + bullet_radius;
}

//Wall

int (wall_collision)(struct map map, int x, int y){
    const int w = sprite_get_w(map.background), h = sprite_get_h(map.background);
    if(x < 0 || w <= x || y < 0 || h <= y) return 0;
    int32_t pos = x + y * w;
    if(0 <= pos && pos < w * h) return map.walls[pos];
    else return 0;
}

