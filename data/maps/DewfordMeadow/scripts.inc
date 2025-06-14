.set LOCALID_PSYDUCK, 5
.set LOCALID_FLOETTE, 4

DewfordMeadow_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordMeadow_OnTransition
	.byte 0

DewfordMeadow_OnTransition:
	setflag FLAG_LANDMARK_DEWFORD_MEADOW
	end

DewfordMeadow_Floette_Script::
	lock
	faceplayer
	playmoncry SPECIES_FLOETTE, CRY_MODE_ENCOUNTER
	msgbox DewfordMeadow_Text_Floette, MSGBOX_DEFAULT
	applymovement LOCALID_PSYDUCK, Common_Movement_Delay48
	waitmovement 0
	release
	end

DewfordMeadow_Psyduck_Script::
	lock
	faceplayer
	playmoncry SPECIES_PSYDUCK, CRY_MODE_ENCOUNTER
	msgbox DewfordMeadow_Text_Psyduck, MSGBOX_DEFAULT
	applymovement LOCALID_FLOETTE, Common_Movement_Delay48
	waitmovement 0
	release
	end

DewfordMeadow_EventScript_ManorSign::
	msgbox DewfordMeadow_Text_ManorSign, MSGBOX_SIGN
	end

DewfordMeadow_Text_ManorSign:
	.string "Dewford Manor: Once a Sea Captain's\n"
	.string "escape, now home only to Pokémon.$"

DewfordMeadow_Text_Psyduck:
	.string "Psy-yu-duck$"
DewfordMeadow_Text_Floette:
	.string "Floo-ette$"