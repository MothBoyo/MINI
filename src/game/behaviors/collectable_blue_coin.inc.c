static struct ObjectHitbox sCollectBlueCoinHitbox = {
    /* interactType:      */ INTERACT_COIN,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 15,
    /* numLootCoins:      */ 0,
    /* radius:            */ 80,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

#define COIN_MODE_IDLE 0
#define COIN_MODE_DIALOG 1
#define COIN_MODE_FINISH 2

void bhv_collect_blue_coin_init(void) {

    //where in the array should look
    u8 CoinActId = GET_BPARAM1(o->oBehParams);
    //in which array should look (0, 1 or 2)
    u8 CoinRowId = GET_BPARAM2(o->oBehParams);


        u8 currentLevelStarFlags = save_file_get_blue_coins_flags((gCurrSaveFileNum - 1), COURSE_NUM_TO_INDEX(gCurrCourseNum), CoinRowId);
        if (currentLevelStarFlags & (1 << CoinActId)) {

            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_GRAY_COIN]; //change Models
        } else {
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BLUE_COIN]; //change Models
        }
    

    obj_set_hitbox(o, &sCollectBlueCoinHitbox);
}


void bhv_collect_blue_coin_loop(void) {
    //o->oFaceAngleYaw += 0x800;
    s16 response;
    o->oAnimState++;

    switch (o->oAction) {
        case COIN_MODE_IDLE: 
                if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                //load row
                u8 CoinActId = GET_BPARAM1(o->oBehParams);
                u8 CoinRowId = GET_BPARAM2(o->oBehParams);

                //save in current file
                save_file_set_blue_coins_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(gCurrCourseNum), (1 << CoinActId), CoinRowId);
                cur_obj_play_sound_2(SOUND_MENU_STAR_SOUND_LETS_A_GO);
                spawn_object(o, MODEL_SPARKLES, bhvCoinSparklesSpawner); 

                //dialog per coin
                cur_obj_hide();

                o->oAction = COIN_MODE_DIALOG; 
                o->oInteractStatus = INT_STATUS_NONE;
            }
            break;    

        case COIN_MODE_DIALOG: 
                {
                if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT) == MARIO_DIALOG_STATUS_SPEAK) {
                o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
                
                //YES NO
                response = obj_update_race_proposition_dialog(DIALOG_002);

                    if (response != DIALOG_RESPONSE_NONE) {
                        if (response == DIALOG_RESPONSE_YES) {
                            save_file_do_save(gCurrSaveFileNum - 1);
                            cur_obj_play_sound_2(SOUND_GENERAL_ACTIVATE_CAP_SWITCH);
                            set_mario_npc_dialog(MARIO_DIALOG_STOP);
                            o->oAction = COIN_MODE_FINISH;  
                        } else if (response == DIALOG_RESPONSE_NO) {
                            cur_obj_play_sound_2(SOUND_OBJ_KOOPA_FLYGUY_DEATH);
                            o->oAction = COIN_MODE_FINISH;  
                        }
                        
                    }
                }
                break;
                }

        case COIN_MODE_FINISH: 
            cur_obj_hide();

            break;
    }
}


//will determine it's model and if should exist based on a table (not really?)
void bhv_star_select_blue_coin_loop(void) {
    o->oAnimState++;
    cur_obj_scale(0.65f);
}