#include <lcom/lcf.h>

#include "elements.h"
#include <stdio.h>
#include <math.h>

//Player

int (build_player)(int start_x, int start_y, int speed, const basic_sprite_t *sprite){
    p.x = start_x;
    p.y = start_y;
    p.xMov = 0;
    p.yMov = 0;
    p.speed = speed;
    p.alive = 1;
    p.player_sprite = sprite_ctor(sprite);

    return 0; 
}

void (draw_player)(){
    if(p.alive){
        sprite_set_pos(p.player_sprite, p.x, p.y);
        sprite_draw(p.player_sprite);
    }
}

void (update_player_pos)(struct map map){
    if(p.alive){
        //player inputs
        int x = p.x;
        int y = p.y;
        p.x = p.x + (p.speed * p.xMov);
        p.y = p.y + (p.speed * p.yMov);
        if(collision_player_wall(map, p)){
            p.x = x;
            p.y = y;
        }
        for(int j = 0; j < n_monsters; j++){
            struct monster monster = monsters[j];
            if(monster.alive && collision_player_monster(monster, p)){
                p.alive = 0;
                break;
            }
        }
    }   
}

//Dir is 0 if horizontal and 1 if vertical
void (update_dir)(int val, int dir){
    switch (dir){
        case 0:
            p.xMov += val;
            break;

        case 1:
            p.yMov += val;
            break;

        default:
            break;
    }
}

int (collision_player_monster)(struct monster monster, struct player player) {
    double player_radius = fmax(sprite_get_w(player.player_sprite), sprite_get_h(player.player_sprite))/2.0;
    double monster_radius = fmax(sprite_get_w(monster.monster_sprite), sprite_get_h(monster.monster_sprite))/2.0;
    double distance_x = monster.x - player.x;
    double distance_y = monster.y - player.y;
    double distance = sqrt(distance_x * distance_x + distance_y * distance_y);
    return distance <= monster_radius + player_radius;
}

int (collision_player_wall)(struct map map, struct player player){
    double radius = fmax(sprite_get_w(player.player_sprite), sprite_get_h(player.player_sprite))/2.0;
    for (double x = -radius; x <= radius; x += 1) {
        double y_pos = sqrt(radius*radius - x*x);
        double y_neg = -y_pos;
        if (wall_collision(map, player.x + x, player.y + y_pos) || wall_collision(map, player.x + x, player.y + y_neg)) return 1;
    }
    return 0;
}

//Monster

int n_monsters = 10;

int (build_monsters)(int start_x, int start_y, const basic_sprite_t *sprite){
    for(int i = 0; i < n_monsters; i++){
        struct monster m;
        monsters[i] = m;
        m.id = i;
        m.x = start_x;
        m.y = start_y;
        m.xspeed = 0;
        m.yspeed = 0;
        m.alive = 1;
        m.monster_sprite = sprite_ctor(sprite);
    }
    return 0; 
}

void (draw_monsters)(){
    for(int i = 0; i < n_monsters; i++){
        struct monster monster = monsters[i];
        if(monster.alive){
            sprite_set_pos(monster.monster_sprite, monster.x, monster.y);
            sprite_draw(monster.monster_sprite);
        }
    }

}

void (update_monster_pos)(struct map map){
    for(int i = 0; i < n_monsters; i++){
        struct monster monster = monsters[i];
        if(monster.alive){
            int rand_x = rand() % 3;
            int rand_y = rand() % 3;
            if(rand_x == 2) rand_x = -1;
            if(rand_y == 2) rand_y = -1;
            int x = monster.x;
            int y = monster.y;
            monster.x = monster.x + monster.xspeed * rand() % 3;
            monster.y = monster.y + monster.yspeed * rand() % 3;
            if(collision_monster_wall(map, monster)){
                monster.x = x;
                monster.y = y;
            }
            for(int j = 0; j < n_bullets; i++){
                struct bullet bullet = bullets[j];
                if(bullet.fired && collision_bullet_monster(monster, bullet)){
                    bullet.fired = 0;
                    monster.alive = 0;
                    break;
                }
            }
        }
    }
}

int (collision_monster_wall)(struct map map, struct monster monster) {
    double radius = fmax(sprite_get_w(monster.monster_sprite), sprite_get_h(monster.monster_sprite))/2.0;
    for (double x = -radius; x <= radius; x += 1) {
        double y_pos = sqrt(radius*radius - x*x);
        double y_neg = -y_pos;
        if (wall_collision(map, monster.x + x, monster.y + y_pos) || wall_collision(map, monster.x + x, monster.y + y_neg)) return 1;
    }
    return 0;
}

//Bullet

int n_bullets = 10;

int (build_bullets)(int start_x, int start_y, const basic_sprite_t *sprite){
    for(int i = 0; i < n_bullets; i++){
        struct bullet b;
        bullets[i] = b;
        b.id = i;
        b.x = start_x;
        b.y = start_y;
        b.xspeed = 0;
        b.yspeed = 0;
        b.fired = 0;
        b.bullet_sprite = sprite_ctor(sprite);
    }
    return 0; 
}

void (draw_bullets)(){
    for(int i = 0; i < n_bullets; i++){
        struct bullet bullet = bullets[i];
        if(bullet.fired){
            sprite_set_pos(bullet.bullet_sprite, bullet.x, bullet.y);
            sprite_draw(bullet.bullet_sprite);
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
            for(int j = 0; j < n_monsters; i++){
                struct monster monster = monsters[j];
                if(monster.alive && collision_bullet_monster(monster, bullet)){
                    bullet.fired = 0;
                    monster.alive = 0;
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

int (collision_bullet_monster)(struct monster monster, struct bullet bullet) {
    double bullet_radius = fmax(sprite_get_w(bullet.bullet_sprite), sprite_get_h(bullet.bullet_sprite))/2.0;
    double monster_radius = fmax(sprite_get_w(monster.monster_sprite), sprite_get_h(monster.monster_sprite))/2.0;
    double distance_x = monster.x - bullet.x;
    double distance_y = monster.y - bullet.y;
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
