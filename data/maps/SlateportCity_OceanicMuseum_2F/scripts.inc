.set LOCALID_CAPT_STERN, 1
.set LOCALID_ARCHIE, 2
.set LOCALID_GRUNT_1, 3
.set LOCALID_GRUNT_2, 4
.set LOCALID_MATT, 9
.set LOCALID_BRAWLY, 8

SlateportCity_OceanicMuseum_2F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_2F_EventScript_CaptStern::
	lock
	msgbox Brawly_Alert_Text, MSGBOX_AUTOCLOSE
	closemessage
	msgbox SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, TRUE
	addobject LOCALID_MATT
	applymovement LOCALID_MATT, SlateportCity_OceanicMuseum_2F_Movement_Matt
	waitmovement 0
	applymovement LOCALID_BRAWLY, Common_Movement_WalkInPlaceFasterUp
	waitmovement LOCALID_BRAWLY
	applymovement LOCALID_BRAWLY, Common_Movement_ExclamationMark 
	waitmovement LOCALID_BRAWLY
	msgbox Matt_OceanicMuseum_Entrance_Text, MSGBOX_AUTOCLOSE
	closemessage
	addobject LOCALID_GRUNT_1
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter
	waitmovement 0
	addobject LOCALID_GRUNT_2
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter
	waitmovement 0
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	@msgbox SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts, MSGBOX_DEFAULT
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_BrawlyFight, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CAPT_STERN, SlateportCity_OceanicMuseum_2F_Movement_SternBack
	waitmovement 0
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_Grunt1Fight, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_1, SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat
	msgbox SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_2, SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_Grunt1Defeated
	waitmovement 0
	@applymovement LOCALID_MATT, SlateportCity_OceanicMuseum_2F_Movement_MattDefeated
	@waitmovement 0
	applymovement LOCALID_GRUNT_1, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_GRUNT_1, Common_Movement_WalkDown
	applymovement LOCALID_GRUNT_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_MattDefeated, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_MeddlingKid, MSGBOX_DEFAULT
	closemessage
	delay 35
	addobject LOCALID_ARCHIE
	applymovement LOCALID_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter
	waitmovement LOCALID_ARCHIE
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BRAWLY, Common_Movement_WalkDown
	waitmovement 0
	applymovement LOCALID_BRAWLY, Common_Movement_WalkLeft
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_BrawlyAskWho, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_ArchieWarning, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_BrawlyReply, MSGBOX_DEFAULT
	closemessage
	savebgm MUS_DUMMY
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_MATT
	fadescreen FADE_FROM_BLACK
	delay 30
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_AQUA_GRUNTS
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_BRAWLY, Common_Movement_FacePlayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_BrawlyThankYouForSavingUs, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CAPT_STERN, SlateportCity_OceanicMuseum_2F_Movement_SternEnd
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_DEVON_GOODS
	call Common_EventScript_PlayerHandedOverTheItem
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_BrawlyIveGotToGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_CAPT_STERN
	removeobject LOCALID_BRAWLY
	setflag FLAG_HIDE_ROUTE_110_TEAM_AQUA
	call_if_eq VAR_REGISTER_BIRCH_STATE, 0, SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch
	setflag FLAG_DELIVERED_DEVON_GOODS
	clearflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1
	fadescreen FADE_FROM_BLACK
	setflag FLAG_BRAWLY_BACK
	release
	end

SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch::
	setvar VAR_REGISTER_BIRCH_STATE, 1
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts::
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth::
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest::
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth:
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest:
	walk_up
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_Unused:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	delay_8
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle:
	walk_right
	face_player
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter:
	walk_down
	walk_right
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end
SlateportCity_OceanicMuseum_2F_Movement_Grunt1Defeated:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end
SlateportCity_OceanicMuseum_2F_Movement_MattDefeated:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end
SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_fast_down
	walk_in_place_faster_up
	step_end

SlateportCity_OceanicMuseum_2F_Movement_Matt:
	walk_down
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SternBack::
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end
SlateportCity_OceanicMuseum_2F_Movement_SternEnd::
	walk_up
	walk_left
	walk_left
	walk_left
	face_player
	step_end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_PressureExperiment::
	msgbox SlateportCity_OceanicMuseum_2F_Text_PressureExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_HoennModel::
	msgbox SlateportCity_OceanicMuseum_2F_Text_HoennModel, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_DeepSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SurfaceSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSTidalReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmarineReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmersibleReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSAnneReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron3::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
SlateportCity_MuseumTrigger0::
	goto_if_eq VAR_SLATEPORT_MUSEUM_TRIGGER, 1, GraniteCave_B3F_SplitFace_NULL
	lock
	msgbox Brawly_Trigger_Text, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_MuseumMovement1
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_ExclamationMark
	applymovement LOCALID_BRAWLY, Common_Movement_ExclamationMark 
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_BRAWLY, Common_Movement_WalkInPlaceFasterLeft 
	waitmovement 0
	setvar VAR_SLATEPORT_MUSEUM_TRIGGER, 1
	call SlateportCity_OceanicMuseum_2F_EventScript_CaptStern
	release
	end
SlateportCity_MuseumTrigger1::
	goto_if_eq VAR_SLATEPORT_MUSEUM_TRIGGER, 1, GraniteCave_B3F_SplitFace_NULL
	lock
	msgbox Brawly_Trigger_Text, MSGBOX_NPC
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_MuseumMovement1
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_ExclamationMark
	applymovement LOCALID_BRAWLY, Common_Movement_ExclamationMark 
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_BRAWLY, Common_Movement_WalkInPlaceFasterLeft 
	waitmovement 0
	setvar VAR_SLATEPORT_MUSEUM_TRIGGER, 1
	call SlateportCity_OceanicMuseum_2F_EventScript_CaptStern
	release
	end

SlateportCity_MuseumTrigger2::
	goto_if_eq VAR_SLATEPORT_MUSEUM_TRIGGER, 1, GraniteCave_B3F_SplitFace_NULL
	lock
	msgbox Brawly_Trigger_Text, MSGBOX_NPC
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_MuseumMovement2
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_ExclamationMark
	applymovement LOCALID_BRAWLY, Common_Movement_ExclamationMark 
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_BRAWLY, Common_Movement_WalkInPlaceFasterLeft 
	waitmovement 0
	setvar VAR_SLATEPORT_MUSEUM_TRIGGER, 1
	call SlateportCity_OceanicMuseum_2F_EventScript_CaptStern
	release
	end

SlateportCity_MuseumTrigger3::
	goto_if_eq VAR_SLATEPORT_MUSEUM_TRIGGER, 1, GraniteCave_B3F_SplitFace_NULL
	lock
	msgbox Brawly_Trigger_Text, MSGBOX_NPC
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_MuseumMovement3
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_ExclamationMark
	applymovement LOCALID_BRAWLY, Common_Movement_ExclamationMark 
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_BRAWLY, Common_Movement_WalkInPlaceFasterLeft 
	waitmovement 0
	setvar VAR_SLATEPORT_MUSEUM_TRIGGER, 1
	call SlateportCity_OceanicMuseum_2F_EventScript_CaptStern
	release
	end

SlateportCity_MuseumTrigger4::
	goto_if_eq VAR_SLATEPORT_MUSEUM_TRIGGER, 1, GraniteCave_B3F_SplitFace_NULL
	lock
	msgbox Brawly_Trigger_Text, MSGBOX_NPC
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_MuseumMovement4
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_ExclamationMark
	applymovement LOCALID_BRAWLY, Common_Movement_ExclamationMark 
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_BRAWLY, Common_Movement_WalkInPlaceFasterLeft 
	waitmovement 0
	setvar VAR_SLATEPORT_MUSEUM_TRIGGER, 1
	call SlateportCity_OceanicMuseum_2F_EventScript_CaptStern
	release
	end

SlateportCity_MuseumMovement0::
	walk_right
	walk_down
	walk_down
	face_right
	step_end

SlateportCity_MuseumMovement1::
	walk_right
	walk_down
	face_right
	step_end

SlateportCity_MuseumMovement2::
	walk_right
	face_right
	step_end

SlateportCity_MuseumMovement3::
	walk_right
	walk_up
	face_right
	step_end

SlateportCity_MuseumMovement4::
	walk_right
	walk_up
	walk_up
	face_right
	step_end

Brawly_Alert_Text::
	.string "BRAWLY: Who are you?$"

SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts:
	.string "CAPT. STERN: Ah! Those must be the parts\nI ordered "
	.string "from MR. STONE of DEVON.\p"
	.string "Thank you! That's great!\n"
	.string "We can prepare for our expedition now.\p"


SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts:
	.string "Hehehe, hold it!\n"
	.string "We'll take those parts!$"

SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou:
	.string "CAPT. STERN: Wh-what?\n"
	.string "Who are you people?$"

SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua:
	.string "MATT: We're TEAM AQUA!\p"
	.string "MATT: Our BOSS wants those parts!\p"
	.string "MATT: I didn't expect\nthe GYM LEADER to be here but whatever\p"
	.string "MATT: Now well'take what we need!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat:
	.string "Awaaaah!\n"
	.string "A kid beat me!$"

SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious:
	.string "Oh, man, what a disaster…\n"
	.string "The BOSS is going to be furious…$"

SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis:
	.string "Humph, sniveling wimp!\n"
	.string "Let me take care of this!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat:
	.string "What?!\n"
	.string "I lost, too!$"

SlateportCity_OceanicMuseum_2F_Text_MeddlingKid:
	.string "GRUNT: Now what?\nIf we don't get the parts"
	.string "we're in for it!\p"
	.string "Arrgh, I didn't count on being meddled\n"
	.string "with by some meddling kid!$"

SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong:
	.string "I came to see what was taking so\n"
	.string "long to snatch some parts.\p"
	.string "I expected the GYM Leader to be here,\nbut I thought you could handle it.\p"
	.string "Maybe was too much for you.$"

SlateportCity_OceanicMuseum_2F_Text_ArchieWarning:
	.string "We are TEAM AQUA,\n"
	.string "and we love the sea!\p"
	.string "And I am TEAM AQUA's leader,\n"
	.string "ARCHIE!\p"
	.string "What makes you interfere with us?\p"
	.string "…No! You can't be!\n"
	.string "You're not one of TEAM MAGMA?\p"
	.string "Wait, that can't be right.\n"
	.string "You're not dressed for the part.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "POKéMON, people… All life depends on\n"
	.string "the sea.\p"
	.string "So, TEAM AQUA is dedicated to\n"
	.string "the expansion of the sea.\p"
	.string "Don't you agree? What we are doing\n"
	.string "is a magnificent undertaking.\p"
	.string "Ah, fine…\n"
	.string "You're still too young to understand\l"
	.string "our noble objective.\p"
	.string "But, I warn you, don't even consider\n"
	.string "interfering with our plans again.\p"
	.string "The consequences will cost you\n"
	.string "dearly!\p"
	.string "And don't you forget it!$"

SlateportCity_OceanicMuseum_2F_Text_BrawlyThankYouForSavingUs:
	.string "BRAWLY: Thanks for the help.\nWhat's your name?\p"
	.string "{PLAYER}? I'll keep it in mind.\nYou helped me a lot earlier.\p"
	.string "I couldn't take them all alone,\nyou are very skilled.$"
SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs:
	.string "CAPT. STERN: Anyway, that was\na tense situation!\p"
	.string "Thank you for saving us!\p"
	.string "Oh, yes, I almost forgot that you\n"
	.string "even brought the parts from DEVON!$"

SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo:
	.string "CAPT. STERN: Whoops!\n"
	.string "There's no time to lose!\p"
	.string "We have to set out on our ocean-floor\n"
	.string "expedition really soon.\p"
	.string "Thanks again, but now I've got\n"
	.string "to go!\p"
	.string "Feel free to wander around and check\n"
	.string "out our facilities, though.$"

SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip:
	.string "I saw a model of a ship here.\p"
	.string "It reminded me of the ABANDONED SHIP\n"
	.string "near DEWFORD TOWN…$"

SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum:
	.string "Don't you dare run around inside\n"
	.string "the MUSEUM!$"

SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine:
	.string "Wow, the submarine's awesome!\n"
	.string "I want to go for a ride!$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1:
	.string "“WATER QUALITY SAMPLE 1,” the\n"
	.string "label says.\p"
	.string "The sea is all connected, but the\n"
	.string "water seems to differ by region.$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2:
	.string "“WATER QUALITY SAMPLE 2,” the\n"
	.string "label says.\p"
	.string "Does the saltiness of seawater differ\n"
	.string "by region, too?$"

SlateportCity_OceanicMuseum_2F_Text_PressureExperiment:
	.string "A rubber ball is expanding and\n"
	.string "shrinking.\p"
	.string "“In the sea, the weight of water itself\n"
	.string "exerts pressure.\p"
	.string "“In shallow water, the pressure is not\n"
	.string "very heavy.\p"
	.string "“However, in extremely deep water,\n"
	.string "the pressure can reach even tens of\l"
	.string "thousands of tons on a small area.”$"

SlateportCity_OceanicMuseum_2F_Text_HoennModel:
	.string "“MODEL OF HOENN REGION”\p"
	.string "It's a miniature diorama of the\n"
	.string "HOENN region.\p"
	.string "Where is LITTLEROOT TOWN on this?$"

SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay:
	.string "It's a display on the flow of seawater.\p"
	.string "“Near the bottom of the sea, water\n"
	.string "flows due to differences in such\l"
	.string "factors as temperature and salinity.”$"

SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay:
	.string "It's a display on the flow of seawater.\p"
	.string "“Toward the surface, seawater flows\n"
	.string "as currents driven by the winds.”$"

SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica:
	.string "“THE FERRY S.S. TIDAL\p"
	.string "“A scale replica of the ship under\n"
	.string "construction at STERN'S SHIPYARD.”$"

SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica:
	.string "“SUBMARINE EXPLORER 1\p"
	.string "“A replica of the high-performance\n"
	.string "ocean floor exploration submarine.”$"

SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica:
	.string "“SUBMERSIBLE POD\p"
	.string "“A replica of a compact, unmanned\n"
	.string "pod for seafloor exploration.”$"

SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica:
	.string "“S.S. ANNE\p"
	.string "“A replica of the luxury liner that\n"
	.string "circles the globe.”$"

Brawly_Trigger_Text::
	.string "BRAWLY: It's not safe to stay here,\nTeam Aqua is looking for Devon Goods.\p"
	.string "CAPT. STERN: I know, but I'm waiting\nthe part from MR. STONE.$"
Matt_OceanicMuseum_Entrance_Text::
	.string "MATT: Well well, look we got here.$"
SlateportCity_OceanicMuseum_2F_Text_BrawlyFight::
	.string "BRAWLY: I won't let you do\nwhatever you want!\p"
	.string "BRAWLY: Captain, stay back.$"
SlateportCity_OceanicMuseum_2F_Text_Grunt1Fight::
	.string "GRUNT: You're not going anywhere!$"
SlateportCity_OceanicMuseum_2F_Text_MattDefeated::
	.string "MATT: Tch, you got lucky.$"
SlateportCity_OceanicMuseum_2F_Text_BrawlyAskWho::
	.string "BRAWLY: Who are you now?!$"
SlateportCity_OceanicMuseum_2F_Text_BrawlyReply::
	.string "BRAWLY: We will not let you do\nwhatever you want ARCHIE!\p"
	.string "BRAWLY: We'll defeat you\neverytime is needed.\p"
	.string "ARCHIE: Fine, see you next time then.$"
SlateportCity_OceanicMuseum_2F_Text_BrawlyIveGotToGo::
	.string "BRAWLY: {PLAYER}, I have to go back\nto the gym of DEWFORD TOWN\p"
	.string "If you're a challenger\nI'll wait you there, see you soon.$"