@ Interact with cuttable tree
EventScript_CutTree::
	lockall
	goto_if_unset FLAG_BADGE01_GET, EventScript_CheckTreeCantCut
	checkpartymove MOVE_CUT
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CheckAxe
	setfieldeffectargument 0, VAR_RESULT
	goto_if_eq VAR_HM_OPTION, 1, EventScript_UseCutSkip
	setvar VAR_FIELD_MOVE_TYPE, 1
	dofieldeffect FLDEFF_USE_CUT_ON_TREE
	waitstate
	goto EventScript_CutTreeDown
	end

@ Use cut from party menu or bag
EventScript_UseCut::
	lockall
	dofieldeffect FLDEFF_USE_CUT_ON_TREE
	waitstate
	goto EventScript_CutTreeDown
	end

EventScript_CheckAxe::
	checkitem ITEM_AXE, 1
	goto_if_eq VAR_RESULT, 1, EventScript_UseCutSkip
	goto EventScript_CheckTreeCantCut
	end

EventScript_UseCutSkip::
	setvar VAR_FIELD_MOVE_TYPE, 2
	dofieldeffect FLDEFF_USE_CUT_ON_TREE
	waitstate
	goto EventScript_CutTreeDown
	end

EventScript_CheckTreeCantCut::
	msgbox Text_CantCut, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CancelCut::
	closemessage
	releaseall
	end

EventScript_CutTreeDown::
	applymovement VAR_LAST_TALKED, Movement_CutTreeDown
	waitmovement 0
	removeobject VAR_LAST_TALKED
	releaseall
	end

Movement_CutTreeDown:
	cut_tree
	step_end

Text_WantToCut:
	.string "This tree looks like it can be\n"
	.string "CUT down!\p"
	.string "Would you like to CUT it?$"

Text_MonUsedFieldMove:
	.string "{STR_VAR_1} used {STR_VAR_2}!$"

Text_CantCut:
	.string "This tree looks like it can be\n"
	.string "cut down!$"

@ Interact with smashable rock
EventScript_RockSmash::
	lockall
	goto_if_unset FLAG_BADGE03_GET, EventScript_CantSmashRock
	checkpartymove MOVE_ROCK_SMASH
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CheckPickaxe
	setfieldeffectargument 0, VAR_RESULT
	goto_if_eq VAR_HM_OPTION, 1, EventScript_UseRockSmashSkip
	setvar VAR_FIELD_MOVE_TYPE, 1
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
	goto EventScript_SmashRock
	end

EventScript_CheckPickaxe::
	checkitem ITEM_PICKAXE, 1
	goto_if_eq VAR_RESULT, 1, EventScript_UseRockSmashSkip
	goto EventScript_CantSmashRock
	end

EventScript_UseRockSmashSkip::
	setvar VAR_FIELD_MOVE_TYPE, 2
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
	goto EventScript_SmashRock
	end

@ Use rock smash from party menu or bag
EventScript_UseRockSmash::
	lockall
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
	goto EventScript_SmashRock
	end

EventScript_SmashRock::
	applymovement VAR_LAST_TALKED, Movement_SmashRock
	waitmovement 0
	removeobject VAR_LAST_TALKED
	specialvar VAR_RESULT, TryUpdateRusturfTunnelState
	goto_if_eq VAR_RESULT, TRUE, EventScript_EndSmash
	special RockSmashWildEncounter
	goto_if_eq VAR_RESULT, FALSE, EventScript_EndSmash
	waitstate
	setvar VAR_FIELD_MOVE_TYPE, 0
	releaseall
	end

EventScript_EndSmash::
	releaseall
	end

Movement_SmashRock:
	rock_smash_break
	step_end

EventScript_CantSmashRock::
	msgbox Text_CantSmash, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CancelSmash::
	closemessage
	releaseall
	end

Text_WantToSmash:
	.string "This rock appears to be breakable.\n"
	.string "Would you like to use ROCK SMASH?$"

Text_CantSmash:
	.string "It's a rugged rock, but a Pokémon or\n"
	.string "pickaxe may be able to smash it.$"

EventScript_StrengthBoulder::
	lockall
	goto_if_unset FLAG_BADGE04_GET, EventScript_CantStrength
	goto_if_set FLAG_SYS_USE_STRENGTH, EventScript_CheckActivatedBoulder
	checkpartymove MOVE_STRENGTH
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CheckPowerGlove
	setfieldeffectargument 0, VAR_RESULT
	goto_if_eq VAR_HM_OPTION, 1, EventScript_UseStrengthSkip
	setvar VAR_FIELD_MOVE_TYPE, 1
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto EventScript_ActivateStrengthMon
	end

EventScript_CheckPowerGlove::
	checkitem ITEM_POWER_GLOVE, 1
	goto_if_eq VAR_RESULT, 1, EventScript_UseStrengthGlove
	goto EventScript_CantStrength
	end

EventScript_UseStrengthSkip::
	lockall
	setvar VAR_FIELD_MOVE_TYPE, 2
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto EventScript_ActivateStrengthMon
	end

EventScript_UseStrengthGlove::
	lockall
	setvar VAR_FIELD_MOVE_TYPE, 2
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto EventScript_ActivateStrengthGlove
	end

EventScript_UseStrength::
	lockall
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto EventScript_ActivateStrengthMon
	end

EventScript_UseStrengthItem::
	lockall
	setvar VAR_FIELD_MOVE_TYPE, 2
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto EventScript_ActivateStrengthGlove
	end

EventScript_ActivateStrengthMon::
	setflag FLAG_SYS_USE_STRENGTH
	playse SE_M_MEGA_KICK
	msgbox Text_MonUsedStrength, MSGBOX_DEFAULT
	waitse
	releaseall
	end

EventScript_ActivateStrengthGlove::
	setflag FLAG_SYS_USE_STRENGTH
	playse SE_M_MEGA_KICK
	msgbox Text_PowerGloveOn, MSGBOX_DEFAULT
	waitse
	releaseall
	end

EventScript_CantStrength::
	msgbox Text_CantStrength, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CheckActivatedBoulder::
	msgbox Text_StrengthActivated, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CancelStrength::
	closemessage
	releaseall
	end

Text_WantToStrength:
	.string "It's a big boulder, but a POKéMON\n"
	.string "may be able to push it aside.\p"
	.string "Would you like to use STRENGTH?$"

Text_MonUsedStrength:
	.string "{STR_VAR_1}'s strength made it\n"
	.string "possible to move boulders around!$"

Text_PowerGloveOn:
	.string "{PLAYER} turned on the Power Glove!$"

Text_CantStrength:
	.string "It's a big boulder, but a Pokémon\n"
	.string "or tool may be able to push it aside.$"

Text_StrengthActivated:
	.string "It is already possible to move boulders\n"
	.string "around.$"

EventScript_UseWaterfall::
	lockall
	checkpartymove MOVE_WATERFALL
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantWaterfall
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	msgbox Text_WantToWaterfall, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_EndWaterfall
	msgbox Text_MonUsedWaterfall, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_WATERFALL
	goto EventScript_EndWaterfall

EventScript_CannotUseWaterfall::
	lockall

EventScript_CantWaterfall::
	msgbox Text_CantWaterfall, MSGBOX_DEFAULT

EventScript_EndWaterfall::
	releaseall
	end

Text_CantWaterfall:
	.string "A wall of water is crashing down with\n"
	.string "a mighty roar.$"

Text_WantToWaterfall:
	.string "It's a large waterfall.\n"
	.string "Would you like to use WATERFALL?$"

Text_MonUsedWaterfall:
	.string "{STR_VAR_1} used WATERFALL.$"

EventScript_UseDive::
	lockall
	checkpartymove MOVE_DIVE
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantDive
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 1, 1
	msgbox Text_WantToDive, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_EndDive
	msgbox Text_MonUsedDive, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndDive
	end

EventScript_CantDive::
	msgbox Text_CantDive, MSGBOX_DEFAULT
	releaseall
	end

EventScript_EndDive::
	releaseall
	end

EventScript_UseDiveUnderwater::
	lockall
	checkpartymove MOVE_DIVE
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantSurface
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 1, 1
	msgbox Text_WantToSurface, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_EndSurface
	msgbox Text_MonUsedDive, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndSurface
	end

EventScript_CantSurface::
	lockall
	msgbox Text_CantSurface, MSGBOX_DEFAULT
	goto EventScript_EndSurface
	end

EventScript_EndSurface::
	releaseall
	end

Text_CantDive:
	.string "The sea is deep here. A POKéMON\n"
	.string "may be able to go underwater.$"

Text_WantToDive:
	.string "The sea is deep here.\n"
	.string "Would you like to use DIVE?$"

Text_MonUsedDive:
	.string "{STR_VAR_1} used DIVE.$"

Text_CantSurface:
	.string "Light is filtering down from above.\n"
	.string "A POKéMON may be able to surface.$"

Text_WantToSurface:
	.string "Light is filtering down from above.\n"
	.string "Would you like to use DIVE?$"

EventScript_FailSweetScent::
	msgbox Text_FailSweetScent, MSGBOX_SIGN
	end

Text_FailSweetScent:
	.string "Looks like there's nothing here…$"

EventScript_OpenSubMenu::
    dynmultipush EventScript_AutoRun, 0
	goto_if_set FLAG_SYS_DEXNAV_GET, EventScript_AddDexNavMenu
	goto EventScript_FinishSubMenu
    end

EventScript_AddDexNavMenu::
	dynmultipush EventScript_DexNav, 1
	goto EventScript_FinishSubMenu
	end

EventScript_FinishSubMenu::
	dynmultistack 0, 0, TRUE, 3, TRUE, 0,DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 0, EventScript_ToggleAutoRun
    goto_if_eq VAR_RESULT, 1, EventScript_OpenDexNav
	goto_if_eq VAR_RESULT, 127, EventScript_Release

EventScript_ToggleAutoRun:
	special EnableAutoRun
	waitstate
	end

EventScript_Release:
	releaseall
	end

EventScript_OpenDexNav:
	fadescreen FADE_TO_BLACK
	special OpenDexNavSub
	waitstate
	end

EventScript_AutoRun:
	.string "Auto Run$"

EventScript_DexNav:
	.string "DexNav$"

EventScript_DisableAutoRun::
    msgbox AutoRunDisabled MSGBOX_SIGN
    end

AutoRunDisabled:
    .string "Auto Run {COLOR RED}Disabled{COLOR DARK_GRAY}.$"

EventScript_EnableAutoRun::
    msgbox AutoRunEnabled MSGBOX_SIGN
    end

AutoRunEnabled:
    .string "Auto Run {COLOR GREEN}Enabled{COLOR DARK_GRAY}.$"
