#include <lcom/lcf.h>

#include "main_menu.h"

struct main_menu {
    size_t sz;
    rectangle_t **r;
    text_t ** t;s
    rectangle_t *frame;
}

menu_t* (menu_ctor)(const font_t *fnt) {
    menu_t *ret = (menu_t *) malloc(sizeof(menu_t));
    ret->sz = 0;
    ret->r = NULL;
    ret->t = NULL;
    return ret;
}




