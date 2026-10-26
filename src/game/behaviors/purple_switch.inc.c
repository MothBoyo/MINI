
/**
 * Behavior for bhvFloorSwitchHardcodedModel, bhvFloorSwitchGrills, and
 * bhvFloorSwitchAnimatesObject.
 *
 * This controls the purple switches that Mario can step on to affect parts of
 * the environment.
 */

void bhv_purple_switch_loop(void) {
    switch (o->oAction) {
        /**
         * Set the switch's model and scale. If Mario is standing near the
         * switch's middle section, transition to the pressed state.
         */

        case PURPLE_SWITCH_ACT_IDLE:

            //cur_obj_set_model(MODEL_PURPLE_SWITCH); 
            cur_obj_scale(1.5f);
            if (
                gMarioObject->platform == o
                && !(gMarioStates[0].action & MARIO_NO_PURPLE_SWITCH)
                && lateral_dist_between_objects(o, gMarioObject) < 127.5f
            ) {
                o->oAction = PURPLE_SWITCH_ACT_PRESSED;
            }
            break;

        /**
         * Collapse the switch downward, play a sound, and shake the screen.
         * Immediately transition to the ticking state.
         */
        case PURPLE_SWITCH_ACT_PRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 1.5f, 0.2f);
            if (o->oTimer == 3) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
                o->oAction = PURPLE_SWITCH_ACT_TICKING;
                cur_obj_shake_screen(SHAKE_POS_SMALL);
                o->oAction = PURPLE_SWITCH_ACT_TICKING;  

            }
            break;

        /**
         * Play a continuous ticking sound that gets faster when time is almost
         * up. When time is up, move to a waiting-while-pressed state.
         */
        case PURPLE_SWITCH_ACT_TICKING:

            //changed condition "not 0" to "1 or 2"
            if (o->oBehParams2ndByte == 2 || o->oBehParams2ndByte == 1) {
                if (o->oBehParams2ndByte == 1 && gMarioObject->platform != o) {
                    o->oAction++;
                } else {
                    if (o->oTimer < 360) {
                        play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gGlobalSoundSource);
                    } else {
                        play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
                    }
                    if (o->oTimer > 400) {
                        o->oAction = PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF;
                    }
                }
            }
            break;

        /**
         * Make the switch look unpressed again, and transition back to the
         * idle state.
         */
        case PURPLE_SWITCH_ACT_UNPRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 0.2f, 1.5f);
            if (o->oTimer == 3) {
                o->oAction = PURPLE_SWITCH_ACT_IDLE;
            }
            break;

        /**
         * Mario is standing on the switch, but time has expired. Wait for
         * him to get off the switch, and when he does so, transition to the
         * unpressed state.
         */
        case PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF:
            if (!cur_obj_is_mario_on_platform()) {
                o->oAction = PURPLE_SWITCH_ACT_UNPRESSED;
            }
            break;
    }
}









#define FLIPSWITCH_BLUE 0
#define FLIPSWITCH_YELLOW 1
#define FLIPSWITCH_GREEN 2


void bhv_flipswitch_init(void) {
    o->parentObj = cur_obj_nearest_object_with_behavior(bhvFlipswitchManager);
}


void bhv_flipswitch_loop(void) {
    switch (o->oAction) {
        /**
         * Set the switch's model and scale. If Mario is standing near the
         * switch's middle section, transition to the pressed state.
         */

        case PURPLE_SWITCH_ACT_IDLE:

            //cur_obj_set_model(MODEL_PURPLE_SWITCH);    
            cur_obj_scale(1.5f);
            if (o->oHealth != FLIPSWITCH_GREEN) {
                if (
                    gMarioObject->platform == o
                    && !(gMarioStates[0].action & MARIO_NO_PURPLE_SWITCH)
                    && lateral_dist_between_objects(o, gMarioObject) < 127.5f
                ) {
                    o->oAction = PURPLE_SWITCH_ACT_PRESSED;
                }
            }
            break;

        /**
         * Collapse the switch downward, play a sound, and shake the screen.
         * Immediately transition to the ticking state.
         */
        case PURPLE_SWITCH_ACT_PRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 1.5f, 0.2f);
            if (o->oTimer == 3) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH); 

                //flipwsith
                switch (o->oHealth) {
                    case FLIPSWITCH_BLUE:
                    o->oHealth = FLIPSWITCH_YELLOW;
                    cur_obj_set_model(MODEL_FLIPSWITCH_YELLOW);    
                    o->parentObj->oAction++; //send signal to parent
                    break;

                    case FLIPSWITCH_YELLOW:
                    o->oHealth = FLIPSWITCH_BLUE;
                    cur_obj_set_model(MODEL_FLIPSWITCH_BLUE);  
                    o->parentObj->oAction--; //send signal to parent
                    break;

                    }

                o->oAction = PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF;
            }
            break;


        /**
         * Make the switch look unpressed again, and transition back to the
         * idle state.
         */
        case PURPLE_SWITCH_ACT_UNPRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 0.2f, 1.5f);
            if (o->oTimer == 3) {
                o->oAction = PURPLE_SWITCH_ACT_IDLE;
            }
            break;

        /**
         * Mario is standing on the switch, but time has expired. Wait for
         * him to get off the switch, and when he does so, transition to the
         * unpressed state.
         */
        case PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF:
            if (!cur_obj_is_mario_on_platform()) {
                o->oAction = PURPLE_SWITCH_ACT_UNPRESSED;
            }
            break;
    }

    //verify
    if (o->parentObj->oAction >= o->parentObj->oHealth) {
        o->oHealth = FLIPSWITCH_GREEN;    
        cur_obj_set_model(MODEL_FLIPSWITCH_GREEN);  
    }    


}


//MANAGER
/*
you need to put bparam2 the amount of switches to press
*/
void bhv_flipswitch_manager_init(void) {
    o->oAction = 0; 
    o->oHealth = o->oBehParams2ndByte; 
}




//manager
void bhv_flipswitch_manager_loop(void) {
    if (o->oAction >= o->oHealth) {
        spawn_default_star(o->oPosX, o->oPosY + 200, o->oPosZ);
        obj_mark_for_deletion(o);
    }

}