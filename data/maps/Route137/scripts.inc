Route137_MapScripts::
	.byte 0

Route137_MapScripts_VictoryRoadGuard::
    goto_if_set FLAG_TALKED_TO_NIKOLAI, Route137_MapScripts_ReadyToBattle
	msgbox Route137_Text_WoahThereKid, MSGBOX_YESNO
    switch VAR_RESULT
	case NO,  Route137_MapScripts_VictoryRoadGuardGetYourBadges
	case YES, Route137_MapScripts_VictoryRoadGuardThenLetsBattle
	case MULTI_B_PRESSED, Route137_MapScripts_VictoryRoadGuardGetYourBadges
	end

Route137_MapScripts_VictoryRoadGuardThenLetsBattle::
	trainerbattle_single TRAINER_NIKOLAI, Route102_Text_CalvinIntro, Route137_Text_AlrightYouWin, Route137_NikolaiMove
	end

Route137_MapScripts_VictoryRoadGuardGetYourBadges::
    setflag FLAG_TALKED_TO_NIKOLAI
    msgbox Route137_Text_VictoryRoadGuardGetYourBadges, MSGBOX_DEFAULT
	end

Route137_MapScripts_ReadyToBattle::
    msgbox Route137_Text_AreYouReadyToBattle, MSGBOX_YESNO
    switch VAR_RESULT
	case NO,  Route137_MapScripts_VictoryRoadGuardGetYourBadges
	case YES, Route137_MapScripts_VictoryRoadGuardThenLetsBattle
	case MULTI_B_PRESSED, Route137_MapScripts_VictoryRoadGuardGetYourBadges
	end     

Route137_NikolaiMove::
    setflag FLAG_HIDE_NIKOLAI
	fadescreen FADE_TO_BLACK 
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	end


Route137_MapScripts_RunningMan:
	msgbox Route137_Text_ILoveRunning, MSGBOX_NPC
	end

Route137_Text_WoahThereKid:
	.string "Woah there kid.\p"
	.string "This cave leads to Vicrory\n"
	.string "road and you dont have a single badge!\p"
	.string "but you got guts trying to come here,\n"
	.string "Tell you what.\p"
	.string "If you beat me I'll let you through\n"
	.string "How does that sound?$"

Route137_Text_AreYouReadyToBattle:
	.string "Are you ready to battle?$"

Route137_Text_VictoryRoadGuardGetYourBadges:
	.string "In that case, go get those badges!$"

Route137_Text_AlrightYouWin:
	.string "Alright you win. You're\n"
	.string "way better than I thought!$"

Route137_Text_ILoveRunning:
	.string "I'm im my daily jog!\p"
	.string "Running everyday keeps the\n"
	.string "doctor away!$"
