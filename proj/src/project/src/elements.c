#include <lcom/lcf.h>

#include "elements.h"
#include "walls.h"
#include "map.h"
#include <stdio.h>
#include <math.h>


static int spawn_coordinate_x[4] = {90,50,950,960};
static int spawn_coordinate_y[4] = {100,500,50,720};

static int house_coordinate_x[4] = {630,135,920,950};
static int house_coordinate_y[4] = {195,500,460,600};

static int house_coordinate_x2[4] = {650,650,650,650};
static int house_coordinate_y2[4] = {520,520,520,520};

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
    p.shot_cooldown = SHOT_COOLDOWN;
    p.cur_cooldown = 2;
    p.alive = 1;
    p.health = 3;
    p.player_idle = sprite_ctor(idle, 20);
    p.player_shooting = sprite_ctor(shooting, 3);
    p.wait = 0;
    p.wait_threshold = 3;
    p.kills = 0;
    return 0; 
}

void (despawn_player)(void) {
    p.x = PLAYER_SPAWN_X; p.y = PLAYER_SPAWN_Y;
    p.health = 3;
    p.alive = 1;
    p.cur_cooldown = 2;
    p.kills = 0;
}

void (draw_player)(){
    if(p.alive){
        if(p.wait > 0) {
            p.wait--;
            sprite_set_pos(p.player_shooting, p.x, p.y);
            sprite_set_angle(p.player_shooting, get_mouse_angle(p.player_shooting));
            sprite_draw(p.player_shooting);
            sprite_update_animation(p.player_shooting, 0);
        }
        else {
            sprite_set_pos(p.player_idle, p.x, p.y);
            sprite_set_angle(p.player_idle, get_mouse_angle(p.player_idle));
            sprite_draw(p.player_idle);
            sprite_update_animation(p.player_idle, 0);
        }
    }
}

void (update_player)(keys_t *keys) {
    p.yMov = keys->s_pressed - keys->w_pressed;
    p.xMov = keys->d_pressed - keys->a_pressed;
    update_player_pos();

    if(keys->lb_pressed && p.cur_cooldown == 0) {
        p.wait = p.wait_threshold;
        spawn_bullet();
        p.cur_cooldown = p.shot_cooldown;
    }
}

void (update_player_pos)(){
    if(p.alive){
        //player inputs
        int x0 = p.x, y0 = p.y;
        int x = p.x + (p.speed * p.xMov);
        int y = p.y + (p.speed * p.yMov);
        if(collision_player_wall(p, -PLAYER_SPEED*2)){
            p.x = x;
            p.y = y;
            if(collision_player_wall(p, -PLAYER_SPEED*3)) {
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
            if(enemies[i].alive && collision_player_enemy(enemies[i], p) && enemies[i].wait == 7){
                
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

int (get_enemies_alive)() {
    int r = 0;
    for(int i = 0; i < n_enemies; i++) {
        if(enemies[i].alive) r++;
    }
    return r;
}

int (collision_player_enemy)(enemy_t enemy, player_t player) {
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

int (player_get_kills)(void) {
    return p.kills;
}

int (player_get_health)(void) {
    return p.health;
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

int (in_range_of_player)(enemy_t enemy) {
    int x = abs(enemy.x - p.x);
    int y = abs(enemy.y - p.y);

    return sqrt(x*x +y*y);
}

void (tick_cooldown)(){
    if(p.cur_cooldown > 0) p.cur_cooldown--;
}

double get_angle(enemy_t e) {
    return atan2(e.y - e.y_entrance, e.x_entrance - e.x);
}

double get_angle_to_player(enemy_t e) {
    return atan2(e.y - p.y, p.x - e.x);
}

double get_angle_two_points(int x, int y, int x1, int y1) {
    return atan2(y - y1, x1 - x);
}

int get_distance(enemy_t e) {
    double distance_x = e.x - e.x_entrance;
    double distance_y = e.y - e.y_entrance;
    double radius = sqrt(distance_x * distance_x + distance_y * distance_y);
    return (radius < 15 ? 1 : 0);
}

//Enemy

int n_enemies = 4;

int (build_enemies)(basic_sprite_t **idle,  basic_sprite_t **attacking) {
    for(int i = 0; i < n_enemies; i++){
        enemy_t m;
        m.id = i;
        m.spawn_point = i;
        m.x = 0.0;
        m.y = 0.0;
        m.speed = ENEMY_SPEED;
        m.x_entrance = 0;
        m.y_entrance = 0;
        m.alive = 0;
        m.in_house = 0;
        m.angle = 0;
        m.enemy_idle = sprite_ctor(idle, 20);
        m.enemy_attacking = sprite_ctor(attacking, 15);
        m.wait = 0;
        m.wait_threshold = 15;
        enemies[i] = m;

    }
    return 0; 
}

void (draw_enemies)() {
    for(int i = 0; i < n_enemies; i++){
        if(enemies[i].alive){
            
        
            if(enemies[i].wait > 0) {
                enemies[i].wait--;
                sprite_set_pos(enemies[i].enemy_attacking, enemies[i].x, enemies[i].y);
                sprite_set_angle(enemies[i].enemy_attacking, enemies[i].angle);
                sprite_draw(enemies[i].enemy_attacking);
                sprite_update_animation(enemies[i].enemy_attacking, 0);
            }
            else {
                sprite_set_pos(enemies[i].enemy_idle, enemies[i].x, enemies[i].y);
                sprite_set_angle(enemies[i].enemy_idle, enemies[i].angle);
                sprite_draw(enemies[i].enemy_idle);
                sprite_update_animation(enemies[i].enemy_idle, 0);
            }
            
        }
    }
}

void (spawn_enemies)(void) {
    for(int i = 0; i < n_enemies; i++){
        if(!enemies[i].alive) {
            enemies[i].alive = 1;
            enemies[i].x = spawn_coordinate_x[enemies[i].spawn_point];
            enemies[i].y = spawn_coordinate_y[enemies[i].spawn_point];
            enemies[i].x_entrance = house_coordinate_x[enemies[i].spawn_point];
            enemies[i].y_entrance = house_coordinate_y[enemies[i].spawn_point];

            enemies[i].angle = get_angle(enemies[i]);
            enemies[i].c = cos(enemies[i].angle);
            enemies[i].s = -sin(enemies[i].angle);

            enemies[i].in_house = 0;
            enemies[i].in_house2 = 0;
        }
    }
}

void (despawn_enemies)(void) {
    for(int i = 0; i < n_enemies; i++){
        if(enemies[i].alive) {
            enemies[i].alive = 0;
            enemies[i].x = spawn_coordinate_x[enemies[i].spawn_point];
            enemies[i].y = spawn_coordinate_y[enemies[i].spawn_point];
            enemies[i].in_house = 0;
        }
    }
}

void (update_enemy_pos)(){
    for(int i = 0; i < n_enemies; i++){
        if(enemies[i].alive){
            int x0 = enemies[i].x;
            int y0 = enemies[i].y;
            int range =in_range_of_player(enemies[i]);
            if(range < DISTANCE_THRESHOLD && !in_sight_of_player(enemies[i])) {
                enemies[i].angle = get_angle_to_player(enemies[i]);
                enemies[i].c = cos(enemies[i].angle);
                enemies[i].s = -sin(enemies[i].angle);
                enemies[i].x += enemies[i].speed*enemies[i].c;
                enemies[i].y += enemies[i].speed*enemies[i].s;
                
                // for animation
                if(!enemies[i].wait && range < ATTACK_THRESHOLD) enemies[i].wait = enemies[i].wait_threshold;
            }
            else {
                if(!enemies[i].in_house && !enemies[i].in_house2) enemies[i].in_house = get_distance(enemies[i]);
                if(!enemies[i].in_house && !enemies[i].in_house2) {
                    enemies[i].x += enemies[i].c * enemies[i].speed;
                    enemies[i].y += enemies[i].s * enemies[i].speed;
                }
                else {
                    if(!enemies[i].in_house2) {
                        enemies[i].x_entrance = house_coordinate_x2[enemies[i].spawn_point];
                        enemies[i].y_entrance = house_coordinate_y2[enemies[i].spawn_point];
                        enemies[i].angle = get_angle(enemies[i]);
                        enemies[i].c = cos(enemies[i].angle);
                        enemies[i].s = -sin(enemies[i].angle);
                        enemies[i].in_house2 = 1;
                    }

                    enemies[i].in_house = get_distance(enemies[i]);
                    if(!enemies[i].in_house) {
                        enemies[i].x += enemies[i].c * enemies[i].speed;
                        enemies[i].y += enemies[i].s * enemies[i].speed;
                    }
                    else {
                        ;
                    }
                }              
            }

            if(collision_enemy_wall(enemies[i], -30)){
                enemies[i].x = x0;
                enemies[i].y = y0;
            }

            ret_pair_t r = is_border(enemies[i].x, enemies[i].y);
                if(!r.x) enemies[i].x = x0;
                if(!r.y) enemies[i].y = y0;
        }
    }
}

int (in_sight_of_player)(enemy_t enemy) {
    int x_e, y_e, x_p, y_p;
    x_e = (int)enemy.x;
    y_e = (int)enemy.y;
    x_p = (int)p.x;
    y_p = (int)p.y;

    double distance_x = enemy.x - (double)p.x;
    double distance_y = enemy.y - (double)p.y;

    double distance = sqrt(distance_x*distance_x + distance_y*distance_y);
    double angle = get_angle_two_points(x_e, y_e, x_p, y_p);
    double c = cos(angle), s = -sin(angle);

    for(double i = 0; i <= distance; i+=10) {
        if(wall_collision(x_e + c*i, y_e + s*i)) return 1;
    }
    
    return 0;
}

int (collision_enemy_wall)( enemy_t enemy, int threshold) {
    double radius = fmax(sprite_get_w(enemy.enemy_idle), sprite_get_h(enemy.enemy_idle))/7.0;
    radius += threshold;
    for (double x = -radius; x <= radius; x += 1) {
        double y_pos = sqrt(radius*radius - x*x);
        double y_neg = -y_pos;
        if (wall_collision(enemy.x + x, enemy.y + y_pos) || wall_collision(enemy.x + x, enemy.y + y_neg)) return 1;
    }
    return 0;
}

//Bullet

int n_bullets = 5;

int (build_bullets)(int start_x, int start_y, basic_sprite_t **sprite){
    for(int i = 0; i < n_bullets; i++){
        bullet_t b;
        b.id = i;
        b.x = start_x;
        b.y = start_y;
        b.angle = 0.0;
        b.fired = false;
        b.speed = BULLET_SPEED;
        b.wait = 0;
        b.wait_threshold =3;
        b.c = 0.0; b.s = 0.0;
        b.bullet_sprite = sprite_ctor(sprite, 3);
        bullets[i] = b;
    }
    return 0; 
}

void (spawn_bullet)(void) {

     for(int i = 0; i < n_bullets; i++){
        if(!bullets[i].fired) {
            bullets[i].fired = true;
            bullets[i].angle = get_mouse_angle(p.player_idle);
            bullets[i].c = cos(bullets[i].angle); 
            bullets[i].s = -sin(bullets[i].angle);
            bullets[i].x = p.x;
            bullets[i].y = p.y;
            sprite_set_angle(bullets[i].bullet_sprite, bullets[i].angle);
            break;
        }
     }
    
}

void despawn_bullets(void) {
    for(int i = 0; i < n_bullets; i++){
        if(bullets[i].fired) {
            bullets[i].fired = 0;
        }
    }
}

void (draw_bullets)(){
    for(int i = 0; i < n_bullets; i++){
        bullets[i].wait++;
        if(bullets[i].fired && bullets[i].wait > bullets[i].wait_threshold){
            sprite_set_pos(bullets[i].bullet_sprite, (int)bullets[i].x, (int)bullets[i].y);
            sprite_draw(bullets[i].bullet_sprite);
            sprite_update_animation(bullets[i].bullet_sprite, 0);
        }
    }

}

void (update_bullet_pos)(){
    for(int i = 0; i < n_bullets; i++){
        if(bullets[i].fired){
            //bullet direction should be worked out here
            bullets[i].x += (bullets[i].c * bullets[i].speed);
            bullets[i].y += (bullets[i].s * bullets[i].speed);

            ret_pair_t r = is_border(bullets[i].x, bullets[i].y);
            if(!r.x || !r.y) {
                bullets[i].fired = 0;
                bullets[i].wait = 0;
            }

            
            if(collision_bullet_wall(bullets[i])){
                bullets[i].fired = 0;
                bullets[i].wait = 0;
            }
             //NEEDS TO BE FIXED
            for(int j = 0; j < n_enemies; j++){
                if(enemies[j].alive){
                    if(collision_bullet_enemy(enemies[j], bullets[i])) {
                        p.kills++;
                        bullets[i].fired = 0;
                        bullets[i].wait = 0;
                        enemies[j].alive = 0;
                        break;
                    } 
                } 
            }
        }
    }
}

int (collision_bullet_wall)(bullet_t bullet) {
    double radius = fmax(sprite_get_w(bullet.bullet_sprite), sprite_get_h(bullet.bullet_sprite))/2.0;
    for (double x = -radius; x <= radius; x += 1) {
        double y_pos = sqrt(radius*radius - x*x);
        double y_neg = -y_pos;
        if (wall_collision(bullet.x + x, bullet.y + y_pos) || wall_collision(bullet.x + x, bullet.y + y_neg)) return 1;
    }
    return 0;
}

int (collision_bullet_enemy)(enemy_t enemy, bullet_t bullet) {
    double bullet_radius = fmax(sprite_get_w(bullet.bullet_sprite), sprite_get_h(bullet.bullet_sprite))/2.0;
    double monster_radius = fmax(sprite_get_w(enemy.enemy_idle), sprite_get_h(enemy.enemy_idle))/4.0;
    double distance_x = enemy.x - bullet.x;
    double distance_y = enemy.y - bullet.y;
    double radius = sqrt(distance_x * distance_x + distance_y * distance_y);
    return radius <= monster_radius + bullet_radius;
}

//Wall

int (wall_collision)(int x, int y){
    const int w = sprite_get_w(map.background), h = sprite_get_h(map.background);
    if(x < 0 || w <= x || y < 0 || h <= y) return 0;
    int32_t pos = x + y * w;
    if(0 <= pos && pos < w * h) return map.walls[pos];
    else return 0;
}

