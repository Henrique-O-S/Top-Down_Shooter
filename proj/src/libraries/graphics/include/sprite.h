#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#define ALPHA_THRESHOLD 0x7F

typedef struct basic_sprite basic_sprite_t;
typedef struct sprite sprite_t;

/// BASIC SPRITE

basic_sprite_t* (basic_sprite_ctor)(const char *const *xpm, int16_t u0, int16_t v0);

void            (basic_sprite_dtor)(basic_sprite_t *p);

const uint8_t* (basic_sprite_get_map)(const basic_sprite_t *p);

uint16_t       (basic_sprite_get_w)  (const basic_sprite_t *p);

uint16_t       (basic_sprite_get_h)  (const basic_sprite_t *p);

int16_t        (basic_sprite_get_u0) (const basic_sprite_t *p);

int16_t        (basic_sprite_get_v0) (const basic_sprite_t *p);

/// SPRITE

sprite_t* (sprite_ctor)(const basic_sprite_t *bsp);

void (sprite_dtor)(sprite_t *p);

void (sprite_set_pos)   (sprite_t *p, int16_t x, int16_t y);

void (sprite_set_angle) (sprite_t *p, double angle);

void (sprite_set_scale) (sprite_t *p, double scale);

double   (sprite_get_angle)(const sprite_t *p);

uint16_t (sprite_get_w)(const sprite_t *p);

uint16_t (sprite_get_h)(const sprite_t *p);

void (sprite_draw)(const sprite_t *p);

#endif //SPRITE_H_INCLUDED
