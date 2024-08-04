RustboroCity_House1_MapScripts::
	.byte 0

RustboroCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_RUSTBORO_NPC_TRADE_COMPLETED, RustboroCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_SEEDOT
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox RustboroCity_House1_Text_IllTradeIfYouWant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, RustboroCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, RustboroCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox RustboroCity_House1_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_RUSTBORO_NPC_TRADE_COMPLETED
	release
	end

RustboroCity_House1_EventScript_DeclineTrade::
	msgbox RustboroCity_House1_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox RustboroCity_House1_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TradeCompleted::
	msgbox RustboroCity_House1_Text_AnyPokemonCanBeCute, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_Hiker::
	msgbox RustboroCity_House1_Text_AllSortsOfPlaces, MSGBOX_NPC
	end

RustboroCity_House1_Hisuian_Thankful::
	msgbox RustboroCity_House1_Text_Hisuian_Thankful, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_Give_HisuianAmulet::
	msgbox RustboroCity_House1_Text_Hisuian_Found, MSGBOX_DEFAULT
	giveitem ITEM_HISUIAN_AMULET
	setflag FLAG_RUSTBORO_HISUI_FLAG
	call RustboroCity_House1_Hisuian_Thankful
	return

RustboroCity_House1_Hisuian_Rejected::
	msgbox RustboroCity_House1_Text_Hisuian_Rejected, MSGBOX_DEFAULT
	release
	return

RustboroCity_House1_EventScript_Hisuian_Collector::
	lock
	faceplayer
	goto_if_set FLAG_RUSTBORO_HISUI_FLAG, RustboroCity_House1_Hisuian_Thankful
	msgbox RustboroCity_House1_Text_Hisuian, MSGBOX_DEFAULT
	setvar VAR_0x8008, 548 @petilil
	copyvar VAR_0x8000, VAR_0x8008
	specialvar VAR_RESULT CheckMonParty
	call_if_eq VAR_RESULT, TRUE, RustboroCity_House1_Give_HisuianAmulet
	call_if_eq VAR_RESULT, FALSE, RustboroCity_House1_Hisuian_Rejected
	end
RustboroCity_House1_Text_IllTradeIfYouWant:
	.string "Huh? My POKéMON is cute?\n"
	.string "Sure, I knew that.\p"
	.string "But if you really want, I'm willing\n"
	.string "to trade it to you.\p"
	.string "I'll trade you my {STR_VAR_2} for\n"
	.string "a {STR_VAR_1} if you want.$"

RustboroCity_House1_Text_PleaseBeGoodToMyPokemon:
	.string "Eheheh…\n"
	.string "Please be good to my POKéMON.$"

RustboroCity_House1_Text_DoesntLookLikeMonToMe:
	.string "Huh? That doesn't look anything like\n"
	.string "a {STR_VAR_1} to me.$"

RustboroCity_House1_Text_YouDontWantToThatsOkay:
	.string "Oh, if you don't want to, that's okay.\n"
	.string "But my POKéMON is cute, you know…$"

RustboroCity_House1_Text_AnyPokemonCanBeCute:
	.string "Any POKéMON can be cute if you raise\n"
	.string "it with care and kindness.$"

RustboroCity_House1_Text_AllSortsOfPlaces:
	.string "In all sorts of places, there are all\n"
	.string "sorts of POKéMON and people.\p"
	.string "I find that fascinating, so I go to all\n"
	.string "sorts of places.$"

RustboroCity_House1_Text_Hisuian:
	.string "I used to be a trainer for long time,\n"
	.string "but I never saw the new Pokemon's form.\p"
	.string "I want to see a Pokemon change into the\n"
	.string "hisuian evolution.\p"
	.string "Do you happen to have a Petilil?$"
RustboroCity_House1_Text_Hisuian_Found:
	.string "Oh you have it! Take this as reward.$"
RustboroCity_House1_Text_Hisuian_Thankful:
	.string "Thanks, now I can finally see my favorite\n"
	.string "hisuian evolution!$"

RustboroCity_House1_Text_Hisuian_Rejected:
	.string "Seems you don't have it.$"