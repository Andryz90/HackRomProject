Underwater_SeafloorCavern_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Underwater_SeafloorCavern_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Underwater_SeafloorCavern_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Underwater_SeafloorCavern_OnLoad
	.byte 0

Underwater_SeafloorCavern_OnTransition:
	setflag FLAG_LANDMARK_SEAFLOOR_CAVERN
	goto_if_set FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, Underwater_SeafloorCavern_EventScript_HideSubmarine
	end

Underwater_SeafloorCavern_EventScript_HideSubmarine::
	setflag FLAG_HIDE_UNDERWATER_SEA_FLOOR_CAVERN_STOLEN_SUBMARINE
	end

Underwater_SeafloorCavern_OnLoad:
	call_if_set FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, Underwater_SeafloorCavern_EventScript_SetSubmarineGoneMetatiles
	end

Underwater_SeafloorCavern_EventScript_SetSubmarineGoneMetatiles::
	setmetatile 5, 3, METATILE_Underwater_RockWall, TRUE
	setmetatile 6, 3, METATILE_Underwater_RockWall, TRUE
	setmetatile 7, 3, METATILE_Underwater_RockWall, TRUE
	setmetatile 8, 3, METATILE_Underwater_RockWall, TRUE
	setmetatile 5, 4, METATILE_Underwater_FloorShadow, FALSE
	setmetatile 6, 4, METATILE_Underwater_FloorShadow, FALSE
	setmetatile 7, 4, METATILE_Underwater_FloorShadow, FALSE
	setmetatile 8, 4, METATILE_Underwater_FloorShadow, FALSE
	setmetatile 5, 5, METATILE_Underwater_FloorShadow, FALSE
	setmetatile 6, 5, METATILE_Underwater_FloorShadow, FALSE
	setmetatile 7, 5, METATILE_Underwater_FloorShadow, FALSE
	setmetatile 8, 5, METATILE_Underwater_FloorShadow, FALSE
	return

Underwater_SeafloorCavern_OnResume:
	setdivewarp MAP_SEAFLOOR_CAVERN_ENTRANCE, 10, 17
	end

Underwater_SeafloorCavern_EventScript_CheckStolenSub::
	msgbox Underwater_SeafloorCavern_Text_SubExplorer1, MSGBOX_SIGN
	end

Underwater_SeafloorCavern_Text_SubExplorer1:
	.string "“SUBMARINE EXPLORER 1” is painted\n"
	.string "on the hull.\p"
	.string "This is the submarine TEAM AQUA\n"
	.string "stole in SLATEPORT!\p"
	.string "TEAM AQUA must have gone\n"
	.string "ashore here. $"

