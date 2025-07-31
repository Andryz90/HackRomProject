.set LOCALID_SPLITFACE, 2

GraniteCave_B3F_MapScripts::
	.byte 0

GraniteCave_B3F_SplitFace_ApprochingPlayer1::
	walk_up
	walk_up
	walk_up
	walk_left
	face_player
	step_end
GraniteCave_B3F_SplitFace_ApprochingPlayer2::
	walk_up
	walk_up
	walk_up
	step_end
GraniteCave_B3F_SplitFace_ApprochingPlayer3::
	walk_up
	walk_up
	walk_up
	walk_right
	face_player
	step_end
GraniteCave_B3F_SplitFace_Huh::
	face_up
	emote_question_mark
	step_end
GraniteCave_B3F_SplitFace_Leaving1::
	walk_right
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

GraniteCave_B3F_SplitFace_Leaving2::
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

GraniteCave_B3F_SplitFace_Leaving3::
	walk_left
	walk_up
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
GraniteCave_B3F_SplitFace_NULL::
	release
	end

GraniteCave_B3F_SplitFace_AfterBattle1::
	msgbox GraniteCave_B3F_SplitFace_LastText, MSGBOX_DEFAULT
	setflag SPLITFACE_ENCOUNTERED
	setvar VAR_SPLITFACE_TRIGGER_1, 1
	giveitem ITEM_EVIOLITE
	msgbox GraniteCave_B3F_SplitFace_BuonanotteLMFAO, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, GraniteCave_B3F_SplitFace_Leaving1
	waitmovement LOCALID_SPLITFACE
	removeobject LOCALID_SPLITFACE
	release
	end
GraniteCave_B3F_SplitFace_Battle1::
	trainerbattle_single TRAINER_SPLITFACE_1, GraniteCave_B3F_SplitFace_BattleIntroText, GraniteCave_B3F_SplitFace_BattleLoseText, GraniteCave_B3F_SplitFace_AfterBattle1, NO_MUSIC
	release 
	end
GraniteCave_B3F_SplitFace_Encounter1::
	goto_if_eq VAR_SPLITFACE_TRIGGER_1, 1 GraniteCave_B3F_SplitFace_NULL
	lock 
	msgbox GraniteCave_B3F_SplitFace_TextSolo, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, Common_Movement_Delay32
	waitmovement  LOCALID_SPLITFACE  
	playse SE_PIN
	applymovement LOCALID_SPLITFACE, GraniteCave_B3F_SplitFace_Huh
	waitmovement  LOCALID_SPLITFACE  
	applymovement LOCALID_SPLITFACE, Common_Movement_Delay32
	waitmovement  LOCALID_SPLITFACE  
	msgbox GraniteCave_B3F_SplitFace_Huh_Text, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, Common_Movement_Delay32
	waitmovement  LOCALID_SPLITFACE 
	applymovement LOCALID_SPLITFACE, GraniteCave_B3F_SplitFace_ApprochingPlayer1
	waitmovement  LOCALID_SPLITFACE 
	msgbox GraniteCave_B3F_SplitFace_TextPlayer, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, Common_Movement_FaceAwayPlayer 
	waitmovement  LOCALID_SPLITFACE  
	msgbox GraniteCave_B3F_SplitFace_Bestemmia, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, Common_Movement_Delay32
	waitmovement  LOCALID_SPLITFACE
	applymovement LOCALID_SPLITFACE, Common_Movement_FacePlayer 
	waitmovement  LOCALID_SPLITFACE
	msgbox GraniteCave_B3F_SplitFace_TextPlayer2, MSGBOX_DEFAULT
	applymovement LOCALID_SPLITFACE, Common_Movement_FacePlayer 
	waitmovement  LOCALID_SPLITFACE
	msgbox GraniteCave_B3F_SplitFace_TextPlayer2_Part2, MSGBOX_DEFAULT
	call GraniteCave_B3F_SplitFace_Battle1
	release
	end
@@ 2nd Trigger 
GraniteCave_B3F_SplitFace_AfterBattle2::
	msgbox GraniteCave_B3F_SplitFace_LastText, MSGBOX_DEFAULT
	setflag SPLITFACE_ENCOUNTERED
	setvar VAR_SPLITFACE_TRIGGER_1, 1
	giveitem ITEM_EVIOLITE
	msgbox GraniteCave_B3F_SplitFace_BuonanotteLMFAO, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, GraniteCave_B3F_SplitFace_Leaving2
	waitmovement LOCALID_SPLITFACE
	removeobject LOCALID_SPLITFACE
	release
	end
GraniteCave_B3F_SplitFace_Battle2::
	trainerbattle_single TRAINER_SPLITFACE_1, GraniteCave_B3F_SplitFace_BattleIntroText, GraniteCave_B3F_SplitFace_BattleLoseText, GraniteCave_B3F_SplitFace_AfterBattle2, NO_MUSIC
	release 
	end
GraniteCave_B3F_SplitFace_Encounter2::
	goto_if_eq VAR_SPLITFACE_TRIGGER_1, 1 GraniteCave_B3F_SplitFace_NULL
	lock 
	msgbox GraniteCave_B3F_SplitFace_TextSolo, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, Common_Movement_Delay32
	waitmovement  LOCALID_SPLITFACE  
	playse SE_PIN
	applymovement LOCALID_SPLITFACE, GraniteCave_B3F_SplitFace_Huh
	waitmovement  LOCALID_SPLITFACE  
	applymovement LOCALID_SPLITFACE, Common_Movement_Delay32
	waitmovement  LOCALID_SPLITFACE  
	msgbox GraniteCave_B3F_SplitFace_Huh_Text, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, Common_Movement_Delay32
	waitmovement  LOCALID_SPLITFACE 
	applymovement LOCALID_SPLITFACE, GraniteCave_B3F_SplitFace_ApprochingPlayer2
	waitmovement  LOCALID_SPLITFACE 
	msgbox GraniteCave_B3F_SplitFace_TextPlayer, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, Common_Movement_FaceAwayPlayer 
	waitmovement  LOCALID_SPLITFACE  
	msgbox GraniteCave_B3F_SplitFace_Bestemmia, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, Common_Movement_Delay32
	waitmovement  LOCALID_SPLITFACE
	applymovement LOCALID_SPLITFACE, Common_Movement_FacePlayer 
	waitmovement  LOCALID_SPLITFACE
	msgbox GraniteCave_B3F_SplitFace_TextPlayer2, MSGBOX_DEFAULT
	applymovement LOCALID_SPLITFACE, Common_Movement_FacePlayer 
	waitmovement  LOCALID_SPLITFACE
	msgbox GraniteCave_B3F_SplitFace_TextPlayer2_Part2, MSGBOX_DEFAULT
	call GraniteCave_B3F_SplitFace_Battle2
	release
	end

@@ 3rd Trigger 
GraniteCave_B3F_SplitFace_AfterBattle3::
	msgbox GraniteCave_B3F_SplitFace_LastText, MSGBOX_DEFAULT
	setflag SPLITFACE_ENCOUNTERED
	setvar VAR_SPLITFACE_TRIGGER_1, 1
	giveitem ITEM_EVIOLITE
	msgbox GraniteCave_B3F_SplitFace_BuonanotteLMFAO, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, GraniteCave_B3F_SplitFace_Leaving3
	waitmovement LOCALID_SPLITFACE
	removeobject LOCALID_SPLITFACE
	release
	end
GraniteCave_B3F_SplitFace_Battle3::
	trainerbattle_single TRAINER_SPLITFACE_1, GraniteCave_B3F_SplitFace_BattleIntroText, GraniteCave_B3F_SplitFace_BattleLoseText, GraniteCave_B3F_SplitFace_AfterBattle3, NO_MUSIC
	release 
	end
GraniteCave_B3F_SplitFace_Encounter3::
	goto_if_eq VAR_SPLITFACE_TRIGGER_1, 1 GraniteCave_B3F_SplitFace_NULL
	lock 
	msgbox GraniteCave_B3F_SplitFace_TextSolo, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, Common_Movement_Delay32
	waitmovement  LOCALID_SPLITFACE  
	playse SE_PIN
	applymovement LOCALID_SPLITFACE, GraniteCave_B3F_SplitFace_Huh
	waitmovement  LOCALID_SPLITFACE  
	applymovement LOCALID_SPLITFACE, Common_Movement_Delay32
	waitmovement  LOCALID_SPLITFACE  
	msgbox GraniteCave_B3F_SplitFace_Huh_Text, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, Common_Movement_Delay32
	waitmovement  LOCALID_SPLITFACE 
	applymovement LOCALID_SPLITFACE, GraniteCave_B3F_SplitFace_ApprochingPlayer3
	waitmovement  LOCALID_SPLITFACE 
	msgbox GraniteCave_B3F_SplitFace_TextPlayer, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, Common_Movement_FaceAwayPlayer 
	waitmovement  LOCALID_SPLITFACE  
	msgbox GraniteCave_B3F_SplitFace_Bestemmia, MSGBOX_AUTOCLOSE
	applymovement LOCALID_SPLITFACE, Common_Movement_Delay32
	waitmovement  LOCALID_SPLITFACE
	applymovement LOCALID_SPLITFACE, Common_Movement_FacePlayer 
	waitmovement  LOCALID_SPLITFACE
	msgbox GraniteCave_B3F_SplitFace_TextPlayer2, MSGBOX_DEFAULT
	applymovement LOCALID_SPLITFACE, Common_Movement_FacePlayer 
	waitmovement  LOCALID_SPLITFACE
	msgbox GraniteCave_B3F_SplitFace_TextPlayer2_Part2, MSGBOX_DEFAULT
	call GraniteCave_B3F_SplitFace_Battle3
	release
	end
GraniteCave_B3F_SplitFace_TextSolo::
	.string "Mmh very interesting mineral. $"

GraniteCave_B3F_SplitFace_Huh_Text::
	.string "Huh? $"

GraniteCave_B3F_SplitFace_TextPlayer::
	.string "Yo.\p"
	.string "I'm one of the developer of the game,\n"
	.string "even though I didn't much... $"

GraniteCave_B3F_SplitFace_Bestemmia::
	.string "Dio Porco. $"

GraniteCave_B3F_SplitFace_CazzoPalle::
	.string "Cazzo palle. $"

GraniteCave_B3F_SplitFace_TextPlayer2::
	.string "So you're {PLAYER},\n"
	.string "the main character I suppose. $"

GraniteCave_B3F_SplitFace_TextPlayer2_Part2::
	.string "I like Ice type a lot and \n"
	.string "I hate the high temperatures.\p"
	.string "Thats why I came here. The Ice types\n"
	.string "are so cute and I love them.\p"
	.string "Did you see the Spheal?\nThey are too precious.\p"
	.string "Btw I'm Splitface, nice to meet you.\p"
	.string "Can you guess which one\nis my favorite Pokémon? $"

GraniteCave_B3F_SplitFace_BattleIntroText::
	.string "Lets battle so you can find it out. $"

GraniteCave_B3F_SplitFace_BattleLoseText::
	.string "That's what happened when you use\n"
	.string "Pokémon that you like, LMFAO. $"

GraniteCave_B3F_SplitFace_LastText::
	.string "I hope you enjoyed the battle, take this,\n"
	.string "will help you in your journey. $"

GraniteCave_B3F_SplitFace_BuonanotteLMFAO::
	.string "Buonanotte. $"