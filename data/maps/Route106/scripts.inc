Route106_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route106_OnFrame
	.byte 0

Route106_OnFrame::
	map_script_2 FLAG_PRES_CALL_BOX, 1, Route106_EventScript_PresidentDoCall
	.2byte 0

Route106_EventScript_TrainerTipsSign::
	msgbox Route106_Text_TrainerTips, MSGBOX_SIGN
	end

Route106_EventScript_Douglas::
	trainerbattle_single TRAINER_DOUGLAS, Route106_Text_DouglasIntro, Route106_Text_DouglasDefeated
	msgbox Route106_Text_DouglasPostBattle, MSGBOX_AUTOCLOSE
	end

Route106_EventScript_PresidentCall::
	goto_if_set FLAG_PRES_CALL_BOX, Route106_EventScript_PresidentDoCall
	releaseall
	end

Route106_EventScript_PresidentDoCall::
	lockall
	pokenavcall Route106_Text_PresidentCall
	waitmessage
	clearflag FLAG_PRES_CALL_BOX
	releaseall
	end

Route106_EventScript_Kyla::
	trainerbattle_single TRAINER_KYLA, Route106_Text_KylaIntro, Route106_Text_KylaDefeated
	msgbox Route106_Text_KylaPostBattle, MSGBOX_AUTOCLOSE
	end

Route106_EventScript_Elliot::
	trainerbattle_single TRAINER_ELLIOT_1, Route106_Text_ElliotIntro, Route106_Text_ElliotDefeated, Route106_EventScript_ElliotRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route106_EventScript_ElliotRematch
	msgbox Route106_Text_ElliotPostBattle, MSGBOX_DEFAULT
	release
	end

Route106_EventScript_ElliotRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route106_Text_ElliotRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ELLIOT_1
	release
	end

Route106_EventScript_ElliotRematch::
	trainerbattle_rematch TRAINER_ELLIOT_1, Route106_Text_ElliotRematchIntro, Route106_Text_ElliotRematchDefeated
	msgbox Route106_Text_ElliotRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route106_EventScript_Ned::
	trainerbattle_single TRAINER_NED, Route106_Text_NedIntro, Route106_Text_NedDefeated
	msgbox Route106_Text_NedPostBattle, MSGBOX_AUTOCLOSE
	end

Route106_Text_TrainerTips:
	.string "TRAINER TIPS\p"
	.string "Advice on catching POKéMON with a ROD:\n"
	.string "Press the A Button if you get a bite.$"

Route106_Text_PresidentCall:
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "MR. STONE: Hello {PLAYER}!\p"
	.string "Steven gave me a call to let me know\n"
	.string "he received my letter.\p"
	.string "I must thank you for helping me with\n"
	.string "this errand, so please visit me in my\l"
	.string "office the next time you are in\l"
	.string "Rustboro City.\p"
	.string "I have a very special item I would\n"
	.string "like to give you.\p"
	.string "See you soon!\p"
	.string "… … … … … …\n"
	.string "… … … … … Click!$"
