
PKMN_Center_Move_Tutor::
	lockall
	faceplayer
	message PKMN_Center_Move_Tutor_Text_HowCanHelp
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_POKE_CENTER_TUTOR
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, PKMN_Center_MoveReminder_EventScript
	case 1, PKMN_Center_MoveDeleter_EventScript
	case 2, Debug_EventScript_InflictStatus1
	case 3, PKMN_Center_Swap_Pokemon_Gender
	@case 4, pre-damage
	@case 5, nature
	case 6, PKMN_Center_EventScript_MaxIVs
	case 7, PKMN_Center_Move_Tutor_General_Exit
	case MULTI_B_PRESSED, PKMN_Center_Move_Tutor_General_Exit
	releaseall
	end

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Move Reminder @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PKMN_Center_MoveReminder_EventScript::
	msgbox PKMN_Center_MoveReminder_Text_WantMeToTeachMove, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, PKMN_Center_Move_Tutor_General_Exit
	goto FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove
	end

PKMN_Center_MoveReminder_EventScriptChooseMon::
	msgbox PKMN_Center_MoveReminder_Text_TutorWhichMon, MSGBOX_DEFAULT
	special ChooseMonForMoveRelearner
	waitstate
	compare VAR_0x8004, 255
	goto_if_eq PKMN_Center_Move_Tutor_General_Exit
	special IsSelectedMonEgg
	compare VAR_RESULT, TRUE
	goto_if_eq PKMN_Center_MoveReminder_EventScriptCantTeachEgg
	compare VAR_0x8005, 0
	goto_if_eq PKMN_Center_MoveReminder_EventScriptNoMoveToTeachMon
	goto PKMN_Center_MoveReminder_EventScriptChooseMove
	end

PKMN_Center_MoveReminder_EventScriptChooseMove::
	msgbox PKMN_Center_MoveReminder_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	compare VAR_0x8004, 0
	goto_if_eq PKMN_Center_MoveReminder_EventScriptChooseMon
	goto PKMN_Center_MoveReminder_EventScriptRememberAnotherMove
	end

PKMN_Center_MoveReminder_EventScriptNoMoveToTeachMon::
	msgbox PKMN_Center_MoveReminder_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto PKMN_Center_MoveReminder_EventScriptChooseMon
	end

PKMN_Center_MoveReminder_EventScriptCantTeachEgg::
	msgbox PKMN_Center_MoveReminder_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto PKMN_Center_MoveReminder_EventScriptChooseMon
	end
	
PKMN_Center_MoveReminder_EventScriptRememberAnotherMove::
	msgbox PKMN_Center_MoveReminder_Text_RememberAnotherMove, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq PKMN_Center_Move_Tutor_General_Exit
	goto PKMN_Center_MoveReminder_EventScriptChooseMon

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Move Deleter @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PKMN_Center_MoveDeleter_EventScript::
	msgbox PKMN_Center_MoveDeleter_Text_ICanMakeMonForgetMove, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, PKMN_Center_MoveDeleter_EventScript_ChooseMonAndMoveToForget
	case NO, PKMN_Center_Move_Tutor_General_Exit
	releaseall
	end

PKMN_Center_MoveDeleter_EventScript_ChooseMonAndMoveToForget::
	msgbox PKMN_Center_MoveDeleter_Text_WhichMonShouldForget, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_eq PKMN_Center_Move_Tutor_General_Exit
	special IsSelectedMonEgg
	compare VAR_RESULT, TRUE
	goto_if_eq PKMN_Center_MoveDeleter_EventScript_EggCantForgetMoves
	special GetNumMovesSelectedMonHas
	compare VAR_RESULT, 1
	goto_if_eq PKMN_Center_MoveDeleter_EventScript_MonOnlyKnowsOneMove
	msgbox PKMN_Center_MoveDeleter_Text_WhichMoveShouldBeForgotten, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special MoveDeleterChooseMoveToForget
	fadescreen FADE_FROM_BLACK
	compare VAR_0x8005, MAX_MON_MOVES
	goto_if_eq PKMN_Center_MoveDeleter_EventScript_ChooseMonAndMoveToForget
	special BufferMoveDeleterNicknameAndMove
	msgbox PKMN_Center_MoveDeleter_Text_MonsMoveShouldBeForgotten, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, PKMN_Center_MoveDeleter_EventScript_TryForgetMove
	case NO, PKMN_Center_Move_Tutor_General_Exit
	releaseall
	end

PKMN_Center_MoveDeleter_EventScript_TryForgetMove::
	special IsLastMonThatKnowsSurf
	compare VAR_RESULT, TRUE
	goto_if_eq PKMN_Center_MoveDeleter_EventScript_LastMonWithSurf
	special MoveDeleterForgetMove
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	msgbox PKMN_Center_MoveDeleter_Text_MonHasForgottenMove, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_MoveDeleter_EventScript_MonOnlyKnowsOneMove::
	special BufferMoveDeleterNicknameAndMove
	msgbox PKMN_Center_MoveDeleter_Text_MonOnlyKnowsOneMove, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_MoveDeleter_EventScript_EggCantForgetMoves::
	msgbox PKMN_Center_MoveDeleter_Text_EggCantForgetMoves, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_MoveDeleter_EventScript_LastMonWithSurf::
	special BufferMoveDeleterNicknameAndMove
	msgbox PKMN_Center_MoveDeleter_Text_CantForgetSurf, MSGBOX_DEFAULT
	releaseall
	end

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Applying Status @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@ Using Debug One that is already tested

@PKMN_Center_MoveDeleter_EventScript_ApplyingStatus::
@	msgbox PKMN_Center_MoveDeleter_Text_ICanMakeMonForgetMove, MSGBOX_YESNO
@	switch VAR_RESULT
@	case YES, PKMN_Center_MoveDeleter_EventScript_ChooseMontoStatus
@	case NO, PKMN_Center_Move_Tutor_General_Exit
@	releaseall
@	end
@PKMN_Center_MoveDeleter_EventScript_ChooseMontoStatus::
@	msgbox PKMN_Center_Text_ApplyingStatus, MSGBOX_DEFAULT
@	special ChoosePartyMon
@	waitstate
@	compare VAR_0x8004, 255
@	goto_if_eq PKMN_Center_Move_Tutor_General_Exit
@	special IsSelectedMonEgg
@	compare VAR_RESULT, TRUE
@	goto_if_eq PKMN_Center_MoveDeleter_EventScript_EggBeStatus
@	call PKMN_Center_MoveDeleter_EventScript_ChooseStatus
@	releaseall
@	end
@
@PKMN_Center_MoveDeleter_EventScript_EggBeStatus::
@	msgbox PKMN_Center_Text_EggCantStatus, MSGBOX_DEFAULT
@	releaseall
@	end
@
@PKMN_Center_MoveDeleter_EventScript_Paralysis::
@	setstatus1 MOVE_EFFECT_PARALYSIS, VAR_0x8004
@	return
@PKMN_Center_MoveDeleter_EventScript_Burn::
@	setstatus1 MOVE_EFFECT_BURN, VAR_0x8004
@	return
@PKMN_Center_MoveDeleter_EventScript_Toxic::
@	setstatus1 MOVE_EFFECT_TOXIC, VAR_0x8004
@	return
@PKMN_Center_MoveDeleter_EventScript_Frostbite::
@	setstatus1 MOVE_EFFECT_FROSTBITE, VAR_0x8004
@	return
@
@PKMN_Center_MoveDeleter_EventScript_Sleep::
@	setstatus1 MOVE_EFFECT_SLEEP, VAR_0x8004
@	return
@
@PKMN_Center_MoveDeleter_EventScript_ChooseStatus::
@	multichoice	17, 0, MULTI_STATUS , TRUE
@	switch VAR_RESULT
@	case 0, PKMN_Center_MoveDeleter_EventScript_Paralysis
@	case 1, PKMN_Center_MoveDeleter_EventScript_Burn
@	case 2, PKMN_Center_MoveDeleter_EventScript_Toxic
@	case 3, PKMN_Center_MoveDeleter_EventScript_Frostbite
@	case 4, PKMN_Center_MoveDeleter_EventScript_Sleep
@	releaseall
@	end

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Swap Gender Pokemon @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PKMN_Center_Swap_Pokemon_Gender::
	msgbox PKMN_Center_Gender_Party, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_eq PKMN_Center_Move_Tutor_General_Exit
	special IsSelectedMonEgg
	compare VAR_RESULT, TRUE
	goto_if_eq PKMN_Center_Text_EggGender
	specialvar VAR_RESULT, SwapPokemonGender
	goto_if_eq VAR_RESULT, FALSE,  PKMN_Center_Text_EggGender
	msgbox PKMN_Center_Done_Text, MSGBOX_DEFAULT
	call PKMN_Center_Move_Tutor_General_Exit
	releaseall
	end

PKMN_Center_Text_EggGender::
	msgbox PKMN_Center_Text_EggGender_Text, MSGBOX_DEFAULT
	call PKMN_Center_Move_Tutor_General_Exit
	releaseall
	end
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Name Rater @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PKMN_Center_NameRater_EventScript::
	msgbox PKMN_Center_NameRater_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_ne PKMN_Center_NameRater_EventScript_RateMonNickname
	compare VAR_0x8004, 255
	goto_if_eq PKMN_Center_Move_Tutor_General_Exit
	end

PKMN_Center_NameRater_EventScript_RateMonNickname::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq PKMN_Center_NameRater_EventScript_CantRateEgg
	special BufferMonNickname
	msgbox PKMN_Center_NameRater_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	compare VAR_RESULT, TRUE
	goto_if_eq PKMN_Center_NameRater_EventScript_NewNameDifferent
	msgbox PKMN_Center_NameRater_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_NameRater_EventScript_CantRateEgg::
	msgbox PKMN_Center_NameRater_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_NameRater_EventScript_NewNameDifferent::
	msgbox PKMN_Center_NameRater_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_Move_Tutor_General_Exit::
    msgbox PKMN_Center_Move_Tutor_Text_SeeYou, MSGBOX_DEFAULT
	releaseall
	end

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Pre-Damage @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
PKMN_Center_EventScript_Exp_Grind::

	releaseall
	end

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Nature Change @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Max IVs @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
PKMN_Center_EventScript_MaxIVs::
	msgbox PKMN_Center_IVs_Party, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_eq PKMN_Center_Move_Tutor_General_Exit
	special IsSelectedMonEgg
	compare VAR_RESULT, TRUE
	goto_if_eq PKMN_Center_Text_EggIVs
	msgbox PKMN_Center_IVs_Single, MSGBOX_DEFAULT
	dynmultipush PKMN_Center_One, 0
	dynmultipush PKMN_Center_All, 1 
	dynmultistack 0, 0, FALSE, 2, FALSE, 0, NULL
	switch VAR_RESULT
	case 0, PKMN_Center_EventScript_MaxIVs_Single
	case 1, PKMN_Center_EventScript_MaxIVs_All
	releaseall
	end
PKMN_Center_Text_EggIVs::
	msgbox PKMN_Center_Text_EggIVs_Text, MSGBOX_DEFAULT
	releaseall
	end
PKMN_Center_EventScript_MaxIVs_Single::
	msgbox PKMN_Center_HeartScale_One, MSGBOX_DEFAULT
	checkitem ITEM_HEART_SCALE, 1
	goto_if_eq VAR_RESULT, FALSE, PKMN_Center_IVs_Exit
	msgbox PKMN_Center_WhichStat, MSGBOX_DEFAULT
	dynmultipush PKMN_Center_HP_IV, 0
	dynmultipush PKMN_Center_Atk_IV, 1
	dynmultipush PKMN_Center_Def_IV, 2
	dynmultipush PKMN_Center_Speed_IV, 3
	dynmultipush PKMN_Center_SpAtk_IV, 4
	dynmultipush PKMN_Center_SpDef_IV, 5
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, NULL
	copyvar VAR_0x8005, VAR_RESULT
	special SetNewIVStat
	msgbox PKMN_Center_IVs_Done_Text, MSGBOX_DEFAULT
	call PKMN_Center_Move_Tutor_General_Exit
	releaseall
	end

PKMN_Center_EventScript_MaxIVs_All::
	msgbox PKMN_Center_HeartScale_All, MSGBOX_DEFAULT
	checkitem ITEM_HEART_SCALE, 3
	goto_if_eq VAR_RESULT, FALSE, PKMN_Center_IVs_Exit
	special SetNewIVStatAll
	msgbox PKMN_Center_IVs_Done_Text, MSGBOX_DEFAULT
	call PKMN_Center_Move_Tutor_General_Exit
	releaseall
	end
	
PKMN_Center_IVs_Exit::
	msgbox PKMN_Center_NotEnough_HeartScale, MSGBOX_DEFAULT
	call PKMN_Center_Move_Tutor_General_Exit
	releaseall
	end
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Strings @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PKMN_Center_Move_Tutor_Text_HowCanHelp:
	.string "How can I help you today?$"

PKMN_Center_Move_Tutor_Text_SeeYou:
	.string "See you later, then!$"

PKMN_Center_MoveReminder_Text_WantMeToTeachMove:
	.string "Would you like a Pokémon to remember\n"
	.string "a move it has forgotten?$"

PKMN_Center_MoveReminder_Text_TutorWhichMon:
	.string "Which Pokémon should remember a move?$"

PKMN_Center_MoveReminder_Text_TeachWhichMove:
	.string "Which move would you like it to\n"
	.string "remember?$"

PKMN_Center_MoveReminder_Text_DontHaveMoveToTeachPokemon:
	.string "I'm sorry, that Pokémon doesn't have\n"
	.string "any moves it can remember.$"

PKMN_Center_MoveReminder_Text_CantTeachEgg:
	.string "I'm sorry, an Egg can't remember any\n"
	.string "moves.$"

PKMN_Center_MoveReminder_Text_RememberAnotherMove:
	.string "Would you like a Pokémon to remember\n"
	.string "another move?$"

PKMN_Center_MoveDeleter_Text_ICanMakeMonForgetMove:
	.string "Would you like one of your Pokémon\n"
	.string "to forget a move?$"

PKMN_Center_MoveDeleter_Text_WhichMonShouldForget:
	.string "Which Pokémon should forget a move?$"

PKMN_Center_MoveDeleter_Text_WhichMoveShouldBeForgotten:
	.string "Which move should be forgotten?$"

PKMN_Center_MoveDeleter_Text_MonOnlyKnowsOneMove:
	.string "{STR_VAR_1} knows only one move,\n"
	.string "so it can't be forgotten.$"

PKMN_Center_MoveDeleter_Text_MonsMoveShouldBeForgotten:
	.string "Hm! {STR_VAR_1}'s {STR_VAR_2}?\n"
	.string "That move should be forgotten?$"

PKMN_Center_MoveDeleter_Text_MonHasForgottenMove:
	.string "It worked to perfection!\p"
	.string "{STR_VAR_1} has forgotten\n"
	.string "{STR_VAR_2} completely.$"

PKMN_Center_MoveDeleter_Text_EggCantForgetMoves:
	.string "What?\n"
	.string "No Egg should know any moves.$"

PKMN_Center_Text_EggCantStatus:
	.string "What?\n"
	.string "Eggs cannot be stasued.$"

PKMN_Center_Text_EggIVs_Text:
	.string "What?\n"
	.string "Eggs has no IVs.$"
PKMN_Center_Text_EggGender_Text:
	.string "What?\nI can't do that!$"
PKMN_Center_MoveDeleter_Text_CantForgetSurf:
	.string "Hm!\p"
	.string "Your {STR_VAR_1} doesn't seem willing\n"
	.string "to forget Surf.$"

PKMN_Center_NameRater_Text_CritiqueWhichMonNickname:
	.string "Which Pokémon's nickname should\n"
	.string "be changed?$"

PKMN_Center_NameRater_Text_WhatShallNewNameBe:
	.string "What would you like {STR_VAR_1}'s\n"
	.string "new nickname to be?$"

PKMN_Center_NameRater_Text_MonShallBeKnownAsName:
	.string "Done! From now on, this Pokémon\n"
	.string "shall be known as {STR_VAR_1}!$"

PKMN_Center_NameRater_Text_NameNoDifferentYetSuperior:
	.string "Okay! {STR_VAR_1}'s nickname\n"
	.string "will stay as it is.$"

PKMN_Center_NameRater_Text_ThatIsMerelyAnEgg:
	.string "Now, now.\n"
	.string "That is merely an Egg!$"

PKMN_Center_Text_Mystery_Gift_NoGiftAvailable:
	.string "I'm sorry, there are no Mystery Gifts\n"
	.string "available at this time.$"

PKMN_Center_Mystery_Gift_Text_ReceivedGift::
	.string "{PLAYER} received {STR_VAR_1}!\p"
	.string "Take good care of {STR_VAR_1}!$"

PKMN_Center_Text_Mystery_Gift_WouldYouLikeGift::
	.string "Thank you for playing\n"
	.string "Inclement Emerald!\p"
	.string "You have a Mystery Gift available:\n"
	.string "a special {STR_VAR_1}!\p"
	.string "Would you like to receive\n"
	.string "{STR_VAR_1}?$"

PKMN_Center_Text_ApplyingStatus::
	.string "Which POKéMON you want to\napply a status to?$"

PKMN_Center_IVs_Party::
	.string "Which POKémon you want to\nmaximize the IVs?$"
PKMN_Center_Gender_Party::
	.string "Which POKémon you want to\nswitch gender?$"
PKMN_Center_IVs_Single::
	.string "Want to do it for just\none stat or all?$"
PKMN_Center_One::
	.string "One$"
PKMN_Center_All::
	.string "All$"
PKMN_Center_HeartScale_One::
	.string "The price is 1 Heart Scale.$"
PKMN_Center_HeartScale_All::
	.string "The price is 3 Hearts Scale.$"
PKMN_Center_NotEnough_HeartScale::
	.string "You have not enough Heart Scale.$"
PKMN_Center_WhichStat::
	.string "Which stat you want to maximize?$"
PKMN_Center_HP_IV::
	.string "HP$"
PKMN_Center_Atk_IV::
	.string "Atk$"
PKMN_Center_Def_IV::
	.string "Def$"
PKMN_Center_Speed_IV::
	.string "Speed$"
PKMN_Center_SpAtk_IV::
	.string "SpAtk$"
PKMN_Center_SpDef_IV::
	.string "SpDef$"
PKMN_Center_IVs_Done_Text::
	.string "Done, thank you.$"
PKMN_Center_Done_Text::
	.string "Done.$"