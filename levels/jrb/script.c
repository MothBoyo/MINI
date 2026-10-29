#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"
#include "make_const_nonconst.h"
#include "levels/jrb/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_jrb_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _jrb_segment_7SegmentRomStart, _jrb_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x0B, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _water_yay0SegmentRomStart, _water_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _clouds_skybox_yay0SegmentRomStart, _clouds_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group4_yay0SegmentRomStart, _group4_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group4_geoSegmentRomStart, _group4_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group13_yay0SegmentRomStart, _group13_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group13_geoSegmentRomStart, _group13_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_5), 
	JUMP_LINK(script_func_global_14), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SHIP_LEFT_HALF_PART, jrb_geo_000978), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SHIP_BACK_LEFT_PART, jrb_geo_0009B0), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SHIP_RIGHT_HALF_PART, jrb_geo_0009E8), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SHIP_BACK_RIGHT_PART, jrb_geo_000A00), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SUNKEN_SHIP, jrb_geo_000990), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SUNKEN_SHIP_BACK, jrb_geo_0009C8), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_ROCK, jrb_geo_000930), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SLIDING_BOX, jrb_geo_000960), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_FALLING_PILLAR, jrb_geo_000900), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_FALLING_PILLAR_BASE, jrb_geo_000918), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_FLOATING_PLATFORM, jrb_geo_000948), 
	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, jrb_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE, 0x01, 53, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE, 0x01, 103, WARP_NO_CHECKPOINT),
		MARIO_POS(0x01, 0, 0, 200, 0),
		OBJECT(MODEL_NONE, 0, 200, 0, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT_WITH_ACTS(MODEL_NONE, 1803, 243, -1985, 0, 0, 0, (0 << 24) | (0 << 16), bhvCollectableBlueCoin, ACT_1),
		OBJECT_WITH_ACTS(MODEL_NONE, 260, 1146, -5562, 0, 0, 0, (0 << 24) | (1 << 16), bhvCollectableBlueCoin, ACT_1),
		OBJECT_WITH_ACTS(MODEL_NONE, -4845, 1922, -5783, 0, 0, 0, (1 << 24) | (0 << 16), bhvCollectableBlueCoin, ACT_2),
		OBJECT_WITH_ACTS(MODEL_NONE, -3874, 2343, 693, 0, 0, 0, (2 << 24) | (0 << 16), bhvCollectableBlueCoin, ACT_3),
		OBJECT_WITH_ACTS(MODEL_NONE, -6600, 2406, 693, 0, 0, 0, (2 << 24) | (1 << 16), bhvCollectableBlueCoin, ACT_3),
		OBJECT_WITH_ACTS(MODEL_NONE, -5886, 2239, 4532, 0, 0, 0, (2 << 24) | (2 << 16), bhvCollectableBlueCoin, ACT_3),
		OBJECT_WITH_ACTS(MODEL_NONE, 5489, 1587, 1296, 0, 0, 0, (4 << 24) | (0 << 16), bhvCollectableBlueCoin, ACT_5),
		OBJECT_WITH_ACTS(MODEL_NONE, 4048, 710, 6848, 0, 0, 0, (4 << 24) | (1 << 16), bhvCollectableBlueCoin, ACT_5),
		OBJECT_WITH_ACTS(MODEL_NONE, 2258, 2813, -7371, 0, 0, 0, (5 << 24) | (0 << 16), bhvCollectableBlueCoin, ACT_6),
		OBJECT_WITH_ACTS(MODEL_CHUCKYA, 4523, 602, 6961, 0, 0, 0, (4 << 24), bhvChuckya, ACT_5),
		OBJECT_WITH_ACTS(MODEL_CHUCKYA, 5016, 745, 6422, 0, 0, 0, (4 << 24), bhvChuckya, ACT_5),
		OBJECT_WITH_ACTS(MODEL_CHUCKYA, 3935, 616, 6153, 0, 0, 0, (4 << 24), bhvChuckya, ACT_5),
		OBJECT_WITH_ACTS(MODEL_CHUCKYA, 3297, 383, 7228, 0, 0, 0, (4 << 24), bhvChuckya, ACT_5),
		OBJECT_WITH_ACTS(MODEL_CHUCKYA, 3115, 537, 5799, 0, 0, 0, (4 << 24), bhvChuckya, ACT_5),
		OBJECT_WITH_ACTS(MODEL_CHUCKYA, 4440, 777, 5487, 0, 0, 0, (4 << 24), bhvChuckya, ACT_5),
		OBJECT_WITH_ACTS(MODEL_FLYGUY, -4459, 2680, -2269, 0, 0, 0, 0x00000000, bhvFlyGuy, ACT_2 | ACT_3),
		OBJECT_WITH_ACTS(MODEL_FLYGUY, -5638, 2801, 2521, 0, 0, 0, 0x00000000, bhvFlyGuy, ACT_2 | ACT_3),
		OBJECT(MODEL_GOOMBA, 1674, 867, -2437, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, 905, 1028, -4905, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, -272, 573, -2293, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, -5440, 1922, -2207, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, -4212, 1922, -3089, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, -5485, 1922, -3501, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, 3543, 778, 4404, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, 5727, 985, 3238, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, 5029, 0, -2335, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, -1907, 0, -4022, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT_WITH_ACTS(MODEL_SHRINKPLATFORM, -5886, 1922, 693, 0, 0, 0, (1 << 16), bhvShrinkPlatform, ACT_3),
		OBJECT_WITH_ACTS(MODEL_SHRINKPLATFORM, -3874, 1922, 693, 0, 0, 0, (1 << 16), bhvShrinkPlatform, ACT_3),
		OBJECT_WITH_ACTS(MODEL_SHRINKPLATFORM, -5886, 1922, 1331, 0, 0, 0, (1 << 16), bhvShrinkPlatform, ACT_3),
		OBJECT_WITH_ACTS(MODEL_SHRINKPLATFORM, -5886, 1922, 2061, 0, 0, 0, (1 << 16), bhvShrinkPlatform, ACT_3),
		OBJECT_WITH_ACTS(MODEL_SHRINKPLATFORM, -5886, 1922, 2876, 0, 0, 0, (1 << 16), bhvShrinkPlatform, ACT_3),
		OBJECT_WITH_ACTS(MODEL_SHRINKPLATFORM, -5886, 1922, 3502, 0, 0, 0, (1 << 16), bhvShrinkPlatform, ACT_3),
		OBJECT_WITH_ACTS(MODEL_SHRINKPLATFORM, -5886, 1922, 4532, 0, 0, 0, (1 << 16), bhvShrinkPlatform, ACT_3),
		OBJECT_WITH_ACTS(MODEL_SHRINKPLATFORM, -5886, 1922, 4026, 0, 0, 0, (1 << 16), bhvShrinkPlatform, ACT_3),
		OBJECT_WITH_ACTS(MODEL_NOTEBLOCK, -5102, 205, -512, 0, 0, 0, (1 << 16), bhvNoteblock, ACT_3),
		OBJECT_WITH_ACTS(MODEL_NOTEBLOCK, -4842, 775, -512, 0, 0, 0, (1 << 16), bhvNoteblock, ACT_3),
		OBJECT_WITH_ACTS(MODEL_NOTEBLOCK, -4579, 1354, -512, 0, 0, 0, (1 << 16), bhvNoteblock, ACT_3),
		OBJECT_WITH_ACTS(MODEL_METAL_BOX, -6600, 2083, 693, 0, 0, 0, (1 << 16), bhvPushableMetalBox, ACT_3),
		OBJECT_WITH_ACTS(MODEL_STAR, 3188, 1724, -5261, 0, 0, 0, 0x00000000, bhvStar, ACT_1),
		OBJECT_WITH_ACTS(MODEL_STAR, -5026, 2479, -5114, 0, 0, 0, (1 << 24), bhvStar, ACT_2),
		OBJECT_WITH_ACTS(MODEL_STAR, -5886, 2305, 4031, 0, 0, 0, (2 << 24), bhvStar, ACT_3),
		OBJECT_WITH_ACTS(MODEL_STAR, -2746, -898, 4916, 0, 0, 0, (3 << 24), bhvStar, ACT_4),
		OBJECT_WITH_ACTS(MODEL_STAR, 6863, 1313, 6690, 0, 0, 0, (4 << 24), bhvStar, ACT_5),
		OBJECT_WITH_ACTS(MODEL_STAR, 3449, 3091, -7324, 0, 0, 0, (5 << 24), bhvStar, ACT_6),
		OBJECT_WITH_ACTS(MODEL_1UP, 7135, 173, -4802, 0, 0, 0, 0x00000000, bhvRainbowStar, ACT_6),
		TERRAIN(jrb_area_1_collision),
		MACRO_OBJECTS(jrb_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SLIDE),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),
	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 0, 200, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};