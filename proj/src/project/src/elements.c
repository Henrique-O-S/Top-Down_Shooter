#include <lcom/lcf.h>

#include "elements.h"
#include <stdio.h>
#include <math.h>

//Player

int build_player(int start_x, int start_y, xpm_map_t sprite){
    p.x = start_x;
    p.y = start_y;
    p.xspeed = 0;
    p.yspeed = 0;
    xpm_image_t img;
    xpm_load(sprite, XPM_8_8_8, &img);
    p.img = img;
    p.player_sprite = sprite_ctor(sprite);

    return 0; 
}

void draw_player(){

}

void update_player_pos(){
    
}

int collision_player_wall(){
    return 0;
}

//Monster

int n_monsters = 10;

int build_monsters(int start_x, int start_y, xpm_map_t sprite){
    for(int i = 0; i < n_monsters; i++){
        struct monster m;
        monsters[i] = m;
        m.id = i;
        m.x = start_x;
        m.y = start_y;
        m.xspeed = 0;
        m.yspeed = 0;
        m.alive = 1;
        xpm_image_t img;
        xpm_load(sprite, XPM_8_8_8, &img);
        m.img = img;
        m.monster_sprite = sprite_ctor(sprite);
    }
    return 0; 
}

void draw_monsters(){
    for(int i = 0; i< n_monsters; i++){
        struct monster monster = monsters[i];
        if(monster.alive){
            //sprite_t *m = sprite_ctor(monsters[i].img);
            sprite_set_pos(monster.monster_sprite, monsters[i].x, monsters[i].y);
            sprite_draw(monster.monster_sprite);
        }
    }

}

void update_monster_pos(struct map map){
    for(int i = 0; i< n_monsters; i++){
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
                monsters[i].x = x;
                monsters[i].y = y;
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

//Wall

int (wall_collision)(struct map map, int x, int y){
    const int w = sprite_get_w(map.background), h = sprite_get_h(map.background);
    if(x < 0 || w <= x || y < 0 || h <= y) return 0;
    int32_t pos = x + y * w;
    if(0 <= pos && pos < w * h) return 1;
    else return 0;
}
