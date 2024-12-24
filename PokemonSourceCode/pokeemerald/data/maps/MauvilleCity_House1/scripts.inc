MauvilleCity_House1_MapScripts::
	.byte 0

MauvilleCity_House1_EventScript_RockSmashDude::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_COIN_CASE, MauvilleCity_House1_EventScript_ReceivedCoinCase
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_COIN_CASE
	setflag FLAG_RECEIVED_COIN_CASE
	goto MauvilleCity_House1_EventScript_ReceivedCoinCase
	release
	end	

	@goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, MauvilleCity_House1_EventScript_ReceivedRockSmash
	@msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	@giveitem ITEM_HM_ROCK_SMASH
	@setflag FLAG_RECEIVED_HM_ROCK_SMASH
	@setflag FLAG_HIDE_ROUTE_111_ROCK_SMASH_TIP_GUY

MauvilleCity_House1_EventScript_ReceivedCoinCase::
	msgbox MauvilleCity_House1_EventScript_ReceivedCoinCase_Text, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
	.string "Woohoo!\p"
	.string "I hear people want to gamble!\nTake this then.$"

MauvilleCity_House1_Text_ExplainRockSmash:
	.string "That HM contains ROCK SMASH.\p"
	.string "If you come across large boulders\n"
	.string "that block your path…\p"
	.string "Well, use that HM move and smash\n"
	.string "them right out of your way!\p"
	.string "Yes, sir! Smash rocks aside, I say!\n"
	.string "Woohoo!$"

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
	.string "Oh, yes, if you smash a rock, a POKéMON\n"
	.string "could come flying out of hiding.\p"
	.string "Woohoo!$"

MauvilleCity_House1_EventScript_ReceivedCoinCase_Text::
	.string "With this you can gamble\nin the GAME CORNER!$"