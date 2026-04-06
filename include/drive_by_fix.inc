#if !defined _INC_drive_by_fix
	#define _INC_drive_by_fix
#else
	#error You cannot include drive_by_fix more than once!
#endif

#define _DRIVE_BY_FIX_VERSION "1.0"

static WEAPON:driveByWeapon[MAX_PLAYERS];
static bool:isPlayerInDriveBy[MAX_PLAYERS];

static dbFix_HideDriveByWeapon(playerid)
{
	return
		driveByWeapon[playerid] = GetPlayerWeapon(playerid),
		isPlayerInDriveBy[playerid] = false,
		SetPlayerArmedWeapon(playerid, WEAPON_FIST),
		ApplyAnimation(playerid, "PED", "CAR_GETIN_RHS", 4.1, false, false, false, false, 1, SYNC_ALL),
		SetTimerEx("dbFix_DriveBy", 500, false, "i", playerid);
}

forward dbFix_DriveBy(playerid);
public  dbFix_DriveBy(playerid)
{
	if (GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
	{
		SetPlayerArmedWeapon(playerid, driveByWeapon[playerid]);
	}
	return isPlayerInDriveBy[playerid] = true;
}

public OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys)
{

	if ((newkeys & KEY_CROUCH) && !(oldkeys & KEY_CROUCH)
	&& GetPlayerState(playerid) == PLAYER_STATE_PASSENGER
	&& GetPlayerCameraMode(playerid) == CAM_MODE_AIMWEAPON_FROMCAR
	&& !isPlayerInDriveBy[playerid])
	{
		dbFix_HideDriveByWeapon(playerid);
	}

	#if defined dbFix_OnPlayerKeyStateChange
		return dbFix_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange dbFix_OnPlayerKeyStateChange

#if defined dbFix_OnPlayerKeyStateChange
	forward dbFix_OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys);
#endif