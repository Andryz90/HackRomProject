DesertUnderpass_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DesertUnderpass_OnTransition
	.byte 0

DesertUnderpass_OnTransition:
	setflag FLAG_LANDMARK_DESERT_UNDERPASS
	end

DesertUnderpass_EventScript_Fossil::
	lock
	faceplayer
	switch VAR_LAST_TALKED
	case LOCALID_HELIX_FOSSIL,   DesertUnderpass_EventScript_Helix
	case LOCALID_DOME_FOSSIL,    DesertUnderpass_EventScript_Dome
	@case LOCALID_ROOT_FOSSIL,   DesertUnderpass_EventScript_Root
	@case LOCALID_CLAW_FOSSIL,   DesertUnderpass_EventScript_Claw
	@case LOCALID_ARMOR_FOSSIL,  DesertUnderpass_EventScript_Armor
	@case LOCALID_SKULL_FOSSIL,  DesertUnderpass_EventScript_Skull
	@case LOCALID_COVER_FOSSIL,  DesertUnderpass_EventScript_Cover
	@case LOCALID_PLUME_FOSSIL,  DesertUnderpass_EventScript_Plume
	@case LOCALID_JAW_FOSSIL,  	 DesertUnderpass_EventScript_Jaw
	@case LOCALID_SAIL_FOSSIL,   DesertUnderpass_EventScript_Sail
	case MULTI_B_PRESSED, DesertUnderpass_EventScript_Fossil_Exit
	release
	end

DesertUnderpass_EventScript_GiveFossilRegistered::
	giveitem VAR_UNUSED_0x8014
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	removeobject VAR_LAST_TALKED
	release
	end

DesertUnderpass_EventScript_Helix::
	setvar VAR_UNUSED_0x8014, ITEM_HELIX_FOSSIL
	special RegisterTalkedFossil
	msgbox DesertUnderpass_Text_FossilRegistered, MSGBOX_YESNO	
	switch VAR_RESULT
	case YES, DesertUnderpass_EventScript_GiveFossilRegistered
	case NO, DesertUnderpass_EventScript_Fossil_Exit
	case MULTI_B_PRESSED, DesertUnderpass_EventScript_Fossil_Exit
	release
	end


DesertUnderpass_EventScript_Dome::
	setvar VAR_UNUSED_0x8014, ITEM_DOME_FOSSIL
	special RegisterTalkedFossil
	msgbox DesertUnderpass_Text_FossilRegistered, MSGBOX_YESNO	
	switch VAR_RESULT
	case YES, DesertUnderpass_EventScript_GiveFossilRegistered
	case NO, DesertUnderpass_EventScript_Fossil_Exit
	case MULTI_B_PRESSED, DesertUnderpass_EventScript_Fossil_Exit
	release
	end

DesertUnderpass_EventScript_Root::
	setvar VAR_UNUSED_0x8014, ITEM_ROOT_FOSSIL
	special RegisterTalkedFossil
	msgbox DesertUnderpass_Text_FossilRegistered, MSGBOX_YESNO	
	switch VAR_RESULT
	case YES, DesertUnderpass_EventScript_GiveFossilRegistered
	case NO, DesertUnderpass_EventScript_Fossil_Exit
	case MULTI_B_PRESSED, DesertUnderpass_EventScript_Fossil_Exit
	release
	end

DesertUnderpass_EventScript_Claw::
	setvar VAR_UNUSED_0x8014, ITEM_CLAW_FOSSIL
	special RegisterTalkedFossil
	msgbox DesertUnderpass_Text_FossilRegistered, MSGBOX_YESNO	
	switch VAR_RESULT
	case YES, DesertUnderpass_EventScript_GiveFossilRegistered
	case NO, DesertUnderpass_EventScript_Fossil_Exit
	case MULTI_B_PRESSED, DesertUnderpass_EventScript_Fossil_Exit
	release
	end

DesertUnderpass_EventScript_Armor::
	setvar VAR_UNUSED_0x8014, ITEM_ARMOR_FOSSIL
	special RegisterTalkedFossil
	msgbox DesertUnderpass_Text_FossilRegistered, MSGBOX_YESNO	
	switch VAR_RESULT
	case YES, DesertUnderpass_EventScript_GiveFossilRegistered
	case NO, DesertUnderpass_EventScript_Fossil_Exit
	case MULTI_B_PRESSED, DesertUnderpass_EventScript_Fossil_Exit
	release
	end

DesertUnderpass_EventScript_Skull::
	setvar VAR_UNUSED_0x8014, ITEM_SKULL_FOSSIL
	special RegisterTalkedFossil
	msgbox DesertUnderpass_Text_FossilRegistered, MSGBOX_YESNO	
	switch VAR_RESULT
	case YES, DesertUnderpass_EventScript_GiveFossilRegistered
	case NO, DesertUnderpass_EventScript_Fossil_Exit
	case MULTI_B_PRESSED, DesertUnderpass_EventScript_Fossil_Exit
	release
	end

DesertUnderpass_EventScript_Cover::
	setvar VAR_UNUSED_0x8014, ITEM_COVER_FOSSIL
	special RegisterTalkedFossil
	msgbox DesertUnderpass_Text_FossilRegistered, MSGBOX_YESNO	
	switch VAR_RESULT
	case YES, DesertUnderpass_EventScript_GiveFossilRegistered
	case NO, DesertUnderpass_EventScript_Fossil_Exit
	case MULTI_B_PRESSED, DesertUnderpass_EventScript_Fossil_Exit
	release
	end

DesertUnderpass_EventScript_Plume::
	setvar VAR_UNUSED_0x8014, ITEM_PLUME_FOSSIL
	special RegisterTalkedFossil
	msgbox DesertUnderpass_Text_FossilRegistered, MSGBOX_YESNO	
	switch VAR_RESULT
	case YES, DesertUnderpass_EventScript_GiveFossilRegistered
	case NO, DesertUnderpass_EventScript_Fossil_Exit
	case MULTI_B_PRESSED, DesertUnderpass_EventScript_Fossil_Exit
	release
	end

DesertUnderpass_EventScript_Jaw::
	setvar VAR_UNUSED_0x8014, ITEM_JAW_FOSSIL
	special RegisterTalkedFossil
	msgbox DesertUnderpass_Text_FossilRegistered, MSGBOX_YESNO	
	switch VAR_RESULT
	case YES, DesertUnderpass_EventScript_GiveFossilRegistered
	case NO, DesertUnderpass_EventScript_Fossil_Exit
	case MULTI_B_PRESSED, DesertUnderpass_EventScript_Fossil_Exit
	release
	end

DesertUnderpass_EventScript_Sail::
	setvar VAR_UNUSED_0x8014, ITEM_SAIL_FOSSIL
	special RegisterTalkedFossil
	msgbox DesertUnderpass_Text_FossilRegistered, MSGBOX_YESNO	
	switch VAR_RESULT
	case YES, DesertUnderpass_EventScript_GiveFossilRegistered
	case NO, DesertUnderpass_EventScript_Fossil_Exit
	case MULTI_B_PRESSED, DesertUnderpass_EventScript_Fossil_Exit
	release
	end

DesertUnderpass_EventScript_Fossil_Exit::
	release 
	end

@ Unused
DesertUnderpass_Text_FoundRootFossil::
	.string "{PLAYER} found the ROOT FOSSIL. $"

@ Unused
DesertUnderpass_Text_FoundClawFossil::
	.string "{PLAYER} found the CLAW FOSSIL. $"

DesertUnderpass_Text_FossilRegistered::
	.string "Inside there is {STR_VAR_1}\n"
	.string "Woud you like to take it? $"