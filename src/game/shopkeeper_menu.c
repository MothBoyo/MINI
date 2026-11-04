#include <PR/ultratypes.h>
#include "sm64.h"
#include "gfx_dimensions.h"
#include "game_init.h"
#include "ingame_menu.h"
#include "segment2.h"
#include "audio/external.h"
#include "text_strings.h"
#include "shopkeeper_menu.h"


#define SHOP_BOX_X 10.0f
#define SHOP_BOX_Y 200.0f
#define SHOP_BOX_W 175.0f
#define SHOP_BOX_H 100.0f
#define SHOP_BOX_ALPHA 150

#define SHOP_TITLE_X 16
#define SHOP_TITLE_Y 183
#define SHOP_OPTION_X 28
#define SHOP_OPTION_Y 147 //start
#define SHOP_OPTION_STEP 18
#define SHOP_CURSOR_X 20
#define SHOP_NUM_OPTIONS 3

//x pos of text fabricated, not an actual text
#define SHOP_PRICE_OPEN_X  (SHOP_OPTION_X + 100 - 20)
#define SHOP_PRICE_COINS_X (SHOP_OPTION_X + 106- 20)
#define SHOP_PRICE_EQ_X    (SHOP_OPTION_X + 130 - 12)
#define SHOP_PRICE_STAR_X  (SHOP_OPTION_X + 142 -12)
#define SHOP_PRICE_CLOSE_X (SHOP_OPTION_X + 158-12)

static u8 sTxtTitle[]    = { TEXT_SHOP_TITLE }; //title of text
static u8 sTxtExchange[] = { TEXT_SHOP_EXCHANGE }; //exchange text
static u8 sTxtExplain[]  = { TEXT_SHOP_EXPLAIN }; //explain me how to 
static u8 sTxtBye[]      = { TEXT_SHOP_BYE }; //end text
static u8 sTxtPOpen[]    = { TEXT_SHOP_PRICE_OPEN }; // (
static u8 sTxtPCoins[]   = { TEXT_SHOP_PRICE_COINS }; //10$
static u8 sTxtPEqual[]      = { TEXT_SHOP_PRICE_EQUAL }; // = ((equal = is cuz idk compiler shit))
static u8 sTxtPStar[]    = { TEXT_SHOP_PRICE_STAR }; // 1*
static u8 sTxtPClose[]   = { TEXT_SHOP_PRICE_CLOSE }; // ) 

static u8 *const sShopOptions[SHOP_NUM_OPTIONS] = { sTxtExchange, sTxtExplain, sTxtBye };

s8 gShopkeeperMenuActive = FALSE;

static s8 sShopIdx;
static u8 sShopVisible;
static u8 sShopOpen;

void shopkeeper_menu_open(void) {
    sShopIdx = 0;
    sShopVisible = TRUE;
    sShopOpen = TRUE;
    gShopkeeperMenuActive = TRUE;
}

void shopkeeper_menu_close(void) {
    sShopOpen = FALSE;
    sShopVisible = FALSE;
    gShopkeeperMenuActive = FALSE;
}

void shopkeeper_menu_hide(void) {
    sShopVisible = FALSE; 
}

void shopkeeper_menu_show(void) {
    sShopVisible = TRUE;
}

s32 shopkeeper_menu_update(void) {
    if (!sShopOpen || !sShopVisible) {
        return SHOP_NONE;
    }
    handle_menu_scrolling(MENU_SCROLL_VERTICAL, &sShopIdx, 0, SHOP_NUM_OPTIONS - 1);

    if (gPlayer1Controller->buttonPressed & (A_BUTTON | START_BUTTON | B_BUTTON)) {
        play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
        return SHOP_EXCHANGE + sShopIdx;   // 0,1,2 == EXCHANGE, EXPLAIN, BYE
    }
    return SHOP_NONE;
}

static void shop_print(s16 x, s16 y, u8 *str, u8 r, u8 g, u8 b) {
    gDPSetEnvColor(gDisplayListHead++, r, g, b, 255);
    print_generic_string(x, y, str);
}

void shopkeeper_menu_render(void) {

    s32 i;
    if (!sShopOpen || !sShopVisible) return;

    //TRANSLUCID Plback block copied form vawvilla
    create_dl_translation_matrix(MENU_MTX_PUSH, SHOP_BOX_X, SHOP_BOX_Y, 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, SHOP_BOX_W / 130.0f, SHOP_BOX_H / 80.0f, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, SHOP_BOX_ALPHA);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    //text
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    shop_print(SHOP_TITLE_X, SHOP_TITLE_Y, sTxtTitle, 255, 255, 255);
    for (i = 0; i < SHOP_NUM_OPTIONS; i++) {
        shop_print(SHOP_OPTION_X, SHOP_OPTION_Y - i * SHOP_OPTION_STEP, sShopOptions[i], 255, 255, 255);
    }
    //price ( 10$ = 1☆ ) glyphs
    shop_print(SHOP_PRICE_OPEN_X,  SHOP_OPTION_Y, sTxtPOpen, 255, 255, 255);
    shop_print(SHOP_PRICE_COINS_X, SHOP_OPTION_Y, sTxtPCoins, 60, 120, 255);
    shop_print(SHOP_PRICE_EQ_X,    SHOP_OPTION_Y, sTxtPEqual, 255, 255, 255);
    shop_print(SHOP_PRICE_STAR_X,  SHOP_OPTION_Y, sTxtPStar, 255, 230,  40);
    shop_print(SHOP_PRICE_CLOSE_X, SHOP_OPTION_Y, sTxtPClose, 255, 255, 255);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

    //Triangulum, entangulum. Veneforis dominus ventium. Veneforis venetisarium 
    create_dl_translation_matrix(MENU_MTX_PUSH, SHOP_CURSOR_X - 2 , SHOP_OPTION_Y - sShopIdx * SHOP_OPTION_STEP, 0);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}