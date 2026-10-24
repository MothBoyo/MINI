////SILVER STARS INIT AND LOOP////

//bparam2 = mode
#define MODE_FREE_JUMP 0        //normal mode
#define MODE_STATIC_JUMP 1      //static mode (jumps in place, for constrained areas)
#define MODE_AIR_TINY_JUMP 2    //air or above tree, or overwater
#define MODE_HOVER 3            //mostly for underwater or air
#define MODE_OTHER 4            //totally static, basically a secret


//bparam3 = radius
    /*
    case 0 = radio 1000
    case 1 = radio 1500
    case 2 = radio 2000
    case 3 = radio 2500
    case 4 = radio 3000
    case 5 = radio 3500
    case 6 = radio 500
    */



static struct ObjectHitbox sSilverStarHitbox = {
    /* interactType:      */ INTERACT_COIN,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,  
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 100,
    /* height:            */ 64,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};





void bhv_silver_star_init(void) {


    o->oVelY = 45.0f;       
    o->oGravity = 2.0f;     

    if (o->oBehParams2ndByte == MODE_HOVER) {
    o->oGravity = 0.0f;     
    }
    

    s32 randDir = random_u16() % 4;
    switch (randDir) {
        case 0: o->oMoveAngleYaw = o->oMoveAngleYaw + 0x0000; break;   //norte
        case 1: o->oMoveAngleYaw = o->oMoveAngleYaw + 0x4000; break;   //este
        case 2: o->oMoveAngleYaw = o->oMoveAngleYaw + 0x8000; break;   //sur
        case 3: o->oMoveAngleYaw = o->oMoveAngleYaw + 0xC000; break;   //oeste
    }



    o->oForwardVel = 0.0f;  
    if (o->oBehParams2ndByte == MODE_FREE_JUMP ){
    o->oForwardVel = 10.0f;    
    }

    struct Object *hiddenSilverStarsStar = cur_obj_nearest_object_with_behavior(bhvHiddenSilverStarsStar);
    if (hiddenSilverStarsStar != NULL) {
        o->parentObj = hiddenSilverStarsStar;
    } 
    else {
        o->parentObj = NULL;
    }
    obj_set_hitbox(o, &sSilverStarHitbox); 
}




void silver_star_floor_detection(f32 hRadius) {

    s32 homeRadius = hRadius;

  
    f32 floorY = find_floor_height(o->oPosX, o->oPosY + 45.0f, o->oPosZ);


    f32 waterY = find_water_level(o->oPosX, o->oPosZ);

    if (o->oPosY <= floorY) {
        o->oPosY = floorY;
        o->oVelY = 45.0f;  
        spawn_object(o, MODEL_SPARKLES, bhvCoinSparklesSpawner); 
        if (o->oDistanceToMario < 1800.0f) cur_obj_play_sound_2(SOUND_MENU_STAR_SOUND);

        

        f32 dx = o->oHomeX - o->oPosX;
        f32 dz = o->oHomeZ - o->oPosZ;
        f32 distanceFromHome = dx*dx + dz*dz;  
        f32 radiusMaxHome = homeRadius * homeRadius;

        if (distanceFromHome > radiusMaxHome) {
            o->oMoveAngleYaw = atan2s(dz, dx);
        }
        else if ((random_u16() % 4) == 0) {
            s32 newDir = random_u16() % 4;
            o->oMoveAngleYaw = newDir * 0x4000;
            }
    

        } 
    else if(o->oPosY <= waterY) {
        o->oPosY = waterY;
        o->oVelY = 45.0f;  
        if (o->oDistanceToMario < 1500.0f)  spawn_object(o, MODEL_WATER_SPLASH , bhvWaterSplash); 
        if (o->oDistanceToMario < 1500.0f)  cur_obj_play_sound_2(SOUND_OBJ_WALKING_WATER); 
    

        f32 dx = o->oHomeX - o->oPosX;
        f32 dz = o->oHomeZ - o->oPosZ;
        f32 distanceFromHome = dx*dx + dz*dz;  
        f32 radiusMaxHome = homeRadius * homeRadius;


        if (distanceFromHome > radiusMaxHome) {
            o->oMoveAngleYaw = atan2s(dz, dx);
        }

        else if ((random_u16() % 4) == 0) {
            s32 newDir = random_u16() % 4;
            o->oMoveAngleYaw = newDir * 0x4000;
            }
        }


}

void bhv_silver_star_loop(void) {

    o->oFaceAngleYaw += 0x600;


    f32 homeRadius = 1000.0f;

    u8 bparam3 = (o->oBehParams >> 8) & 0xFF;

    switch (bparam3) {
        case 1:
            homeRadius = 1500.0f;
            break;
        case 2:
            homeRadius = 2000.0f;
            break;
        case 3:
            homeRadius = 2500.0f;
            break;
         case 4:
            homeRadius = 3000.0f;
            break;
         case 5:
            homeRadius = 3500.0f;
            break;
         case 6:
            homeRadius = 500.0f;
            break;        
        default:
            homeRadius = 1000.0f; 
            break;
    }    


    cur_obj_update_floor_and_walls();
    cur_obj_if_hit_wall_bounce_away();
 
    
    struct Surface *floor = o->oFloor;

   
    if (floor == NULL) {
    o->oVelY = 45.0f; 
    }

    
    if (o->oBehParams2ndByte == MODE_FREE_JUMP || o->oBehParams2ndByte == MODE_STATIC_JUMP ) {
    
   
    o->oPosX += o->oForwardVel * sins(o->oMoveAngleYaw);
    o->oPosZ += o->oForwardVel * coss(o->oMoveAngleYaw);


    
    o->oVelY -= o->oGravity;

   
    o->oPosY += o->oVelY;

  
    silver_star_floor_detection(homeRadius);    
      
    }


    if (o->oBehParams2ndByte == MODE_AIR_TINY_JUMP) {

    o->oVelY -= o->oGravity * 0.7f;
    o->oPosY += o->oVelY;

    if (o->oPosY <= o->oHomeY) {
        o->oPosY = o->oHomeY;
        o->oVelY = 25.0f;  
        spawn_object(o, MODEL_SPARKLES, bhvCoinSparklesSpawner); 
        
        if (o->oDistanceToMario < 1200.0f) cur_obj_play_sound_2(SOUND_MENU_STAR_SOUND);
        }

    }

    if (o->oBehParams2ndByte == MODE_HOVER ) {
    
    //magic numbers just to ajust the sin wave
    o->oPosY = o->oPosY + (sins(o->oTimer * 0x900) * 5.0f );
    o->oTimer = o->oTimer + 1;

    if (o->oPosY == o->oHomeY){
        spawn_object(o, MODEL_SPARKLES, bhvCoinSparklesSpawner); 
        if (o->oDistanceToMario < 1000.0f) cur_obj_play_sound_2(SOUND_MENU_STAR_SOUND);
        }

    }


    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->parentObj != NULL) {
            o->parentObj->oHiddenStarTriggerCounter++;

            if (o->parentObj->oHiddenStarTriggerCounter != o->parentObj->oHiddenStarTriggerTotal) {
                if (o->parentObj->oHiddenStarTriggerCounter > 99) {
                    spawn_orange_number(9, 28, 0, 0);
                    spawn_orange_number(9, -28, 0, 0);
                }
                else if (o->parentObj->oHiddenStarTriggerCounter >= 10) {
                    spawn_orange_number(o->parentObj->oHiddenStarTriggerCounter % 10, 28, 0, 0);
                    spawn_orange_number(o->parentObj->oHiddenStarTriggerCounter / 10, -28, 0, 0);
                }
                else {
                    spawn_orange_number(o->parentObj->oHiddenStarTriggerCounter, 0, 0, 0);
                }
            }
                play_sound(SOUND_MENU_STAR_SOUND ,gGlobalSoundSource);

        if (o->parentObj->oHiddenStarTriggerCounter != 5) {

            gStarDanceIsSilver = TRUE; //CUSTOM FOR SILVER STARS
            gMarioState->action = ACT_FALL_AFTER_STAR_GRAB;       
            //2 is arg to mario_cutscene.c
            gMarioState->actionArg = 2;
        }
            gMarioState->vel[0] = 0;
            gMarioState->vel[2] = 0;


        }

        coin_collected();
        // DESPAWN THE SILVER STAR?
        o->oInteractStatus = INT_STATUS_NONE;
    }
}











//SILVER STARS STAR SPAWNER INIT AND LOOP
void bhv_hidden_silver_stars_star_init(void) {

    s16 remainingSilverStars = count_objects_with_behavior(bhvCollectableSilverStar);
    if (remainingSilverStars == 0) {
        struct Object *starObj = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvStar, o->oPosX, o->oPosY, o->oPosZ, 0, 0, 0);
        starObj->oBehParams = o->oBehParams;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
    spawn_object(o, MODEL_TRANSPARENT_STAR, bhvRedCoinStarMarker);
    o->oHiddenStarTriggerCounter = 5 - remainingSilverStars;

    
}


void bhv_hidden_silver_stars_star_loop(void) {
    switch (o->oAction) {
        case 0:
            if (o->oHiddenStarTriggerCounter == 5) {
                o->oAction = 1;
            }
            break;
        case 1:
            if (o->oTimer > 2) {
                spawn_default_star(o->oPosX, o->oPosY, o->oPosZ); 
                spawn_mist_particles();
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
    
}



