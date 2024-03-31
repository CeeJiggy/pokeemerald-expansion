EventScript_StatEdit::
    lock
	faceplayer
    goto_if_unset FLAG_BADGE02_GET, EventScript_CantEdit 
    msgbox gText_EditStatsGreeting, MSGBOX_DEFAULT
    goto EventScript_StatEditPrompt
    end

EventScript_StatEditPrompt::
    dynmultipush EventScript_Edit, 0
	dynmultipush EventScript_Info, 1
	dynmultipush EventScript_Leave, 2
    dynmultistack 20, 0, FALSE, 3, TRUE, 0, DYN_MULTICHOICE_CB_NONE
    goto_if_eq VAR_RESULT, 1, EventScript_TellInfo
    goto_if_eq VAR_RESULT, 2, EventScript_ReleaseEditStats
    goto_if_eq VAR_RESULT, 127, EventScript_ReleaseEditStats
    fadescreen FADE_TO_BLACK
    special StatEditor_Init
    waitstate
	goto EventScript_ReleaseEditStats
    end

EventScript_TellInfo::
    msgbox gText_EditorInfo, MSGBOX_DEFAULT
    goto EventScript_StatEditPrompt
	end

EventScript_CantEdit::
    msgbox gText_CantEdit, MSGBOX_DEFAULT
	release
	end

EventScript_ReleaseEditStats::
    msgbox gText_EndEditStats, MSGBOX_DEFAULT
	release
	end

EventScript_Edit:
	.string "Edit Stats$"

EventScript_Info:
	.string "Info$"

EventScript_Leave:
	.string "Cancel$"
