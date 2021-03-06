#pragma once

#include "Main.h"

int ScoreAtrrib ( const char *pszName, int iSize, void *pbuf );
int ResetHUD ( const char *pszName, int iSize, void *pbuf );
int SetFOV ( const char *pszName, int iSize, void *pbuf );
int TextMsg ( const char *pszName, int iSize, void *pbuf );
int TeamInfo ( const char *pszName, int iSize, void *pbuf );
int CurWeapon ( const char *pszName, int iSize, void *pbuf );
int WeaponList ( const char *pszName, int iSize, void *pbuf );
int DeathMsg ( const char *pszName, int iSize, void *pbuf );

void AtRoundStart ( );

extern pfnUserMsgHook pScoreAtrrib;
extern pfnUserMsgHook pResetHUD;
extern pfnUserMsgHook pSetFOV;
extern pfnUserMsgHook pTeamInfo;
extern pfnUserMsgHook pCurWeapon;
extern pfnUserMsgHook pWeaponList;
extern pfnUserMsgHook pDeathMsg;
extern pfnUserMsgHook pTextMsg;