Route135_MapScripts::
  .byte 0

Route135_Eventscript_Jason::
	trainerbattle_single TRAINER_JASON, Route135_Text_JasonIntro, Route135_Text_JasonDefeated
	msgbox Route135_Text_JasonPostBattle, MSGBOX_AUTOCLOSE
