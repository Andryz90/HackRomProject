InsideOfTruck_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, InsideOfTruck_OnLoad
	map_script MAP_SCRIPT_ON_RESUME, InsideOfTruck_OnResume
	.byte 0

InsideOfTruck_OnLoad:
	setmetatile 4, 1, METATILE_InsideOfTruck_ExitLight_Top, FALSE
	setmetatile 4, 2, METATILE_InsideOfTruck_ExitLight_Mid, FALSE
	setmetatile 4, 3, METATILE_InsideOfTruck_ExitLight_Bottom, FALSE
	end

InsideOfTruck_OnResume:
	setstepcallback STEP_CB_TRUCK
	end

InsideOfTruck_EventScript_SetIntroFlags::
	lockall
	setflag FLAG_HIDE_MAP_NAME_POPUP
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, InsideOfTruck_EventScript_SetIntroFlagsMale
	goto_if_eq VAR_RESULT, FEMALE, InsideOfTruck_EventScript_SetIntroFlagsFemale
	end

InsideOfTruck_EventScript_SetIntroFlagsMale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
	setvar VAR_LITTLEROOT_INTRO_STATE, 1
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_SIBLING
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 1
	setdynamicwarp MAP_LITTLEROOT_TOWN, 3, 10
	call InsideOfTruck_EventScript_GameMode
	releaseall
	end

InsideOfTruck_EventScript_SetIntroFlagsFemale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F
	setvar VAR_LITTLEROOT_INTRO_STATE, 2
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_SIBLING
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 1
	setdynamicwarp MAP_LITTLEROOT_TOWN, 12, 10
	call InsideOfTruck_EventScript_GameMode
	releaseall
	end

InsideOfTruck_EventScript_MovingBox::
	msgbox InsideOfTruck_Text_BoxPrintedWithMonLogo, MSGBOX_SIGN
	end

InsideOfTruck_EventScript_GameMode:: 
	msgbox InsideOfTruck_Text_GameMode, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_GAME_MODE_CHOICE, TRUE
	switch VAR_RESULT
	case 0, InsideOfTruck_Standard_Choice
	case 1, InsideOfTruck_Hardcore_Choice
	case 2, InsideOfTruck_Nuzlocke_Choice
	return

InsideOfTruck_Standard_Choice::
		msgbox InsideOfTruck_Text_GameMode_Standard, MSGBOX_YESNO
		switch VAR_RESULT
		case YES, InsideOfTruck_GameModeS_Selected
		case NO, InsideOfTruck_EventScript_GameMode
		InsideOfTruck_GameModeS_Selected::
			msgbox InsideOfTruck_Text_GameModeS_Selected, MSGBOX_DEFAULT
			return
InsideOfTruck_Hardcore_Choice::
		msgbox InsideOfTruck_Text_GameMode_Hardcore, MSGBOX_YESNO
		switch VAR_RESULT
		case YES, InsideOfTruck_GameModeH_Selected
		case NO, InsideOfTruck_EventScript_GameMode
		InsideOfTruck_GameModeH_Selected::
			msgbox InsideOfTruck_Text_GameModeH_Selected, MSGBOX_DEFAULT
			setvar VAR_GAME_MODE, 1
			return
	InsideOfTruck_Nuzlocke_Choice::
		msgbox InsideOfTruck_Text_GameMode_Nuzlocke, MSGBOX_YESNO
		switch VAR_RESULT
		case YES, InsideOfTruck_GameModeN_Selected
		case NO, InsideOfTruck_EventScript_GameMode
		InsideOfTruck_GameModeN_Selected::
			msgbox InsideOfTruck_Text_GameModeN_Selected, MSGBOX_DEFAULT
			setvar VAR_GAME_MODE, 2
			return
InsideOfTruck_Text_BoxPrintedWithMonLogo:
	.string "The box is printed with a POKéMON logo.\p"
	.string "It's a POKéMON brand moving and\n"
	.string "delivery service.$"

InsideOfTruck_Text_GameMode::
	.string "Before proceeding please select\nthe game mode.$"

InsideOfTruck_Text_GameMode_Standard::
	.string "Standard mode is the vanilla\n"
	.string "experience of the hack.\p"
	.string "There are no restriction,\n"
	.string "no level cap\pand the difficulty is standard.\p"
	.string "You want to select Standard Mode?$"

InsideOfTruck_Text_GameMode_Hardcore::
	.string "Hardcore mode is for the players\n"
	.string "that want to play the game\p"
	.string "with challenge and restrictions.\p"
	.string "There are level caps and\nenemy's teams are tougher.\n"
	.string "You want to select Hardcore Mode?$"

InsideOfTruck_Text_GameMode_Nuzlocke::
	.string "It's a mode thought to enjoy\n"
	.string "the Nuzlocke's experience.\p"
	.string "There are level caps and enemy's teams\nare build different\p"
	.string "than the standard mode.\pTo the player are also given "
	.string "more items\nto improve the quality of life\nfor the game.\p"
	.string "You want to select Nuzlocke Mode?$"

InsideOfTruck_Text_GameModeS_Selected::
	.string "You selected Standard Mode!$"
InsideOfTruck_Text_GameModeH_Selected::
	.string "You selected Hardcore Mode!$"
InsideOfTruck_Text_GameModeN_Selected::
	.string "You selected Nuzlocke Mode!$"