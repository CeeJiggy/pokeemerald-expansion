EventScript_UseSurf::
	goto_if_eq VAR_SURF_TYPE, 3, EventScript_UseSurfBoard
	checkpartymove MOVE_SURF
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CheckSurfBoard
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	lockall
	setvar VAR_SURF_TYPE, 1
	dofieldeffect FLDEFF_USE_SURF
	setvar VAR_SURF_TYPE, 0
	end

EventScript_CheckSurfBoard::
	checkitem ITEM_SURFBOARD, 1
	goto_if_eq VAR_RESULT, 1, EventScript_UseSurfBoard
	goto EventScript_EndUseSurf
	end

EventScript_UseSurfBoard::
	lockall
	setvar VAR_SURF_TYPE, 2
	dofieldeffect FLDEFF_USE_SURF
	setvar VAR_SURF_TYPE, 0
	end

EventScript_ReleaseUseSurf::
	releaseall

EventScript_EndUseSurf::
	end
