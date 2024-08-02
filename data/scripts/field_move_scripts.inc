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

@ Use cut from party menu
EventScript_UseCut::
	lockall
	goto EventScript_CutTreeCommon

Movement_CutTreeDown:
	cut_tree
	step_end

Text_WantToCut:
	.string "This tree looks like it can be\n"
	.string "CUT down!\p"
	.string "Would you like to CUT it?$"

Text_MonUsedFieldMove:
	.string "{STR_VAR_1} used {STR_VAR_2}!$"

Text_PlayerUsedPickaxe:
	.string "{PLAYER} used the Pickaxe!$"

Text_PlayerUsedAxe:
	.string "{PLAYER} used the Axe!$"

Text_CantCut:
	.string "This tree looks like it can be\n"
	.string "CUT down!$"

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

EventScript_FollowerFieldMove:
	getdirectiontoface VAR_0x8005, OBJ_EVENT_ID_FOLLOWER, OBJ_EVENT_ID_PLAYER
	specialvar VAR_0x8006, GetPlayerFacingDirection
	goto_if_eq VAR_0x8005, DIR_NONE, EventScript_FollowerFieldMoveEnd
	@ Swap follower and player
	call EventScript_FollowerSwap
	@ Face follower in direction and jump
	switch VAR_0x8006
	case DIR_NORTH, EventScript_FollowerJumpNorth
	case DIR_EAST, EventScript_FollowerJumpEast
	case DIR_SOUTH, EventScript_FollowerJumpSouth
	case DIR_WEST, EventScript_FollowerJumpWest
EventScript_FollowerFieldMoveEnd:
	return

EventScript_FollowerSwap:
	switch VAR_0x8005
	case DIR_NORTH, EventScript_FollowerMoveNorth
	case DIR_EAST, EventScript_FollowerMoveEast
	case DIR_SOUTH, EventScript_FollowerMoveSouth
	case DIR_WEST, EventScript_FollowerMoveWest
	return

EventScript_FollowerMoveNorth:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_WalkUp
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	return

EventScript_FollowerMoveEast:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_WalkRight
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkLeft
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	return

EventScript_FollowerMoveSouth:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_WalkDown
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	return

EventScript_FollowerMoveWest:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_WalkLeft
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	return

EventScript_FollowerJumpNorth:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpUp
	waitmovement 0
	return

EventScript_FollowerJumpEast:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpRight
	waitmovement 0
	return

EventScript_FollowerJumpSouth:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpDown
	waitmovement 0
	return

EventScript_FollowerJumpWest:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpLeft
	waitmovement 0
	return

EventScript_EndSmash::
	releaseall
	end

Movement_WalkUp:
	walk_up
	step_end

Movement_JumpUp:
	jump_in_place_up
	step_end

Movement_WalkRight:
	walk_right
	step_end

Movement_JumpRight:
	jump_in_place_right
	step_end

Movement_WalkDown:
	walk_down
	step_end

Movement_JumpDown:
	jump_in_place_down
	step_end

Movement_WalkLeft:
	walk_left
	step_end

Movement_JumpLeft:
	jump_in_place_left
	step_end

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
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CheckSurfBoardWaterfall
	setfieldeffectargument 0, VAR_RESULT
	goto_if_eq VAR_HM_OPTION, 1, EventScript_UseWaterfallSkip
	setvar VAR_FIELD_MOVE_TYPE, 1
	dofieldeffect FLDEFF_USE_WATERFALL
	goto EventScript_EndWaterfall
	end

EventScript_UseWaterfallSkip::
	setvar VAR_FIELD_MOVE_TYPE, 2
	dofieldeffect FLDEFF_USE_WATERFALL
	goto EventScript_EndWaterfall
	end

EventScript_CheckSurfBoardWaterfall::
	checkitem ITEM_SURFBOARD, 1
	goto_if_eq VAR_RESULT, 1, EventScript_UseWaterfallSkip
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantWaterfall
	end

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
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CheckScuba
	setfieldeffectargument 0, VAR_RESULT
	goto_if_eq VAR_HM_OPTION, 1, EventScript_UseDiveSkip
	setvar VAR_FIELD_MOVE_TYPE, 1
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndDive
	end

EventScript_UseDiveItem::
	lockall
	setfieldeffectargument 0, VAR_RESULT
	setvar VAR_FIELD_MOVE_TYPE, 2
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndDive
	end

EventScript_UseDiveUnderItem::
	lockall
	setfieldeffectargument 0, VAR_RESULT
	setvar VAR_FIELD_MOVE_TYPE, 2
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndSurface
	end

EventScript_UseDiveUnderwater::
	lockall
	checkpartymove MOVE_DIVE
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CheckScubaUnder
	setfieldeffectargument 0, VAR_RESULT
	goto_if_eq VAR_HM_OPTION, 1, EventScript_UseDiveUnderSkip
	setvar VAR_FIELD_MOVE_TYPE, 1
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndSurface
	end

EventScript_CheckScuba::
	checkitem ITEM_SCUBA_GEAR, 1
	goto_if_eq VAR_RESULT, 1, EventScript_UseDiveSkip
	goto EventScript_CantDive
	end

EventScript_CheckScubaUnder::
	checkitem ITEM_SCUBA_GEAR, 1
	goto_if_eq VAR_RESULT, 1, EventScript_UseDiveUnderSkip
	goto EventScript_CantSurface
	end

EventScript_UseDiveSkip::
	setvar VAR_FIELD_MOVE_TYPE, 2
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndDive
	end

EventScript_UseDiveUnderSkip::
	setvar VAR_FIELD_MOVE_TYPE, 2
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndSurface
	end

EventScript_CantDive::
	msgbox Text_CantDive, MSGBOX_DEFAULT
	releaseall
	end

EventScript_EndDive::
	releaseall
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
    dynmultipush EventScript_AutoRun, 1
	goto_if_set FLAG_SYS_DEXNAV_GET, EventScript_AddDexNavMenu
	goto EventScript_FinishSubMenu
    end

EventScript_AddDexNavMenu::
	dynmultipush EventScript_DexNav, 0
	goto_if_set FLAG_BADGE06_GET, EventScript_AddFlyMenu
	goto EventScript_FinishSubMenu
	end

EventScript_AddFlyMenu::
	dynmultipush EventScript_FlyMenu, 2
	goto EventScript_FinishSubMenu
	end

EventScript_FinishSubMenu::
	dynmultistack 0, 0, FALSE, 3, TRUE, 1,DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 0, EventScript_OpenDexNav
	goto_if_eq VAR_RESULT, 1, EventScript_ToggleAutoRun
    goto_if_eq VAR_RESULT, 2, EventScript_CheckFly
	goto_if_eq VAR_RESULT, 127, EventScript_Release


EventScript_CheckFly::
	special CheckCanFly
	goto_if_eq VAR_RESULT, TRUE, EventScript_OpenFlyMenu
	goto EventScript_CantFly
	end
	
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

EventScript_OpenFlyMenu:
	fadescreen FADE_TO_BLACK
	setvar VAR_0x800A, USED_FLY_WHISTLE
	special FieldLoadFlyMap
	waitstate
	end

EventScript_AutoRun:
	.string "Auto Run$"

EventScript_DexNav:
	.string "DexNav$"

EventScript_FlyMenu:
	.string "Altaria Whistle$"

EventScript_DisableAutoRun::
    msgbox AutoRunDisabled MSGBOX_SIGN
    end

AutoRunDisabled:
    .string "Auto Run {COLOR RED}Disabled{COLOR DARK_GRAY}.$"

EventScript_EnableAutoRun::
    msgbox AutoRunEnabled MSGBOX_SIGN
    end

EventScript_CantFly::
    msgbox CantFlyMsg MSGBOX_SIGN
    end

AutoRunEnabled:
    .string "Auto Run {COLOR GREEN}Enabled{COLOR DARK_GRAY}.$"

CantFlyMsg:
    .string "Looks like you can't use that here...$"
