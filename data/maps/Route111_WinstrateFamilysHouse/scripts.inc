Route111_WinstrateFamilysHouse_MapScripts::
	.byte 0

Route111_WinstrateFamilysHouse_EventScript_Victor::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICTOR
	msgbox Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Victoria::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICTORIA
	goto_if_set FLAG_RECEIVED_CHOICE_ITEM, Route111_ChoiceItemGive_EventScript
	msgbox Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace, MSGBOX_DEFAULT
	dynmultipush Choice_Scarf_Text, 0
	dynmultipush Choice_Band_Text, 1
	dynmultipush Choice_Specs_Text, 2
	dynmultipush PKMN_Center_Cancel, 3
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, NULL
	compare VAR_RESULT, MULTI_B_PRESSED
	switch VAR_RESULT
	case 0, Route111_WinstrateFamilysHouse_EventScript_ReceivedChoiceScarf
	case 1, Route111_WinstrateFamilysHouse_EventScript_ReceivedChoiceBand
	case 2, Route111_WinstrateFamilysHouse_EventScript_ReceivedChoiceSpecs
	case 3, Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles
	goto_if_eq Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	release
	end

Route111_ChoiceItemGive_EventScript::
	lock
	msgbox Route111_WinstrateFamilyHouse_Text_ChoiceItemGiven, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	release
	end

Route111_WinstrateFamilysHouse_EventScript_ReceivedChoiceScarf::
	giveitem ITEM_CHOICE_SCARF
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CHOICE_ITEM
	msgbox Route111_WinstrateFamilyHouse_Text_ChoiceItemGiven, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_ReceivedChoiceBand::
	giveitem ITEM_CHOICE_BAND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CHOICE_ITEM
	msgbox Route111_WinstrateFamilyHouse_Text_ChoiceItemGiven, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_ReceivedChoiceSpecs::
	giveitem ITEM_CHOICE_SPECS
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CHOICE_ITEM
	msgbox Route111_WinstrateFamilyHouse_Text_ChoiceItemGiven, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vivi::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VIVI
	msgbox Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vicky::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICKY
	goto_if_set FLAG_TEMP_4, Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrong, MSGBOX_DEFAULT
	setflag FLAG_TEMP_4
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo::
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_0x8008, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou:
	.string "You're the first TRAINER I've seen who\n"
	.string "deploys POKéMON so masterfully.\p"
	.string "But, I should tell you--my son is\n"
	.string "stronger than you.\p"
	.string "He even took the POKéMON LEAGUE\n"
	.string "challenge, I'll have you know. $"

Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace:
	.string "We use this choice items to be more\n"
	.string "effectively strengthen our POKéMON\l"
	.string "in battle.\p"
	.string "Since you've beaten all of us here,\n"
	.string "I don't know if you need it, but we\l"
	.string "would like you to have one?. $"

Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles:
	.string "When it comes to POKéMON battles,\n"
	.string "we tend to be pretty passionate. $"

Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers:
	.string "Mommy is stronger than Daddy.\p"
	.string "I'm stronger than Mommy.\p"
	.string "And Grandma's stronger than me!\p"
	.string "But my big brother is even stronger\n"
	.string "than Grandma. $"

Route111_WinstrateFamilysHouse_Text_GrandsonStrong:
	.string "There's no question that you're strong.\p"
	.string "But if you were to battle my grandson,\n"
	.string "you'd end up crying in frustration.\p"
	.string "He's much stronger than any TRAINER\n"
	.string "our family knows.\p"
	.string "He must be challenging the POKéMON\n"
	.string "LEAGUE CHAMPION by now.\p"
	.string "Knowing my grandson, he could be the\n"
	.string "CHAMPION already! $"

Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort:
	.string "My grandson must be challenging the\n"
	.string "POKéMON LEAGUE CHAMPION by now.\p"
	.string "Knowing my grandson, he could be the\n"
	.string "CHAMPION already! $"

Route111_WinstrateFamilyHouse_Text_ChoiceItemGiven::
	.string "I hope this item help you as well. $"

Choice_Scarf_Text::
	.string "CHOICE SCARF $"
Choice_Band_Text::
	.string "CHOICE BAND $"
Choice_Specs_Text::
	.string "CHOICE SPECS $"