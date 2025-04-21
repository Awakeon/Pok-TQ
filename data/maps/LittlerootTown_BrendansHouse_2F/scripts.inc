.set LOCALID_RIVAL, 1
.set LOCALID_POKE_BALL, 2

LittlerootTown_BrendansHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_BrendansHouse_2F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_BrendansHouse_2F_OnWarp
	.byte 0

LittlerootTown_BrendansHouse_2F_OnTransition:
	call_if_lt VAR_LITTLEROOT_RIVAL_STATE, 2, LittlerootTown_BrendansHouse_2F_EventScript_CheckSetReadyToMeetBrendan
	call_if_ge VAR_LITTLEROOT_RIVAL_STATE, 3, LittlerootTown_BrendansHouse_2F_EventScript_CheckShouldUpdateBrendanPos
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 4, PlayersHouse_2F_EventScript_BlockStairsUntilClockIsSet
	call SecretBase_EventScript_SetDecorationFlags
	setvar VAR_SECRET_BASE_INITIALIZED, 0
	end

LittlerootTown_BrendansHouse_2F_EventScript_CheckShouldUpdateBrendanPos::
	goto_if_set FLAG_MET_RIVAL_LILYCOVE, LittlerootTown_BrendansHouse_2F_EventScript_TryUpdateBrendanPos
	goto_if_ge VAR_BIRCH_LAB_STATE, 2, LittlerootTown_BrendansHouse_2F_EventScript_Ret
	goto LittlerootTown_BrendansHouse_2F_EventScript_TryUpdateBrendanPos

LittlerootTown_BrendansHouse_2F_EventScript_TryUpdateBrendanPos::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_BrendansHouse_2F_EventScript_Ret
	@ Odd that the MaysHouse equivalent was used below instead
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_MaysHouse_2F_EventScript_Ret
	setobjectxyperm LOCALID_RIVAL, 0, 2
	setobjectmovementtype LOCALID_RIVAL, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_2F_EventScript_Ret::
	return

LittlerootTown_BrendansHouse_2F_EventScript_CheckSetReadyToMeetBrendan::
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, LittlerootTown_BrendansHouse_2F_EventScript_SetReadyToMeetBrendan
	return

LittlerootTown_BrendansHouse_2F_EventScript_SetReadyToMeetBrendan::
	setvar VAR_LITTLEROOT_RIVAL_STATE, 2
	return

LittlerootTown_BrendansHouse_2F_OnWarp:
	map_script_2 VAR_SECRET_BASE_INITIALIZED, 0, LittlerootTown_BrendansHouse_2F_EventScript_CheckInitDecor
	.2byte 0

LittlerootTown_BrendansHouse_2F_EventScript_CheckInitDecor::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, SecretBase_EventScript_InitDecorations
	end

LittlerootTown_BrendansHouse_2F_EventScript_RivalsPokeBall::
	lockall
	goto_if_eq VAR_LITTLEROOT_RIVAL_STATE, 2, LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendan
	msgbox RivalsHouse_2F_Text_ItsRivalsPokeBall, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendan::
	delay 10
	addobject LOCALID_RIVAL
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanEnters
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	delay 10
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_eq VAR_FACING, DIR_NORTH, LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanNorth
	call_if_eq VAR_FACING, DIR_SOUTH, LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanSouth
	call_if_eq VAR_FACING, DIR_WEST, LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanWest
	call_if_eq VAR_FACING, DIR_EAST, LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanEast
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanNorth::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerNorth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox RivalsHouse_2F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanNorth
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCNorth
	waitmovement 0
	return

LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanSouth::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerSouth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox RivalsHouse_2F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanSouth
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCSouth
	waitmovement 0
	return

LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanWest::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerWest
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox RivalsHouse_2F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanWest
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCWest
	waitmovement 0
	return

LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanEast::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerEast
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox RivalsHouse_2F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCEast
	waitmovement 0
	return

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1::
    setflag FLAG_SYS_POKEMON_GET
    msgbox PlayersHouse_Starter_Ball, MSGBOX_SIGN
	random 20
	goto_if_eq VAR_RESULT, 1, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_A
	goto_if_eq VAR_RESULT, 2, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_B
	goto_if_eq VAR_RESULT, 3, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_C
	goto_if_eq VAR_RESULT, 4, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_D
	goto_if_eq VAR_RESULT, 5, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_E
	goto_if_eq VAR_RESULT, 6, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_F
	goto_if_eq VAR_RESULT, 7, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_G
	goto_if_eq VAR_RESULT, 8, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_H
	goto_if_eq VAR_RESULT, 9, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_I
	goto_if_eq VAR_RESULT, 10, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_J
	goto_if_eq VAR_RESULT, 11, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_K
	goto_if_eq VAR_RESULT, 12, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_L
	goto_if_eq VAR_RESULT, 13, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_M
	goto_if_eq VAR_RESULT, 14, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_N
	goto_if_eq VAR_RESULT, 15, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_O
	goto_if_eq VAR_RESULT, 16, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_P
	goto_if_eq VAR_RESULT, 17, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_Q
	goto_if_eq VAR_RESULT, 18, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_R
	goto_if_eq VAR_RESULT, 19, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_S
	goto  LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_T


LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_A::
    givemon SPECIES_CHIKORITA, 10
	removeobject VAR_LAST_TALKED
    setflag FLAG_HIDE_STARTER_BALL_1
    end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_B::
   givemon      SPECIES_LITTEN, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_C::
   givemon      SPECIES_AXEW, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_D::
   givemon      SPECIES_TEPIG, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_E::
   givemon      SPECIES_SWINUB, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_F::
   givemon      SPECIES_SOLOSIS, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_G::
   givemon      SPECIES_SPHEAL, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_H::
   givemon      SPECIES_BUDEW, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_I::
   givemon      SPECIES_VENIPEDE, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_J::
   givemon      SPECIES_TYNAMO, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_K::
   givemon      SPECIES_TOTODILE, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_L::
   givemon      SPECIES_ROWLET, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_M::
   givemon      SPECIES_LITWICK, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_N::
   givemon      SPECIES_ELEKID, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_O::
   givemon      SPECIES_RHYHORN, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_P::
   givemon      SPECIES_CHESPIN, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_Q::
   givemon      SPECIES_NACLI, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_R::
   givemon      SPECIES_SLAKOTH, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_S::
   givemon      SPECIES_KLINK, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_1_T::
   givemon      SPECIES_PAWNIARD, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2::
    setflag FLAG_SYS_POKEMON_GET
    msgbox PlayersHouse_Starter_Ball, MSGBOX_SIGN
	random 20
	goto_if_eq VAR_RESULT, 1, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_A
	goto_if_eq VAR_RESULT, 2, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_B
	goto_if_eq VAR_RESULT, 3, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_C
	goto_if_eq VAR_RESULT, 4, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_D
	goto_if_eq VAR_RESULT, 5, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_E
	goto_if_eq VAR_RESULT, 6, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_F
	goto_if_eq VAR_RESULT, 7, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_G
	goto_if_eq VAR_RESULT, 8, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_H
	goto_if_eq VAR_RESULT, 9, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_I
	goto_if_eq VAR_RESULT, 10, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_J
	goto_if_eq VAR_RESULT, 11, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_K
	goto_if_eq VAR_RESULT, 12, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_L
	goto_if_eq VAR_RESULT, 13, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_M
	goto_if_eq VAR_RESULT, 14, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_N
	goto_if_eq VAR_RESULT, 15, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_O
	goto_if_eq VAR_RESULT, 16, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_P
	goto_if_eq VAR_RESULT, 17, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_Q
	goto_if_eq VAR_RESULT, 18, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_R
	goto_if_eq VAR_RESULT, 19, LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_S
	goto  LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_T

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_A::
    givemon SPECIES_STARLY, 10
	removeobject VAR_LAST_TALKED
    setflag FLAG_HIDE_STARTER_BALL_1
    end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_B::
   givemon      SPECIES_GIBLE, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_C::
   givemon      SPECIES_CHARMANDER, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_D::
   givemon      SPECIES_MACHOP, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_E::
   givemon      SPECIES_GEODUDE_ALOLA, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_F::
   givemon      SPECIES_SNIVY, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_G::
   givemon      SPECIES_ROGGENROLA, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_H::
   givemon      SPECIES_FENNEKIN, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_I::
   givemon      SPECIES_MANKEY, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_J::
   givemon      SPECIES_MAGBY, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_K::
   givemon      SPECIES_HAPPINY, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_L::
   givemon      SPECIES_DUSKULL, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_M::
   givemon      SPECIES_VANILLITE, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_N::
   givemon      SPECIES_WEEDLE, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_O::
   givemon      SPECIES_SANDILE, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_P::
   givemon      SPECIES_COSMOG, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_Q::
   givemon      SPECIES_WHISMUR, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_R::
   givemon      SPECIES_JANGMO_O, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_S::
   givemon      SPECIES_SOBBLE, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end

LittlerootTown_BrendansHouse_2F_EventScript_Starter_Ball_2_T::
   givemon      SPECIES_TYMPOLE, 10
   removeobject VAR_LAST_TALKED
   setflag      FLAG_HIDE_STARTER_BALL_1
   end


LittlerootTown_BrendansHouse_2F_Movement_BrendanEnters:
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerNorth:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCNorth:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanNorth:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerSouth:
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCSouth:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanSouth:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerWest:
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCWest:
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanWest:
	delay_8
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerEast:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCEast:
	walk_up
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

@ Unused, the player is already facing this direction so its unneeded
LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanEast:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_2F_EventScript_PC::
	lockall
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_BrendansHouse_2F_EventScript_CheckPlayersPC
	goto_if_eq VAR_RESULT, FEMALE, LittlerootTown_BrendansHouse_2F_EventScript_CheckRivalsPC
	end

LittlerootTown_BrendansHouse_2F_EventScript_CheckPlayersPC::
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
	special BedroomPC
	waitstate
	releaseall
	end

LittlerootTown_BrendansHouse_2F_EventScript_TurnOffPlayerPC::
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

LittlerootTown_BrendansHouse_2F_EventScript_CheckRivalsPC::
	msgbox gText_PokemonTrainerSchoolEmail, MSGBOX_DEFAULT
	releaseall
	end

PlayersHouse_2F_EventScript_Notebook::
	msgbox PlayersHouse_2F_Text_Notebook, MSGBOX_SIGN
	end

PlayersHouse_2F_EventScript_GameCube::
	msgbox DifficultySelect_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DifficultySelectHard
	msgbox YouStayedOnNormalMode, MSGBOX_AUTOCLOSE
	end

DifficultySelectHard::
    msgbox HardModeSelectedText, MSGBOX_AUTOCLOSE
    increasedifficulty 
	end

DifficultySelect_Text:
    .string "STOP MASHING A\p"
	.string "WOULD YOU LIKE TO PLAY\n"
    .string "ON HARD MODE?$"

YouStayedOnNormalMode:
    .string "You are on Normal Mode.$"

HardModeSelectedText:
    .string "Good Luck.$"

PlayersHouse_2F_Text_ClockIsStopped:
	.string "The clock is stopped…\p"
	.string "Better set it and start it!$"

PlayersHouse_2F_Text_HowDoYouLikeYourRoom:
	.string "MOM: {PLAYER}, how do you like your\n"
	.string "new room?\p"
	.string "Good! Everything's put away neatly!\p"
	.string "They finished moving everything in\n"
	.string "downstairs, too.\p"
	.string "POKéMON movers are so convenient!\p"
	.string "Oh, you should make sure that\n"
	.string "everything's all there on your desk.$"

PlayersHouse_2F_Text_Notebook:
	.string "{PLAYER} flipped open the notebook.\p"
	.string "ADVENTURE RULE NO. 1\n"
	.string "Open the MENU with START.\p"
	.string "ADVENTURE RULE NO. 2\n"
	.string "Record your progress with SAVE.\p"
	.string "The remaining pages are blank…$"

Common_Text_LookCloserAtMap:
	.string "{PLAYER} took a closer look at the\n"
	.string "HOENN region map.$"

PlayersHouse_2F_Text_ItsAGameCube:
	.string "It's a Nintendo GameCube.\p"
	.string "A Game Boy Advance is connected to\n"
	.string "serve as the Controller.$"

PlayersHouse_Starter_Ball:
    .string "It's a pokeball.$"
