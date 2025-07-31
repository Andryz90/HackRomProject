DuneCave_MapScripts::
	.byte 0

Braille_Dummy_Messages_Cock::
	lockall
	braillemsgbox DesertRuins_Braille_Cock
	releaseall
	end
Braille_Dummy_Messages_Suca::
	lockall
	braillemsgbox DesertRuins_Braille_Suca
	releaseall
	end

Team_MagmaGrunt_NotUnderstanding1::
	lock
	msgbox MagmaGrunt_NotUnderstanding_Text, MSGBOX_DEFAULT
	applymovement MAGMA_GRUNT1, Common_Movement_ExclamationMark
	applymovement MAGMA_GRUNT1, Common_Movement_Delay32
	waitmovement 0
	applymovement MAGMA_GRUNT1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MagmaGrunt_GetOut_Text, MSGBOX_DEFAULT
	applymovement MAGMA_GRUNT1, Common_Movement_FaceUp
	waitmovement 0
	release 
	end
Team_MagmaGrunt_NotUnderstanding2::
	lock
	msgbox MagmaGrunt_NotUnderstanding_Text, MSGBOX_DEFAULT
	applymovement MAGMA_GRUNT2, Common_Movement_ExclamationMark
	applymovement MAGMA_GRUNT2, Common_Movement_Delay32
	waitmovement 0
	applymovement MAGMA_GRUNT2, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MagmaGrunt_GetOut_Text, MSGBOX_DEFAULT
	applymovement MAGMA_GRUNT2, Common_Movement_FaceUp
	waitmovement 0
	release 
	end

MagmaGrunt_NotUnderstanding_Text::
	.string "I don't understand what's\n"
	.string "written here...  $"

MagmaGrunt_GetOut_Text::
	.string "Ehi! Get out of here!\n"
	.string "Mind your own business.  $"