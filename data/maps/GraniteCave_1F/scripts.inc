GraniteCave_1F_MapScripts::
	.byte 0

GraniteCave_1F_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash::
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
	.string "Hey, you.\n"
	.string "It used to get awfully dark ahead.\l"
	.string "Thankfully, that's not a problem\l"
	.string "anymore.\p"
	.string "I still have a ton of these leftover\n"
	.string "HMs, so you might as well take one!$"


GraniteCave_1F_Text_ExplainFlash:
	.string "That guy who came by earlier…\n"
	.string "STEVEN, I think it was.\p"
	.string "You ought to be able to find him\n"
	.string "if you head down into the cave.\p"
	.string "Best of luck to you!$"

