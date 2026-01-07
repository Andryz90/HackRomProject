.set LOCALID_VICTOR, 1
.set LOCALID_VICTORIA, 2
.set LOCALID_VIVI, 3
.set LOCALID_VICKY, 4
.set LOCALID_BREAKABLE_ROCK, 16

@ Note: LOCALID_ROUTE111_PLAYER_FALLING is a local id for this map used elsewhere. It's defined in event_objects.h

Route111_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Route111_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, Route111_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route111_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route111_OnFrame
	.byte 0

Route111_OnLoad:
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 2, Route111_EventScript_MagmaDesertEvent
	call_if_unset FLAG_REGI_DOORS_OPENED,   Route111_EventScript_CloseDesertRuins
	call_if_eq VAR_MIRAGE_TOWER_STATE, 1,   Route111_EventScript_ShowTemporaryMirageTower
	end

Route111_EventScript_CloseDesertRuins::
	setmetatile 29, 86, METATILE_General_RockWall_RockBase, TRUE
	setmetatile 29, 87, METATILE_General_RockWall_SandBase, TRUE
	return

@ Show Mirage Tower just prior to disintegration. Mirage Tower is otherwise handled by the map layout
Route111_EventScript_ShowTemporaryMirageTower::
	setmetatile 18, 53, METATILE_Mauville_MirageTower_Tile0, FALSE
	setmetatile 19, 53, METATILE_Mauville_MirageTower_Tile1, FALSE
	setmetatile 20, 53, METATILE_Mauville_MirageTower_Tile2, FALSE
	setmetatile 18, 54, METATILE_Mauville_MirageTower_Tile3, FALSE
	setmetatile 19, 54, METATILE_Mauville_MirageTower_Tile4, FALSE
	setmetatile 20, 54, METATILE_Mauville_MirageTower_Tile5, FALSE
	setmetatile 18, 55, METATILE_Mauville_MirageTower_Tile6, FALSE
	setmetatile 19, 55, METATILE_Mauville_MirageTower_Tile7, FALSE
	setmetatile 20, 55, METATILE_Mauville_MirageTower_Tile8, FALSE
	setmetatile 18, 56, METATILE_Mauville_MirageTower_Tile9, FALSE
	setmetatile 19, 56, METATILE_Mauville_MirageTower_TileA, FALSE
	setmetatile 20, 56, METATILE_Mauville_MirageTower_TileB, FALSE
	setmetatile 18, 57, METATILE_Mauville_MirageTower_TileC, FALSE
	setmetatile 19, 57, METATILE_Mauville_MirageTower_TileD, FALSE
	setmetatile 20, 57, METATILE_Mauville_MirageTower_TileE, FALSE
	setmetatile 18, 58, METATILE_Mauville_MirageTower_TileF, FALSE
	setmetatile 19, 58, METATILE_Mauville_MirageTower_Tile10, FALSE
	setmetatile 20, 58, METATILE_Mauville_MirageTower_Tile11, FALSE
	return

Route111_OnTransition:
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 2, Route111_EventScript_SetMusicForMagma
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 0
	special SetMirageTowerVisibility
	call_if_set FLAG_BADGE03_GET, Route111_EventScript_WallyWarp
	call_if_unset FLAG_MIRAGE_TOWER_VISIBLE, Route111_EventScript_SetLayoutNoMirageTower
	call_if_eq VAR_MIRAGE_TOWER_STATE, 1, Route111_EventScript_SetFallingPlayerGfx
	call_if_eq VAR_MIRAGE_TOWER_STATE, 2, Route111_EventScript_SetMirageTowerGone
	call Route111_EventScript_CheckSetSandstorm
	call GabbyAndTy_EventScript_UpdateLocation
	@goto_if_not_defeated TRAINER_VICKY, Route111_EventScript_SetWinstratesNotDefeated
	end

@ ***************	 TEAM MAGMA - DESERT BEGIN	********************

@	Init/End Scripts of the event
Route111_EventScript_MagmaDesertEvent::
	goto_if_unset FLAG_MAXIE_DESERT, Route111_EventScript_MagmDesert_Init
	return

@	Init Scripts of the event
Route111_EventScript_MagmDesert_Init::
	clearflag FLAG_HIDE_MAGMA_GRUNT_DESERT 	@ Magma Grunts and other NPC Visible
	setflag FLAG_REGI_DOORS_OPENED         	@ Temporary open the regi
	setflag FLAG_HIDE_TRAINER_DESERT	   	@ Temporary hide trainer inside
	call_if_eq VAR_WALLY_ROUTE111_TRIGGER,  0xFF, Route111_Prepare_WallyEvent 
	call_if_ge VAR_WALLY_ROUTE111_TRIGGER,  3, Route111_Move_NPC_Guard
	call_if_defeated TRAINER_TABITHA_DESERT, Route111_Desert_SetObjectPositionAfterBattle
	return

@ Prepare Wally Script for the start of the event
Route111_Prepare_WallyEvent::
	setvar VAR_WALLY_ROUTE111_TRIGGER, 2
	return

Route111_Move_NPC_Guard::
	setobjectxyperm LOCALID_GRUNT_DESERT_GUARD1, 0, 0 @Move temporarly in order to not be shown again
	setobjectxyperm LOCALID_GRUNT_DESERT_GUARD2, 0, 0 @Move temporarly in order to not be shown again
	setobjectxyperm LOCALID_GRUNT_DESERT_GUARD3, 0, 0 @Move temporarly in order to not be shown again
	setobjectxyperm LOCALID_GRUNT_DESERT_GUARD4, 0, 0 @Move temporarly in order to not be shown again
	setobjectxyperm LOCALID_WALLY_DESERT, 11, 37
	return 

@ Generic Grunt Scripts
Route111_EventScript_MagmaGrunts_Text::
	.string "What do you want now?\nWe'll get what we want \l"
	.string "and nobody can't stop us! \p"
	.string "Now get out! $"
Route111_EventScript_MagmaGrunts::
	lock
	faceplayer
	msgbox Route111_EventScript_MagmaGrunts_Text, MSGBOX_DEFAULT
	release
	end

@ Edo scripts 
Route111_SplitfaceInitial_Text::
	.string "SPLITFACE: Why are these bozos here\nand why am I stuck here in this heat?!\p"
	.string "{PLAYER}, I'll handle here,\nyou can take care the rest.\l"
	.string "Please I don't want to stay here much.\p"
	.string "DIO BOIAAAA $"
Route111_Abomasnow_Text::
	.string "Abomaaaa! $"
Route111_Abomasnow_Interaction::
	lock
	applymovement LOCALID_ABOMASNOW_DESERT, Common_Movement_ExclamationMark
	playmoncry SPECIES_ABOMASNOW, CRY_MODE_ENCOUNTER
	message Route111_Abomasnow_Text
	waitmoncry
	release
	end
Route111_Glalie_Text::
	.string "Grarieee! $"
Route111_Glalie_Interaction::
	lock
	applymovement LOCALID_GLALIE_DESERT, Common_Movement_ExclamationMark
	playmoncry SPECIES_GLALIE, CRY_MODE_ENCOUNTER
	message Route111_Glalie_Text
	waitmoncry
	release
	end
Route111_SplitfaceInitial_EventScript::
	lock
	msgbox Route111_SplitfaceInitial_Text, MSGBOX_DEFAULT
	applymovement LOCALID_GLALIE_DESERT, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_ABOMASNOW_DESERT, Common_Movement_WalkInPlaceFasterDown
	playmoncry SPECIES_ABOMASNOW, CRY_MODE_NORMAL
	playmoncry SPECIES_GLALIE, CRY_MODE_NORMAL
	waitmoncry
	release
	end

Call_Player_Text::
	.string "{PLAYER}! $"

Player_Approaching_Wally1::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	face_left
	step_end

Player_Approaching_Wally2::
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	face_left
	step_end

Player_Approaching_Wally3::
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	face_left
	step_end

Player_Approaching_Wally4::
	walk_up
	walk_right
	walk_up
	walk_up
	face_left
	step_end

Player_Approaching_Wally5::
	walk_up
	walk_up
	walk_up
	face_left
	step_end

Player_Approaching_Wally6::
	walk_up
	walk_up
	walk_left
	face_left
	step_end

Wally_Help_Text::
	.string "WALLY: I was reached by your neighbour,\nasking me for help. \l"
	.string "But they're too many to handle! \p"
	.string "Help me out and lets finish them! $"

MagmaGrunts_Before_MultiBattle_Text::
	.string "GRUNTS: You will not stop us! $"

@ Wally Scripts 
Route111_Wally_Desert_EventScript1::
	lockall
	applymovement LOCALID_WALLY_DESERT, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Call_Player_Text, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Player_Approaching_Wally1 @Only difference in triggers
	waitmovement 0
	setweather WEATHER_SANDSTORM
	doweather
	applymovement LOCALID_WALLY_DESERT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Wally_Help_Text, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	applymovement LOCALID_WALLY_DESERT, Common_Movement_FaceUp
	waitmovement 0
	call Route111_Wally_Desert_MultiBattle
	call Route111_Wally_PostBattle
	releaseall
	end

Route111_Wally_Desert_EventScript2::
	lockall
	applymovement LOCALID_WALLY_DESERT, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Call_Player_Text, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Player_Approaching_Wally2 @Only difference in triggers
	waitmovement 0
	setweather WEATHER_SANDSTORM
	doweather
	applymovement LOCALID_WALLY_DESERT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Wally_Help_Text, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	applymovement LOCALID_WALLY_DESERT, Common_Movement_FaceUp
	waitmovement 0
	call Route111_Wally_Desert_MultiBattle
	call Route111_Wally_PostBattle
	releaseall
	end


Route111_Wally_Desert_EventScript3::
	lockall
	applymovement LOCALID_WALLY_DESERT, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Call_Player_Text, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Player_Approaching_Wally3 @Only difference in triggers
	waitmovement 0
	setweather WEATHER_SANDSTORM
	doweather
	applymovement LOCALID_WALLY_DESERT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Wally_Help_Text, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	applymovement LOCALID_WALLY_DESERT, Common_Movement_FaceUp
	waitmovement 0
	call Route111_Wally_Desert_MultiBattle
	call Route111_Wally_PostBattle
	releaseall
	end

Route111_Wally_Desert_EventScript4::
	lockall
	applymovement LOCALID_WALLY_DESERT, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Call_Player_Text, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Player_Approaching_Wally4 @Only difference in triggers
	waitmovement 0
	setweather WEATHER_SANDSTORM
	doweather
	applymovement LOCALID_WALLY_DESERT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Wally_Help_Text, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	applymovement LOCALID_WALLY_DESERT, Common_Movement_FaceUp
	waitmovement 0
	call Route111_Wally_Desert_MultiBattle
	call Route111_Wally_PostBattle
	releaseall
	end

Route111_Wally_Desert_EventScript5::
	lockall
	applymovement LOCALID_WALLY_DESERT, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Call_Player_Text, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Player_Approaching_Wally5 @Only difference in triggers
	waitmovement 0
	setweather WEATHER_SANDSTORM
	doweather
	applymovement LOCALID_WALLY_DESERT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Wally_Help_Text, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	applymovement LOCALID_WALLY_DESERT, Common_Movement_FaceUp
	waitmovement 0
	call Route111_Wally_Desert_MultiBattle
	call Route111_Wally_PostBattle
	releaseall
	end

Route111_Wally_Desert_EventScript6::
	lockall
	applymovement LOCALID_WALLY_DESERT, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox Call_Player_Text, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Player_Approaching_Wally6 @Only difference in triggers
	waitmovement 0
	setweather WEATHER_SANDSTORM
	doweather
	applymovement LOCALID_WALLY_DESERT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Wally_Help_Text, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	applymovement LOCALID_WALLY_DESERT, Common_Movement_FaceUp
	waitmovement 0
	call Route111_Wally_Desert_MultiBattle
	call Route111_Wally_PostBattle
	releaseall
	end
Route111_GuardianGrunts_Flees::
	.string "GRUNT: It's too late now, we'll succeed $"
Route111_GuardianGrunts_Finale::
	.string "GRUNTS: You can't stop our boss now! $"

@Note that the walk_fast_up are exagerated in order to guarantee the object are not in camera and will not be load in the middle of the desert
Route111_GuardianGrunt4_Flee_Movement:
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route111_GuardianGrunt1_Flee_Movement:
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route111_GuardianGrunt3_Flee_Movement:
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route111_GuardianGrunt2_Flee_Movement:
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end


Route111_Wally_Final_Text_Female::
	.string "WALLY: Phew... \l"
	.string "It wasn't easy, thanks for the help. \p"
	.string "We don't have time though.\nI don't know what it's going on, but \l"
	.string "we need to stop it as soon as possible. \p"
	.string "{PLAYER}, I'll go help MAY.\nYou try to stop TEAM MAGMA instead. \p"
	.string "We'll join you as soon as we can. $"
Route111_Wally_Final_Text_Male::
	.string "WALLY: Phew... \l"
	.string "It wasn't easy, thanks for the help. \p"
	.string "We don't have time though.\nI don't know what it's going on, but \l"
	.string "we need to stop it as soon as possible. \p"
	.string "{PLAYER}, I'll go help BRENDAN.\nYou try to stop TEAM MAGMA instead. \p"
	.string "We'll join you as soon as we can. $"

Route111_Wally_JoinRival::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route111_Wally_PostBattle::
	setvar VAR_WALLY_ROUTE111_TRIGGER, 3
	applymovement LOCALID_GRUNT_DESERT_GUARD4, Common_Movement_LockFacingDirection
	applymovement LOCALID_GRUNT_DESERT_GUARD3, Common_Movement_LockFacingDirection
	applymovement LOCALID_GRUNT_DESERT_GUARD2, Common_Movement_LockFacingDirection
	applymovement LOCALID_GRUNT_DESERT_GUARD1, Common_Movement_LockFacingDirection
	waitmovement LOCALID_GRUNT_DESERT_GUARD1
	waitmovement LOCALID_GRUNT_DESERT_GUARD2
	waitmovement LOCALID_GRUNT_DESERT_GUARD3
	waitmovement LOCALID_GRUNT_DESERT_GUARD4
	applymovement LOCALID_GRUNT_DESERT_GUARD4, Common_Movement_WalkUpSlow
	applymovement LOCALID_GRUNT_DESERT_GUARD1, Common_Movement_WalkUpSlow
	waitmovement LOCALID_GRUNT_DESERT_GUARD4
	waitmovement LOCALID_GRUNT_DESERT_GUARD1
	delay 5
	applymovement LOCALID_GRUNT_DESERT_GUARD1, Common_Movement_WalkUpSlow
	applymovement LOCALID_GRUNT_DESERT_GUARD4, Common_Movement_WalkUpSlow
	applymovement LOCALID_GRUNT_DESERT_GUARD3, Common_Movement_WalkUpSlow
	applymovement LOCALID_GRUNT_DESERT_GUARD2, Common_Movement_WalkUpSlow
	waitmovement LOCALID_GRUNT_DESERT_GUARD4
	waitmovement LOCALID_GRUNT_DESERT_GUARD1
	waitmovement LOCALID_GRUNT_DESERT_GUARD3
	waitmovement LOCALID_GRUNT_DESERT_GUARD2
	message Route111_GuardianGrunts_Flees
	applymovement LOCALID_GRUNT_DESERT_GUARD4, Common_Movement_UnlockFacingDirection
	applymovement LOCALID_GRUNT_DESERT_GUARD3, Common_Movement_UnlockFacingDirection
	applymovement LOCALID_GRUNT_DESERT_GUARD2, Common_Movement_UnlockFacingDirection
	applymovement LOCALID_GRUNT_DESERT_GUARD1, Common_Movement_UnlockFacingDirection
	waitmovement LOCALID_GRUNT_DESERT_GUARD4
	waitmovement LOCALID_GRUNT_DESERT_GUARD3
	waitmovement LOCALID_GRUNT_DESERT_GUARD2
	waitmovement LOCALID_GRUNT_DESERT_GUARD1
	applymovement LOCALID_GRUNT_DESERT_GUARD4, Route111_GuardianGrunt4_Flee_Movement
	applymovement LOCALID_GRUNT_DESERT_GUARD1, Route111_GuardianGrunt1_Flee_Movement
	waitmovement LOCALID_GRUNT_DESERT_GUARD4
	waitmovement LOCALID_GRUNT_DESERT_GUARD1
	closemessage
	message Route111_GuardianGrunts_Finale
	applymovement LOCALID_GRUNT_DESERT_GUARD3, Route111_GuardianGrunt3_Flee_Movement
	applymovement LOCALID_GRUNT_DESERT_GUARD2, Route111_GuardianGrunt2_Flee_Movement
	waitmovement LOCALID_GRUNT_DESERT_GUARD3
	waitmovement LOCALID_GRUNT_DESERT_GUARD2
	setobjectxyperm LOCALID_GRUNT_DESERT_GUARD1, 0, 0 @Move temporarly in order to not be shown again
	setobjectxyperm LOCALID_GRUNT_DESERT_GUARD2, 0, 0 @Move temporarly in order to not be shown again
	setobjectxyperm LOCALID_GRUNT_DESERT_GUARD3, 0, 0 @Move temporarly in order to not be shown again
	setobjectxyperm LOCALID_GRUNT_DESERT_GUARD4, 0, 0 @Move temporarly in order to not be shown again
	closemessage
	applymovement LOCALID_WALLY_DESERT, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route111_Wally_Final_Female
	goto_if_eq VAR_RESULT, FEMALE, Route111_Wally_Final_Male
	releaseall
	end
Route111_Wally_Final_Female::
	msgbox Route111_Wally_Final_Text_Female, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY_DESERT, Route111_Wally_JoinRival
	waitmovement 0
	setobjectxyperm LOCALID_WALLY_DESERT, 11, 37
	releaseall
	end
Route111_Wally_Final_Male::
	msgbox Route111_Wally_Final_Text_Male, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY_DESERT, Route111_Wally_JoinRival
	waitmovement 0
	setobjectxyperm LOCALID_WALLY_DESERT, 11, 37
	releaseall
	end

Route111_Wally_Desert_Script_Text::
	.string "WALLY: {PLAYER}, hurry up! \nWe'll handle it here. $"
Route111_Wally_Desert_Script_Text_Final::
	.string "WALLY: {PLAYER}, we've almost done it\n"
	.string "Lets beat MAXIE. $"
Route111_Wally_Desert_Script::
	lock
	call_if_defeated TRAINER_TABITHA_DESERT, Route111_Wally_Desert_Script_Final
	msgbox Route111_Wally_Desert_Script_Text, MSGBOX_DEFAULT
	release
	end
Route111_Wally_Desert_Script_Final::
	lock
	faceplayer
	msgbox Route111_Wally_Desert_Script_Text, MSGBOX_DEFAULT
	release
	end
Route111_Desert_May_Text::
	.string "MAY: {PLAYER}! Don't worry abous us, \n"
	.string "we can handle them. \lBut there's no other time, \l"
	.string "please go ahead and stop them! $"
Route111_Desert_May_Text_Final::
	.string "MAY: {PLAYER}, if we beat MAXIE\nwe end it. \p"
	.string "Lets do it! $"
Route111_Desert_Brendan_Text::
	.string "BRENDAN: {PLAYER}! Don't worry abous us, \n"
	.string "we can handle them. \lBut there's no other time, \l"
	.string "please go ahead and stop them! $"
Route111_Desert_Brendan_Text_Final::
	.string "BRENDAN: {PLAYER}, if we beat MAXIE\nwe end it. \p"
	.string "Lets do it! $"
Route111_Rival_Desert_Script::
	lock
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route111_Desert_May_Script
	goto_if_eq VAR_RESULT, FEMALE, Route111_Desert_Brendan_Script
	release
	end

Route111_Desert_May_Script::
	call_if_defeated TRAINER_TABITHA_DESERT, Route111_May_Desert_Script_Final
	msgbox Route111_Desert_May_Text, MSGBOX_DEFAULT
	release
	end 
Route111_Desert_Brendan_Script::
	call_if_defeated TRAINER_TABITHA_DESERT, Route111_Brendan_Desert_Script_Final
	msgbox Route111_Desert_Brendan_Text, MSGBOX_DEFAULT
	release
	end 

Route111_May_Desert_Script_Final::
	faceplayer
	msgbox Route111_Desert_May_Text_Final, MSGBOX_DEFAULT
	release
	end
Route111_Brendan_Desert_Script_Final::
	faceplayer
	msgbox Route111_Desert_Brendan_Text_Final, MSGBOX_DEFAULT
	release
	end
@@Multi Battle
Route111_DesertGrunt1_Defeat::
	.string "GRUNT: Grrr, it's not over! $"
Route111_DesertGrunt2_Defeat::
	.string "GRUNT: Tch... $"
Route111_Wally_Desert_MultiBattle::
	choose_mons
	compare VAR_RESULT, FALSE
	call_if_eq Route111_Wally_Desert_EventScript_ChooseMons
	msgbox MagmaGrunts_Before_MultiBattle_Text, MSGBOX_DEFAULT
    multi_2_vs_2 TRAINER_GRUNT_DESERT_MULTI1, Route111_DesertGrunt1_Defeat, TRAINER_GRUNT_DESERT_MULTI2, Route111_DesertGrunt2_Defeat,  PARTNER_WALLY_DESERT
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq RusturfTunnel_EventScript_Lost
    return 

Route111_Wally_Desert_EventScript_ChooseMons::
    msgbox MeteorFalls_1F_1R_Text_ChooseMons, MSGBOX_DEFAULT
    choose_mons
	compare VAR_RESULT, FALSE
	call_if_eq Route111_Wally_Desert_MultiBattle
    return

@@ Enemy Grunts in Desert Scripts
Roue111_Spinning_Grunt_EventScript::
	trainerbattle_single TRAINER_MAGMA_GRUNT_DESERT_SPINNER1, Desert_Text_Grunt1Spinning, MtChimney_Text_Grunt1Defeat
	msgbox MtChimney_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end
Roue111_Grunt1_EventScript::
	trainerbattle_single TRAINER_GRUNT_DESERT1, MtChimney_Text_Grunt2Intro, MtChimney_Text_Grunt2Defeat
	msgbox MtChimney_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

@@ Double Battle 2 trainers
Desert_Text_Grunt2Intro::
	.string "You shouldn't be here and\nI can't let you pass. $"
Desert_Text_Grunt2Defeat::
	.string "BOSS, I'm sorry... $"
Desert_Text_Grunt2PostBattle::
	.string "Maxie will make everyone happy. $"
Roue111_Grunt2_EventScript::
	trainerbattle_single TRAINER_GRUNT_DESERT2, Desert_Text_Grunt2Intro, Desert_Text_Grunt2Defeat
	msgbox Desert_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end
Desert_Text_Grunt3Intro::
	.string "You're not going anywhere! $"
Desert_Text_Grunt3Defeat::
	.string "No, it can't be! $"
Desert_Text_Grunt3PostBattle::
	.string "Our BOSS is too far ahead, \nyou'll not making in time. $"
Roue111_Grunt3_EventScript::
	trainerbattle_single TRAINER_GRUNT_DESERT3, Desert_Text_Grunt3Intro, Desert_Text_Grunt3Defeat
	msgbox Desert_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

Desert_Text_Grunt4Intro::
	.string "MAXIE told us to protect the desert\nand it's exactly what I'm gonnna do. $"
Desert_Text_Grunt4Defeat::
	.string "I-I failed? $"
Desert_Text_Grunt4PostBattle::
	.string "The other GRUNTS will revenge me. $"
Roue111_Grunt4_EventScript::
	trainerbattle_single TRAINER_GRUNT_DESERT4, Desert_Text_Grunt4Intro, Desert_Text_Grunt4Defeat
	msgbox Desert_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

Desert_Text_Grunt2Spinning::
	.string "I love deserts!\nIt's so warm here. $"
Desert_Text_Grunt2SpinningDefeat::
	.string "A-aargh W-why? $"
Desert_Text_Grunt2SpinningPostBattle::
	.string "You will not ruin my plan\nto stay here. $"
Roue111_GruntSpinning2_EventScript::
	trainerbattle_single TRAINER_MAGMA_GRUNT_DESERT_SPINNER2, Desert_Text_Grunt2Spinning, Desert_Text_Grunt2SpinningDefeat
	msgbox Desert_Text_Grunt2SpinningPostBattle, MSGBOX_AUTOCLOSE
	end
Desert_Text_Grunt3Spinning::
	.string "We're here to make everyone happy! $"
Desert_Text_Grunt3SpinningDefeat::
	.string "Wh-what?!"
Desert_Text_Grunt3SpinningPostBattle::
	.string "I didn't convince you enough. $"
Roue111_GruntSpinning3_EventScript::
	trainerbattle_single TRAINER_MAGMA_GRUNT_DESERT_SPINNER3, Desert_Text_Grunt3Spinning, Desert_Text_Grunt3SpinningDefeat
	msgbox Desert_Text_Grunt3SpinningPostBattle, MSGBOX_AUTOCLOSE
	end
Desert_Text_CoupleIntro::
	.string "We've decoded the messages\nin the cave. We understood\l"
	.string "the secret behind it! $"
Desert_Text_CoupleDefeat::
	.string "How did you manage to defeat us? $"
Desert_Text_CouplePostBattle::
	.string "I disappointed MAXIE... $"
Roue111_Grunt5_EventScript::
	trainerbattle_single TRAINER_GRUNT_DESERT5, Desert_Text_CoupleIntro, Desert_Text_CoupleDefeat
	msgbox Desert_Text_CouplePostBattle, MSGBOX_AUTOCLOSE
	end
Roue111_Grunt6_EventScript::
	trainerbattle_single TRAINER_GRUNT_DESERT6, Desert_Text_CoupleIntro, Desert_Text_CoupleDefeat
	msgbox Desert_Text_CouplePostBattle, MSGBOX_AUTOCLOSE
	end
Route111_WingGuard_Text::
	.string "You're not allowed to enter,\nour BOSS is there.\p"
	.string "So get lost! $"
Route111_WingGuard_EvenScript::
	lock
	msgbox Route111_WingGuard_Text, MSGBOX_DEFAULT
	release
	end
Route111_Desert_Tabitha_Intro::
	.string "TABITHA: Well well,\nso you're must be {PLAYER}. \p"
	.string "MAXIE warned us about you,\nit seems you've cause a lot\l"
	.string "of problems already. \p"
	.string "We came here after using\nthe METEORITE in MT.CHIMNEY.\p"
	.string "We used it in order to shake\nthe ground and wake REGIROCK up.\p"
	.string "We figured it out how to\nunlock the chamber, gaining access\l"
	.string "to the final room. \p"
	.string "You've come too late,\nMAXIE is already there.\p"
	.string "But I can't let you pass anyway,\nrisking to disturb the BOSS. $"

Route111_Desert_Grunts_EndHere::
	.string "GRUNTS: Your journey ends here\nfufufu... $"

Route111_Desert_WallyReachPlayer::
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_down
	walk_fast_left
	face_up
	step_end
Route111_Desert_RivalReachPlayer::
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_down
	walk_fast_right
	face_up
	step_end

Route111_Tabitha_Battle_Intro_May::
	.string "WALLY: {PLAYER}! It seems we made it\nin time!\p"
	.string "MAY: We'll take care of them,\n"
	.string "you just focus on moving ahead! $"
Route111_Tabitha_Battle_Intro_Brendan::
	.string "WALLY: {PLAYER}! It seems we made it\nin time!\p"
	.string "BRENDAN: We'll take care of them,\n"
	.string "you just focus on moving ahead! $"
Route111_Tabitha_Battle_Intro::
	.string "TABITHA: You're going nowhere! $"

Route111_Tabitha_Battle_Defeat::
	.string "H-how is possible?!\nWe will not lose! $"
 Route111_Tabitha_Finale::
	.string "TABITHA: Tch. Fine, you can go.\p"
	.string "You'll perish from our BOSS anyway. $"

Route111_Desert_Tabitha_EventScript::
	lock
	call_if_defeated TRAINER_TABITHA_DESERT, Route111_Desert_Tabitha_Final_Script
	hidefollower 0
	msgbox Route111_Desert_Tabitha_Intro, MSGBOX_DEFAULT
	applymovement LOCALID_GRUNT_RIGHT_WING, Common_Movement_WalkDown
	applymovement LOCALID_GRUNT_LEFT_WING, Common_Movement_WalkDown
	waitmovement LOCALID_GRUNT_RIGHT_WING
	waitmovement LOCALID_GRUNT_LEFT_WING
	applymovement LOCALID_GRUNT_RIGHT_WING Common_Movement_FacePlayer
	applymovement LOCALID_GRUNT_LEFT_WING Common_Movement_FacePlayer
	waitmovement LOCALID_GRUNT_RIGHT_WING
	waitmovement LOCALID_GRUNT_LEFT_WING
	msgbox Route111_Desert_Grunts_EndHere, MSGBOX_DEFAULT
	call RustboroCity_EventScript_PlayRivalMusic
	setobjectxyperm LOCALID_WALLY_DESERT 31, 84
	setobjectxyperm LOCALID_RIVAL_DESERT 27, 84
	addobject LOCALID_WALLY_DESERT
	addobject LOCALID_RIVAL_DESERT
	applymovement LOCALID_WALLY_DESERT, Route111_Desert_WallyReachPlayer
	applymovement LOCALID_RIVAL_DESERT, Route111_Desert_RivalReachPlayer
	waitmovement LOCALID_WALLY_DESERT
	waitmovement LOCALID_RIVAL_DESERT
	applymovement LOCALID_GRUNT_RIGHT_WING, Common_Movement_FaceDown
	applymovement LOCALID_GRUNT_LEFT_WING, Common_Movement_FaceDown
	waitmovement LOCALID_GRUNT_RIGHT_WING
	waitmovement LOCALID_GRUNT_LEFT_WING
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route111_Desert_Tabitha_May
	goto_if_eq VAR_RESULT, FEMALE, Route111_Desert_Tabitha_Brendan
	release 
	end
Route111_Desert_Tabitha_May::
	msgbox Route111_Tabitha_Battle_Intro_May, MSGBOX_DEFAULT
	goto Route111_Desert_Tabitha_Battle
	release
	end
Route111_Desert_Tabitha_Brendan::
	msgbox Route111_Tabitha_Battle_Intro_Brendan, MSGBOX_DEFAULT
	goto Route111_Desert_Tabitha_Battle
	release
	end

Route111_Desert_Tabitha_Battle::
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	trainerbattle_single TRAINER_TABITHA_DESERT, Route111_Tabitha_Battle_Intro, Route111_Tabitha_Battle_Defeat, Route111_Desert_Tabitha_OutEntrance, FALSE
	Route111_Desert_Tabitha_OutEntrance:
	applymovement LOCALID_GRUNT_RIGHT_WING, Common_Movement_WalkRight
	applymovement LOCALID_GRUNT_LEFT_WING, Common_Movement_WalkLeft
	waitmovement LOCALID_GRUNT_RIGHT_WING
	waitmovement LOCALID_GRUNT_LEFT_WING
	applymovement LOCALID_GRUNT_RIGHT_WING, Common_Movement_FaceLeft
	applymovement LOCALID_GRUNT_LEFT_WING, Common_Movement_FaceRight
	waitmovement LOCALID_GRUNT_RIGHT_WING
	waitmovement LOCALID_GRUNT_LEFT_WING
	msgbox Route111_Tabitha_Finale, MSGBOX_DEFAULT
	applymovement LOCALID_TABITHA_DESERT, Common_Movement_WalkRight
	waitmovement LOCALID_TABITHA_DESERT
	applymovement LOCALID_TABITHA_DESERT, Common_Movement_FaceLeft
	waitmovement LOCALID_TABITHA_DESERT
	setvar VAR_WALLY_ROUTE111_TRIGGER, 100
	call Route111_Desert_SetObjectPositionAfterBattle
	release 
	end
Route111_Desert_SetObjectPositionAfterBattle::
	call_if_unset FLAG_MAXIE_DESERT, Route111_Desert_PrepareObjForMaxie
	return
Route111_Desert_PrepareObjForMaxie::
	setobjectxyperm LOCALID_WALLY_DESERT 30, 90
	setobjectxyperm LOCALID_RIVAL_DESERT 28, 90
	setobjectxyperm LOCALID_TABITHA_DESERT 30, 88
	setobjectxyperm LOCALID_GRUNT_LEFT_WING 27, 89
	setobjectxyperm LOCALID_GRUNT_RIGHT_WING 31, 89
	setobjectmovementtype LOCALID_WALLY_DESERT, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_RIVAL_DESERT, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_TABITHA_DESERT, MOVEMENT_TYPE_FACE_LEFT
	setobjectmovementtype LOCALID_GRUNT_RIGHT_WING, MOVEMENT_TYPE_FACE_LEFT
	setobjectmovementtype LOCALID_GRUNT_LEFT_WING, MOVEMENT_TYPE_FACE_RIGHT
	return

Route111_Desert_Tabitha_Final_Script::
	lock
	msgbox Route111_Tabitha_Finale, MSGBOX_DEFAULT
	release
	end
@ ***************	 TEAM MAGMA - DESERT END	********************

Route111_EventScript_Cacturne::
	lockall
	faceplayer
	setwildbattle SPECIES_CACTURNE, 40
	waitse
	playmoncry SPECIES_CACTURNE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, DewfordTown_EventScript_DefeatedSandy
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, DewfordTown_EventScript_DefeatedSandy
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, DewfordTown_EventScript_DefeatedSandy 
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, DewfordTown_EventScript_DefeatedSandy
	releaseall
	end

Route111_EventScript_Maractus::
	lockall
	faceplayer
	setwildbattle SPECIES_MARACTUS, 40
	waitse
	playmoncry SPECIES_MARACTUS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, DewfordTown_EventScript_DefeatedSandy
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, DewfordTown_EventScript_DefeatedSandy
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, DewfordTown_EventScript_DefeatedSandy 
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, DewfordTown_EventScript_DefeatedSandy
	releaseall
	end

Route111_EventScript_SetFallingPlayerGfx::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route111_EventScript_SetFallingPlayerGfxMale
	goto_if_eq VAR_RESULT, FEMALE, Route111_EventScript_SetFallingPlayerGfxFemale
	return

Route111_EventScript_SetFallingPlayerGfxMale::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	return

Route111_EventScript_SetFallingPlayerGfxFemale::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	return

Route111_EventScript_CheckSetSandstorm::
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	goto_if_lt VAR_TEMP_1, 34, Route111_EventScript_EndCheckSetSandstorm
	goto_if_gt VAR_TEMP_1, 107, Route111_EventScript_EndCheckSetSandstorm
	goto_if_gt VAR_TEMP_1, 72, Route111_EventScript_SetSandstorm
	goto_if_gt VAR_TEMP_0, 2000, Route111_EventScript_EndCheckSetSandstorm
	goto_if_lt VAR_TEMP_0, 8, Route111_EventScript_EndCheckSetSandstorm
Route111_EventScript_SetSandstorm::
	setweather WEATHER_SANDSTORM
Route111_EventScript_EndCheckSetSandstorm::
	return

Route111_EventScript_SetWallyRoute111::
	goto_if_set FLAG_HIDE_WALLY_ROUTE111, Common_EventScript_Return
	setobjectxyperm LOCALID_WALLY_R111, 19, 101
	setvar VAR_WALLY_ROUTE111_TRIGGER, 1
	return
Route111_EventScript_WallyWarp::
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, Route111_EventScript_SetWallyRoute111
	return
Route111_EventScript_SetWinstratesNotDefeated::
	clearflag FLAG_HIDE_ROUTE_111_VICTOR_WINSTRATE
	setflag FLAG_HIDE_ROUTE_111_VICTORIA_WINSTRATE
	setflag FLAG_HIDE_ROUTE_111_VIVI_WINSTRATE
	setflag FLAG_HIDE_ROUTE_111_VICKY_WINSTRATE
	cleartrainerflag TRAINER_VICTOR
	cleartrainerflag TRAINER_VICTORIA
	cleartrainerflag TRAINER_VIVI
	end

Route111_EventScript_SetLayoutNoMirageTower::
	setmaplayoutindex LAYOUT_ROUTE111_NO_MIRAGE_TOWER
	return

Route111_EventScript_SetMirageTowerGone::
	setvar VAR_MIRAGE_TOWER_STATE, 3
	return

Route111_OnWarp:
	map_script_2 VAR_MIRAGE_TOWER_STATE, 1, Route111_EventScript_HidePlayerForMirageTower
	.2byte 0

Route111_EventScript_HidePlayerForMirageTower::
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_LITTLEROOT_TOWN
	end
Route111_EventScript_SetMusicForMagma::
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	return

Route111_OnFrame:
	map_script_2 VAR_WALLY_ROUTE111_TRIGGER, 6, Route111_Andry_EventScript_OnFrame_Final
	map_script_2 VAR_WALLY_ROUTE111_TRIGGER, 5, Route111_CloseRegiDoors_After_MagmaDesert_EventScript
	map_script_2 VAR_MIRAGE_TOWER_STATE, 1, Route111_EventScript_MirageTowerDisappear
	.2byte 0

@After beating Maxie, reset the doors of Regirock and the state at the original one
Route111_CloseRegiDoors_After_MagmaDesert_EventScript::
	lock
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 12 @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	clearflag FLAG_REGI_DOORS_OPENED
	setvar VAR_LAVARIDGE_TOWN_STATE, 3 @Event no more triggerable in load
	setvar VAR_WALLY_ROUTE111_TRIGGER, 6 @Event no more triggerable in map
	clearflag FLAG_HIDE_ANDRY_ROUTE111 @Andry visible
	fadescreenswapbuffers FADE_TO_BLACK
	setmetatile 29, 86, METATILE_General_RockWall_RockBase, TRUE
	setmetatile 29, 87, METATILE_General_RockWall_SandBase, TRUE
	setobjectxyperm LOCALID_ANDRY_MAGMA_DESERT 31, 82
	special DrawWholeMapView
	fadescreenswapbuffers FADE_FROM_BLACK
	waitstate
	addobject LOCALID_ANDRY_MAGMA_DESERT
	@Andry Script:
	applymovement LOCALID_ANDRY_MAGMA_DESERT, Route111_Desert_AndryReachPlayer
	waitmovement 0
	msgbox Route111_Andry_MagmDesert_Speech, MSGBOX_DEFAULT
	giveitem ITEM_LIFE_ORB
	msgbox Route111_Andry_MagmDesert_Leave_Text, MSGBOX_DEFAULT
	@Warp out of desert
	setobjectxyperm LOCALID_PLAYER 11, 67
	setwarp MAP_ROUTE111, 11, 67
	special DoContestHallWarp
	waitstate
	msgbox Demo_IsFinished_Text, MSGBOX_DEFAULT
	release
	end
Route111_Andry_EventScript_OnFrame_Final::
	lock
	setweather WEATHER_SUNNY
	setvar VAR_TEMP_3, 0
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 2, Route111_EventScript_KeepMagmaMusicTrigger
	fadenewbgm MUS_ROUTE110
	doweather
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	applymovement LOCALID_ANDRY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Route111_Andry_MagmDesert_Finale, MSGBOX_DEFAULT
	call Route111_AndryWalkingScript
	removeobject LOCALID_ANDRY_MAGMA_DESERT
	call Level_Cap_Increased_Global_Script
	setvar VAR_WALLY_ROUTE111_TRIGGER, 7 @No more trigger
	release
	end
Route111_Andry_MagmDesert_Speech::
	.string "So you must be {PLAYER}. \p"
	.string "I came here because Ed- \nI mean, SPLITFACE told me to, \l"
	.string "but it looks like you've already\lhandled everything yourself. \p"
	.string "Sorry I wasn't here sooner\nto give you an hand. \p"
	.string "You're strong, I like that.\n"
	.string "By the way, I'm ANDRY. \p"
	.string "ANDRY: Here, take this item.\nIt will help you on your journey. $"

Route111_Andry_MagmDesert_Leave_Text::
	.string "ANDRY: Now, lets leave. $"
Route111_Andry_MagmDesert_Finale::
	.string "ANDRY: Here we go. \p"
	.string "{PLAYER}, I have to go now.\n"
	.string "Thank you, we'll meet again. $"
Route111_Desert_AndryReachPlayer::
	walk_down
	walk_down
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	face_player
	step_end

Route111_EventScript_MirageTowerDisappear::
	lockall
	special StartMirageTowerShake
	waitstate
	delay 24
	playse SE_FALL
	addobject LOCALID_ROUTE111_PLAYER_FALLING
	special StartPlayerDescendMirageTower
	waitstate
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_LITTLEROOT_TOWN
	removeobject LOCALID_ROUTE111_PLAYER_FALLING
	delay 16
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 16
	special StartMirageTowerDisintegration
	waitstate
	special StartMirageTowerFossilFallAndSink
	waitstate
	setvar VAR_MIRAGE_TOWER_STATE, 2
	clearflag FLAG_HIDE_DESERT_UNDERPASS_FOSSIL
	goto_if_set FLAG_CHOSE_CLAW_FOSSIL, Route111_EventScript_RootFossilDisappeared
	msgbox Route111_Text_ClawFossilDisappeared, MSGBOX_DEFAULT
	releaseall
	end

Route111_EventScript_RootFossilDisappeared::
	msgbox Route111_Text_RootFossilDisappeared, MSGBOX_DEFAULT
	releaseall
	end

@ Unused
Route111_Movement_PlayerFall::
	lock_anim
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

Route111_EventScript_Girl::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_ROUTE_111_RECEIVED_BERRY, Route111_EventScript_ReceivedBerry
	msgbox Route111_Text_WateredPlantsEveryDayTakeBerry, MSGBOX_DEFAULT
	giveitem ITEM_RAZZ_BERRY, 10
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_ROUTE_111_RECEIVED_BERRY
	special GetPlayerBigGuyGirlString
	msgbox Route111_Text_GoingToTryToMakeDifferentColorBerries, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_ReceivedBerry::
	msgbox Route111_Text_WhatColorBerriesToLookForToday, MSGBOX_DEFAULT
	release
	end

@ Unused
Route111_EventScript_ViciousSandstormTriggerUp::
	lockall
	setvar VAR_0x8004, 0
	goto Route111_EventScript_ViciousSandstormTrigger
	end

Route111_EventScript_ViciousSandstormTriggerDown::
	lockall
	setvar VAR_0x8004, 1
	goto Route111_EventScript_ViciousSandstormTrigger
	end

Route111_EventScript_ViciousSandstormTriggerLeft::
	lockall
	setvar VAR_0x8004, 2
	goto Route111_EventScript_ViciousSandstormTrigger
	end

@ Unused
Route111_EventScript_ViciousSandstormTriggerRight::
	lockall
	setvar VAR_0x8004, 3
	goto Route111_EventScript_ViciousSandstormTrigger
	end

Route111_EventScript_ViciousSandstormTrigger::
	checkitem ITEM_GO_GOGGLES
	goto_if_eq VAR_RESULT, FALSE, Route111_EventScript_PreventRouteAccess
	setvar VAR_TEMP_3, 1
	releaseall
	end

Route111_EventScript_PreventRouteAccess::
	msgbox gText_SandstormIsVicious, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8004, 0, Route111_EventScript_PushUpFromRoute
	call_if_eq VAR_0x8004, 1, Route111_EventScript_PushDownFromRoute
	call_if_eq VAR_0x8004, 2, Route111_EventScript_PushLeftFromRoute
	call_if_eq VAR_0x8004, 3, Route111_EventScript_PushRightFromRoute
	releaseall
	end

Route111_EventScript_PushUpFromRoute::
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_PushUpFromRoute
	waitmovement 0
	return

Route111_EventScript_PushDownFromRoute::
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_PushDownFromRoute
	waitmovement 0
	return

Route111_EventScript_PushLeftFromRoute::
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_PushLeftFromRoute
	waitmovement 0
	return

Route111_EventScript_PushRightFromRoute::
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_PushRightFromRoute
	waitmovement 0
	return

Route111_Movement_PushUpFromRoute:
	walk_up
	step_end

Route111_Movement_PushDownFromRoute:
	walk_down
	step_end

Route111_Movement_PushLeftFromRoute:
	walk_left
	step_end

Route111_Movement_PushRightFromRoute:
	walk_right
	step_end

Route111_EventScript_SunTrigger::
	setweather WEATHER_SUNNY
	setvar VAR_TEMP_3, 0
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 2, Route111_EventScript_KeepMagmaMusicTrigger
	fadenewbgm MUS_ROUTE110
	doweather
	end

Route111_EventScript_SandstormTrigger::
	setweather WEATHER_SANDSTORM
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 2, Route111_EventScript_KeepMagmaMusicTrigger
	fadenewbgm MUS_DESERT
	doweather
	end
Route111_EventScript_KeepMagmaMusicTrigger::
	doweather
	end

Route111_EventScript_Victor::
	lock
	faceplayer
	setflag FLAG_LANDMARK_WINSTRATE_FAMILY
	msgbox Route111_Text_BattleOurFamily, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_EventScript_BattleWinstrates
	msgbox Route111_Text_IsThatSo, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_BattleWinstrates::
	msgbox Route111_Text_VictorIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_VICTOR, Route111_Text_VictorDefeat
	applymovement LOCALID_VICTOR, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	msgbox Route111_Text_VictorPostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_VICTOR, Route111_Movement_WinstrateEnterHouse
	waitmovement 0
	removeobject LOCALID_VICTOR
	call Route111_EventScript_CloseWinstrateDoor
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_WaitForNextWinstrate
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	addobject LOCALID_VICTORIA
	applymovement LOCALID_VICTORIA, Route111_Movement_WinstrateExitHouse
	waitmovement 0
	call Route111_EventScript_CloseWinstrateDoor
	msgbox Route111_Text_VictoriaIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_VICTORIA, Route111_Text_VictoriaDefeat
	applymovement LOCALID_VICTORIA, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	msgbox Route111_Text_VictoriaPostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_VICTORIA, Route111_Movement_WinstrateEnterHouse
	waitmovement 0
	removeobject LOCALID_VICTORIA
	call Route111_EventScript_CloseWinstrateDoor
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_WaitForNextWinstrate
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	addobject LOCALID_VIVI
	applymovement LOCALID_VIVI, Route111_Movement_WinstrateExitHouse
	waitmovement 0
	call Route111_EventScript_CloseWinstrateDoor
	msgbox Route111_Text_ViviIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_VIVI, Route111_Text_ViviDefeat
	applymovement LOCALID_VIVI, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	msgbox Route111_Text_ViviPostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_VIVI, Route111_Movement_WinstrateEnterHouse
	waitmovement 0
	removeobject LOCALID_VIVI
	call Route111_EventScript_CloseWinstrateDoor
	applymovement OBJ_EVENT_ID_PLAYER, Route111_Movement_WaitForNextWinstrate
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	addobject LOCALID_VICKY
	applymovement LOCALID_VICKY, Route111_Movement_WinstrateExitHouse
	waitmovement 0
	call Route111_EventScript_CloseWinstrateDoor
	msgbox Route111_Text_VickyIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_VICKY, Route111_Text_VickyDefeat
	msgbox Route111_Text_VickyPostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_VICKY, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	call Route111_EventScript_OpenWinstrateDoor
	applymovement LOCALID_VICKY, Route111_Movement_WinstrateEnterHouse
	waitmovement 0
	removeobject LOCALID_VICKY
	call Route111_EventScript_CloseWinstrateDoor
	release
	end

Route111_EventScript_OpenWinstrateDoor::
	opendoor 13, 113
	waitdooranim
	return

Route111_EventScript_CloseWinstrateDoor::
	closedoor 13, 113
	waitdooranim
	return

Route111_Movement_WinstrateEnterHouse:
	walk_in_place_faster_up
	walk_up
	step_end

Route111_Movement_WinstrateExitHouse:
	walk_down
	step_end

Route111_Movement_WaitForNextWinstrate:
	delay_16
	delay_16
	delay_16
	step_end

Route111_EventScript_RouteSignMauville::
	msgbox Route111_Text_RouteSignMauville, MSGBOX_SIGN
	end

Route111_EventScript_WinstrateHouseSign::
	msgbox Route111_Text_WinstrateHouseSign, MSGBOX_SIGN
	end

Route111_EventScript_RouteSign112::
	msgbox Route111_Text_RouteSign112, MSGBOX_SIGN
	end

Route111_EventScript_RouteSign113::
	msgbox Route111_Text_RouteSign113, MSGBOX_SIGN
	end

Route111_EventScript_OldLadysRestStopSign::
	msgbox Route111_Text_OldLadysRestStopSign, MSGBOX_SIGN
	end

Route111_EventScript_TrainerTipsSpAtkSpDef::
	msgbox Route111_Text_TrainerTipsSpAtkSpDef, MSGBOX_SIGN
	end

Route111_EventScript_Man1::
	msgbox Route111_Text_ToughToKeepWinningUpTheRanks, MSGBOX_NPC
	end

Route111_EventScript_Man2::
	msgbox Route111_Text_WinstrateFamilyDestroyedMe, MSGBOX_NPC
	end

Route111_EventScript_Hiker::
	lock
	faceplayer
	goto_if_eq VAR_MIRAGE_TOWER_STATE, 3, Route111_EventScript_HikerMirageTowerGone
	goto_if_eq VAR_MIRAGE_TOWER_STATE, 2, Route111_EventScript_HikerMirageTowerDisintegrated
	goto_if_set FLAG_MIRAGE_TOWER_VISIBLE, Route111_EventScript_HikerMirageTowerVisible
	msgbox Route111_Text_ShouldBeMirageTowerAroundHere, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_HikerMirageTowerGone::
	msgbox Route111_Text_MirageTowerHasntBeenSeenSince, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_HikerMirageTowerDisintegrated::
	msgbox Route111_Text_ThatWasShockingSandRainedDown, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_HikerMirageTowerVisible::
	msgbox Route111_Text_MirageTowerClearlyVisible, MSGBOX_DEFAULT
	release
	end

@Route111_EventScript_RockSmashTipFatMan::
@	lockall
@	applymovement LOCALID_ROCK_SMASH_MAN, Common_Movement_FacePlayer
@	waitmovement 0
@	msgbox Route111_Text_MauvilleUncleToldMeToTakeRockSmash, MSGBOX_DEFAULT
@	closemessage
@	applymovement LOCALID_ROCK_SMASH_MAN, Common_Movement_FaceOriginalDirection
@	waitmovement 0
@	releaseall
@	end

Route111_EventScript_Drew::
	trainerbattle_single TRAINER_DREW, Route111_Text_DrewIntro, Route111_Text_DrewDefeat
	msgbox Route111_Text_DrewPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Heidi::
	trainerbattle_single TRAINER_HEIDI, Route111_Text_HeidiIntro, Route111_Text_HeidiDefeat
	msgbox Route111_Text_HeidiPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Beau::
	trainerbattle_single TRAINER_BEAU, Route111_Text_BeauIntro, Route111_Text_BeauDefeat
	msgbox Route111_Text_BeauPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Becky::
	trainerbattle_single TRAINER_BECKY, Route111_Text_BeckyIntro, Route111_Text_BeckyDefeat
	msgbox Route111_Text_BeckyPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Dusty::
	trainerbattle_single TRAINER_DUSTY_1, Route111_Text_DustyIntro, Route111_Text_DustyDefeat, Route111_EventScript_RegisterDusty
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route111_EventScript_RematchDusty
	msgbox Route111_Text_DustyPostBattle, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_RegisterDusty::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route111_Text_DustyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DUSTY_1
	release
	end

Route111_EventScript_RematchDusty::
	trainerbattle_rematch TRAINER_DUSTY_1, Route111_Text_DustyRematchIntro, Route111_Text_DustyRematchDefeat
	msgbox Route111_Text_DustyPostRematch, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Travis::
	trainerbattle_single TRAINER_TRAVIS, Route111_Text_TravisIntro, Route111_Text_TravisDefeat
	msgbox Route111_Text_TravisPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Irene::
	trainerbattle_single TRAINER_IRENE, Route111_Text_IreneIntro, Route111_Text_IreneDefeat
	msgbox Route111_Text_IrenePostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Daisuke::
	trainerbattle_single TRAINER_DAISUKE, Route111_Text_DaisukeIntro, Route111_Text_DaisukeDefeat
	msgbox Route111_Text_DaisukePostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Wilton::
	trainerbattle_single TRAINER_WILTON_1, Route111_Text_WiltonIntro, Route111_Text_WiltonDefeat, Route111_EventScript_RegisterWilton
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route111_EventScript_RematchWilton
	msgbox Route111_Text_WiltonPostBattle, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_RegisterWilton::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route111_Text_WiltonRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_WILTON_1
	release
	end

Route111_EventScript_RematchWilton::
	trainerbattle_rematch TRAINER_WILTON_1, Route111_Text_WiltonRematchIntro, Route111_Text_WiltonRematchDefeat
	msgbox Route111_Text_WiltonPostRematch, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Brooke::
	trainerbattle_single TRAINER_BROOKE_1, Route111_Text_BrookeIntro, Route111_Text_BrookeDefeat, Route111_EventScript_RegisterBrooke
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route111_EventScript_RematchBrooke
	msgbox Route111_Text_BrookePostBattle, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_RegisterBrooke::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route111_Text_BrookeRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BROOKE_1
	release
	end

Route111_EventScript_RematchBrooke::
	trainerbattle_rematch TRAINER_BROOKE_1, Route111_Text_BrookeRematchIntro, Route111_Text_BrookeRematchDefeat
	msgbox Route111_Text_BrookePostRematch, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Hayden::
	trainerbattle_single TRAINER_HAYDEN, Route111_Text_HaydenIntro, Route111_Text_HaydenDefeat
	msgbox Route111_Text_HaydenPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Bianca::
	trainerbattle_single TRAINER_BIANCA, Route111_Text_BiancaIntro, Route111_Text_BiancaDefeat
	msgbox Route111_Text_BiancaPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Tyron::
	trainerbattle_single TRAINER_TYRON, Route111_Text_TyronIntro, Route111_Text_TyronDefeat
	msgbox Route111_Text_TyronPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Celina::
	trainerbattle_single TRAINER_CELINA, Route111_Text_CelinaIntro, Route111_Text_CelinaDefeat
	msgbox Route111_Text_CelinaPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Celia::
	trainerbattle_single TRAINER_CELIA, Route111_Text_CeliaIntro, Route111_Text_CeliaDefeat
	msgbox Route111_Text_CeliaPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Bryan::
	trainerbattle_single TRAINER_BRYAN, Route111_Text_BryanIntro, Route111_Text_BryanDefeat
	msgbox Route111_Text_BryanPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_Branden::
	trainerbattle_single TRAINER_BRANDEN, Route111_Text_BrandenIntro, Route111_Text_BrandenDefeat
	msgbox Route111_Text_BrandenPostBattle, MSGBOX_AUTOCLOSE
	end

Route111_EventScript_TrainerHillSign::
	msgbox Route111_Text_TrainerHillSign, MSGBOX_SIGN
	end

Route111_EventScript_Wally_BattleTrigger1::
	lock
	applymovement LOCALID_WALLY_R111, Common_Movement_FaceDown
	applymovement LOCALID_WALLY_R111, Common_Movement_ExclamationMark
	waitmovement 0
	playse SE_PIN
	msgbox Route111_Text_WallyCallPlayer, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	waitmovement LOCALID_PLAYER
	turnobject LOCALID_PLAYER, DIR_SOUTH
	trainerbattle_single TRAINER_WALLY_MAUVILLE, Route111_Text_WallyIntro, Route111_Text_WallyDefeat, Route111_EventScript_Wally_PostBattle, NO_MUSIC
	release
	end
Player_Trigger2::
	walk_up
	walk_left
	step_end
Route111_EventScript_Wally_BattleTrigger2::
	lock
	applymovement LOCALID_WALLY_R111, Common_Movement_FaceDown
	applymovement LOCALID_WALLY_R111, Common_Movement_ExclamationMark
	waitmovement 0
	playse SE_PIN
	msgbox Route111_Text_WallyCallPlayer, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Player_Trigger2
	waitmovement 0
	turnobject LOCALID_PLAYER, DIR_SOUTH
	trainerbattle_single TRAINER_WALLY_MAUVILLE, Route111_Text_WallyIntro, Route111_Text_WallyDefeat, Route111_EventScript_Wally_PostBattle, NO_MUSIC
	release
	end
Route111_EventScript_Wally_PostBattle::
	msgbox Route111_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	applymovement LOCALID_WALLY_R111, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement LOCALID_WALLY_R111, Common_Movement_Delay32
	waitmovement 0
	applymovement LOCALID_WALLY_R111, Common_Movement_Delay32
	waitmovement 0
	applymovement LOCALID_WALLY_R111, Common_Movement_QuestionMark
	msgbox Wally_Uhm, MSGBOX_DEFAULT
	waitmovement 0
	applymovement LOCALID_WALLY_R111, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Route111_Text_Wally_SomethingForMe, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	msgbox Route111_Text_Wally_GiveHM03, MSGBOX_DEFAULT
	waitfanfare
	msgbox Route111_Text_Wally_AfterGivenHM03, MSGBOX_DEFAULT
	msgbox Route111_Text_Wally_Finale, MSGBOX_DEFAULT	
	applymovement LOCALID_WALLY_R111, Common_Movement_FaceOriginalDirection
	waitmovement 0
	@Here he smashes the rock
	applymovement LOCALID_BREAKABLE_ROCK, Movement_SmashRock
	waitmovement 0
	removeobject LOCALID_BREAKABLE_ROCK
	@@@
	applymovement LOCALID_WALLY_R111, Wally_Ending_Scene
	waitmovement 0
	setflag FLAG_HIDE_WALLY_ROUTE111
	setvar VAR_WALLY_ROUTE111_TRIGGER, 0xFF
	setvar VAR_ROUTE111_STATE, 1 @Handle the Andry/Edo Triggers
	removeobject LOCALID_WALLY_R111
	release
	end

Wally_Ending_Scene::
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	step_end

@@@@@@@@@@ ANDRY/EDO Interaction @@@@@@@@@@@@@@


@@@ Movements @@@
Route111_AndryMovement::
	face_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end
Route111_EdoMovement::
	face_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route111_PlayerMovement1:
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

Route111_PlayerMovement2:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

Route111_PlayerMovement3:
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

Route111_PlayerMovement4:
	walk_up
	walk_up
	walk_up
	step_end

Route111_PlayerMovement5:
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

Route111_PlayerMovement6:
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

Route111_PlayerMovement7:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

@@@ Common @@@
Route111_AndryWalkingScript::
	applymovement LOCALID_ANDRY, Route111_AndryMovement
	waitmovement  LOCALID_ANDRY
	removeobject  LOCALID_ANDRY
	return
Route111_EdoSurprised::
	msgbox Route111_EdoCaldo, MSGBOX_AUTOCLOSE
	applymovement LOCALID_EDO, Common_Movement_FacePlayer
	waitmovement  LOCALID_EDO
	applymovement LOCALID_EDO, Common_Movement_ExclamationMark
	waitmovement  LOCALID_EDO
	return

Route111_EdoDesertInteraction::
	msgbox Route111_EdoIntro_Text, MSGBOX_DEFAULT
	applymovement LOCALID_EDO, Common_Movement_QuestionMark
	waitmovement  LOCALID_EDO
	msgbox Route111_EdoMiddleInteraction_Text1, MSGBOX_DEFAULT
	applymovement LOCALID_EDO, Common_Movement_FaceLeft
	waitmovement  LOCALID_EDO
	msgbox Route111_EdoMiddleInteraction_Text2, MSGBOX_DEFAULT
	applymovement LOCALID_EDO, Common_Movement_FacePlayer
	waitmovement  LOCALID_EDO
	msgbox Route111_EdoMiddleInteraction_Text3, MSGBOX_DEFAULT
	return

Route111_AndryEdoEncounter1::
	lock
	setvar VAR_ROUTE111_STATE, 2
	call Route111_AndryWalkingScript
	applymovement OBJ_EVENT_ID_PLAYER, Route111_PlayerMovement1
	waitmovement OBJ_EVENT_ID_PLAYER
	call Route111_EdoSurprised
	call Route111_EdoDesertInteraction
	applymovement LOCALID_EDO, Route111_EdoMovement
	message Route111_EdoInteractionExit_Text
	waitmovement 
	removeobject LOCALID_EDO
	release
	end

Route111_AndryEdoEncounter2::
	lock
	setvar VAR_ROUTE111_STATE, 2
	call Route111_AndryWalkingScript
	applymovement OBJ_EVENT_ID_PLAYER, Route111_PlayerMovement2
	waitmovement OBJ_EVENT_ID_PLAYER
	call Route111_EdoSurprised
	call Route111_EdoDesertInteraction
	applymovement LOCALID_EDO, Route111_EdoMovement
	message Route111_EdoInteractionExit_Text
	waitmovement 
	removeobject LOCALID_EDO
	release
	end

Route111_AndryEdoEncounter3::
	lock
	setvar VAR_ROUTE111_STATE, 2
	call Route111_AndryWalkingScript
	applymovement OBJ_EVENT_ID_PLAYER, Route111_PlayerMovement3
	waitmovement OBJ_EVENT_ID_PLAYER
	call Route111_EdoSurprised
	call Route111_EdoDesertInteraction
	applymovement LOCALID_EDO, Route111_EdoMovement
	message Route111_EdoInteractionExit_Text
	waitmovement 
	removeobject LOCALID_EDO
	release
	end

Route111_AndryEdoEncounter4::
	lock
	setvar VAR_ROUTE111_STATE, 2
	call Route111_AndryWalkingScript
	applymovement OBJ_EVENT_ID_PLAYER, Route111_PlayerMovement4
	waitmovement OBJ_EVENT_ID_PLAYER
	call Route111_EdoSurprised
	call Route111_EdoDesertInteraction
	applymovement LOCALID_EDO, Route111_EdoMovement
	message Route111_EdoInteractionExit_Text
	waitmovement 
	removeobject LOCALID_EDO
	release
	end

Route111_AndryEdoEncounter5::
	lock
	setvar VAR_ROUTE111_STATE, 2
	call Route111_AndryWalkingScript
	applymovement OBJ_EVENT_ID_PLAYER, Route111_PlayerMovement5
	waitmovement OBJ_EVENT_ID_PLAYER
	call Route111_EdoSurprised
	call Route111_EdoDesertInteraction
	applymovement LOCALID_EDO, Route111_EdoMovement
	message Route111_EdoInteractionExit_Text
	waitmovement 
	removeobject LOCALID_EDO
	release
	end

Route111_AndryEdoEncounter6::
	lock
	setvar VAR_ROUTE111_STATE, 2
	call Route111_AndryWalkingScript
	applymovement OBJ_EVENT_ID_PLAYER, Route111_PlayerMovement6
	waitmovement OBJ_EVENT_ID_PLAYER
	call Route111_EdoSurprised
	call Route111_EdoDesertInteraction
	applymovement LOCALID_EDO, Route111_EdoMovement
	message Route111_EdoInteractionExit_Text
	waitmovement 
	removeobject LOCALID_EDO
	release
	end

Route111_AndryEdoEncounter7::
	lock
	setvar VAR_ROUTE111_STATE, 2
	call Route111_AndryWalkingScript
	applymovement OBJ_EVENT_ID_PLAYER, Route111_PlayerMovement7
	waitmovement OBJ_EVENT_ID_PLAYER
	call Route111_EdoSurprised
	call Route111_EdoDesertInteraction
	applymovement LOCALID_EDO, Route111_EdoMovement
	message Route111_EdoInteractionExit_Text
	waitmovement 
	removeobject LOCALID_EDO
	release
	end

Route111_Text_BattleOurFamily:
	.string "Hello! I take it you're a traveler.\p"
	.string "How's this? What do you say to taking\n"
	.string "on our family of four in a series of\l"
	.string "POKéMON battles?  $"

Route111_Text_IsThatSo:
	.string "Is that so?\n"
	.string "Drop in, if you change your mind!  $"

Route111_Text_VictorIntro:
	.string "That's the spirit! I like you!  $"

Route111_Text_VictorDefeat:
	.string "Aiyah!\n"
	.string "You're a lot tougher than I expected!  $"

Route111_Text_VictorPostBattle:
	.string "Hey, all!\n"
	.string "I've found a pretty strong TRAINER!  $"

Route111_Text_VictoriaIntro:
	.string "Oh, my goodness! Aren't you young?\p"
	.string "You must be quite the TRAINER to beat\n"
	.string "my husband, though.\p"
	.string "It's my turn to battle now!  $"

Route111_Text_VictoriaDefeat:
	.string "Oh, gosh!\n"
	.string "I can't get over how strong you are!  $"

Route111_Text_VictoriaPostBattle:
	.string "There's a strong TRAINER here!\n"
	.string "This one's really strong!  $"

Route111_Text_ViviIntro:
	.string "You're stronger than Mommy? Wow!\p"
	.string "But I'm strong, too!\n"
	.string "Really! Honestly!  $"

Route111_Text_ViviDefeat:
	.string "Huh? Did I just lose?  $"

Route111_Text_ViviPostBattle:
	.string "This stinks…\p"
	.string "…Snivel… Grandma!  $"

Route111_Text_VickyIntro:
	.string "How dare you make my granddaughter\n"
	.string "cry!\p"
	.string "For that, I'm going to smack you!\n"
	.string "Prepare to lose!  $"

Route111_Text_VickyDefeat:
	.string "Kwah! You are strong…\n"
	.string "My granddaughter was right…  $"

Route111_Text_VickyPostBattle:
	.string "If you're not in any hurry,\n"
	.string "visit with us awhile.  $"

Route111_Text_ToughToKeepWinningUpTheRanks:
	.string "If you don't raise your POKéMON some\n"
	.string "more, it could be tough to keep winning\l"
	.string "up through the ranks.\p"
	.string "I've heard the POKéMON LEAGUE's\n"
	.string "ELITE FOUR are far stronger than\l"
	.string "any GYM LEADER.  $"

Route111_Text_WinstrateFamilyDestroyedMe:
	.string "I challenged the WINSTRATE family,\n"
	.string "but four matches in a row is tough\l"
	.string "going… They destroyed me.  $"

Route111_Text_RouteSignMauville:
	.string "ROUTE 111\n"
	.string "{DOWN_ARROW} MAUVILLE CITY  $"

Route111_Text_WinstrateHouseSign:
	.string "“Our family's hearts beat as one!”\n"
	.string "THE WINSTRATE'S HOUSE  $"

Route111_Text_RouteSign112:
	.string "ROUTE 111\n"
	.string "{LEFT_ARROW} ROUTE 112  $"

Route111_Text_RouteSign113:
	.string "ROUTE 111\n"
	.string "{LEFT_ARROW} ROUTE 113  $"

Route111_Text_OldLadysRestStopSign:
	.string "OLD LADY'S REST STOP\n"
	.string "“Come in and rest your tired bones.”  $"

Route111_Text_TrainerTipsSpAtkSpDef:
	.string "TRAINER TIPS\p"
	.string "One of the indicators of a POKéMON's\n"
	.string "powerfulness is SP. ATK. It stands for\l"
	.string "“SPECIAL ATTACK.”\p"
	.string "Likewise, SP. DEF stands for “SPECIAL\n"
	.string "DEFENSE.”  $"

Route111_Text_ShouldBeMirageTowerAroundHere:
	.string "There should be a tower made of sand\n"
	.string "around here somewhere.\p"
	.string "But for some reason, it can be seen\n"
	.string "sometimes, and sometimes not.\p"
	.string "That's why I call it the MIRAGE TOWER.  $"

Route111_Text_MirageTowerClearlyVisible:
	.string "I see it!\n"
	.string "The tower of sand!\p"
	.string "The sand tower they called a mirage\n"
	.string "is clearly visible!\p"
	.string "But it looks so fragile…\n"
	.string "It could crumble away anytime…\p"
	.string "I want to go inside it, but I can't\n"
	.string "get my courage up for it…  $"

Route111_Text_ThatWasShockingSandRainedDown:
	.string "Whoa…\n"
	.string "That was shocking.\p"
	.string "Sand rained down in chunks all of\n"
	.string "a sudden.\p"
	.string "What was it like inside?\n"
	.string "Were there sandy ghosts and such?  $"

Route111_Text_MirageTowerHasntBeenSeenSince:
	.string "Since I spoke to you, the tower of sand\n"
	.string "hasn't been seen.\p"
	.string "Perhaps it really was\n"
	.string "the MIRAGE TOWER…  $"

Route111_Text_ClawFossilDisappeared:
	.string "The CLAW FOSSIL disappeared into\n"
	.string "the sand…  $"

Route111_Text_RootFossilDisappeared:
	.string "The ROOT FOSSIL disappeared into\n"
	.string "the sand…  $"

Route111_Text_MauvilleUncleToldMeToTakeRockSmash:
	.string "Oh, no!\p"
	.string "My uncle in MAUVILLE told me to take\n"
	.string "ROCK SMASH with me if I was going to\l"
	.string "ROUTE 111!\p"
	.string "My uncle? He lives across from\n"
	.string "the bike shop in MAUVILLE.  $"

Route111_Text_TrainerHillSign:
	.string "{RIGHT_ARROW} TRAINER HILL ENTRANCE\p"
	.string "“Scale the heights, you hot-blooded\n"
	.string "TRAINERS!”  $"

Route111_Text_WallyCallPlayer::
	.string "{PLAYER}!  $"

Route111_Text_WallyIntro:
	.string "I'm glad to see you!\p"
	.string "You already have 3 BADGES, huh?\nYou really are a great TRAINER!\p"
	.string "But I have the DYNAMO BADGE too!\p"
	.string "I'm not weak anymore,\nI'll show you how strong I've become!  $"

Route111_Text_WallyDefeat::
	.string "Wow! You're really strong!  $"

Route111_Text_WallyPostBattle::
	.string "Now I understand what\nmy team needs to become stronger.\p"
	.string "I'm going to train even harder.\p"
	.string "I feel like I've learned a lot from\n"
	.string "just one battle with you.  $"

Wally_Uhm::
	.string "Uhm…?  $"
Route111_Text_Wally_SomethingForMe::
	.string "You have something for me?\p"
	.string "Oh, I see...  $"
Route111_Text_Wally_GiveHM03::
	.string "{PLAYER} handed over HM06 to WALLY!  $"
Route111_Text_Wally_AfterGivenHM03::
	.string "I forgot about that.\nSo my uncle asked you to gave it to me?\p"
	.string "That's so sweet,\nthanks a lot {PLAYER}.\p"
	.string "I truly appreciate it.\n"
	.string "I owe you a favor.  $"

Route111_Text_Wally_Finale::
	.string "{PLAYER}, I have to go.\p"
	.string "Next time, I will not lose!  $"

Route111_EdoCaldo::
	.string "Che caldo...  $"
Route111_EdoIntro_Text::
	.string "Yo {PLAYER}!\nI didn't expect to find you here.\p"
	.string "You already have three badges, huh?\nYou're speedrunning your adventure, I see.  $"
Route111_EdoMiddleInteraction_Text1::
	.string "Huh? The person that was here?  $"
Route111_EdoMiddleInteraction_Text2::
	.string "It's just a friend of mine.\p"
	.string "You'll may see him again,\n"
	.string "if you continue your jorney.  $"
Route111_EdoMiddleInteraction_Text3::
	.string "I have to go, as you know\nI really hate the hot weather.\p"
	.string "This desert is killing me.\n"
	.string "See ya.  $"
Route111_EdoInteractionExit_Text::
	.string "Dio porco che caldo.  $"

Common_Script_End::
	end

Demo_IsFinished_Text::
	.string "The demo is finished.\nThanks for playing!\p"
	.string "The game now is identical\nto the vanilla one.\p"
	.string "If you encountered bugs or want\nto report something\p"
	.string "Message on Discord: andryz90.\p"
	.string ":3$"