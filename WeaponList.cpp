#include "WeaponList.h"

namespace Client
{
	int WeaponList::OldWeaponBits;
	int WeaponList::WeaponListIndex;

	weapon_list_s* WeaponList::WeaponListData;

	void WeaponList::SetWeaponData ( weapon_list_s* weapon )
	{
		switch ( weapon->ID )
		{
		case WEAPONLIST_P228:
			weapon->ClipCap = CLIPCAP_P228;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 4096.0f;
			weapon->wallpierce1 = 0.8f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 32;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_P228;

			break;

		case WEAPONLIST_SCOUT:
			weapon->ClipCap = CLIPCAP_SCOUT;
			weapon->penetrate = WALL_PEN2;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.98f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 75;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_SCOUT;

			break;

		case WEAPONLIST_HEGRENADE:
			weapon->ClipCap = 0;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 0.0f;
			weapon->wallpierce1 = 0.0f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 0;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_NONE;

			break;

		case WEAPONLIST_XM1014:
			weapon->ClipCap = CLIPCAP_XM1014;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 0.0f;
			weapon->wallpierce1 = 0.0f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 0;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_XM1014;

			break;

		case WEAPONLIST_C4:
			weapon->ClipCap = 0;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 0.0f;
			weapon->wallpierce1 = 0.0f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 0;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_NONE;

			break;

		case WEAPONLIST_MAC10:
			weapon->ClipCap = CLIPCAP_MAC10;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.82f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 29;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_MAC10;

			break;

		case WEAPONLIST_AUG:
			weapon->ClipCap = CLIPCAP_AUG;
			weapon->penetrate = WALL_PEN1;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.96f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 32;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_AUG;

			break;

		case WEAPONLIST_SMOKEGRENADE:
			weapon->ClipCap = 0;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 0.0f;
			weapon->wallpierce1 = 0.0f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 0;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_NONE;

			break;

		case WEAPONLIST_ELITE:
			weapon->ClipCap = CLIPCAP_ELITE;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.75f;
			weapon->wallpierce2 = 0.75f;
			weapon->damage1 = 20;
			weapon->damage2 = 27;
			weapon->bullettype = BULLET_ELITE;

			break;

		case WEAPONLIST_FIVESEVEN:
			weapon->ClipCap = CLIPCAP_FIVESEVEN;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 4096.0f;
			weapon->wallpierce1 = 0.885f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 14;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_FIVESEVEN;

			break;

		case WEAPONLIST_UMP45:
			weapon->ClipCap = CLIPCAP_UMP45;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.82f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 30;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_UMP45;

			break;

		case WEAPONLIST_SG550:
			weapon->ClipCap = CLIPCAP_SG550;
			weapon->penetrate = WALL_PEN1;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.98f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 40;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_SG550;

			break;

		case WEAPONLIST_GALIL:
			weapon->ClipCap = CLIPCAP_GALIL;
			weapon->penetrate = WALL_PEN1;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.96f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 33;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_GALIL;

			break;

		case WEAPONLIST_FAMAS:
			weapon->ClipCap = CLIPCAP_FAMAS;
			weapon->penetrate = WALL_PEN1;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.96f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 33;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_FAMAS;

			break;

		case WEAPONLIST_USP:
			weapon->ClipCap = CLIPCAP_USP;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 4096.0f;
			weapon->wallpierce1 = 0.79f;
			weapon->wallpierce2 = 0.79f;
			weapon->damage1 = 34;
			weapon->damage2 = 30;
			weapon->bullettype = BULLET_USP;

			break;

		case WEAPONLIST_GLOCK18:
			weapon->ClipCap = CLIPCAP_GLOCK18;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.75f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 20;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_GLOCK18;

			break;

		case WEAPONLIST_AWP:
			weapon->ClipCap = CLIPCAP_AWP;
			weapon->penetrate = WALL_PEN2;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.99f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 115;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_AWP;

			break;

		case WEAPONLIST_MP5:
			weapon->ClipCap = CLIPCAP_MP5;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.84f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 26;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_MP5;

			break;

		case WEAPONLIST_M249:
			weapon->ClipCap = CLIPCAP_M249;
			weapon->penetrate = WALL_PEN1;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.97f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 32;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_M249;

			break;

		case WEAPONLIST_M3:
			weapon->ClipCap = CLIPCAP_M3;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 0.0f;
			weapon->wallpierce1 = 0.0f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 0;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_M3;

			break;

		case WEAPONLIST_M4A1:
			weapon->ClipCap = CLIPCAP_M4A1;
			weapon->penetrate = WALL_PEN1;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.97f;
			weapon->wallpierce2 = 0.95f;
			weapon->damage1 = 32;
			weapon->damage2 = 33;
			weapon->bullettype = BULLET_M4A1;

			break;

		case WEAPONLIST_TMP:
			weapon->ClipCap = CLIPCAP_TMP;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.85f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 20;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_TMP;

			break;

		case WEAPONLIST_G3SG1:
			weapon->ClipCap = CLIPCAP_G3SG1;
			weapon->penetrate = WALL_PEN1;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.98f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 60;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_G3SG1;

			break;

		case WEAPONLIST_FLASHBANG:
			weapon->ClipCap = 0;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 0.0f;
			weapon->wallpierce1 = 0.0f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 0;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_NONE;

			break;

		case WEAPONLIST_DEAGLE:
			weapon->ClipCap = CLIPCAP_DEAGLE;
			weapon->penetrate = WALL_PEN1;
			weapon->distance = 4096.0f;
			weapon->wallpierce1 = 0.81f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 54;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_DEAGLE;

			break;

		case WEAPONLIST_SG552:
			weapon->ClipCap = CLIPCAP_SG552;
			weapon->penetrate = WALL_PEN1;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.955f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 33;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_SG552;

			break;

		case WEAPONLIST_AK47:
			weapon->ClipCap = CLIPCAP_AK47;
			weapon->penetrate = WALL_PEN1;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.98f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 36;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_AK47;

			break;

		case WEAPONLIST_KNIFE:
			weapon->ClipCap = 0;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 0.0f;
			weapon->wallpierce1 = 0.0f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 0;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_NONE;

			break;

		case WEAPONLIST_P90:
			weapon->ClipCap = CLIPCAP_P90;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 8192.0f;
			weapon->wallpierce1 = 0.885f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 21;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_P90;

			break;

		default:
			weapon->ClipCap = 0;
			weapon->penetrate = WALL_PEN0;
			weapon->distance = 0.0f;
			weapon->wallpierce1 = 0.0f;
			weapon->wallpierce2 = 0.0f;
			weapon->damage1 = 0;
			weapon->damage2 = 0;
			weapon->bullettype = BULLET_NONE;

			break;
		}
	}

	weapon_list_s* WeaponList::GetCurWeapon ( )
	{
		for ( int i = 0; i < WeaponListIndex; ++i )
		{
			if ( WeaponListData[i].Active && WeaponListData[i].CurWeapon )
				return &WeaponListData[i];
		}

		return 0;
	}

	weapon_list_s* WeaponList::GetSecWeapon ( )
	{
		for ( int i = 0; i < WeaponListIndex; ++i )
		{
			if ( WeaponListData[i].Active && WeaponListData[i].Slot == 1 )
				return &WeaponListData[i];
		}

		return 0;
	}

	bool WeaponList::IsReloading ( )
	{
		weapon_list_s* TmpWeapon = GetCurWeapon ( );

		if ( TmpWeapon && TmpWeapon->weapondata.m_fInReload )
			return true;

		return false;
	}

	bool WeaponList::IsCurWeaponSec ( )
	{
		weapon_list_s* TmpWeapon = GetSecWeapon ( );

		if ( TmpWeapon && TmpWeapon->CurWeapon )
			return true;

		return false;
	}

	bool WeaponList::CanCurWeaponAttack ( )
	{
		weapon_list_s* TmpWeapon = GetCurWeapon ( );

		if ( TmpWeapon && TmpWeapon->weapondata.m_flNextPrimaryAttack <= 0.0f )
			return true;

		return false;
	}

	bool WeaponList::IsCurWeaponInBurst ( )
	{
		weapon_list_s* TmpWeapon = GetCurWeapon ( );

		if ( TmpWeapon )
		{
			if ( TmpWeapon->ID == WEAPONLIST_GLOCK18 && TmpWeapon->weapondata.m_iWeaponState & GLOCK18_BURST )
				return true;
		}

		return false;
	}

	bool WeaponList::IsCurWeaponSilenced ( )
	{
		weapon_list_s* TmpWeapon = GetCurWeapon ( );

		if ( TmpWeapon )
		{
			if ( TmpWeapon->ID == WEAPONLIST_M4A1 && TmpWeapon->weapondata.m_iWeaponState & M4A1_SILENCER )
				return true;

			if ( TmpWeapon->ID == WEAPONLIST_USP && TmpWeapon->weapondata.m_iWeaponState & USP_SILENCER )
				return true;
		}

		return false;
	}

	int WeaponList::GetCurWeaponId ( )
	{
		weapon_list_s* TmpWeapon = GetCurWeapon ( );

		if ( TmpWeapon )
			return TmpWeapon->ID;

		return -1;
	}

	int WeaponList::GetWeaponIndexByID ( int WeaponID )
	{
		for ( int i = 0; i < WeaponListIndex; ++i )
		{
			if ( WeaponListData[i].ID == WeaponID )
				return i;
		}

		return -1;
	}

	void WeaponList::WeaponListCurWeapon ( int CurWeapon, int WeaponID, int Ammo )
	{
		int Index = GetWeaponIndexByID ( WeaponID );

		if ( Index != -1 )
			WeaponListData[Index].CAmmo = Ammo;
	}

	void WeaponList::WeaponListAmmoX ( int ID, int Count )
	{
		for ( int i = 0; i < WeaponListIndex; ++i )
		{
			if ( WeaponListData[i].AmmoType == ID )
			{
				WeaponListData[i].XAmmo = Count;
			}
		}
	}

	void WeaponList::WeaponListUpdate ( int WeaponBits )
	{
		if ( WeaponBits != OldWeaponBits )
		{
			OldWeaponBits = WeaponBits;

			for ( int i = 0; i < WeaponListIndex; ++i )
			{
				if ( WeaponBits & ( 1 << WeaponListData[i].ID ) )
				{
					WeaponListData[i].Active = true;
				}
				else
				{
					WeaponListData[i].Active = false;
					WeaponListData[i].CAmmo = 0;
				}
			}
		}
	}

	void WeaponList::WeaponListAdd ( char* weaponname, int ammo1type, int max1, int ammo2type, int max2, int slot, int slotpos, int id, int flags )
	{
		if ( WeaponListIndex < MAX_WEAPON_LIST )
		{
			int len = lstrlenA ( weaponname );

			if ( len > MAX_WEAPON_NAME )
				return;

			lstrcpynA ( WeaponListData[WeaponListIndex].command, weaponname, len + 1 );

			char *NOSPRD_WPN = "weapon_";
			char *NOSPRD_MP5 = "'mp5navy";

			if ( len > 7 && !Utils::native_memcpy2 ( weaponname, NOSPRD_WPN, 7 ) )
			{
				weaponname = weaponname + 7;

				WeaponListData[WeaponListIndex].len = len - 7;
			}
			else
				WeaponListData[WeaponListIndex].len = len;

			if ( WeaponListData[WeaponListIndex].len == 7 && !Utils::native_memcpy2 ( weaponname, NOSPRD_MP5, 7 ) )
				WeaponListData[WeaponListIndex].len = 3;

			memcpy ( WeaponListData[WeaponListIndex].name, weaponname, WeaponListData[WeaponListIndex].len );

			WeaponListData[WeaponListIndex].name[WeaponListData[WeaponListIndex].len] = 0;

			WeaponListData[WeaponListIndex].AmmoType = ammo1type;

			if ( max1 == 255 )
				WeaponListData[WeaponListIndex].Max1 = -1;
			else
				WeaponListData[WeaponListIndex].Max1 = max1;

			WeaponListData[WeaponListIndex].Ammo2Type = ammo2type;

			if ( max2 == 255 )
				WeaponListData[WeaponListIndex].Max2 = -1;
			else
				WeaponListData[WeaponListIndex].Max2 = max2;

			WeaponListData[WeaponListIndex].Slot = slot;
			WeaponListData[WeaponListIndex].SlotPos = slotpos;

			WeaponListData[WeaponListIndex].ID = id;
			WeaponListData[WeaponListIndex].Flags = flags;

			WeaponListData[WeaponListIndex].CAmmo = 0;
			WeaponListData[WeaponListIndex].XAmmo = 0;

			WeaponListData[WeaponListIndex].Active = false;
			WeaponListData[WeaponListIndex].CurWeapon = false;

			SetWeaponData ( &WeaponListData[WeaponListIndex] );

			Utils::native_memset ( &WeaponListData[WeaponListIndex].weapondata, 0, sizeof ( weapon_data_t ) );

			++WeaponListIndex;
		}
	}

	void WeaponList::WeaponListClear ( )
	{
		Utils::native_memset ( WeaponListData, sizeof ( weapon_list_s ) * MAX_WEAPON_LIST, 0 );

		WeaponListIndex = 0;
	}
}