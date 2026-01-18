Common_EventScript_FindItem::
	callnative GetItemBallIdAndAmountFromTemplate
	finditem VAR_RESULT VAR_0x8009
	end

Common_EventScript_FindItem_AndSave_Temp::
	lock
	callnative GetItemBallIdAndAmountFromTemplate @Take and save the name in var result
	bufferitemname STR_VAR_1, VAR_RESULT
	copyvar VAR_FOR_TEMP_ITEM, VAR_RESULT @Mi salvo in questa var l'item che è stato preso per ultimo (serve per alcuni script, tipo rival rustboro)
	msgbox ItemContainedInBall_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, QuitItemPick
	callnative GetItemBallIdAndAmountFromTemplate @ Retake the data because the player has override the VAR_RESULT with the choice (I could save the VAR_RESULT value in another special var but this is safest)
	finditem VAR_RESULT, VAR_0x8009
	release
	end
Common_EventScript_FindItem_Temp::
	lock
	callnative GetItemBallIdAndAmountFromTemplate @Take and save the name in var result
	bufferitemname STR_VAR_1, VAR_RESULT
	msgbox ItemContainedInBall_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, QuitItemPick
	callnative GetItemBallIdAndAmountFromTemplate @ Retake the data because the player has override the VAR_RESULT with the choice (I could save the VAR_RESULT value in another special var but this is safest)
	finditem VAR_RESULT, VAR_0x8009
	release
	end

Common_EventScript_GimmighoulCoin::
	finditem ITEM_GIMMIGHOUL_COIN, 100
	end

QuitItemPick::
	release
	end
ItemContainedInBall_Text::
	.string "The item contained in the ball is:\n{STR_VAR_1}.\p"
	.string "Woud you like to take it? $"
