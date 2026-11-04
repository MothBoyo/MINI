#ifndef SHOPKEEPER_MENU_H
#define SHOPKEEPER_MENU_H

#include "types.h"

enum ShopkeeperMenuResult {
    SHOP_NONE,
    SHOP_EXCHANGE,
    SHOP_EXPLAIN,
    SHOP_BYE,
};

extern s8 gShopkeeperMenuActive;

void shopkeeper_menu_open(void);
void shopkeeper_menu_close(void);
void shopkeeper_menu_hide(void); //hide text while dialgo or star
void shopkeeper_menu_show(void); //show again
s32  shopkeeper_menu_update(void); //return ShopkeeperMenuResult for case
void shopkeeper_menu_render(void);

#endif