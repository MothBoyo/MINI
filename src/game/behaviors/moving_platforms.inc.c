//shrinkplatform
#define SHRINKPLATFROM_ACT_IDLE 0
#define SHRINKPLATFROM_ACT_SHRINK 1
#define SHRINKPLATFROM_ACT_INACTIVE 2


void star_shrink_platform_loop(void) {

    switch(o->oAction) {

    case SHRINKPLATFROM_ACT_IDLE:
    load_object_collision_model();
        //si mario pisa
    if (gMarioObject->platform == o){
        o->oAction = SHRINKPLATFROM_ACT_SHRINK;  
        play_sound(SOUND_MENU_PINCH_MARIO_FACE, gGlobalSoundSource);  

    }
    break;

    case SHRINKPLATFROM_ACT_SHRINK:
    //se achica
    load_object_collision_model();
    o->header.gfx.scale[0] = o->header.gfx.scale[0] - 0.01f;
    o->header.gfx.scale[2] = o->header.gfx.scale[2] - 0.01f;

    //si llega un punto, se desactiva
    if (o->header.gfx.scale[0] <= 0.2f){
        o->oAction = SHRINKPLATFROM_ACT_INACTIVE;  
        spawn_mist_particles(); 
        cur_obj_hide(); 

    }
    break;
      
    //not done yet respawnable :p
    case SHRINKPLATFROM_ACT_INACTIVE:
    if (o->oBehParams2ndByte == 0){
        obj_mark_for_deletion(o);
    } else {
        o->header.gfx.scale[0] = 1.0;
        o->header.gfx.scale[2] = 1.0;

        if (o->oTimer > 120) {
            o->oAction = SHRINKPLATFROM_ACT_IDLE;    
            cur_obj_unhide(); 
        }

    }

    break;

    }
}
