#include "Other.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			PlayerStruct Other::Player[33];

			void ChangeName(char *str)
			{
				if (strstr(str, "  ") != NULL)
				{
					strcpy(strstr(str, "  "), strstr(str, "  ") + 1);
					return;
				}
				if (str[0] == str[strlen(str) - 1])
				{
					char buf[256];
					char sbuf[2] = "A";
					sbuf[0] = str[0];
					strcpy_s(buf, sbuf);
					strcat_s(buf, str);
					strcpy(str, buf);
					return;
				}
				if (strlen(str) > 16)
				{
					str[strlen(str) - 1] = 0;
					return;
				}
				if (strstr(str, ".") != NULL)
				{
					*strstr(str, ".") = ',';
					return;
				}
				if (strstr(str, ",") != NULL)
				{
					*strstr(str, ",") = '.';
					return;
				}
				if (strstr(str, " ") != NULL)
				{
					char buf[256];
					strcpy_s(buf, str);
					strcpy(strstr(buf, " ") + 1, strstr(str, " "));
					strcpy(str, buf);
					return;
				}
				if (strstr(str, "-") != NULL)
				{
					*strstr(str, "-") = '=';
					return;
				}
				if (strstr(str, "=") != NULL)
				{
					*strstr(str, "=") = '-';
					return;
				}
				if (strstr(str, ":") != NULL)
				{
					*strstr(str, ":") = ';';
					return;
				}
				if (str[strlen(str) - 1] == str[strlen(str) - 2])
				{
					str[strlen(str) - 1] = 0;
					return;
				}
				strcat(str, ".");
			}

			void Other::DrawAimSpot ( )
			{
				cl_entity_s* Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( AimBot::Weapons::GetTargetID ( ) );

				if ( AimBot::Weapons::FriendlyFire ( AimBot::Weapons::GetTargetID ( ) ) &&
					AimBot::Weapons::VisibleCheck ( AimBot::Weapons::GetTargetID ( ) ) &&
					g_Info->GetValidationEntity ( Entity ) )
				{
					Vector2D vAim;

					if ( Utils::CalcScreen ( AimBot::Weapons::GetAimHitBoxByIndex ( AimBot::Weapons::GetTargetID ( ) ), vAim ) )
					{
						Vector uppt = AimBot::Weapons::GetAimHitBoxByIndex ( AimBot::Weapons::GetTargetID ( ) ) - g_Info->GetVectorEyePosition ( );

						float Length = uppt.Length ( );

						int size = int ( 3800.0f / Length );

						int x1 = ( int )vAim[0];
						int y1 = int ( vAim[1] - size / 2 );

						int x2 = int ( vAim[0] - size / 2 );
						int y2 = ( int )vAim[1];

						Renderer::g_Drawing->FillArea ( x1, y1, 1, size, 0, 255, 200, 255 );
						Renderer::g_Drawing->FillArea ( x2, y2, size, 1, 0, 255, 200, 255 );
					}
				}
			}

			void Other::DrawAimFOV ( )
			{
				float FOV = 0.0f;

				byte Color[3];

				Color[3] = g_Vars.Other.DrawAimFovColor[3];

				if ( g_Vars.Aim.FOVDistance && AimBot::Weapons::GetTargetID ( ) )
				{
					cl_entity_s *Entity = SDK::Interfaces::g_pEngine->GetEntityByIndex ( AimBot::Weapons::GetTargetID ( ) );

					Vector uppt = Entity->origin - g_Info->GetVectorEyePosition ( );

					FOV = g_Info->GetShotsFired ( ) >= g_Vars.Weapons[g_Info->GetWeaponID ( )].BulletControl[0] ?
						g_Vars.Weapons[g_Info->GetWeaponID ( )].RecoilFOV : g_Vars.Weapons[g_Info->GetWeaponID ( )].FOV * 500.0f / uppt.Length ( );

					if ( g_Info->GetShotsFired ( ) < g_Vars.Weapons[g_Info->GetWeaponID ( )].BulletControl[0] )
					{
						if ( FOV > g_Vars.Weapons[g_Info->GetWeaponID ( )].FOV * 3.0f )
							FOV = g_Vars.Weapons[g_Info->GetWeaponID ( )].FOV * 3.0f;

						if ( FOV < g_Vars.Weapons[g_Info->GetWeaponID ( )].FOV / 2.0f )
							FOV = g_Vars.Weapons[g_Info->GetWeaponID ( )].FOV / 2.0f;
					}
				}
				else
				{
					FOV = g_Info->GetShotsFired ( ) >= g_Vars.Weapons[g_Info->GetWeaponID ( )].BulletControl[0] ?
						g_Vars.Weapons[g_Info->GetWeaponID ( )].RecoilFOV : g_Vars.Weapons[g_Info->GetWeaponID ( )].FOV;
				}

				FOV = FOV / g_Info->GetFOV ( ) * SDK::Interfaces::g_Screen.iWidth / 2.0f;

				int x = SDK::Interfaces::g_Screen.iWidth / 2 - ( int )Utils::GetPunchScreen ( )[1];
				int y = SDK::Interfaces::g_Screen.iHeight / 2 + ( int )Utils::GetPunchScreen ( )[0];

				Renderer::g_Drawing->Circle ( x, y, ( int )FOV, 100, 1, g_Vars.Other.DrawAimFovColor[0], g_Vars.Other.DrawAimFovColor[1], g_Vars.Other.DrawAimFovColor[2], 255 );
			}

			void Other::DrawPunch ( )
			{
				int x = SDK::Interfaces::g_Screen.iWidth / 2 - ( int )Utils::GetPunchScreen ( )[1] - 1;
				int y = SDK::Interfaces::g_Screen.iHeight / 2 + ( int )Utils::GetPunchScreen ( )[0] - 1;

				Renderer::g_Drawing->FillArea ( x, y, 3, 3, 255, 0, 0, 255 );
			}

			void Other::DrawSpread ( )
			{
				int x = ( int )Spread::GetDrawSpread ( )[0] - 1;
				int y = ( int )Spread::GetDrawSpread ( )[1] - 1;

				Renderer::g_Drawing->FillArea ( x, y, 3, 3, 255, 180, 0, 255 );
			}

			void Other::NameStealer()
			{
				static DWORD timer = GetTickCount();

				if (g_Vars.Other.NameStealer)
				{
					char cNames[MAX_CLIENTS][MAX_PLAYER_NAME_LENGTH];
					unsigned int iCount = 0;

					if (GetTickCount() - timer < g_Vars.Other.NameStealer)
						return;

					for (int i = 1; i <= SDK::Interfaces::g_pEngine->GetMaxClients(); i++)
					{
						if (i == Player->iIndex)
							continue;

						if (SDK::Interfaces::g_pEngineMsgBase[i].name == NULL || SDK::Interfaces::g_pEngineMsgBase[i].name == "")
							continue;

						if (strlen(SDK::Interfaces::g_pEngineMsgBase[i].name) <= 1)
							continue;

						strcpy_s(cNames[iCount++], SDK::Interfaces::g_pEngineMsgBase[i].name);
					}

					if (iCount > 0)
					{
						char cmdstr[256];
						char name[MAX_PLAYER_NAME_LENGTH];
						unsigned int n = rand() % iCount;
						strcpy_s(cmdstr, "name \"");
						strcpy_s(name, cNames[n]);
						ChangeName(name);
						strcat_s(cmdstr, name);
						strcat_s(cmdstr, "\"");
						SDK::Interfaces::g_pEngine->pfnClientCmd(cmdstr);
					}
				}

				timer = GetTickCount();
			}

			void Other::StatusAimBot ( )
			{
				if (g_Vars.Weapons[g_Info->GetWeaponID()].Aim == 1)
				{
					int x;
					int y;
					Renderer::g_Fonts->Print(26, 5, (BYTE)g_Vars.Other.FontColor[0], (BYTE)g_Vars.Other.FontColor[1], (BYTE)g_Vars.Other.FontColor[2],
						(BYTE)g_Vars.Other.FontColor[3], g_Vars.Other.FontOutline ? FL_OUTLINE : FL_NONE, "Aim");
					Renderer::g_Drawing->FillArea(5, 5, 35, 15, 10, 10, 10, 100);
					Renderer::g_Drawing->FillArea(5, 5, 3, 15, 0, 255, 0, 255);
				}
				else if (g_Vars.Weapons[g_Info->GetWeaponID()].Aim == 0)
				{
					int x;
					int y;
					Renderer::g_Fonts->Print(26, 5, (BYTE)g_Vars.Other.FontColor[0], (BYTE)g_Vars.Other.FontColor[1], (BYTE)g_Vars.Other.FontColor[2],
						(BYTE)g_Vars.Other.FontColor[3], g_Vars.Other.FontOutline ? FL_OUTLINE : FL_NONE, "Aim");
					Renderer::g_Drawing->FillArea(5, 5, 35, 15, 10, 10, 10, 100);
					Renderer::g_Drawing->FillArea(5, 5, 3, 15, 255, 0, 0, 255);
				}
			}

			void Other::StatusTriggerBot ( )
			{
				bool TriggerActive = g_Vars.Trigger.Enable && g_Vars.TriggerWeapons[g_Info->GetWeaponID ( )].Trigger &&TriggerBot::Trigger::Active;

				int x = TriggerActive ? SDK::Interfaces::g_Screen.iWidth - 167 : SDK::Interfaces::g_Screen.iWidth - 175;
				int y = 235;

				Renderer::g_Fonts->Print ( x, y, ( BYTE )g_Vars.Other.FontColor[0], ( BYTE )g_Vars.Other.FontColor[1], ( BYTE )g_Vars.Other.FontColor[2],
					( BYTE )g_Vars.Other.FontColor[3], g_Vars.Other.FontOutline ? FL_OUTLINE : FL_NONE, TriggerActive ? "TRIGGERBOT: ENABLED" : "TRIGGERBOT: DISABLED" );
			}


			void Other::HUD_Redraw ( )
			{
				if ( g_Info->GetAliveLocal ( ) && !g_Info->GetBadWeapon ( ) )
				{
					if ( g_Vars.Functions.Weapons && g_Vars.Aim.Enable )
					{
						if ( g_Vars.Weapons[g_Info->GetWeaponID ( )].Aim )
						{
							if ( g_Vars.Other.DrawAimSpot ) DrawAimSpot ( );
							if ( g_Vars.Other.DrawAimFOV ) DrawAimFOV ( );
						}

						if ( g_Vars.Other.StatusAimBot ) StatusAimBot ( );
					}

					if ( g_Vars.Functions.TriggerWeapons && g_Vars.Trigger.Enable )
					{
						if ( g_Vars.Other.StatusTriggerBot ) StatusTriggerBot ( );
					}

					if ( g_Vars.Other.DrawPunch ) DrawPunch ( );
					if ( g_Vars.Other.DrawSpread ) DrawSpread ( );
				}


			}
		}
	}
}