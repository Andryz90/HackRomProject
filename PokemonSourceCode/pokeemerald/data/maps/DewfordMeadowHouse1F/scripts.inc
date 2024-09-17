DewfordMeadowHouse1F_MapScripts::
	.byte 0
DewfordMeadowHouse1F_MimikyuuEncounter::
	lockall
	faceplayer
	setwildbattle SPECIES_MIMIKYU, 50
	waitse
	playmoncry SPECIES_MIMIKYU, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MarineCave_End_EventScript_DefeatedMimikyuu
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MarineCave_End_EventScript_DefeatedMimikyuu
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MarineCave_End_EventScript_DefeatedMimikyuu 
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MarineCave_End_EventScript_DefeatedMimikyuu
	setflag FLAG_DEFEATED_MIMIKYUU
	releaseall
	end
MarineCave_End_EventScript_DefeatedMimikyuu::
	setflag FLAG_DEFEATED_MIMIKYUU
	goto Common_EventScript_RemoveStaticPokemon
	end
