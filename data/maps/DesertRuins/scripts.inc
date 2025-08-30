DesertRuins_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, DesertRuins_OnResume
	map_script MAP_SCRIPT_ON_LOAD, DesertRuins_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, DesertRuins_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Desert_Ruin_Maxie_OnFrameTable
	.byte 0

DesertRuins_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, DesertRuins_EventScript_TryRemoveRegirock
	end

DesertRuins_EventScript_TryRemoveRegirock::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

DesertRuins_OnLoad:
	call_if_unset FLAG_MAXIE_DESERT, Desert_Ruin_Maxie_InitScript
	call_if_unset FLAG_SYS_REGIROCK_PUZZLE_COMPLETED, DesertRuins_EventScript_HideRegiEntrance
	call_if_eq VAR_WALLY_ROUTE111_TRIGGER, 4, Desert_Ruin_CalcPos_ForRegiDoor
	end

Desert_Ruin_Maxie_OnFrameTable::
	map_script_2 VAR_WALLY_ROUTE111_TRIGGER, 100, Desert_Ruin_Maxie_Trigger
	map_script_2 VAR_WALLY_ROUTE111_TRIGGER, 4, Desert_Ruin_Closing_Regi_Door_EventScript
	.2byte 0
	
DesertRuins_EventScript_HideRegiEntrance::
	setmetatile 7, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 8, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 9, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 9, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	return

DesertRuins_OnTransition:
	setflag FLAG_LANDMARK_DESERT_RUINS
	call_if_unset FLAG_DEFEATED_REGIROCK, DesertRuins_EventScript_ShowRegirock
	end

DesertRuins_EventScript_ShowRegirock::
	clearflag FLAG_HIDE_REGIROCK
	return

DesertRuins_EventScript_CaveEntranceMiddle::
	lockall
	goto_if_set FLAG_SYS_REGIROCK_PUZZLE_COMPLETED, DesertRuins_EventScript_BigHoleInWall
	braillemsgbox DesertRuins_Braille_UseRockSmash
	releaseall
	end

DesertRuins_EventScript_BigHoleInWall::
	msgbox gText_BigHoleInTheWall, MSGBOX_DEFAULT
	releaseall
	end

DesertRuins_EventScript_CaveEntranceSide::
	lockall
	braillemsgbox DesertRuins_Braille_UseRockSmash
	releaseall
	end

DesertRuins_EventScript_Regirock::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIROCK, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGIROCK, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, DesertRuins_EventScript_DefeatedRegirock
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, DesertRuins_EventScript_RanFromRegirock
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, DesertRuins_EventScript_RanFromRegirock
	setflag FLAG_DEFEATED_REGIROCK
	release
	end

DesertRuins_EventScript_DefeatedRegirock::
	setflag FLAG_DEFEATED_REGIROCK
	goto Common_EventScript_RemoveStaticPokemon
	end

DesertRuins_EventScript_RanFromRegirock::
	setvar VAR_0x8004, SPECIES_REGIROCK
	goto Common_EventScript_LegendaryFlewAway
	end

Desert_Ruin_Maxie_InitScript::
	setflag FLAG_SYS_REGIROCK_PUZZLE_COMPLETED @Show the entrance
	setflag FLAG_HIDE_REGIROCK
	setvar VAR_TEMP_2, 0
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	goto_if_ne VAR_TEMP_0, 8, Common_EventScript_Return
	goto_if_ne VAR_TEMP_1, 11, Common_EventScript_Return
	setvar VAR_TEMP_2, 1
	return

Maxie_Started_Speech::
	.string "MAXIE: Finally, \nthe power of the golem... $"

Desert_Ruin_Maxie_Finale_Text::
	.string "MAXIE: You could have this time,\nbut we'll achieve our goal,\lyou can count on it. \p"
	.string "Now that we've the power, \nthere's no need to stay here any longer.\p"
	.string "We're retreating. \lI'll not forget you {PLAYER}. $"

Common_EventScript_Return::
	return

Desert_Ruin_Maxie_Trigger::
	goto_if_ne VAR_TEMP_2, 1, Common_EventScript_Return
	lockall
	msgbox Maxie_Started_Speech, MSGBOX_AUTOCLOSE
	closemessage
	applymovement LOCALID_MAXIE_REGIROCK_CHAMBER, Common_Movement_ExclamationMark
	waitmovement LOCALID_MAXIE_REGIROCK_CHAMBER
	applymovement LOCALID_MAXIE_REGIROCK_CHAMBER, Common_Movement_FaceDown
	waitmovement LOCALID_MAXIE_REGIROCK_CHAMBER
	delay 10
	applymovement LOCALID_MAXIE_REGIROCK_CHAMBER, Common_Movement_WalkDown2
	waitmovement LOCALID_MAXIE_REGIROCK_CHAMBER
	msgbox MtChimney_Text_MaxieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAXIE_DESERT, MtChimney_Text_MaxieDefeat
	msgbox Desert_Ruin_Maxie_Finale_Text, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	setflag FLAG_MAXIE_DESERT
	setflag FLAG_HIDE_MAGMA_GRUNT_DESERT
	clearflag FLAG_HIDE_TRAINER_DESERT
	setvar VAR_WALLY_ROUTE111_TRIGGER, 4
	removeobject LOCALID_MAXIE_REGIROCK_CHAMBER
	fadescreen FADE_FROM_BLACK
	releaseall
	end


Desert_Ruin_CalcPos_ForRegiDoor::
	setvar VAR_TEMP_2, 0
	getplayerxy VAR_TEMP_3, VAR_TEMP_1 @temp var 0 is always 0 when entering the room for some reason
	goto_if_ne VAR_TEMP_3, 8, Common_EventScript_Return
	goto_if_ne VAR_TEMP_1, 20, Common_EventScript_Return
	setvar VAR_TEMP_2, 5
	return
Desert_Ruin_Closing_Regi_Door_EventScript::
	goto_if_ne VAR_TEMP_2, 5, Common_EventScript_Return
	lock
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	fadescreen FADE_TO_BLACK
	setvar VAR_WALLY_ROUTE111_TRIGGER, 5
	clearflag FLAG_SYS_REGIROCK_PUZZLE_COMPLETED
	setmetatile 7, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 8, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 9, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 9, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	special DrawWholeMapView
	fadescreen FADE_FROM_BLACK
	release
	end
