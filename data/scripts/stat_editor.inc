EventScript_StatEdit::
    lock
	faceplayer
    msgbox gText_WantToEditStats, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_ReleaseEditStats
    fadescreen FADE_TO_BLACK
    special StatEditor_Init
    waitstate
	goto EventScript_ReleaseEditStats
    end

EventScript_ReleaseEditStats::
    msgbox gText_EndEditStats, MSGBOX_DEFAULT
	release
	end
