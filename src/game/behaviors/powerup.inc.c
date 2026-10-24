//custom fire flower by gembai


#define POWERUP_WAIT 0
#define POWERUP_TRANSFORM 1
#define POWERUP_TIMER 2
#define POWERUP_END 3
#define POWERUP_END_TRANSFORM 4
#define POWERUP_FREEZED 10 


#define POWERUP_PROPELLER_INDEX 5

void bhv_propeller_shroom_loop(void) {

    if (o->oAction == POWERUP_FREEZED){
        return;
    }

    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x150);

    //RETURN NORMAL MARIO AFTER 
    if (gMarioState->action == ACT_STAR_DANCE_EXIT || 
                gMarioState->action == ACT_STAR_DANCE_NO_EXIT || 
                    gMarioState->action == ACT_STAR_DANCE_WATER ||
                        gMarioState->action == ACT_FALL_AFTER_STAR_GRAB) {
            gMarioState->powerupState = 0;
    }

    switch (o->oAction) {

        case POWERUP_WAIT:  
            if (obj_check_if_collided_with_object(o, gMarioObject)) {
                play_sound(SOUND_MARIO_HERE_WE_GO, gGlobalSoundSource);
                gMarioState->powerupState = POWERUP_PROPELLER_INDEX;
                cur_obj_become_intangible();
                cur_obj_disable_rendering();
                o->oAction = POWERUP_TRANSFORM;
               // play_cap_music(SEQUENCE_ARGS(4, SEQ_EVENT_FIRE_MARIO)); //no music :p
                play_sound(SOUND_MENU_EXIT_PIPE, gGlobalSoundSource);

            }
            break;        

        case POWERUP_TRANSFORM:  
            //FLICKERS BEETWEEN 0 AND INDEX
            if (o->oTimer % 4 == 0) {
            if (gMarioState->powerupState == POWERUP_PROPELLER_INDEX) {
                gMarioState->powerupState = 0;
                } else {
                    gMarioState->powerupState = POWERUP_PROPELLER_INDEX;
                }
            }

            if (o->oTimer > 25) { // (30 frames) aprox
                o->oAction = POWERUP_TIMER;
                gMarioState->powerupState = POWERUP_PROPELLER_INDEX;
                
            }
            break;      

        case POWERUP_TIMER:  
            //DO NOTHING
            break;   


    }


}