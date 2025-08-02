FallarborTown_MoveRelearnersHouse_MapScripts::
	.byte 0

FallarborTown_MoveRelearnersHouse_EventScript_MoveRelearner::
	lockall
	applymovement LOCALID_MOVE_RELEARNER, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_set FLAG_TEMP_1, FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove
	msgbox FallarborTown_MoveRelearnersHouse_Text_ImTheMoveTutor, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	goto FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove
	end

FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove::
	checkitem ITEM_HEART_SCALE
	goto_if_eq VAR_RESULT, FALSE, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	@msgbox FallarborTown_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon, MSGBOX_DEFAULT
	special ChooseMonForMoveRelearner
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_MoveRelearnersHouse_EventScript_CantTeachEgg
	goto_if_eq VAR_0x8005, 0, FallarborTown_MoveRelearnersHouse_EventScript_NoMoveToTeachMon
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMove
	end

FallarborTown_MoveRelearnersHouse_EventScript_ChooseMove::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	goto_if_eq VAR_0x8004, 0, FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	msgbox FallarborTown_MoveRelearnersHouse_Text_HandedOverHeartScale, MSGBOX_DEFAULT
	removeitem ITEM_HEART_SCALE
	goto FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	end

FallarborTown_MoveRelearnersHouse_EventScript_NoMoveToTeachMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_CantTeachEgg::
	msgbox FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_MaxCantTeachEgg::
	msgbox FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale::
	msgbox FallarborTown_MoveRelearnersHouse_Text_ComeBackWithHeartScale, MSGBOX_DEFAULT
	releaseall
	end

FallarborTown_MoveRelearnersHouse_Text_ImTheMoveTutor:
	.string "I'm the MOVE TUTOR.\p"
	.string "I know all the moves that POKéMON\n"
	.string "learn--every one of them--and I can\l"
	.string "teach POKéMON those moves.\p"
	.string "I can teach a move to a POKéMON\n"
	.string "of yours if you'd like.\p"
	.string "I'll do it for a HEART SCALE.\n"
	.string "I'm collecting those now.  $"

FallarborTown_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove:
	.string "Oh! That's it! That's an honest to\n"
	.string "goodness HEART SCALE!\p"
	.string "Let me guess, you want me to teach\n"
	.string "a move?  $"

FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon:
	.string "Which POKéMON needs tutoring?  $"

FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove:
	.string "Which move should I teach?  $"

FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon:
	.string "Sorry…\p"
	.string "It doesn't appear as if I have any move\n"
	.string "I can teach that POKéMON.  $"

FallarborTown_MoveRelearnersHouse_Text_HandedOverHeartScale:
	.string "{PLAYER} handed over one HEART SCALE\n"
	.string "in exchange.  $"

FallarborTown_MoveRelearnersHouse_Text_MaxShrooms:
	.string "{PLAYER} handed over one MAX MUSHROOMS\n"
	.string "in exchange.  $"


FallarborTown_MoveRelearnersHouse_Text_ComeBackWithHeartScale:
	.string "If your POKéMON need to learn a move,\n"
	.string "come back with a HEART SCALE.  $"

FallarborTown_MoveRelearnersHouse_Text_ComeBackWithMushrooms:
	.string "If your POKéMON need to learn the move,\n"
	.string "come back with the MUSHROOMS.  $"

FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg:
	.string "Hunh? There isn't a single move that\n"
	.string "I can teach an EGG.  $"



@ Tutor Move 
FallarborTownTutor_EventScript::
	@lockall
	msgbox FallarborTown_Tutor_Text_ImTheMoveTutor, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, FallarborTown_Tutor_EventScript_AskTeachMove
	case NO, PKMN_Center_Move_Tutor_General_Exit
	end

FallarborTown_Tutor_EventScript_AskTeachMove::
	checkitem ITEM_HEART_SCALE
	goto_if_eq VAR_RESULT, FALSE, FallarborTown_Tutor_EventScript_ComeBackWithHeartScale
	@msgbox FallarborTown_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove, MSGBOX_YESNO
	@switch VAR_RESULT
	@case NO, FallarborTown_Tutor_EventScript_ComeBackWithHeartScale
	goto FallarborTown_TutorHouse_EventScript_ChooseMon
	end

FallarborTown_TutorHouse_EventScript_ChooseMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon, MSGBOX_DEFAULT
	special ChooseMonForTutor
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FallarborTown_Tutor_EventScript_ComeBackWithHeartScale
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_Tutor_EventScript_CantTeachEgg
	goto_if_eq VAR_0x8005, 0, FallarborTown_Tutor_EventScript_NoMoveToTeachMon
	goto FallarborTown_Tutor_EventScript_ChooseMove
	end

FallarborTown_Tutor_EventScript_ChooseMove::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachTutorMove
	waitstate
	goto_if_eq VAR_0x8004, 0, FallarborTown_TutorHouse_EventScript_ChooseMon
	msgbox FallarborTown_MoveRelearnersHouse_Text_HandedOverHeartScale, MSGBOX_DEFAULT
	removeitem ITEM_HEART_SCALE
	goto FallarborTown_Tutor_EventScript_ComeBackWithHeartScale
	end

FallarborTown_Tutor_EventScript_NoMoveToTeachMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto FallarborTown_TutorHouse_EventScript_ChooseMon
	end

FallarborTown_Tutor_EventScript_CantTeachEgg::
	msgbox FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto FallarborTown_TutorHouse_EventScript_MaxTutorChooseMon
	end

FallarborTown_Tutor_EventScript_ComeBackWithHeartScale::
	msgbox FallarborTown_MoveRelearnersHouse_Text_ComeBackWithHeartScale, MSGBOX_DEFAULT
	releaseall
	end

FallarborTown_Tutor_EventScript_ComeBackWithMushrooms::
	msgbox FallarborTown_MoveRelearnersHouse_Text_ComeBackWithMushrooms, MSGBOX_DEFAULT
	releaseall
	end

FallarborTown_Tutor_EventScript_MaxCantTeachEgg::
	msgbox FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto FallarborTown_TutorHouse_EventScript_ChooseMon
	end
FallarborTown_Tutor_Text_ImTheMoveTutor:
	.string "I can teach special moves\nto your Pokémon.\p"
	.string "This service requires,\njust 1 Heart Scale.\p"
	.string "Are you interested?  $"


FallarborTown_Tutor_Max_Moves::
	lockall
	applymovement LOCALID_MOVE_RELEARNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FallarborTown_Tutor_Max_Moves_Text, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, FallarborTown_Tutor_Max_Moves_Service
	case NO, PKMN_Center_Move_Tutor_General_Exit
	releaseall
	end

FallarborTown_TutorHouse_EventScript_MaxTutorChooseMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon, MSGBOX_DEFAULT
	special ChooseMonForMaxTutor
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FallarborTown_Tutor_EventScript_ComeBackWithMushrooms
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_Tutor_EventScript_MaxCantTeachEgg
	goto_if_eq VAR_0x8005, 0, FallarborTown_Tutor_EventScript_NoMaxMoveToTeachMon
	goto FallarborTown_Tutor_EventScript_MaxTutorChooseMove
	end

FallarborTown_Tutor_EventScript_MaxTutorChooseMove::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachTutorMove
	waitstate
	goto_if_eq VAR_0x8004, 0, FallarborTown_TutorHouse_EventScript_MaxTutorChooseMon
	msgbox FallarborTown_MoveRelearnersHouse_Text_MaxShrooms, MSGBOX_DEFAULT
	removeitem ITEM_MAX_MUSHROOMS
	goto FallarborTown_Tutor_EventScript_ComeBackWithMushrooms
	end

FallarborTown_Tutor_Max_Moves_Service::
	checkitem ITEM_MAX_MUSHROOMS
	goto_if_eq VAR_RESULT, FALSE, FallarborTown_Tutor_EventScript_NotEnoughMushRooms
	special ChooseMonForMaxTutor
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, PKMN_Center_Move_Tutor_General_Exit
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_Tutor_EventScript_MaxCantTeachEgg
	goto_if_eq VAR_0x8005, 0, FallarborTown_Tutor_EventScript_NoMaxMoveToTeachMon
	goto FallarborTown_Tutor_EventScript_MaxTutorChooseMove
	releaseall
	end
FallarborTown_Tutor_EventScript_NoMaxMoveToTeachMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto FallarborTown_Tutor_Max_Moves_Service
	end

FallarborTown_Tutor_EventScript_NotEnoughMushRooms::
	msgbox FallarborTown_Tutor_Max_Moves_NotEnoughMushRooms_Text, MSGBOX_DEFAULT
	releaseall
	end

FallarborTown_Tutor_Max_Moves_NotEnoughMushRooms_Text::
	.string "You don't have mushrooms,\n"
	.string "See you later. $"

FallarborTown_Tutor_Max_Moves_SelectMon::
	.string "Which Pokemon do you choose? $"

FallarborTown_Tutor_Max_Moves_Text::
	.string "I'm the MAX Tutor.\p"
	.string "I can teach the exclusive move\nto a POKéMON if can learn it.\p"
	.string "I only need a Max Mushrooms. \nDo you have want it? $"