// cannon.inc.c

/*
note_ the entire yaw is rotate 90 degrees so when placing obhect in blender add 90 :P
note 2 mode 2 is broken totally broken

bparam1 = mode. 
    mode0:moves angle up and down, //dont do too high values or BROKEN (43 is the max), 45 works but looks weird, 50 broken asf
    mode1: moves angle felt and right
    mode2: moves in one direction indefitive "up or down" //BROKEN not saveable
    mode3: moves in one direction indefitive "left or right"

bparam2 = speed of the movement
bparam3 = amout of movenet (in case of mode 0 or 1)
bparam4 = sign of the movement (in case of mode 2 or 3) 

*/

#define MOVE_MULTIPLIER 10
#define ONE_DIR_MULTIPLIER 10

#define oCannonBasePitch                    oF4   
#define oCannonBaseYaw                      oF8   

#define oCannonHomeYaw                      oFC  
#define oCannonHomeYawIsInitialized         o104 //??? yes no

void bhv_cannon_base_unused_loop(void) {
    o->oPosY += o->oVelY;
}

void opened_cannon_act_idle(void) { // act 0
    if (o->oTimer == 0) {
        o->oInteractStatus = INT_STATUS_NONE;
        vec3f_copy(&o->oPosVec, &o->oHomeVec); //why not SET_HOME(), ????
        o->oMoveAnglePitch = 0;
        o->oCannonHomeYaw = o->oMoveAngleYaw;
        o->oCannonAngle = 0;
        o->oCannonIsActive = FALSE;
        cur_obj_enable_rendering();
        cur_obj_become_tangible();
    }

    if (o->oDistanceToMario < 7500.0f) {
        cur_obj_become_tangible();
        cur_obj_enable_rendering();
        if (o->oInteractStatus & INT_STATUS_INTERACTED
         && (!(o->oInteractStatus & INT_STATUS_TOUCHED_BOB_OMB))) { // bob-omb explodes when it gets into a cannon
            o->oAction = 4;
            o->oCannonIsActive = TRUE;
            o->oCannonTimeSinceActivated = 1;
        } else {
            o->oInteractStatus = INT_STATUS_NONE;
        }
    } else {
        cur_obj_become_intangible();
        cur_obj_disable_rendering();
        o->oCannonIsActive = FALSE;
    }
}

void opened_cannon_act_rising(void) { // act 4
    if (o->oTimer == 0) {
        cur_obj_play_sound_2(SOUND_OBJ_CANNON_RISE);
    }

    o->oPosY += 5.0f;
    f32 horizontalVel = (f32)(((o->oTimer / 2) & 0x1) - 0.5f) * 2; 
    o->oPosX += horizontalVel;
    o->oPosZ += horizontalVel;

    if (o->oTimer > 67) {
        horizontalVel *= 2;
        o->oPosX += horizontalVel;
        o->oPosZ += horizontalVel;
        o->oAction = 6;
    }
}

void opened_cannon_act_turning_yaw(void) { // act 6
    if (o->oTimer == 0) {
        cur_obj_play_sound_2(SOUND_OBJ_CANNON_TURN);
    }

    if (o->oTimer < 4) {
        f32 horizontalVel = ((f32)(((o->oTimer / 2) & 0x1) - 0.5f) * 4.0f);
        o->oPosX += horizontalVel;
        o->oPosZ += horizontalVel;
    } else {
        if (o->oTimer >= 6) {
            if (o->oTimer < 22) {
                o->oMoveAngleYaw =
                    o->oMoveAngleYaw = o->oCannonHomeYaw + (s16)(sins(o->oCannonAngle) * 0x4000);
                o->oCannonAngle += 0x400;
            } else if (o->oTimer >= 26) {
                o->oCannonAngle = 0;
                o->oAction = 5;
            }
        }
    }
}

void opened_cannon_act_pitch_up(void) { // act 5
    if (o->oTimer == 0) {
        cur_obj_play_sound_2(SOUND_OBJ_CANNON_BARREL_PITCH);
    }
    if (o->oTimer >= 4) {
        if (o->oTimer < 20) {
            o->oCannonAngle += 0x400;
            o->oMoveAnglePitch = (sins(o->oCannonAngle) * 0x2000);
        } else if (o->oTimer >= 25) {
            o->oAction = 1;
        }
    }
}



void opened_cannon_act_ready(void) { // act 1
    cur_obj_become_intangible();
    cur_obj_disable_rendering();

    o->oCannonIsActive = FALSE;
    gMarioShotFromCannon = TRUE;

    if (o->oTimer == 0) {
        o->oCannonBasePitch = o->oMoveAnglePitch;
        o->oCannonBaseYaw   = o->oMoveAngleYaw;
    }
    
    u8 mode = GET_BPARAM1(o->oBehParams);
    s16 speed = GET_BPARAM2(o->oBehParams);
    s16 amplitude = DEGREES(GET_BPARAM3(o->oBehParams)); //convert to angles
    s16 dir = (GET_BPARAM4(o->oBehParams) == 0) ? 1 : -1; //IF BPRAAMA is 1 ten clockwise, if not countwerclowside, or reverse?

    switch (mode) {
        case 0: //up and wodn
            o->oMoveAnglePitch = o->oCannonBasePitch + (s16)(sins(o->oTimer * speed * MOVE_MULTIPLIER) * amplitude);
            break;
        case 1: //left right
            o->oMoveAngleYaw = o->oCannonBaseYaw + (s16)(sins(o->oTimer * speed * MOVE_MULTIPLIER) * amplitude);
            break;
        case 2: //pitch one dir
            o->oMoveAnglePitch += dir * speed * ONE_DIR_MULTIPLIER;
            break;
        case 3: //yaw one dir
            o->oMoveAngleYaw += dir * speed * ONE_DIR_MULTIPLIER;
            break;
    }
  
}


void opened_cannon_act_shoot(void) { // act 2
    o->oAction = 3;
}

void opened_cannon_act_resetting(void) { // act 3
    if (o->oTimer > 3) {
        o->oAction = 0;
    }
}

ObjActionFunc sOpenedCannonActions[] = {
    opened_cannon_act_idle,
    opened_cannon_act_ready,
    opened_cannon_act_shoot,
    opened_cannon_act_resetting,
    opened_cannon_act_rising,
    opened_cannon_act_pitch_up,
    opened_cannon_act_turning_yaw,
};

void bhv_cannon_base_loop(void) {

    if (o->oCannonHomeYawIsInitialized == FALSE) {
        o->oCannonHomeYaw  = o->oMoveAngleYaw; //SET ROTATION BASED ON OBJACT
        o->oCannonHomeYawIsInitialized = TRUE;
    }

    cur_obj_call_action_function(sOpenedCannonActions);

    if (o->oCannonTimeSinceActivated) {
        o->oCannonTimeSinceActivated++;
    }

    o->oInteractStatus = INT_STATUS_NONE;
}

void bhv_cannon_barrel_loop(void) {
    struct Object *parent = o->parentObj;

    if (parent->header.gfx.node.flags & GRAPH_RENDER_ACTIVE) {
        cur_obj_enable_rendering();
        obj_copy_pos(o, o->parentObj);
        o->oMoveAngleYaw = o->parentObj->oMoveAngleYaw;
        o->oFaceAnglePitch = o->parentObj->oMoveAnglePitch;
    } else {
        cur_obj_disable_rendering();
    }
}
