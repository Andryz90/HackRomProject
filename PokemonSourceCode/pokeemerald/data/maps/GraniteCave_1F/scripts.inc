.set LOCALID_HIKER, 1

GraniteCave_1F_MapScripts::
	.byte 0
GraniteCave_1F_EventScript_Hiker_ApproachingPlayer1::
	walk_right
	walk_right
	walk_right
	step_end

GraniteCave_1F_EventScript_Hiker_ApproachingPlayer2::
	walk_right
	walk_right
	walk_right
	walk_up
	face_player
	step_end

GraniteCave_1F_EventScript_Hiker_ApproachingPlayer3::
	walk_right
	walk_right
	walk_right
	walk_down
	face_player
	step_end

GraniteCave_1F_EventScript_Hiker2::
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_B3F_SplitFace_NULL
	lock
	faceplayer
	applymovement LOCALID_HIKER, Common_Movement_ExclamationMark
	waitmovement LOCALID_HIKER
	applymovement LOCALID_HIKER, GraniteCave_1F_EventScript_Hiker_ApproachingPlayer2
	waitmovement LOCALID_HIKER
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end
GraniteCave_1F_EventScript_Hiker::
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_B3F_SplitFace_NULL
	lock
	faceplayer
	applymovement LOCALID_HIKER, Common_Movement_ExclamationMark
	waitmovement LOCALID_HIKER
	applymovement LOCALID_HIKER, GraniteCave_1F_EventScript_Hiker_ApproachingPlayer1
	waitmovement LOCALID_HIKER
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_Hiker3::
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_B3F_SplitFace_NULL
	lock
	faceplayer
	applymovement LOCALID_HIKER, Common_Movement_ExclamationMark
	waitmovement LOCALID_HIKER
	applymovement LOCALID_HIKER, GraniteCave_1F_EventScript_Hiker_ApproachingPlayer3
	waitmovement LOCALID_HIKER
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash::
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
	.string "Hey, you.\n"
	.string "It gets awfully dark ahead.\l"
	.string "It'll be tough trying to explore.\p"
	.string "That guy who came by earlier…\n"
	.string "STEVEN, I think it was.\p"
	.string "He knew how to use FLASH, so he ought\n"
	.string "to be all right, but…\p"
	.string "Well, for us HIKERS, helping out those\n"
	.string "that we meet is our motto.\p"
	.string "Here you go, I'll pass this on to you.$"

GraniteCave_1F_Text_ExplainFlash:
	.string "It very useful, lights up\n"
	.string "even the inky darkness of caves.\p"
	.string "But the move is now automatic\n"
	.string "when entering a dark location.\p"
	.string "It's just need the item, the badge and\na POKéMON that can learn it!\p"
	.string "You need to obtain the GYM BADGE\n"
	.string "from DEWFORD's POKéMON GYM first.\p"
	.string "Good luck!$"

