VerdanturfPrairie_MapScripts::
	.byte 0

VerdanturfPrarie_Woman:: 	
	lock
	faceplayer
	goto_if_set FLAG_RELAXED_MINT_GIRL, VerdanturfPrarie_HopeEnjoy
	msgbox VerdanturfPrarie_LoveFlower_Text, MSGBOX_DEFAULT
	msgbox VerdanturfPrarie_RelaxMint_Text, MSGBOX_DEFAULT
	giveitem ITEM_RELAXED_MINT, 1
	setflag FLAG_RELAXED_MINT_GIRL
	msgbox VerdanturfPrarie_HopeEnjoy_Text, MSGBOX_DEFAULT
	release
	end 
VerdanturfPrarie_HopeEnjoy::
	msgbox VerdanturfPrarie_HopeEnjoy_Text, MSGBOX_DEFAULT
	release
	end 

VerdanturfPrarie_Meganium::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MEGANIUM, CRY_MODE_NORMAL
	msgbox VerdanturfPrarie_Meganium_Text, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VerdanturfPrarie_FlowerLover::
	lock
	faceplayer
	msgbox VerdanturfPrarie_FlowerLover_Text, MSGBOX_DEFAULT
	release
	end

VerdanturfPrarie_PicnicWoman::
	lock
	faceplayer
	msgbox VerdanturfPrarie_PicnicWoman_Text, MSGBOX_DEFAULT
	release
	end

VerdanturfPrarie_Slurpuff::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SLURPUFF, CRY_MODE_NORMAL
	msgbox VerdanturfPrarie_Slurpuff_Text, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VerdanturfPrarie_Sunflora::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SUNFLORA, CRY_MODE_NORMAL
	msgbox VerdanturfPrarie_Sunflora_Text, MSGBOX_DEFAULT
	waitmoncry
	release
	end
VerdanturfPrarie_Sunflora_Text::
	.string "Flora$"
VerdanturfPrarie_Slurpuff_Text::
	.string "S-slurp?$"

VerdanturfPrarie_PicnicWoman_Text::
	.string "I love making picnics here.\pThe weather is so nice\nand the air is so fresh!$"

VerdanturfPrarie_FlowerLover_Text::
	.string "I love watering the flowers here.\nThey bloom so beautifully!$"

VerdanturfPrarie_LoveFlower_Text::
	.string "I love flowers,\nhere the air is so fresh.\p"
	.string "Breathing here is good for the health.\nThe POKéMON here seems to love it too.\p"
	.string "It's so relaxing, don't you think so too?$"

VerdanturfPrarie_RelaxMint_Text::	
	.string "I picked up this,\nhere, take it without problem.$"

VerdanturfPrarie_HopeEnjoy_Text::
	.string "I hope you enjoy to stay here.$"

VerdanturfPrarie_Meganium_Text::
	.string "M-megaa$"