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
#include "levels/hmc/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_hmc_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _hmc_segment_7SegmentRomStart, _hmc_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _cave_yay0SegmentRomStart, _cave_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group6_yay0SegmentRomStart, _group6_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group6_geoSegmentRomStart, _group6_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group17_yay0SegmentRomStart, _group17_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group17_geoSegmentRomStart, _group17_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_YAY0(0xa, _wdw_skybox_yay0SegmentRomStart, _wdw_skybox_yay0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_7), 
	JUMP_LINK(script_func_global_18), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_WOODEN_DOOR, wooden_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_METAL_DOOR, metal_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_HAZY_MAZE_DOOR, hazy_maze_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_METAL_PLATFORM, hmc_geo_0005A0), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_METAL_ARROW_PLATFORM, hmc_geo_0005B8), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_ELEVATOR_PLATFORM, hmc_geo_0005D0), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_ROLLING_ROCK, hmc_geo_000548), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_ROCK_PIECE, hmc_geo_000570), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_ROCK_SMALL_PIECE, hmc_geo_000588), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_RED_GRILLS, hmc_geo_000530), 
	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, hmc_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_1UP, 0, 0, -2130, 0, 0, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_1UP, 625, 0, -2130, 0, 0, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_1UP, 1305, 0, -2130, 0, 0, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_1UP, 2170, 0, -2130, 0, 0, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_1UP, 2903, 0, -2130, 0, 0, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_1UP, 3557, 0, -2130, 0, 0, 0, 0x00000000, bhv1Up),
		MARIO_POS(0x01, 0, 0, 200, 0),
		OBJECT(MODEL_NONE, 0, 200, 0, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 6, 58, -2773, 0, 0, 0, (0 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 6, 58, -3276, 0, 0, 0, (1 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 6, 58, -3809, 0, 0, 0, (2 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 636, 58, -2773, 0, 0, 0, (1 << 24) | (0 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 636, 58, -3276, 0, 0, 0, (1 << 24) | (1 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 636, 58, -3809, 0, 0, 0, (1 << 24) | (2 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 1358, 58, -2773, 0, 0, 0, (2 << 24) | (0 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 1358, 58, -3276, 0, 0, 0, (2 << 24) | (1 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 1358, 58, -3809, 0, 0, 0, (2 << 24) | (2 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 2195, 58, -2773, 0, 0, 0, (3 << 24) | (0 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 2195, 58, -3276, 0, 0, 0, (3 << 24) | (1 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 2195, 58, -3809, 0, 0, 0, (3 << 24) | (2 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 2932, 58, -2773, 0, 0, 0, (4 << 24) | (0 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 2932, 58, -3276, 0, 0, 0, (4 << 24) | (1 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 2932, 58, -3809, 0, 0, 0, (4 << 24) | (2 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 3604, 58, -2773, 0, 0, 0, (5 << 24) | (0 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 3604, 58, -3276, 0, 0, 0, (5 << 24) | (1 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_NONE, 3604, 58, -3809, 0, 0, 0, (5 << 24) | (2 << 16), bhvCollectableBlueCoin),
		OBJECT(MODEL_STAR, -1239, 385, -2114, 0, 0, 0, 0x00000000, bhvStar),
		TERRAIN(hmc_area_1_collision),
		MACRO_OBJECTS(hmc_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_EVENT_MERRY_GO_ROUND),
		TERRAIN_TYPE(TERRAIN_SNOW),
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