EventScript_UseSurf::
	goto_if_eq VAR_SURF_TYPE, 3, EventScript_UseSurfSkip
	checkpartymove MOVE_SURF
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CheckSurfBoard
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	goto_if_eq VAR_HM_OPTION, 1, EventScript_UseSurfSkip
	lockall
	setvar VAR_SURF_TYPE, 1
	dofieldeffect FLDEFF_USE_SURF
	setvar VAR_SURF_TYPE, 0
	end

EventScript_CheckSurfBoard::
	checkitem ITEM_SURFBOARD, 1
	goto_if_eq VAR_RESULT, 1, EventScript_UseSurfSkip
	goto EventScript_EndUseSurf
	end

EventScript_UseSurfSkip::
	lockall
	setvar VAR_SURF_TYPE, 2
	dofieldeffect FLDEFF_USE_SURF
	setvar VAR_SURF_TYPE, 0
	end

EventScript_ReleaseUseSurf::
	releaseall

EventScript_EndUseSurf::
	end
