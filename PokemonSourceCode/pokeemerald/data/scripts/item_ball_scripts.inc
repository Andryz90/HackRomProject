Common_EventScript_FindItem::
	callnative GetItemBallIdAndAmountFromTemplate
	finditem VAR_RESULT VAR_0x8009
	end

Common_EventScript_FindItem_Temp::
	callnative GetItemBallIdAndAmountFromTemplate
	copyvar VAR_FOR_TEMP_ITEM, VAR_RESULT @Mi salvo in questa var l'item che è stato preso per ultimo
	finditem VAR_RESULT VAR_0x8009
	end