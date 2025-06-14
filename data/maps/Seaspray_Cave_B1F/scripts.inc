.set LOCALID_ABOMASNOW, 1
Seaspray_Cave_B1F_MapScripts::
	.byte 0

Seaspray_Cave_B1F_AbomasnowEncounter::
	lockall
	faceplayer
	setwildbattle SPECIES_ABOMASNOW, 70, ITEM_ABOMASITE
	waitse
	playmoncry SPECIES_ABOMASNOW, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MarineCave_End_EventScript_DefeatedAbomasnow
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MarineCave_End_EventScript_DefeatedAbomasnow
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MarineCave_End_EventScript_DefeatedAbomasnow 
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MarineCave_End_EventScript_DefeatedAbomasnow
	setflag FLAG_DEFEATED_ABOMASNOW
	releaseall
	end
MarineCave_End_EventScript_DefeatedAbomasnow::
	setflag FLAG_DEFEATED_ABOMASNOW
	goto Common_EventScript_RemoveStaticPokemon
	end
