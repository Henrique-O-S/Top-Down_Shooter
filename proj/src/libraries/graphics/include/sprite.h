#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

/**
 * @defgroup sprite sprite
 * @ingroup libraries
 *
 * @{
 */


#include <stdint.h>


#define ALPHA_THRESHOLD 0x7F

/**
 * @brief Basic sprite that contains a xpm map and offset values to center it
 * @param map xpm map vector
 * @param w width of the map
 * @param h height of the map
 * @param x_offset offset value for the x axis
 * @param y_offset offset value for the y axis
 */
struct basic_sprite{
    uint8_t *map;
    uint16_t w, h;
    int16_t x_offset, y_offset;
};
typedef struct basic_sprite basic_sprite_t;

/**
 * @brief Basic sprite that contains a xpm map and offset values to center it
 * @param bsp array of basic sprites
 * @param current_animation current basic sprite in use
 * @param animation number of basic sprites
 * @param current_wait current wait value
 * @param wait wait value between animations
 * @param x position in the x axis
 * @param y position in the y axis
 * @param angle angle to be used for the basic sprites (0-2PI)
 * @param c cos value for the angle
 * @param s sin value for the angle
 */
struct sprite{
    basic_sprite_t **bsp;
    uint8_t current_animation, animation, current_wait, wait;
    int16_t x, y, x_offset, y_offset; //position in screen
    double angle, s, c;
};


typedef struct sprite sprite_t;

/// BASIC SPRITE


/**
 * @brief Basic sprite constructor that maps xpm into memory
 * @param xpm xpm map to be loaded
 * @param x_offset offset value for the x axis
 * @param y_offset offset value for the y axis
 * @return constructed basic sprite
 */
basic_sprite_t* (basic_sprite_ctor)(const char *const *xpm, int16_t x_offset, int16_t y_offset);

/**
 * @brief Basic sprite destructor that frees mapped memory
 *  @param p basic sprite to be freed
 */
void            (basic_sprite_dtor)(basic_sprite_t *p);

/**
 * @brief Gets xpm map from basic sprite
 * @param p basic sprite
 * @return xpm map
 */
const uint8_t* (basic_sprite_get_map)(const basic_sprite_t *p);

/**
 * @brief Gets xpm map width
 * @param p basic sprite
 * @return map width
 */
uint16_t       (basic_sprite_get_w)  (const basic_sprite_t *p);

/**
 * @brief Gets xpm map height
 * @param p basic sprite
 * @return map height
 */
uint16_t       (basic_sprite_get_h)  (const basic_sprite_t *p);

/**
 * @brief Gets xpm map x_offset
 * @param p basic sprite
 * 
 */
int16_t        (basic_sprite_get_x_offset) (const basic_sprite_t *p);

/**
 * @brief Gets xpm map y_offset
 * @param p basic sprite
 * 
 */
int16_t        (basic_sprite_get_y_offset) (const basic_sprite_t *p);

/// SPRITE

/**
 * @brief Sprite constructor that contains multiple basic sprite
 * @param bsp array of basic sprites
 * @param animation number of animations
 * @return constructed sprite
 */
sprite_t* (sprite_ctor)(basic_sprite_t **bsp, uint8_t animation);

/**
 * @brief Sprite destructor that frees mapped memory
 *  @param p Sprite to be freed
 */
void (sprite_dtor)(sprite_t *p);

/**
 * @brief Sets sprite position in screen
 * @param p sprite
 * @param x position in the x axis
 * @param y position in the y axis
 */
void (sprite_set_pos)   (sprite_t *p, int16_t x, int16_t y);

/**
 * @brief Sets sprite angle
 * @param p sprite
 * @param angle angle of the sprite
 */
void (sprite_set_angle) (sprite_t *p, double angle);

/**
 * @brief Gets sprite angle
 * @param p sprite
 * @return sprite angle
 */
double   (sprite_get_angle)(const sprite_t *p);

/**
 * @brief Gets width from default basic sprite
 * @param p sprite
 * @return basic sprite width
 */
uint16_t (sprite_get_w)(const sprite_t *p);

/**
 * @brief Gets height from default basic sprite
 * @param p sprite
 * @return basic sprite height
 */
uint16_t (sprite_get_h)(const sprite_t *p);

/**
 * @brief Gets horizontal value from sprite
 * @param p sprite
 * @return sprite horizontal value
 */
uint16_t (sprite_get_X)(const sprite_t *p);

/**
 * @brief Gets vertical value from sprite
 * @param p sprite
 * @return sprite vertical value
 */
uint16_t (sprite_get_Y)(const sprite_t *p);

/**
 * @brief Gets angle value between two sprites 
 * @param p main sprite
 * @param p1 target sprite
 * @return angle 
 */
double (sprite_angle_of_two)(const sprite_t *p, const sprite_t *p1);

/**
 * @brief Draws sprite into double buffer 
 * @param p main sprite
 */
void (sprite_draw)(const sprite_t *p);

/**
 * @brief Updates sprite animation into the next one
 * @param p main sprite
 * @param reset if 0, continues animation, otherwise resets into the first animation
 */
void (sprite_update_animation) (sprite_t *p, int reset);

/**
 * @brief Updates sprite animation into the indicated one
 * @param p main sprite
 * @param animation animation to be choosen
 */
void (sprite_choose_animation) (sprite_t *p, int animation);

/**
 * @}
 */

#endif //SPRITE_H_INCLUDED
