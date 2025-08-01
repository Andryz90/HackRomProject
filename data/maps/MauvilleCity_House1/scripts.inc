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

MauvilleCity_House1_EventScript_ReceivedCoinCase::
	msgbox MauvilleCity_House1_EventScript_ReceivedCoinCase_Text, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
	.string "Woohoo!\p"
	.string "I hear people want to gamble!\n"
	.string "Take this then.  $"

MauvilleCity_House1_Text_ExplainRockSmash:
	.string "That HM contains ROCK SMASH.\p"
	.string "If you come across large boulders\n"
	.string "that block your path…\p"
	.string "Well, use that HM move and smash\n"
	.string "them right out of your way.  $"

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
	.string "Oh, yes, if you smash a rock, a POKéMON\n"
	.string "could come flying out of hiding.  $"

MauvilleCity_House1_EventScript_ReceivedCoinCase_Text::
	.string "With this you can gamble\n"
	.string "in the GAME CORNER!  $"