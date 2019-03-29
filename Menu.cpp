#include "Menu.h"
#include "backdrop.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{
			M_Entry Menu::MenuEntry[MAX_SUBS_MENU];
			S_Entry Menu::SubmEntry[MAX_SUBS_MENU];
			SS_Entry Menu::SubSubmEntry[MAX_SUBS_MENU];

			int Menu::M_EntryPos, Menu::M_EntrySize;
			int Menu::S_EntryPos, Menu::S_EntrySize;
			int Menu::SS_EntryPos, Menu::SS_EntrySize;

			char Menu::String[20];

			bool Menu::SubMenu, Menu::SubSubMenu;
			bool Menu::Visible, Menu::InputString;
			bool Menu::VisibleAnimation;

			float Menu::flVisibleAnimationTimer;

			int Menu::BoxWidth, Menu::BoxHeight;
			BYTE Menu::BoxOutlineColor[4], Menu::BoxColor[4];
			BYTE Menu::BoxSelectColor[4], Menu::TextColor[3];

			enum MENU_ENTRY
			{
				MAIN, AIMBOT, TRIGGERBOT, VISUALS, MISC, KEYS, LOAD_SETTINGS, SAVE_SETTINGS
			};

			enum SUBMENU_ENTRY_AIMBOT
			{
				GLOBALS, PISTOLS, RIFLES, SNIPERS, CURRENT, RECOIL, AUTOPISTOL, FASTZOOM
			};

			enum SUBMENU_ENTRY_TRIGGERBOT
			{
				TGLOBALS, TPISTOLS, TRIFLES, TSNIPERS, TCURRENT
			};

			enum SUBMENU_ENTRY_VISUALS
			{
				SCREENINFO, ESP, ESP_COLORS,
				CHAMS, CHAMS_COLORS, NOFLASH, CROSSHAIR, OTHER
			};

			enum SUBMENU_ENTRY_MISC
			{
				SPEED, BUNNYHOP, GROUNDSTRAFE
			};

			enum SUBMENU_ENTRY_KEYS
			{
				KMAIN, KPANICS, KTRIGGERBOT, KSPEED, KBUNNYHOP, KGROUNDSTRAFE
			};

			void Menu::SetSettings ( )
			{
				BoxWidth = 200;
				BoxHeight = 24;

				for ( int i = 0; i < 4; ++i )
				{
					BoxOutlineColor[i] = g_Vars.Menu.BoxOutlineColor[i];
					BoxColor[i] = g_Vars.Menu.BoxColor[i];
					BoxSelectColor[i] = g_Vars.Menu.BoxSelectColor[i];

					if ( i < 3 )
					{
						TextColor[i] = g_Vars.Menu.TextColor[i];
					}
				}
			}



			void Menu::Initialize ( )
			{
				 
				//draw::backdrop();  // crash! i fuck your mom behz


				if (g_Vars.ScreenInfo.times)
				{

                    #define time "         Time:" __TIME__
					Renderer::g_Drawing->FillArea(896, 35, 109, 18, BoxColor[0], BoxColor[1], BoxColor[2], BoxColor[3]);
					Renderer::g_Verdana->Print(931, 49, TextColor[0],
						TextColor[1], TextColor[2], 255, FL_OUTLINE | FL_CENTER, time);

					Renderer::g_Drawing->FillArea(898, 37, 5, 14, /**/ 8, 201, 1, BoxColor[3]);

				}

				Clear ( );
				Add ( "Меню", false, false );
				Add ( "Аимбот", false, false );
				Add ( "Триггербот", false, false );
				Add ( "Визуалы", false, false );
				Add ( "Миск", false, false );
				Add ( "Бинды", true, false );
				Add ( "Загрузить кфг", false, true );
				Add ( "Сохранить кфг", false, true );

				switch ( M_EntryPos )
				{
				case MENU_ENTRY::MAIN:
				{
					AddSubInt("АнтиСкрин", 0, 0, 0, 0, false, true, false, true,
						true, false, TextColor[0], TextColor[1], TextColor[2]);

					AddSubInt ( "Язык", &g_Vars.Main.Language, RUSSIAN, ENGLISH, 1, false, true,
						false, true, false, false, TextColor[0], TextColor[1], TextColor[2] );

					AddSubInt ( "Валидность игрока", &g_Vars.Main.PlayerValidCheck, 1, 2, 1, false, true,
						false, true, false, false, TextColor[0], TextColor[1], TextColor[2] );

					AddSubInt ( "АнтиСкрин", 0, 0, 0, 0, false, true, false, true,
						true, false, TextColor[0], TextColor[1], TextColor[2] );

					AddSubInt ( "Тип обводки шрифта", &g_Vars.Main.FontOutlineStyle, 1, 2, 1, false, false,
						false, true, false, false, TextColor[0], TextColor[1], TextColor[2] );

					if ( S_EntryPos == 2 )
					{
						AddSubSubBool ( "Включить", &g_Vars.Main.AntiScreenEnable, false, false, true, false, false );
						AddSubSubInt ( "Таймер", &g_Vars.Main.AntiScreenTimer, 1, 1000, 1, false, false, false, false, false );
					}

					break;
				}

				case MENU_ENTRY::AIMBOT:
				{
					g_Vars.Functions.Weapons ?
						AddSubInt ( "Глобальное", 0, 0, 0, 0, false, true, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "Глобальное", 0, 0, 0, 0, false, true, false, false, true, false, 100, 100, 100 );

					g_Vars.Functions.Weapons ?
						AddSubInt ( "Пистолеты", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "Пистолеты", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );

					g_Vars.Functions.Weapons ?
						AddSubInt ( "Винтовки", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "Винтовки", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );

					g_Vars.Functions.Weapons ?
						AddSubInt ( "Снайперки", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "Снайперки", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );

					g_Vars.Functions.Weapons ?
						AddSubInt ( "Оружие в руках", 0, 0, 0, 0, false, true, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "Оружие в руках", 0, 0, 0, 0, false, true, false, false, true, false, 100, 100, 100 );

					g_Vars.Functions.Recoil ?
						AddSubInt ( "Контроль разброса", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "Контроль разброса", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );

					g_Vars.Functions.AutoPistol ?
						AddSubInt ( "АвтоПистол", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "АвтоПистол", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );

					g_Vars.Functions.FastZoom ?
						AddSubInt ( "Фастзум", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "Фастзум", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );

					switch ( S_EntryPos )
					{
					case SUBMENU_ENTRY_AIMBOT::GLOBALS:
					{
						AddSubSubBool ( "Включить", &g_Vars.Aim.Enable, false, false, true, false, false );
						AddSubSubBool ( "рСайлент", &g_Vars.Aim.Silent, false, false, true, false, false );
						AddSubSubBool ( "Огонь по своим", &g_Vars.Aim.FriendlyFire, false, false, true, false, false );
						AddSubSubBool ( "Видимость", &g_Vars.Aim.VisibleCheck, false, false, true, false, false );
						AddSubSubBool ( "Слепость", &g_Vars.Aim.FlashCheck, false, false, true, false, false );
						AddSubSubBool ( "Дистанция FOV", &g_Vars.Aim.FOVDistance, false, false, true, false, false );
						AddSubSubInt ( "Задержка после убийства", &g_Vars.Aim.KillDelay, 0, 1000, 1, false, false, false, false, false );

						break;
					}

					case SUBMENU_ENTRY_AIMBOT::PISTOLS:
					{

						AddSubSubBool ( "Включить", &g_Vars.Weapons[26].Aim, false, false, true, false, false );
						AddSubSubInt ( "Старт контроля разброса", &g_Vars.Weapons[26].BulletControl[0], 1, 1000, 1, false, false, false, false, false );
						AddSubSubInt ( "Конец контроля разброса", &g_Vars.Weapons[26].BulletControl[1], 1, 1000, 1, false, false, false, false, false );
						AddSubSubInt ( "Точка наведения", &g_Vars.Weapons[26].HitBox, 0,  11, 1, false, false, false, false, false );
						AddSubSubBool ( "Рандомная точка", &g_Vars.Weapons[26].HitBoxNearest, false, false, true, false, false );
						AddSubSubFloat ( "Предугадывание", &g_Vars.Weapons[26].Prediction, 0.0f, 5.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "FOV", &g_Vars.Weapons[26].FOV, 0.0f, 90.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Плавность", &g_Vars.Weapons[26].Smooth, 1.0f, 50.0f, 0.01f, true, false, false, false, false );
						AddSubSubBool ("АвтоАим", &g_Vars.Weapons[26].Auto, false, false, true, false, false);
						AddSubSubFloat("Плавность АвтоАима", &g_Vars.Weapons[26].AutoSmooth, 1.0f, 50.0f, 0.01f, true, false, false, false, false);
						AddSubSubInt ( "Задержка", &g_Vars.Weapons[26].Delay, 0, 1000, 1, false, false, false, false, false );
						AddSubSubInt ( "Тип задержки", &g_Vars.Weapons[26].DelayType, 1, 3, 1, false, false, false, false, false );
						AddSubSubFloat ( "Контроль разброса", &g_Vars.Weapons[26].Recoil, 0.0f, 3.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Предугадывание разброса", &g_Vars.Weapons[26].RecoilPrediction, 0.0f, 5.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "FOV разброса", &g_Vars.Weapons[26].RecoilFOV, 0.0f, 90.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Плавность разброса", &g_Vars.Weapons[26].RecoilSmooth, 0.0f, 50.0f, 0.01f, true, false, false, false, false );

						break;
					}

					case SUBMENU_ENTRY_AIMBOT::RIFLES:
					{
						AddSubSubBool ( "Включить", &g_Vars.Weapons[28].Aim, false, false, true, false, false );
						AddSubSubInt ( "Старт контроля разброса", &g_Vars.Weapons[28].BulletControl[0], 1, 1000, 1, false, false, false, false, false );
						AddSubSubInt ( "Конец контроля разброса", &g_Vars.Weapons[28].BulletControl[1], 1, 1000, 1, false, false, false, false, false );
						AddSubSubInt ( "Точкая наведения", &g_Vars.Weapons[28].HitBox, 0, 11, 1, false, false, false, false, false );
						AddSubSubBool ( "Рандомная точка", &g_Vars.Weapons[28].HitBoxNearest, false, false, true, false, false );
						AddSubSubFloat ( "Предугадывание", &g_Vars.Weapons[28].Prediction, 0.0f, 5.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "FOV", &g_Vars.Weapons[28].FOV, 0.0f, 90.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Плавность", &g_Vars.Weapons[28].Smooth, 1.0f, 50.0f, 0.01f, true, false, false, false, false );
						AddSubSubBool("АвтоАим", &g_Vars.Weapons[28].Auto, false, false, true, false, false);
						AddSubSubInt ( "Задержка", &g_Vars.Weapons[28].Delay, 0, 1000, 1, false, false, false, false, false );
						AddSubSubInt ( "Тип задержки", &g_Vars.Weapons[28].DelayType, 1, 3, 1, false, false, false, false, false );
						AddSubSubFloat ( "Контроль разброса", &g_Vars.Weapons[28].Recoil, 0.0f, 3.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Предугадывание разброса", &g_Vars.Weapons[28].RecoilPrediction, 0.0f, 5.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "FOV разброса", &g_Vars.Weapons[28].RecoilFOV, 0.0f, 90.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Плавность разброса", &g_Vars.Weapons[28].RecoilSmooth, 0.0f, 50.0f, 0.01f, true, false, false, false, false );

						break;
					}

					case SUBMENU_ENTRY_AIMBOT::SNIPERS:
					{
						AddSubSubBool ( "Включить", &g_Vars.Weapons[18].Aim, false, false, true, false, false );
						AddSubSubInt ( "Старт контроля разброса", &g_Vars.Weapons[18].BulletControl[0], 1, 1000, 1, false, false, false, false, false );
						AddSubSubInt ( "Конец контроля разброса", &g_Vars.Weapons[18].BulletControl[1], 1, 1000, 1, false, false, false, false, false );
						AddSubSubInt ( "Точкая наведения", &g_Vars.Weapons[18].HitBox, 0, 11, 1, false, false, false, false, false );
						AddSubSubBool ( "Рандомная точка", &g_Vars.Weapons[18].HitBoxNearest, false, false, true, false, false );
						AddSubSubFloat ( "Предугадывание", &g_Vars.Weapons[18].Prediction, 0.0f, 5.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "FOV", &g_Vars.Weapons[18].FOV, 0.0f, 90.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Плавность", &g_Vars.Weapons[18].Smooth, 1.0f, 50.0f, 0.01f, true, false, false, false, false );
						AddSubSubBool("АвтоАим", &g_Vars.Weapons[18].Auto, false, false, true, false, false);
						AddSubSubInt ( "Задержка", &g_Vars.Weapons[18].Delay, 0, 1000, 1, false, false, false, false, false );
						AddSubSubInt ( "Тип задержки", &g_Vars.Weapons[18].DelayType, 1, 3, 1, false, false, false, false, false );
						AddSubSubFloat ( "Контроль разброса", &g_Vars.Weapons[18].Recoil, 0.0f, 3.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Предугадывание разброса", &g_Vars.Weapons[18].RecoilPrediction, 0.0f, 5.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "FOV разброса", &g_Vars.Weapons[18].RecoilFOV, 0.0f, 90.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Плавность разброса", &g_Vars.Weapons[18].RecoilSmooth, 0.0f, 50.0f, 0.01f, true, false, false, false, false );

						break;
					}

					case SUBMENU_ENTRY_AIMBOT::CURRENT:
					{
						AddSubSubBool ( "Включить", &g_Vars.Weapons[g_Info->GetWeaponID ( )].Aim, false, false, true, false, false );
						AddSubSubInt ( "Начало контроля разброса", &g_Vars.Weapons[g_Info->GetWeaponID ( )].BulletControl[0], 1, 1000, 1, false, false, false, false, false );
						AddSubSubInt ( "Конец контроля разброса", &g_Vars.Weapons[g_Info->GetWeaponID ( )].BulletControl[1], 1, 1000, 1, false, false, false, false, false );
						AddSubSubInt ( "Точкая наведения", &g_Vars.Weapons[g_Info->GetWeaponID ( )].HitBox, 0, 11, 1, false, false, false, false, false );
						AddSubSubBool ( "Рандомная точка", &g_Vars.Weapons[g_Info->GetWeaponID ( )].HitBoxNearest, false, false, true, false, false );
						AddSubSubFloat ( "Предугадываение", &g_Vars.Weapons[g_Info->GetWeaponID ( )].Prediction, 0.0f, 5.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "FOV", &g_Vars.Weapons[g_Info->GetWeaponID ( )].FOV, 0.0f, 90.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Плавность", &g_Vars.Weapons[g_Info->GetWeaponID ( )].Smooth, 1.0f, 50.0f, 0.01f, true, false, false, false, false );
						AddSubSubBool("АвтоАим", &g_Vars.Weapons[g_Info->GetWeaponID()].Auto, false, false, true, false, false);
						AddSubSubInt ( "Задержка", &g_Vars.Weapons[g_Info->GetWeaponID ( )].Delay, 0, 1000, 1, false, false, false, false, false );
						AddSubSubInt ( "Тип задержки", &g_Vars.Weapons[g_Info->GetWeaponID ( )].DelayType, 1, 3, 1, false, false, false, false, false );
						AddSubSubFloat ( "Контроль разброса", &g_Vars.Weapons[g_Info->GetWeaponID ( )].Recoil, 0.0f, 3.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Предугадывание разброса", &g_Vars.Weapons[g_Info->GetWeaponID ( )].RecoilPrediction, 0.0f, 5.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "FOV разброса", &g_Vars.Weapons[g_Info->GetWeaponID ( )].RecoilFOV, 0.0f, 90.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Плавность разброса", &g_Vars.Weapons[g_Info->GetWeaponID ( )].RecoilSmooth, 0.0f, 50.0f, 0.01f, true, false, false, false, false );

						break;
					}

					case SUBMENU_ENTRY_AIMBOT::RECOIL:
					{
						AddSubSubBool ( "Включить", &g_Vars.Recoil.Enable, false, false, true, false, false );
						AddSubSubFloat ( "Ось X", &g_Vars.Recoil.X, 0.0f, 3.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Ось Y", &g_Vars.Recoil.Y, 0.0f, 3.0f, 0.01f, true, false, false, false, false );
						AddSubSubFloat ( "Плавность", &g_Vars.Recoil.Smooth, 1.0f, 50.0f, 0.01f, true, false, false, false, false );
						AddSubSubInt ( "Начало контроля", &g_Vars.Recoil.BulletStart, 1, 1000, 1, false, false, false, false, false );

						break;
					}

					case SUBMENU_ENTRY_AIMBOT::AUTOPISTOL:
					{
						AddSubSubBool ( "Включить", &g_Vars.AutoPistol.Enable, false, false, true, false, false );
						AddSubSubInt ( "Задержка", &g_Vars.AutoPistol.Delay, 0, 1000, 1, false, false, false, false, false );

						break;
					}

					case SUBMENU_ENTRY_AIMBOT::FASTZOOM:
					{
						AddSubSubBool ( "Включить", &g_Vars.FastZoom.Enable, false, false, true, false, false );
						AddSubSubInt ( "Задержка", &g_Vars.FastZoom.Delay, 0, 1000, 1, false, false, false, false, false );
						AddSubSubBool ( "Быстрый свитч", &g_Vars.FastZoom.QuickSwitch, false, false, true, false, false );

						break;
					}
					}

					break;
				}

				case MENU_ENTRY::TRIGGERBOT:
				{
					g_Vars.Functions.TriggerWeapons ?
						AddSubInt ( "Глобальные", 0, 0, 0, 0, false, true, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "Глобальные", 0, 0, 0, 0, false, true, false, false, true, false, 100, 100, 100 );

					g_Vars.Functions.TriggerWeapons ?
						AddSubInt ( "Пистолеты", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "Пистолеты", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );

					g_Vars.Functions.TriggerWeapons ?
						AddSubInt ( "Винтовки", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "Винтовки", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );

					g_Vars.Functions.TriggerWeapons ?
						AddSubInt ( "Снайперки", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "Снайперки", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );

					g_Vars.Functions.TriggerWeapons ?
						AddSubInt ( "Оружие в руках", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "Оружие в руках", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );

					switch (S_EntryPos)
					{
					case SUBMENU_ENTRY_TRIGGERBOT::TGLOBALS:
					{
						AddSubSubBool("Включить", &g_Vars.Trigger.Enable, false, false, true, false, false);
						AddSubSubBool("Огонь по своим", &g_Vars.Trigger.FriendlyFire, false, false, true, false, false);
						AddSubSubBool("Видимость", &g_Vars.Trigger.VisibleCheck, false, false, true, false, false);
						AddSubSubBool("ОнлиЗум", &g_Vars.Trigger.SnipersOnlyInZoom, false, false, true, false, false);

						break;
					}

					case SUBMENU_ENTRY_TRIGGERBOT::TPISTOLS:
					{
						AddSubSubBool("Включить", &g_Vars.TriggerWeapons[26].Trigger, false, false, true, false, false);
						AddSubSubBool("Только в голову", &g_Vars.TriggerWeapons[26].OnlyHead, false, false, true, false, false);
						AddSubSubBool("ПроКонтроль", &g_Vars.TriggerWeapons[26].ProSpread, false, false, true, false, false);

						break;
					}

					case SUBMENU_ENTRY_TRIGGERBOT::TRIFLES:
					{
						AddSubSubBool("Включить", &g_Vars.TriggerWeapons[28].Trigger, false, false, true, false, false);
						AddSubSubBool("Только в голову", &g_Vars.TriggerWeapons[28].OnlyHead, false, false, true, false, false);
						AddSubSubBool("ПроКонтроль", &g_Vars.TriggerWeapons[28].ProSpread, false, false, true, false, false);

						break;
					}

					case SUBMENU_ENTRY_TRIGGERBOT::TSNIPERS:
					{
						AddSubSubBool("Включить", &g_Vars.TriggerWeapons[18].Trigger, false, false, true, false, false);
						AddSubSubBool("Только в голову", &g_Vars.TriggerWeapons[18].OnlyHead, false, false, true, false, false);
						AddSubSubBool("ПроКонтроль", &g_Vars.TriggerWeapons[18].ProSpread, false, false, true, false, false);

						break;
					}

					case SUBMENU_ENTRY_TRIGGERBOT::TCURRENT:
					{
						AddSubSubBool("Включить", &g_Vars.TriggerWeapons[g_Info->GetWeaponID()].Trigger, false, false, true, false, false);
						AddSubSubBool("Только в голову", &g_Vars.TriggerWeapons[g_Info->GetWeaponID()].OnlyHead, false, false, true, false, false);
						AddSubSubBool("ПроКонтроль", &g_Vars.TriggerWeapons[g_Info->GetWeaponID()].ProSpread, false, false, true, false, false);

						break;
					}
					}

					break;
				}

				case MENU_ENTRY::VISUALS:
				{
					if (g_Vars.Functions.ScreenInfo)
					{
						AddSubInt("СкринИнфо", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2]);
					}
					if ( g_Vars.Functions.ESP )
					{
						AddSubInt ( "Есп", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] );
						AddSubInt ( "Цвета Есп", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] );
					}
					else
					{
						AddSubInt ( "Есп", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );
						AddSubInt ( "Цвета Есп", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );
					}

					if ( g_Vars.Functions.Chams )
					{
						AddSubInt ( "Чамсы", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] );
						AddSubInt ( "Цвета чамсов", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] );
					}
					else
					{
						AddSubInt ( "Чамсы", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );
						AddSubInt ( "Цвета чамсов", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );
					}

					g_Vars.Functions.NoFlash ?
						AddSubInt ( "АнтиФлеш", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "АнтиФлеш", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );

					g_Vars.Functions.Crosshair ?
						AddSubInt ( "Кастомный прицел", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] ) :
						AddSubInt ( "Кастомный прицел", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100 );

					AddSubInt ( "Остальное", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2] );

					switch ( S_EntryPos )
					{

						case SUBMENU_ENTRY_VISUALS::SCREENINFO:
					{
						AddSubSubBool("Включить", &g_Vars.ScreenInfo.Enable, false, false, true, false, false);
						AddSubSubBool("Время", &g_Vars.ScreenInfo.times, false, true, true, false, false);
						AddSubSubBool("Ватермарк", &g_Vars.ScreenInfo.Watermark, false, true, true, false, false);
						AddSubSubInt("Фпс", &g_Vars.ScreenInfo.FPS, 0, 2, 1, false, false, false, false, false);
						AddSubSubInt("Марка", &g_Vars.ScreenInfo.Copyright, 0, 2, 1, false, false, false, false, false);
						AddSubSubInt("Показать бинды", &g_Vars.ScreenInfo.ShowKeys, 0, 2, 1, false, false, false, false, false);
						AddSubSubInt("Скорость юнита", &g_Vars.ScreenInfo.KreedzInfo, 0, 2, 1, false, true, false, false, false);
						AddSubSubInt("Фонт.Колор.R", &g_Vars.ScreenInfo.FontColor[0], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Фонт.Колор.G", &g_Vars.ScreenInfo.FontColor[1], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Фонт.Колор.B", &g_Vars.ScreenInfo.FontColor[2], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Фонт.Колор.A", &g_Vars.ScreenInfo.FontColor[3], 0, 255, 1, false, false, false, false, false);
						AddSubSubBool("Фонт.Alpha", &g_Vars.ScreenInfo.FontOutline, false, false, true, false, false);

						break;

					}

					case SUBMENU_ENTRY_VISUALS::ESP:
					{
						AddSubSubBool("Включить", &g_Vars.ESP.Enable, false, true, true, false, false);
						AddSubSubInt("Игроки", &g_Vars.ESP.Player, 0, 3, 1, false, false, false, false, false);
						AddSubSubBool("Только когда видно", &g_Vars.ESP.PlayerVisibleOnly, false, false, true, false, false);
						AddSubSubInt("Тип Квадратов", &g_Vars.ESP.PlayerBox, 0, 3, 1, false, false, false, false, false);
						AddSubSubInt("Заливка Квадратов", &g_Vars.ESP.PlayerBoxFilled, 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Обводка Квадратов", &g_Vars.ESP.PlayerBoxOutline, 0, 1, 1, false, false, false, false, false);
						AddSubSubBool("Ник игрока", &g_Vars.ESP.PlayerName, false, false, true, false, false);
						AddSubSubBool("Оружие игрока", &g_Vars.ESP.PlayerWeapon, false, false, true, false, false);
						AddSubSubBool("Скелетон", &g_Vars.ESP.PlayerSkeleton, false, false, true, false, false);
						AddSubSubBool("Скрин", &g_Vars.ESP.ScreenESP, false, false, true, false, false);
						AddSubSubBool("Просмотр игрока", &g_Vars.ESP.PlayerBarrel, false, true, true, false, false);
						AddSubSubBool("Бомба на полу", &g_Vars.ESP.WorldC4, false, false, true, false, false);
						AddSubSubBool("Оружие на полу", &g_Vars.ESP.WorldItems, false, false, true, false, false);
						AddSubSubBool("Гранаты на полу", &g_Vars.ESP.WorldNades, false, true, true, false, false);
						AddSubSubInt("Таймер бомбы", &g_Vars.ESP.C4Timer, 0, 2, 1, false, false, false, false, false);
						AddSubSubInt("Таймер на бомбе", &g_Vars.ESP.C4TimerValue, 0, 100, 1, false, true, false, false, false);
						AddSubSubBool("СаундЕСП", &g_Vars.ESP.Sound, false, false, true, false, false);
						AddSubSubInt("Дистанция ", &g_Vars.ESP.SoundDistance, 0, 10000, 10, false, false, false, false, false);
						AddSubSubInt("Время цвета", &g_Vars.ESP.SoundFadeTime, 0, 5000, 10, false, false, false, false, false);

						break;
					}

					case SUBMENU_ENTRY_VISUALS::ESP_COLORS:
					{
						AddSubSubInt ( "Цвет-R когда видно Т", &g_Vars.ESP.ColorTVis[0], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-G когда видно Т", &g_Vars.ESP.ColorTVis[1], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-B когда видно Т", &g_Vars.ESP.ColorTVis[2], 0, 255, 1, false, true, false, false, false );
						AddSubSubInt ( "Цвет-R когда не видно Т", &g_Vars.ESP.ColorTHide[0], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-G когда не видно Т", &g_Vars.ESP.ColorTHide[1], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-B когда не видно Т", &g_Vars.ESP.ColorTHide[2], 0, 255, 1, false, true, false, false, false );
						AddSubSubInt ( "Цвет-R когда видно KТ", &g_Vars.ESP.ColorCTVis[0], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-G когда видно KТ", &g_Vars.ESP.ColorCTVis[1], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-B когда видно KТ", &g_Vars.ESP.ColorCTVis[2], 0, 255, 1, false, true, false, false, false );
						AddSubSubInt ( "Цвет-R когда не видно KТ", &g_Vars.ESP.ColorCTHide[0], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-G когда не видно KТ", &g_Vars.ESP.ColorCTHide[1], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-B когда не видно KТ", &g_Vars.ESP.ColorCTHide[2], 0, 255, 1, false, true, false, false, false );
						AddSubSubInt ( "Цвет-R шрифта", &g_Vars.ESP.FontColor[0], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-G шрифта", &g_Vars.ESP.FontColor[1], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-B шрифта", &g_Vars.ESP.FontColor[2], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-A шрифта", &g_Vars.ESP.FontColor[3], 0, 255, 1, false, false, false, false, false );

						break;
					}

					case SUBMENU_ENTRY_VISUALS::CHAMS:
					{
						AddSubSubBool ( "Включить", &g_Vars.Chams.Enable, false, true, true, false, false );
						AddSubSubInt ( "Игроки", &g_Vars.Chams.Player, 0, 2, 1, false, false, false, false, false );
						AddSubSubBool ( "Только когда видно", &g_Vars.Chams.PlayerVisibleOnly, false, false, true, false, false );
						AddSubSubInt ( "Тип рендера", &g_Vars.Chams.PlayerRenderType, 1, 5, 1, false, true, false, false, false );
						AddSubSubBool ( "Оружие", &g_Vars.Chams.Weapon, false, false, true, false, false );
						AddSubSubBool ( "Только когда видно", &g_Vars.Chams.WeaponVisibleOnly, false, false, true, false, false );
						AddSubSubInt ( "Тип рендера", &g_Vars.Chams.WeaponRenderType, 1, 5, 1, false, true, false, false, false );
						AddSubSubBool ( "Руки", &g_Vars.Chams.Hands, false, false, true, false, false );
						AddSubSubInt ( "Тип рендера", &g_Vars.Chams.HandsRenderType, 1, 5, 1, false, false, false, false, false );
						AddSubSubInt("Цвет-R рук", &g_Vars.Chams.HandsColor[0], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-G рук", &g_Vars.Chams.HandsColor[1], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-B рук", &g_Vars.Chams.HandsColor[2], 0, 255, 1, false, false, false, false, false);

						break;
					}

					case SUBMENU_ENTRY_VISUALS::CHAMS_COLORS:
					{
						AddSubSubInt("Цвет-R когда видно Т", &g_Vars.Chams.ColorTVis[0], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-G когда видно Т", &g_Vars.Chams.ColorTVis[1], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-B когда видно Т", &g_Vars.Chams.ColorTVis[2], 0, 255, 1, false, true, false, false, false);
						AddSubSubInt("Цвет-R когда не видно Т", &g_Vars.Chams.ColorTHide[0], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-G когда не видно Т", &g_Vars.Chams.ColorTHide[1], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-B когда не видно Т", &g_Vars.Chams.ColorTHide[2], 0, 255, 1, false, true, false, false, false);
						AddSubSubInt("Цвет-R когда видно KТ", &g_Vars.Chams.ColorCTVis[0], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-G когда видно KТ", &g_Vars.Chams.ColorCTVis[1], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-B когда видно KТ", &g_Vars.Chams.ColorCTVis[2], 0, 255, 1, false, true, false, false, false);
						AddSubSubInt("Цвет-R когда не видно KТ", &g_Vars.Chams.ColorCTHide[0], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-G когда не видно KТ", &g_Vars.Chams.ColorCTHide[1], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-B когда не видно KТ", &g_Vars.Chams.ColorCTHide[2], 0, 255, 1, false, true, false, false, false);
						AddSubSubInt("Цвет-R когда видно оружия", &g_Vars.Chams.WeaponColorVis[0], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-G когда видно оружия", &g_Vars.Chams.WeaponColorVis[1], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-B когда видно оружия", &g_Vars.Chams.WeaponColorVis[2], 0, 255, 1, false, true, false, false, false);
						AddSubSubInt("Цвет-R когда не видно оружия", &g_Vars.Chams.WeaponColorHide[0], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-G когда не видно оружия", &g_Vars.Chams.WeaponColorHide[1], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-B когда не видно оружия", &g_Vars.Chams.WeaponColorHide[2], 0, 255, 1, false, true, false, false, false);

						break;
					}

					case SUBMENU_ENTRY_VISUALS::NOFLASH:
					{
						AddSubSubBool ( "Включить", &g_Vars.NoFlash.Enable, false, false, true, false, false );
						AddSubSubInt ( "Прозрачность", &g_Vars.NoFlash.FadeLimit, 0, 255, 1, false, true, false, false, false );
						AddSubSubBool ( "Кастомный цвет", &g_Vars.NoFlash.FadeColorEnable, false, false, true, false, false );
						AddSubSubInt ( "Цвет-R", &g_Vars.NoFlash.FadeColor[0], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-G", &g_Vars.NoFlash.FadeColor[1], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-B", &g_Vars.NoFlash.FadeColor[2], 0, 255, 1, false, false, false, false, false );
						AddSubSubBool ( "Рандомный", &g_Vars.NoFlash.FadeColorRandom, false, true, true, false, false );
						AddSubSubInt ( "Текст", &g_Vars.NoFlash.DrawFlashed, 0, 2, 1, false, false, false, false, false );
						AddSubSubBool ( "Обводка текста", &g_Vars.NoFlash.FontOutline, false, false, true, false, false );

						break;
					}

					case SUBMENU_ENTRY_VISUALS::CROSSHAIR:
					{
						AddSubSubBool ( "Включить", &g_Vars.Crosshair.Enable, false, false, true, false, false );
						AddSubSubBool ( "Точка", &g_Vars.Crosshair.Dot, false, false, true, false, false );
						AddSubSubInt ( "Размер", &g_Vars.Crosshair.Size, 0, 50, 1, false, false, false, false, false );
						AddSubSubInt ( "Пробел внутри", &g_Vars.Crosshair.Gap, 0, 50, 1, false, false, false, false, false );
						AddSubSubInt ( "Толщина", &g_Vars.Crosshair.Thickness, 1, 3, 1, false, false, false, false, false );
						AddSubSubBool ( "Динамический", &g_Vars.Crosshair.Dynamic, false, false, true, false, false );
						AddSubSubFloat ( "Масштаб динамики", &g_Vars.Crosshair.DynamicScale, 0.0f, 10.0f, 0.01f, true, false, false, false, false );
						AddSubSubBool ( "Обводка", &g_Vars.Crosshair.Outline, false, false, true, false, false );
						AddSubSubBool ( "Для снайперок", &g_Vars.Crosshair.Snipers, false, true, true, false, false );
						AddSubSubInt ( "Цвет-R", &g_Vars.Crosshair.Color[0], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-G", &g_Vars.Crosshair.Color[1], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-B", &g_Vars.Crosshair.Color[2], 0, 255, 1, false, false, false, false, false );
						AddSubSubInt ( "Цвет-A", &g_Vars.Crosshair.Color[3], 0, 255, 1, false, false, false, false, false );

						break;
					}

					case SUBMENU_ENTRY_VISUALS::OTHER:
					{
						if ( g_Vars.Functions.Weapons )
						{
							AddSubSubBool("Точка наведения аима", &g_Vars.Other.DrawAimSpot, false, true, true, false, false);
							AddSubSubBool("FOV Аима", &g_Vars.Other.DrawAimFOV, false, false, true, false, false);
							AddSubSubInt("Цвет-R", &g_Vars.Other.DrawAimFovColor[0], 0, 255, 1, false, false, false, false, false);
							AddSubSubInt("Цвет-G", &g_Vars.Other.DrawAimFovColor[1], 0, 255, 1, false, false, false, false, false);
							AddSubSubInt("Цвет-B", &g_Vars.Other.DrawAimFovColor[2], 0, 255, 1, false, false, false, false, false);
						}

						AddSubSubBool ( "Точка в середине", &g_Vars.Other.DrawPunch, false, false, true, false, false );
						AddSubSubBool ( "Точка разброса", &g_Vars.Other.DrawSpread, false, true, true, false, false);
						AddSubSubBool("АнтиСмок", &g_Vars.Other.RemoveSmoke, false, false, true, false, false);
						AddSubSubBool("НочнойМод", &g_Vars.Other.NightMode, false, false, true, false, false);
						AddSubSubBool("Радужное Меню", &g_Vars.Other.Rainbow1, false, true, true, false, false);
						AddSubSubBool("Неймстиллер", &g_Vars.Other.NameStealer, false, true, true, false, false);
						AddSubSubInt("Цвет-R текста", &g_Vars.Other.FontColor[0], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-G текста", &g_Vars.Other.FontColor[1], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-B текста", &g_Vars.Other.FontColor[2], 0, 255, 1, false, false, false, false, false);
						AddSubSubInt("Цвет-A текста", &g_Vars.Other.FontColor[3], 0, 255, 1, false, false, false, false, false);
						AddSubSubBool("Обводка шрифта", &g_Vars.Other.FontOutline, false, false, true, false, false);

						break;
					}
					}

					break;
				}

				case MENU_ENTRY::MISC:
				{
					g_Vars.Functions.Speed ?
						AddSubInt("Скорость", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2]) :
						AddSubInt("Скорость", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100);

					g_Vars.Functions.BunnyHop ?
						AddSubInt("Бхоп", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2]) :
						AddSubInt("Бхоп", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100);

					g_Vars.Functions.GroundStrafe ?
						AddSubInt("Стрейф", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2]) :
						AddSubInt("Стрейф", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100);

					switch (S_EntryPos)
					{
					case SUBMENU_ENTRY_MISC::SPEED:
					{
						AddSubSubFloat("Player", &g_Vars.Speed.Player, 0.0f, 100.0f, 0.01f, true, false, false, false, false);
						AddSubSubInt("Engine", &g_Vars.Speed.Engine, -255, 255, 1, false, false, false, false, false);
						AddSubSubFloat("Boost", &g_Vars.Speed.Boost, 1.1f, 100.0f, 0.01f, true, false, false, false, false);
						AddSubSubFloat("Slowmotion", &g_Vars.Speed.Slowmo, 0.0f, 0.9f, 0.01f, true, true, false, false, false);
						AddSubSubBool("Helper", &g_Vars.Speed.Helper, false, false, true, false, false);
						AddSubSubFloat("Helper.Ground", &g_Vars.Speed.HelperGround, 0.0f, 100.0f, 0.01f, true, false, false, false, false);
						AddSubSubFloat("Helper.Ladder", &g_Vars.Speed.HelperLadder, 0.0f, 100.0f, 0.01f, true, false, false, false, false);
						AddSubSubFloat("Helper.Fly", &g_Vars.Speed.HelperFly, 0.0f, 100.0f, 0.01f, true, false, false, false, false);

						break;
					}

					case SUBMENU_ENTRY_MISC::BUNNYHOP:
					{
						AddSubSubBool("NoSlowdown", &g_Vars.BunnyHop.NoSlowdown, false, false, true, false, false);
						AddSubSubBool("Scroll.Emulation", &g_Vars.BunnyHop.ScrollEmulation, false, false, true, false, false);
						AddSubSubInt("Scroll.Direction", &g_Vars.BunnyHop.ScrollDirection, DOWN, UP, 1, false, false, false, false, false);
						AddSubSubFloat("Scroll.Distance.Min", &g_Vars.BunnyHop.ScrollDistance[0], 0.0f, 50.0f, 0.01f, true, false, false, false, false);
						AddSubSubFloat("Scroll.Distance.Max", &g_Vars.BunnyHop.ScrollDistance[1], 0.0f, 50.0f, 0.01f, true, false, false, false, false);
						AddSubSubBool("Scroll.RandFails", &g_Vars.BunnyHop.ScrollRandFails, false, false, true, false, false);
						AddSubSubBool("OnLadder", &g_Vars.BunnyHop.OnLadder, false, true, true, false, false);
						AddSubSubBool("Helper", &g_Vars.BunnyHop.Helper, false, false, true, false, false);
						AddSubSubBool("Helper.NoSlowdown", &g_Vars.BunnyHop.HelperNoSlowdown, false, false, true, false, false);
						AddSubSubInt("Helper.IdealPercent", &g_Vars.BunnyHop.HelperIdealPercent, 0, 100, 1, false, true, false, false, false);
						AddSubSubBool("StandUp.Auto", &g_Vars.BunnyHop.StandUpAuto, false, false, true, false, false);
						AddSubSubInt("StandUp.FallVelocity", &g_Vars.BunnyHop.StandUpFallVelocity, 0, 250, 1, false, false, false, false, false);

						if (g_Vars.BunnyHop.ScrollDistance[0] > g_Vars.BunnyHop.ScrollDistance[1])
							g_Vars.BunnyHop.ScrollDistance[0] = g_Vars.BunnyHop.ScrollDistance[1];

						if (g_Vars.BunnyHop.ScrollDistance[1] < g_Vars.BunnyHop.ScrollDistance[0])
							g_Vars.BunnyHop.ScrollDistance[1] = g_Vars.BunnyHop.ScrollDistance[0];

						break;
					}

					case SUBMENU_ENTRY_MISC::GROUNDSTRAFE:
					{
						AddSubSubBool("Scroll.Emulation", &g_Vars.GroundStrafe.ScrollEmulation, false, false, true, false, false);
						AddSubSubInt("Scroll.Direction", &g_Vars.GroundStrafe.ScrollDirection, DOWN, UP, 1, false, false, false, false, false);
						AddSubSubFloat("Scroll.Distance.Min", &g_Vars.GroundStrafe.ScrollDistance[0], 0.0f, 50.0f, 0.01f, true, false, false, false, false);
						AddSubSubFloat("Scroll.Distance.Max", &g_Vars.GroundStrafe.ScrollDistance[1], 0.0f, 50.0f, 0.01f, true, false, false, false, false);
						AddSubSubInt("Scroll.Count.Min", &g_Vars.GroundStrafe.ScrollCount[0], 1, 50, 1, false, false, false, false, false);
						AddSubSubInt("Scroll.Count.Max", &g_Vars.GroundStrafe.ScrollCount[1], 1, 50, 1, false, false, false, false, false);
						AddSubSubFloat("Slowdown.Scale", &g_Vars.GroundStrafe.SlowdownScale, 0.0f, 2.0f, 0.01f, true, false, false, false, false);
						AddSubSubFloat("Slowdown.Angle", &g_Vars.GroundStrafe.SlowdownAngle, 0.0f, 45.0f, 0.01f, true, false, false, false, false);
						AddSubSubBool("FallRun", &g_Vars.GroundStrafe.FallRun, false, true, true, false, false);
						AddSubSubBool("Helper", &g_Vars.GroundStrafe.Helper, false, true, true, false, false);
						AddSubSubInt("StandUp.FallVelocity", &g_Vars.GroundStrafe.StandUpFallVelocity, 0, 250, 1, false, false, false, false, false);

						if (g_Vars.GroundStrafe.ScrollDistance[0] > g_Vars.GroundStrafe.ScrollDistance[1])
							g_Vars.GroundStrafe.ScrollDistance[0] = g_Vars.GroundStrafe.ScrollDistance[1];

						if (g_Vars.GroundStrafe.ScrollDistance[1] < g_Vars.GroundStrafe.ScrollDistance[0])
							g_Vars.GroundStrafe.ScrollDistance[1] = g_Vars.GroundStrafe.ScrollDistance[0];

						if (g_Vars.GroundStrafe.ScrollCount[0] > g_Vars.GroundStrafe.ScrollCount[1])
							g_Vars.GroundStrafe.ScrollCount[0] = g_Vars.GroundStrafe.ScrollCount[1];

						if (g_Vars.GroundStrafe.ScrollCount[1] < g_Vars.GroundStrafe.ScrollCount[0])
							g_Vars.GroundStrafe.ScrollCount[1] = g_Vars.GroundStrafe.ScrollCount[0];

						break;
					}
					}

					break;
				}

				case MENU_ENTRY::KEYS:
				{
					AddSubInt("Main", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2]);
					AddSubInt("Panic", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2]);

					g_Vars.Functions.TriggerWeapons ?
						AddSubInt("TriggerBot", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2]) :
						AddSubInt("TriggerBot", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100);

					g_Vars.Functions.Speed ?
						AddSubInt("Speed", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2]) :
						AddSubInt("Speed", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100);

					g_Vars.Functions.BunnyHop ?
						AddSubInt("BunnyHop", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2]) :
						AddSubInt("BunnyHop", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100);

					g_Vars.Functions.GroundStrafe ?
						AddSubInt("GroundStrafe", 0, 0, 0, 0, false, false, false, true, true, false, TextColor[0], TextColor[1], TextColor[2]) :
						AddSubInt("GroundStrafe", 0, 0, 0, 0, false, false, false, false, true, false, 100, 100, 100);

					switch (S_EntryPos)
					{
					case SUBMENU_ENTRY_KEYS::KMAIN:
						AddSubSubKey("ASS.Key", &g_Vars.Main.AntiScreenKey, false, true, false, false, true);
						AddSubSubKey("Reload.Key", &g_Vars.Main.ReloadKey, false, false, false, false, true);
						AddSubSubKey("Save.Key", &g_Vars.Main.SaveKey, false, false, false, false, true);
						AddSubSubKey("Menu.Key", &g_Vars.Menu.Key, false, false, false, false, true);

						break;

					case SUBMENU_ENTRY_KEYS::KPANICS:
						AddSubSubKey("Key", &g_Vars.Main.PanicKey, false, false, false, false, true);
						AddSubSubKey("AimBot.Key", &g_Vars.Main.PanicAimBotKey, false, false, false, false, true);
						AddSubSubKey("Visuals.Key", &g_Vars.Main.PanicVisualsKey, false, false, false, false, true);
						AddSubSubKey("Misc.Key", &g_Vars.Main.PanicMiscKey, false, false, false, false, true);

						break;

					case SUBMENU_ENTRY_KEYS::KTRIGGERBOT:
						AddSubSubKey("Key", &g_Vars.Trigger.Key, false, false, false, false, true);
						AddSubSubKey("Switch.Key", &g_Vars.Trigger.SwitchKey, false, false, false, false, true);

						break;

					case SUBMENU_ENTRY_KEYS::KSPEED:
						AddSubSubKey("Boost.Key", &g_Vars.Speed.BoostKey, false, false, false, false, true);
						AddSubSubKey("Slowmo.Key", &g_Vars.Speed.SlowmoKey, false, false, false, false, true);

						break;

					case SUBMENU_ENTRY_KEYS::KBUNNYHOP:
						AddSubSubKey("Key", &g_Vars.BunnyHop.Key, false, false, false, false, true);
						AddSubSubKey("StandUp.Key", &g_Vars.BunnyHop.StandUpKey, false, false, false, false, true);

						break;

					case SUBMENU_ENTRY_KEYS::KGROUNDSTRAFE:
						AddSubSubKey("Key", &g_Vars.GroundStrafe.Key, false, false, false, false, true);
						AddSubSubKey("StandUp.Key", &g_Vars.GroundStrafe.StandUpKey, false, false, false, false, true);

						break;
					}

					break;
				}
				}
			}

			void Menu::DrawFadeAnimation ( )
			{
				if ( VisibleAnimation )
				{
					++flVisibleAnimationTimer;

					if ( flVisibleAnimationTimer <= 28.0f )
					{
						BYTE Alpha = ( BYTE )Utils::Interp ( 1.0f, flVisibleAnimationTimer, 28.0f, Visible ? 0.0f : 120.0f, Visible ? 0.0f : 0.0f );

						Renderer::g_Drawing->FillArea ( 0, 0, SDK::Interfaces::g_Screen.iWidth, SDK::Interfaces::g_Screen.iHeight, 0, 0, 0, 0 );
					}
					else
					{
						Renderer::g_Drawing->FillArea ( 0, 0, SDK::Interfaces::g_Screen.iWidth, SDK::Interfaces::g_Screen.iHeight, 0, 0, 0, Visible ? 0 : 0 );

						flVisibleAnimationTimer = 0.0f;

						VisibleAnimation = false;
					}
				}
				else
				{
					if ( Visible )
					{
						Renderer::g_Drawing->FillArea ( 0, 0, SDK::Interfaces::g_Screen.iWidth, SDK::Interfaces::g_Screen.iHeight, 0, 0, 0, 0 );
					}
				}
			}

			void Menu::DrawMenu(int x, int y)
			{
				if (g_Vars.ScreenInfo.Watermark)
				{
					Renderer::g_Drawing->FillArea(896, 5, 109, 18, BoxColor[0], BoxColor[1], BoxColor[2], BoxColor[3]);

					//Renderer::g_Drawing->FillArea(899, 6, 101, 15, BoxColor[0], BoxColor[1], BoxColor[2], BoxColor[3]);
					Renderer::g_Drawing->FillArea(907, 8, 6, 11, 216, 216, 216, BoxColor[3]);

					Renderer::g_Drawing->FillArea(932, 8, 6, 11, 216, 216, 216, BoxColor[3]);

					Renderer::g_Verdana->Print(946, 17, TextColor[0],
						TextColor[1], TextColor[2], 255, FL_OUTLINE | FL_CENTER, "A    V     chlenix ");

					if (g_Vars.Aim.Enable)
					{
						Renderer::g_Drawing->FillArea(907, 8, 6, 11, 225, 111, 0, BoxColor[3]);
					}

					if (g_Vars.ESP.Enable)
					{
						Renderer::g_Drawing->FillArea(932, 8, 6, 11, 225, 111, 0, BoxColor[3]);
					}
				}

				if (!Visible)
				{
					Utils::native_memset(SubSubmEntry, sizeof(SubSubmEntry), 0);
					Utils::native_memset(SubmEntry, sizeof(SubmEntry), 0);
					Utils::native_memset(MenuEntry, sizeof(MenuEntry), 0);

					return;
				}

				Initialize();

				//Renderer::g_Drawing->Box(x, y, BoxWidth, BoxHeight, 1, BoxOutlineColor[0], BoxOutlineColor[1], BoxOutlineColor[2], BoxOutlineColor[3]);

				int HeadY = y;
				int HeadBoxWidth = BoxWidth - 2;
				int HeadBoxHeight = BoxHeight - 2;
				int HeadMenuBoxX = x + 1;
				int HeadMenuBoxY = y + 1;

				Renderer::g_Drawing->FillArea(HeadMenuBoxX, HeadMenuBoxY, HeadBoxWidth, HeadBoxHeight, BoxColor[0], BoxColor[1], BoxColor[2], BoxColor[3]);

				int HeadMenuTextX = HeadMenuBoxX + int(HeadBoxWidth / 2.0f);
				int HeadMenuTextY = HeadMenuBoxY + int(HeadBoxHeight / 2.0f) + 4;

				//Renderer::g_Drawing->FillArea(912, 8, 6, 12, /*10,10*/ 225, 111, 0, BoxColor[3]);
				Renderer::g_Verdana->Print(HeadMenuTextX, HeadMenuTextY, TextColor[0],
					TextColor[1], TextColor[2], 255, FL_OUTLINE | FL_CENTER, "CHLENIX");

				y += BoxHeight + 2;

				int MenuBoxX = x + 1;
				int MenuTextX = MenuBoxX + 6;
				int MenuBoxY = 0;
				int MenuTextY = 0;

				for (int i = 0; i < M_EntrySize; ++i)
				{
					MenuBoxY = y + 1;
					MenuTextY = MenuBoxY + int(HeadBoxHeight / 2.0f) + 4;

					Renderer::g_Drawing->Box(x, y, BoxWidth, BoxHeight, 1, BoxOutlineColor[0], BoxOutlineColor[1], BoxOutlineColor[2], BoxOutlineColor[3]);
					Renderer::g_Drawing->FillArea(MenuBoxX, MenuBoxY, HeadBoxWidth, HeadBoxHeight, BoxColor[0], BoxColor[1], BoxColor[2], BoxColor[3]);

					if (i == M_EntryPos)
					{
						if (!SubMenu)
						{
							Renderer::g_Drawing->FillArea(MenuBoxX, MenuBoxY, HeadBoxWidth, HeadBoxHeight,
								255, 111, 0, BoxSelectColor[3]);
						}

						Renderer::g_Drawing->FillArea(MenuBoxX, MenuBoxY, 2, HeadBoxHeight, 255, 93, 0, 200);
					}

					for (int a = 0; a < MAX_NAME_CHAR; ++a)
					{
						MenuEntry[i].Name[a] ^= MENU_ENTRY_KEY;
					}

					Renderer::g_Verdana->Print(MenuTextX, MenuTextY, TextColor[0], TextColor[1], TextColor[2], 255, FL_OUTLINE, MenuEntry[i].Name);

					y += BoxHeight + 1;

					if (MenuEntry[i].Space)
					{
						y += BoxHeight + 1;
					}
				}

				x += BoxWidth + 1;

				int HeadSubMenuBoxX = x + 1;
				int HeadSubMenuBoxY = y + 1;

				if (SubMenu)
				{
					int SubMenuBoxOutlineY = HeadY + BoxHeight + 2;
					int SubMenuBoxX = x + 1;
					int SubMenuBoxY = SubMenuBoxOutlineY + 1;
					int SubMenuTextX = SubMenuBoxX + 6;
					int SubMenuTextY = SubMenuBoxY + int(HeadBoxHeight / 2.0f) + 4;

					for (int i = 0; i < S_EntrySize; ++i)
					{
						Renderer::g_Drawing->Box(x, SubMenuBoxOutlineY, BoxWidth, BoxHeight, 1,
							BoxOutlineColor[0], BoxOutlineColor[1], BoxOutlineColor[2], BoxOutlineColor[3]);

						Renderer::g_Drawing->FillArea(SubMenuBoxX, SubMenuBoxY, HeadBoxWidth, HeadBoxHeight,
							BoxColor[0], BoxColor[1], BoxColor[2], BoxColor[3]);

						if (i == S_EntryPos)
						{
							if (!SubSubMenu)
								Renderer::g_Drawing->FillArea(SubMenuBoxX, SubMenuBoxY, HeadBoxWidth,
									HeadBoxHeight, 255, 111, 0, BoxSelectColor[3]);

							Renderer::g_Drawing->FillArea(SubMenuBoxX, SubMenuBoxY, 2, HeadBoxHeight,
								255, 111, 0, 255);
						}

						for (int a = 0; a < MAX_NAME_CHAR; ++a)
						{
							SubmEntry[i].Name[a] ^= SUBM_ENTRY_KEY;
						}

						Renderer::g_Verdana->Print(SubMenuTextX, SubMenuTextY, SubmEntry[i].Color[0],
							SubmEntry[i].Color[1], SubmEntry[i].Color[2], 255, FL_OUTLINE, SubmEntry[i].Name);

						if (!SubmEntry[i].Sub)
						{
							if (SubmEntry[i].Auto)
							{
								if (!SubmEntry[i].Float)
								{
									if (!SubmEntry[i].iMin)
									{
										if (*SubmEntry[i].iValue == SubmEntry[i].iMin)
										{
											Renderer::g_Verdana->Print(SubMenuTextX + (BoxWidth - 42),
												SubMenuTextY, 255, 80, 80, 255, FL_OUTLINE, "off");
										}
										else if (*SubmEntry[i].iValue == SubmEntry[i].iMax)
										{
											Renderer::g_Verdana->Print(SubMenuTextX + (BoxWidth - 42),
												SubMenuTextY, 80, 255, 80, 255, FL_OUTLINE, "auto");
										}
										else
										{
											Renderer::g_Verdana->Print(SubMenuTextX + (BoxWidth - 42),
												SubMenuTextY, 80, 255, 80, 255, FL_OUTLINE, "%d", *SubmEntry[i].iValue);
										}
									}
									else
									{
										if (*SubmEntry[i].iValue == SubmEntry[i].iMax)
										{
											Renderer::g_Verdana->Print(SubMenuTextX + (BoxWidth - 42),
												SubMenuTextY, 80, 255, 80, 255, FL_OUTLINE, "auto");
										}
										else
										{
											Renderer::g_Verdana->Print(SubMenuTextX + (BoxWidth - 42),
												SubMenuTextY, 80, 255, 80, 255, FL_OUTLINE, "%d", *SubmEntry[i].iValue);
										}
									}
								}
							}
							else
							{
								if (SubmEntry[i].Float)
								{
									Renderer::g_Verdana->Print(SubMenuTextX + (BoxWidth - 42), SubMenuTextY,
										255, 255, 255, 255, FL_OUTLINE, "%.2f", *SubmEntry[i].flValue);
								}
								else
								{
									if (SubmEntry[i].Switch)
									{
										*SubmEntry[i].iValue ?
											Renderer::g_Verdana->Print(SubMenuTextX + (BoxWidth - 42),
												SubMenuTextY, 80, 255, 80, 255, FL_OUTLINE, "on", *SubmEntry[i].iValue) :

											Renderer::g_Verdana->Print(SubMenuTextX + (BoxWidth - 42),
												SubMenuTextY, 255, 80, 80, 255, FL_OUTLINE, "off");
									}
									else
									{
										if (!SubmEntry[i].iMin && (SubmEntry[i].iMax == 2 || SubmEntry[i].iMax == 4))
										{
											*SubmEntry[i].iValue ?
												Renderer::g_Verdana->Print(SubMenuTextX + (BoxWidth - 42),
													SubMenuTextY, 80, 255, 80, 255, FL_OUTLINE, "%d", *SubmEntry[i].iValue) :

												Renderer::g_Verdana->Print(SubMenuTextX + (BoxWidth - 42),
													SubMenuTextY, 255, 80, 80, 255, FL_OUTLINE, "off");
										}
										else if (SubmEntry[i].iMin == ENGLISH && SubmEntry[i].iMax == RUSSIAN)
										{
											if (*SubmEntry[i].iValue == ENGLISH)
											{
												Renderer::g_Verdana->Print(SubMenuTextX + (BoxWidth - 60),
													SubMenuTextY, 255, 255, 255, 255, FL_OUTLINE, "english");
											}
											else if (*SubmEntry[i].iValue == RUSSIAN)
											{
												Renderer::g_Verdana->Print(SubMenuTextX + (BoxWidth - 60),
													SubMenuTextY, 255, 255, 255, 255, FL_OUTLINE, "russian");
											}
										}
										else
										{
											Renderer::g_Verdana->Print(SubMenuTextX + (BoxWidth - 42), SubMenuTextY,
												255, 255, 255, 255, FL_OUTLINE, "%d", *SubmEntry[i].iValue);
										}
									}
								}
							}
						}

						SubMenuBoxOutlineY += BoxHeight + 1;
						SubMenuBoxY += BoxHeight + 1;
						SubMenuTextY += BoxHeight + 1;

						if (SubmEntry[i].Space)
						{
							SubMenuBoxOutlineY += BoxHeight + 1;
							SubMenuBoxY += BoxHeight + 1;
							SubMenuTextY += BoxHeight + 1;
						}
					}
				}

				x += BoxWidth + 1;

				int HeadSubSubMenuBoxX = x + 1;
				int HeadSubSubSubMenuBoxY = y + 1;

				if (SubSubMenu)
				{
					int SubSubMenuBoxOutlineY = HeadY + BoxHeight + 2;
					int SubSubMenuBoxX = x + 1;
					int SubSubMenuBoxY = SubSubMenuBoxOutlineY + 1;
					int SubSubMenuTextX = SubSubMenuBoxX + 6;
					int SubSubMenuTextY = SubSubMenuBoxY + int(HeadBoxHeight / 2.0f) + 4;

					for (int i = 0; i < SS_EntrySize; ++i)
					{
						Renderer::g_Drawing->Box(x, SubSubMenuBoxOutlineY, BoxWidth, BoxHeight, 1,
							BoxOutlineColor[0], BoxOutlineColor[1], BoxOutlineColor[2], BoxOutlineColor[3]);

						Renderer::g_Drawing->FillArea(SubSubMenuBoxX, SubSubMenuBoxY, HeadBoxWidth,
							HeadBoxHeight, BoxColor[0], BoxColor[1], BoxColor[2], BoxColor[3]);

						if (i == SS_EntryPos)
						{
							Renderer::g_Drawing->FillArea(SubSubMenuBoxX, SubSubMenuBoxY, HeadBoxWidth,
								HeadBoxHeight, 255, 93, 0, BoxSelectColor[3]);

							Renderer::g_Drawing->FillArea(SubSubMenuBoxX, SubSubMenuBoxY, 2, HeadBoxHeight,
								255, 93, 0, 200);

							if (InputString)
							{
								if (SubSubmEntry[SS_EntryPos].String)
								{
									Renderer::g_Drawing->FillArea(SubSubMenuTextX + (BoxWidth - 102),
										SubSubMenuTextY - 11, 92, 15, 0, 0, 0, 200);
								}
								else
								{
									Renderer::g_Drawing->FillArea(SubSubMenuTextX + (BoxWidth - 42),
										SubSubMenuTextY - 11, 32, 15, 0, 0, 0, 200);
								}
							}
						}

						for (int a = 0; a < MAX_NAME_CHAR; ++a)
						{
							SubSubmEntry[i].Name[a] ^= SUBM_ENTRY_KEY;
						}

						Renderer::g_Verdana->Print(SubSubMenuTextX, SubSubMenuTextY, TextColor[0],
							TextColor[1], TextColor[2], 255, FL_OUTLINE, SubSubmEntry[i].Name);

						if (SubSubmEntry[i].String)
						{
							char* StringKey = Files::KeyToString(*SubSubmEntry[i].kValue);

							if (!InputString || i != SS_EntryPos)
							{
								Renderer::g_Verdana->Print(SubSubMenuTextX + int((BoxWidth - (42 + lstrlen(StringKey) * 4.2f))),
									SubSubMenuTextY, 255, 255, 255, 255, FL_OUTLINE, StringKey);
							}
							else
							{
								Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 100),
									SubSubMenuTextY, 255, 255, 255, 255, FL_OUTLINE, String);
							}
						}
						else
						{
							if (SubSubmEntry[i].Auto)
							{
								if (!SubSubmEntry[i].Float)
								{
									if (!SubSubmEntry[i].iMin)
									{
										if (*SubSubmEntry[i].iValue == SubSubmEntry[i].iMin)
										{
											Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42),
												SubSubMenuTextY, 255, 80, 80, 255, FL_OUTLINE, "off");
										}
										else if (*SubSubmEntry[i].iValue == SubSubmEntry[i].iMax)
										{
											Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42),
												SubSubMenuTextY, 80, 255, 80, 255, FL_OUTLINE, "auto");
										}
										else
										{
											Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42),
												SubSubMenuTextY, 80, 255, 80, 255, FL_OUTLINE, "%d", *SubSubmEntry[i].iValue);
										}
									}
									else
									{
										if (*SubSubmEntry[i].iValue == SubSubmEntry[i].iMax)
										{
											Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42),
												SubSubMenuTextY, 80, 255, 80, 255, FL_OUTLINE, "auto");
										}
										else
										{
											Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42),
												SubSubMenuTextY, 80, 255, 80, 255, FL_OUTLINE, "%d", *SubSubmEntry[i].iValue);
										}
									}
								}
							}
							else
							{
								if (SubSubmEntry[i].Float)
								{
									if (!InputString || i != SS_EntryPos)
									{
										Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42), SubSubMenuTextY,
											255, 255, 255, 255, FL_OUTLINE, "%.2f", *SubSubmEntry[i].flValue);
									}
									else
									{
										Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42), SubSubMenuTextY,
											255, 255, 255, 255, FL_OUTLINE, "%s", String);
									}
								}
								else
								{
									if (SubSubmEntry[i].Switch)
									{
										*SubSubmEntry[i].bValue ?
											Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42),
												SubSubMenuTextY, 80, 255, 80, 255, FL_OUTLINE, "on") :

											Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42),
												SubSubMenuTextY, 255, 80, 80, 255, FL_OUTLINE, "off");
									}
									else
									{
										if (!SubSubmEntry[i].iMin && (SubSubmEntry[i].iMax == 2 || SubSubmEntry[i].iMax == 4))
										{
											*SubSubmEntry[i].iValue ?
												Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42),
													SubSubMenuTextY, 80, 255, 80, 255, FL_OUTLINE, "%d", *SubSubmEntry[i].iValue) :

												Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42),
													SubSubMenuTextY, 255, 80, 80, 255, FL_OUTLINE, "off");
										}
										else if (SubSubmEntry[i].iMin == ENGLISH && SubSubmEntry[i].iMax == RUSSIAN)
										{
											if (*SubSubmEntry[i].iValue == ENGLISH)
											{
												Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 60),
													SubSubMenuTextY, 255, 255, 255, 255, FL_OUTLINE, "english");
											}
											else if (*SubSubmEntry[i].iValue == RUSSIAN)
											{
												Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 60),
													SubSubMenuTextY, 255, 255, 255, 255, FL_OUTLINE, "russian");
											}
										}
										else if (SubSubmEntry[i].iMin == DOWN && SubSubmEntry[i].iMax == UP)
										{
											if (*SubSubmEntry[i].iValue == DOWN)
											{
												Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42),
													SubSubMenuTextY, 255, 255, 255, 255, FL_OUTLINE, "down");
											}
											else if (*SubSubmEntry[i].iValue == UP)
											{
												Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42),
													SubSubMenuTextY, 255, 255, 255, 255, FL_OUTLINE, "up");
											}
										}
										else
										{
											if (!InputString || i != SS_EntryPos)
											{
												Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42), SubSubMenuTextY,
													255, 255, 255, 255, FL_OUTLINE, "%d", *SubSubmEntry[i].iValue);
											}
											else
											{
												Renderer::g_Verdana->Print(SubSubMenuTextX + (BoxWidth - 42), SubSubMenuTextY,
													255, 255, 255, 255, FL_OUTLINE, String);
											}
										}
									}
								}
							}
						}

						SubSubMenuBoxOutlineY += BoxHeight + 1;
						SubSubMenuBoxY += BoxHeight + 1;
						SubSubMenuTextY += BoxHeight + 1;

						if (SubSubmEntry[i].Space)
						{
							SubSubMenuBoxOutlineY += BoxHeight + 1;
							SubSubMenuBoxY += BoxHeight + 1;
							SubSubMenuTextY += BoxHeight + 1;
						}
					}
				}
			}

			void Menu::SetAimBotPistolsSettings()
			{
				BYTE PistolsList[] = { 1, 10, 11, 16, 17 };

				for (int i = 0; i < sizeof(PistolsList); ++i)
				{
					g_Vars.Weapons[PistolsList[i]].Aim = g_Vars.Weapons[26].Aim;
					g_Vars.Weapons[PistolsList[i]].BulletControl[0] = g_Vars.Weapons[26].BulletControl[0];
					g_Vars.Weapons[PistolsList[i]].BulletControl[1] = g_Vars.Weapons[26].BulletControl[1];
					g_Vars.Weapons[PistolsList[i]].HitBoxNearest = g_Vars.Weapons[26].HitBoxNearest;
					g_Vars.Weapons[PistolsList[i]].HitBox = g_Vars.Weapons[26].HitBox;
					g_Vars.Weapons[PistolsList[i]].Prediction = g_Vars.Weapons[26].Prediction;
					g_Vars.Weapons[PistolsList[i]].FOV = g_Vars.Weapons[26].FOV;
					g_Vars.Weapons[PistolsList[i]].Smooth = g_Vars.Weapons[26].Smooth;
					g_Vars.Weapons[PistolsList[i]].Delay = g_Vars.Weapons[26].Delay;
					g_Vars.Weapons[PistolsList[i]].DelayType = g_Vars.Weapons[26].DelayType;
					g_Vars.Weapons[PistolsList[i]].Recoil = g_Vars.Weapons[26].Recoil;
					g_Vars.Weapons[PistolsList[i]].RecoilPrediction = g_Vars.Weapons[26].RecoilPrediction;
					g_Vars.Weapons[PistolsList[i]].RecoilFOV = g_Vars.Weapons[26].RecoilFOV;
					g_Vars.Weapons[PistolsList[i]].RecoilSmooth = g_Vars.Weapons[26].RecoilSmooth;
				}
			}

			void Menu::SetAimBotRiflesSettings()
			{
				BYTE RiflesList[] = { 7, 8, 12, 14, 15, 19, 20, 21, 22, 23, 27, 28, 30 };

				for (int i = 0; i < sizeof(RiflesList); ++i)
				{
					g_Vars.Weapons[RiflesList[i]].Aim = g_Vars.Weapons[28].Aim;
					g_Vars.Weapons[RiflesList[i]].BulletControl[0] = g_Vars.Weapons[28].BulletControl[0];
					g_Vars.Weapons[RiflesList[i]].BulletControl[1] = g_Vars.Weapons[28].BulletControl[1];
					g_Vars.Weapons[RiflesList[i]].HitBoxNearest = g_Vars.Weapons[28].HitBoxNearest;
					g_Vars.Weapons[RiflesList[i]].HitBox = g_Vars.Weapons[28].HitBox;
					g_Vars.Weapons[RiflesList[i]].Prediction = g_Vars.Weapons[28].Prediction;
					g_Vars.Weapons[RiflesList[i]].FOV = g_Vars.Weapons[28].FOV;
					g_Vars.Weapons[RiflesList[i]].Smooth = g_Vars.Weapons[28].Smooth;
					g_Vars.Weapons[RiflesList[i]].Delay = g_Vars.Weapons[28].Delay;
					g_Vars.Weapons[RiflesList[i]].DelayType = g_Vars.Weapons[28].DelayType;
					g_Vars.Weapons[RiflesList[i]].Recoil = g_Vars.Weapons[28].Recoil;
					g_Vars.Weapons[RiflesList[i]].RecoilPrediction = g_Vars.Weapons[28].RecoilPrediction;
					g_Vars.Weapons[RiflesList[i]].RecoilFOV = g_Vars.Weapons[28].RecoilFOV;
					g_Vars.Weapons[RiflesList[i]].RecoilSmooth = g_Vars.Weapons[28].RecoilSmooth;
				}
			}

			void Menu::SetAimBotSnipersSettings()
			{
				BYTE SnipersList[] = { 3, 18, 24, 13 };

				for (int i = 0; i < sizeof(SnipersList); ++i)
				{
					g_Vars.Weapons[SnipersList[i]].Aim = g_Vars.Weapons[18].Aim;
					g_Vars.Weapons[SnipersList[i]].BulletControl[0] = g_Vars.Weapons[18].BulletControl[0];
					g_Vars.Weapons[SnipersList[i]].BulletControl[1] = g_Vars.Weapons[18].BulletControl[1];
					g_Vars.Weapons[SnipersList[i]].HitBoxNearest = g_Vars.Weapons[18].HitBoxNearest;
					g_Vars.Weapons[SnipersList[i]].HitBox = g_Vars.Weapons[18].HitBox;
					g_Vars.Weapons[SnipersList[i]].Prediction = g_Vars.Weapons[18].Prediction;
					g_Vars.Weapons[SnipersList[i]].FOV = g_Vars.Weapons[18].FOV;
					g_Vars.Weapons[SnipersList[i]].Smooth = g_Vars.Weapons[18].Smooth;
					g_Vars.Weapons[SnipersList[i]].Delay = g_Vars.Weapons[18].Delay;
					g_Vars.Weapons[SnipersList[i]].DelayType = g_Vars.Weapons[18].DelayType;
					g_Vars.Weapons[SnipersList[i]].Recoil = g_Vars.Weapons[18].Recoil;
					g_Vars.Weapons[SnipersList[i]].RecoilPrediction = g_Vars.Weapons[18].RecoilPrediction;
					g_Vars.Weapons[SnipersList[i]].RecoilFOV = g_Vars.Weapons[18].RecoilFOV;
					g_Vars.Weapons[SnipersList[i]].RecoilSmooth = g_Vars.Weapons[18].RecoilSmooth;
				}
			}

			void Menu::SetTriggerBotPistolsSettings()
			{
				BYTE PistolsList[] = { 1, 10, 11, 16, 17 };

				for (int i = 0; i < sizeof(PistolsList); ++i)
				{
					g_Vars.TriggerWeapons[PistolsList[i]].Trigger = g_Vars.TriggerWeapons[26].Trigger;
					g_Vars.TriggerWeapons[PistolsList[i]].OnlyHead = g_Vars.TriggerWeapons[26].OnlyHead;
					g_Vars.TriggerWeapons[PistolsList[i]].ProSpread = g_Vars.TriggerWeapons[26].ProSpread;
				}
			}

			void Menu::SetTriggerBotRiflesSettings()
			{
				BYTE RiflesList[] = { 7, 8, 12, 14, 15, 19, 20, 21, 22, 23, 27, 28, 30 };

				for (int i = 0; i < sizeof(RiflesList); ++i)
				{
					g_Vars.TriggerWeapons[RiflesList[i]].Trigger = g_Vars.TriggerWeapons[28].Trigger;
					g_Vars.TriggerWeapons[RiflesList[i]].OnlyHead = g_Vars.TriggerWeapons[28].OnlyHead;
					g_Vars.TriggerWeapons[RiflesList[i]].ProSpread = g_Vars.TriggerWeapons[28].ProSpread;
				}
			}

			void Menu::SetTriggerBotSnipersSettings()
			{
				BYTE SnipersList[] = { 3, 18, 24, 13 };

				for (int i = 0; i < sizeof(SnipersList); ++i)
				{
					g_Vars.TriggerWeapons[SnipersList[i]].Trigger = g_Vars.TriggerWeapons[18].Trigger;
					g_Vars.TriggerWeapons[SnipersList[i]].OnlyHead = g_Vars.TriggerWeapons[18].OnlyHead;
					g_Vars.TriggerWeapons[SnipersList[i]].ProSpread = g_Vars.TriggerWeapons[18].ProSpread;
				}
			}

			void Menu::Add(const char* Name, bool Space, bool Function)
			{
				Utils::native_memset(MenuEntry[M_EntrySize].Name, sizeof(M_Entry::Name), 0);

				lstrcpy(MenuEntry[M_EntrySize].Name, Name);

				for (int i = 0; i < MAX_NAME_CHAR; ++i)
				{
					MenuEntry[M_EntrySize].Name[i] ^= MENU_ENTRY_KEY;
				}

				MenuEntry[M_EntrySize].Space = Space;
				MenuEntry[M_EntrySize].Function = Function;

				++M_EntrySize;
			}

			void Menu::AddSubFloat(const char* Name, float* Value, float Min, float Max, float Step,
				bool Float, bool Space, bool Switch, bool Active, bool Sub, bool Auto, BYTE R, BYTE G, BYTE B)
			{
				Utils::native_memset(SubmEntry[S_EntrySize].Name, sizeof(S_Entry::Name), 0);

				lstrcpy(SubmEntry[S_EntrySize].Name, Name);

				for (int i = 0; i < MAX_NAME_CHAR; ++i)
				{
					SubmEntry[S_EntrySize].Name[i] ^= SUBM_ENTRY_KEY;
				}

				SubmEntry[S_EntrySize].flValue = Value;
				SubmEntry[S_EntrySize].flMin = Min;
				SubmEntry[S_EntrySize].flMax = Max;
				SubmEntry[S_EntrySize].flStep = Step;
				SubmEntry[S_EntrySize].Float = Float;
				SubmEntry[S_EntrySize].Space = Space;
				SubmEntry[S_EntrySize].Switch = Switch;
				SubmEntry[S_EntrySize].Active = Active;
				SubmEntry[S_EntrySize].Sub = Sub;
				SubmEntry[S_EntrySize].Auto = Auto;

				SubmEntry[S_EntrySize].Color[0] = R;
				SubmEntry[S_EntrySize].Color[1] = G;
				SubmEntry[S_EntrySize].Color[2] = B;

				++S_EntrySize;
			}

			void Menu::AddSubInt(const char* Name, int* Value, int Min, int Max, int Step,
				bool Float, bool Space, bool Switch, bool Active, bool Sub, bool Auto, BYTE R, BYTE G, BYTE B)
			{
				Utils::native_memset(SubmEntry[S_EntrySize].Name, sizeof(S_Entry::Name), 0);

				lstrcpy(SubmEntry[S_EntrySize].Name, Name);

				for (int i = 0; i < MAX_NAME_CHAR; ++i)
				{
					SubmEntry[S_EntrySize].Name[i] ^= SUBM_ENTRY_KEY;
				}

				SubmEntry[S_EntrySize].iValue = Value;
				SubmEntry[S_EntrySize].iMin = Min;
				SubmEntry[S_EntrySize].iMax = Max;
				SubmEntry[S_EntrySize].iStep = Step;
				SubmEntry[S_EntrySize].Float = Float;
				SubmEntry[S_EntrySize].Space = Space;
				SubmEntry[S_EntrySize].Switch = Switch;
				SubmEntry[S_EntrySize].Active = Active;
				SubmEntry[S_EntrySize].Sub = Sub;
				SubmEntry[S_EntrySize].Auto = Auto;

				SubmEntry[S_EntrySize].Color[0] = R;
				SubmEntry[S_EntrySize].Color[1] = G;
				SubmEntry[S_EntrySize].Color[2] = B;

				++S_EntrySize;
			}

			void Menu::AddSubBool(const char* Name, bool* Value, bool Float, bool Space,
				bool Switch, bool Active, bool Sub, bool Auto, BYTE R, BYTE G, BYTE B)
			{
				Utils::native_memset(SubmEntry[S_EntrySize].Name, sizeof(S_Entry::Name), 0);

				lstrcpy(SubmEntry[S_EntrySize].Name, Name);

				for (int i = 0; i < MAX_NAME_CHAR; ++i)
				{
					SubmEntry[S_EntrySize].Name[i] ^= SUBM_ENTRY_KEY;
				}

				SubmEntry[S_EntrySize].bValue = Value;
				SubmEntry[S_EntrySize].Float = Float;
				SubmEntry[S_EntrySize].Space = Space;
				SubmEntry[S_EntrySize].Switch = Switch;
				SubmEntry[S_EntrySize].Active = Active;
				SubmEntry[S_EntrySize].Sub = Sub;
				SubmEntry[S_EntrySize].Auto = Auto;

				SubmEntry[S_EntrySize].Color[0] = R;
				SubmEntry[S_EntrySize].Color[1] = G;
				SubmEntry[S_EntrySize].Color[2] = B;

				++S_EntrySize;
			}

			void Menu::AddSubSubFloat(const char* Name, float* Value, float Min, float Max,
				float Step, bool Float, bool Space, bool Switch, bool Auto, bool String)
			{
				Utils::native_memset(SubSubmEntry[SS_EntrySize].Name, sizeof(SS_Entry::Name), 0);

				lstrcpy(SubSubmEntry[SS_EntrySize].Name, Name);

				for (int i = 0; i < MAX_NAME_CHAR; ++i)
				{
					SubSubmEntry[SS_EntrySize].Name[i] ^= SUBM_ENTRY_KEY;
				}

				SubSubmEntry[SS_EntrySize].flValue = Value;
				SubSubmEntry[SS_EntrySize].flMin = Min;
				SubSubmEntry[SS_EntrySize].flMax = Max;
				SubSubmEntry[SS_EntrySize].flStep = Step;
				SubSubmEntry[SS_EntrySize].Float = Float;
				SubSubmEntry[SS_EntrySize].Space = Space;
				SubSubmEntry[SS_EntrySize].Switch = Switch;
				SubSubmEntry[SS_EntrySize].Auto = Auto;
				SubSubmEntry[SS_EntrySize].String = String;

				++SS_EntrySize;
			}

			void Menu::AddSubSubInt(const char* Name, int* Value, int Min, int Max,
				int Step, bool Float, bool Space, bool Switch, bool Auto, bool String)
			{
				Utils::native_memset(SubSubmEntry[SS_EntrySize].Name, sizeof(SS_Entry::Name), 0);

				lstrcpy(SubSubmEntry[SS_EntrySize].Name, Name);

				for (int i = 0; i < MAX_NAME_CHAR; ++i)
				{
					SubSubmEntry[SS_EntrySize].Name[i] ^= SUBM_ENTRY_KEY;
				}

				SubSubmEntry[SS_EntrySize].iValue = Value;
				SubSubmEntry[SS_EntrySize].iMin = Min;
				SubSubmEntry[SS_EntrySize].iMax = Max;
				SubSubmEntry[SS_EntrySize].iStep = Step;
				SubSubmEntry[SS_EntrySize].Float = Float;
				SubSubmEntry[SS_EntrySize].Space = Space;
				SubSubmEntry[SS_EntrySize].Switch = Switch;
				SubSubmEntry[SS_EntrySize].Auto = Auto;
				SubSubmEntry[SS_EntrySize].String = String;

				++SS_EntrySize;
			}

			void Menu::AddSubSubKey(const char* Name, BYTE* Value,
				bool Float, bool Space, bool Switch, bool Auto, bool String)
			{
				Utils::native_memset(SubSubmEntry[SS_EntrySize].Name, sizeof(SS_Entry::Name), 0);

				lstrcpy(SubSubmEntry[SS_EntrySize].Name, Name);

				for (int i = 0; i < MAX_NAME_CHAR; ++i)
				{
					SubSubmEntry[SS_EntrySize].Name[i] ^= SUBM_ENTRY_KEY;
				}

				SubSubmEntry[SS_EntrySize].kValue = Value;
				SubSubmEntry[SS_EntrySize].Float = Float;
				SubSubmEntry[SS_EntrySize].Space = Space;
				SubSubmEntry[SS_EntrySize].Switch = Switch;
				SubSubmEntry[SS_EntrySize].Auto = Auto;
				SubSubmEntry[SS_EntrySize].String = String;

				++SS_EntrySize;
			}

			void Menu::AddSubSubBool(const char* Name, bool* Value,
				bool Float, bool Space, bool Switch, bool Auto, bool String)
			{
				Utils::native_memset(SubSubmEntry[SS_EntrySize].Name, sizeof(SS_Entry::Name), 0);

				lstrcpy(SubSubmEntry[SS_EntrySize].Name, Name);

				for (int i = 0; i < MAX_NAME_CHAR; ++i)
				{
					SubSubmEntry[SS_EntrySize].Name[i] ^= SUBM_ENTRY_KEY;
				}

				SubSubmEntry[SS_EntrySize].bValue = Value;
				SubSubmEntry[SS_EntrySize].Float = Float;
				SubSubmEntry[SS_EntrySize].Space = Space;
				SubSubmEntry[SS_EntrySize].Switch = Switch;
				SubSubmEntry[SS_EntrySize].Auto = Auto;
				SubSubmEntry[SS_EntrySize].String = String;

				++SS_EntrySize;
			}

			void Menu::Clear()
			{
				for (int i = 0; i < M_EntrySize; ++i)
				{
					Utils::native_memset(&MenuEntry[i].Name, sizeof(M_Entry::Name), 0);
				}

				for (int i = 0; i < S_EntrySize; ++i)
				{
					Utils::native_memset(&MenuEntry[i].Name, sizeof(S_Entry::Name), 0);

					SubmEntry[i].flValue = 0;
					SubmEntry[i].flMin = 0.0f;
					SubmEntry[i].flMax = 0.0f;
					SubmEntry[i].flStep = 0.0f;

					SubmEntry[i].iValue = 0;
					SubmEntry[i].iMin = 0;
					SubmEntry[i].iMax = 0;
					SubmEntry[i].iStep = 0;

					SubmEntry[i].bValue = 0;

					SubmEntry[i].Float = false;
					SubmEntry[i].Space = false;
					SubmEntry[i].Switch = false;
					SubmEntry[i].Active = false;
					SubmEntry[i].Sub = false;
					SubmEntry[i].Auto = false;

					SubmEntry[i].Color[0] = 0;
					SubmEntry[i].Color[1] = 0;
					SubmEntry[i].Color[2] = 0;
				}

				for (int i = 0; i < SS_EntrySize; ++i)
				{
					Utils::native_memset(&MenuEntry[i].Name, sizeof(SS_Entry::Name), 0);

					SubSubmEntry[i].flValue = 0;
					SubSubmEntry[i].flMin = 0.0f;
					SubSubmEntry[i].flMax = 0.0f;
					SubSubmEntry[i].flStep = 0.0f;

					SubSubmEntry[i].iValue = 0;
					SubSubmEntry[i].iMin = 0;
					SubSubmEntry[i].iMax = 0;
					SubSubmEntry[i].iStep = 0;

					SubSubmEntry[i].bValue = 0;

					SubSubmEntry[i].Float = false;
					SubSubmEntry[i].Space = false;
					SubSubmEntry[i].Switch = false;
					SubSubmEntry[i].Auto = false;
					SubSubmEntry[i].String = false;
				}

				M_EntrySize = 0;
				S_EntrySize = 0;
				SS_EntrySize = 0;
			}

			void Menu::HUD_Redraw()
			{
				SetSettings();
				DrawFadeAnimation();
				DrawMenu(20, 8);
			}

			void Menu::HUD_Key_Event(bool& RetFlag, int& keynum)
			{
				RetFlag = false;

				if (keynum == g_Vars.Menu.Key)
				{
					Visible = !Visible;

					VisibleAnimation = true;
				}

				if (!Visible) return;

				if (!SubMenu)
				{
					if (keynum == K_ENTER || keynum == K_RIGHTARROW)
					{
						if (MenuEntry[M_EntryPos].Function)
						{
							if (keynum == K_ENTER)
							{
								if (M_EntryPos == LOAD_SETTINGS)
								{
									Files::ReloadSettings();

									if (g_Vars.Main.Language == ENGLISH)
									{
										ConsolePrintColor(100, 255, 200, HPP);
										ConsolePrintColor(200, 255, 200, SETTINGS_RELOADED_ENG);
									}
									else if (g_Vars.Main.Language == RUSSIAN)
									{
										ConsolePrintColor(100, 255, 200, HPP);
										ConsolePrintColor(200, 255, 200, SETTINGS_RELOADED_RUS);
									}

									SDK::Interfaces::g_pEngine->pfnPlaySoundByName("vox/loading.wav", 1);
								}
								else if (M_EntryPos == SAVE_SETTINGS)
								{
									Files::SaveSettings();

									if (g_Vars.Main.Language == ENGLISH)
									{
										ConsolePrintColor(100, 255, 200, HPP);
										ConsolePrintColor(200, 255, 200, SETTINGS_SAVED_ENG);
									}
									else if (g_Vars.Main.Language == RUSSIAN)
									{
										ConsolePrintColor(100, 255, 200, HPP);
										ConsolePrintColor(200, 255, 200, SETTINGS_SAVED_RUS);
									}

									SDK::Interfaces::g_pEngine->pfnPlaySoundByName("vox/save.wav", 1);
								}
							}
						}
						else
						{
							S_EntryPos = 0;

							SubMenu = true;
						}
					}
					else if (keynum == K_UPARROW)
					{
						if (M_EntryPos > 0)
							--M_EntryPos;
					}
					else if (keynum == K_DOWNARROW)
					{
						if (M_EntryPos < (M_EntrySize - 1))
							++M_EntryPos;
					}
					else if (keynum == K_BACKSPACE)
					{
						Visible = false;
					}
				}
				else
				{
					if (!SubSubMenu)
					{
						if (SubmEntry[S_EntryPos].Sub && (keynum == K_ENTER || keynum == K_RIGHTARROW || keynum == K_LEFTARROW))
						{
							if (keynum == K_LEFTARROW)
							{
								return;
							}

							if (keynum == K_ENTER || keynum == K_RIGHTARROW)
							{
								if (SubmEntry[S_EntryPos].Active)
								{
									SS_EntryPos = 0;

									SubSubMenu = true;
								}
							}
						}
						else if (keynum == K_UPARROW)
						{
							if (S_EntryPos > 0)
								--S_EntryPos;
							else
								SubMenu = false;
						}
						else if (keynum == K_DOWNARROW)
						{
							if (S_EntryPos < (S_EntrySize - 1))
								++S_EntryPos;
						}
						else if (keynum == K_LEFTARROW)
						{
							if (SubmEntry[S_EntryPos].Float)
							{
								*SubmEntry[S_EntryPos].flValue -= SubmEntry[S_EntryPos].flStep;

								if (*SubmEntry[S_EntryPos].flValue < SubmEntry[S_EntryPos].flMin)
									*SubmEntry[S_EntryPos].flValue = SubmEntry[S_EntryPos].flMin;
							}
							else
							{
								if (!SubmEntry[S_EntryPos].Switch)
								{
									*SubmEntry[S_EntryPos].iValue -= SubmEntry[S_EntryPos].iStep;

									if (*SubmEntry[S_EntryPos].iValue < SubmEntry[S_EntryPos].iMin)
										*SubmEntry[S_EntryPos].iValue = SubmEntry[S_EntryPos].iMin;
								}
								else
									*SubmEntry[S_EntryPos].bValue = false;
							}
						}
						else if (keynum == K_RIGHTARROW)
						{
							if (SubmEntry[S_EntryPos].Float)
							{
								*SubmEntry[S_EntryPos].flValue += SubmEntry[S_EntryPos].flStep;

								if (*SubmEntry[S_EntryPos].flValue > SubmEntry[S_EntryPos].flMax)
									*SubmEntry[S_EntryPos].flValue = SubmEntry[S_EntryPos].flMax;
							}
							else
							{
								if (!SubmEntry[S_EntryPos].Switch)
								{
									*SubmEntry[S_EntryPos].iValue += SubmEntry[S_EntryPos].iStep;

									if (*SubmEntry[S_EntryPos].iValue > SubmEntry[S_EntryPos].iMax)
										*SubmEntry[S_EntryPos].iValue = SubmEntry[S_EntryPos].iMax;
								}
								else
									*SubmEntry[S_EntryPos].bValue = true;
							}
						}
						else if (keynum == K_BACKSPACE)
						{
							SubMenu = false;
						}
					}
					else
					{
						static int i;

						if (keynum == K_ENTER)
						{
							if (SubSubmEntry[SS_EntryPos].String)
							{
								if (InputString)
								{
									*SubSubmEntry[SS_EntryPos].kValue = Files::StringToKey(String);

									i = 0;

									Utils::native_memset(String, sizeof(String), 0);

									InputString = false;
								}
								else
								{
									InputString = true;
								}
							}
							else
							{
								if (!SubSubmEntry[SS_EntryPos].Switch && !SubSubmEntry[SS_EntryPos].Auto)
								{
									if (InputString)
									{
										if (SubSubmEntry[SS_EntryPos].Float)
										{
											*SubSubmEntry[SS_EntryPos].flValue = (float)atof(String);
										}
										else
										{
											*SubSubmEntry[SS_EntryPos].iValue = atoi(String);
										}

										i = 0;

										Utils::native_memset(String, sizeof(String), 0);

										InputString = false;
									}
									else
									{
										InputString = true;
									}
								}
							}
						}

						if (InputString)
						{
							if (keynum == K_BACKSPACE)
							{
								if (i)
								{
									--i;
									String[i] = ' ';
								}

								return;
							}
							else if (keynum == K_LEFTARROW)
							{
								if (i)
								{
									--i;

									if (i < 0)
										i = 0;
								}

								return;
							}
							else if (keynum == K_RIGHTARROW)
							{
								if (i)
								{
									++i;

									if (i > lstrlen(String))
										i = lstrlen(String);
								}

								return;
							}

							if (i == (SubSubmEntry[SS_EntryPos].String ? 10 : 5)) return;

							if (SubSubmEntry[SS_EntryPos].String)
							{
								switch (keynum)
								{
								case K_0: String[i] = '0'; ++i; break;
								case K_1: String[i] = '1'; ++i; break;
								case K_2: String[i] = '2'; ++i; break;
								case K_3: String[i] = '3'; ++i; break;
								case K_4: String[i] = '4'; ++i; break;
								case K_5: String[i] = '5'; ++i; break;
								case K_6: String[i] = '6'; ++i; break;
								case K_7: String[i] = '7'; ++i; break;
								case K_8: String[i] = '8'; ++i; break;
								case K_9: String[i] = '9'; ++i; break;
								case K_POINT: String[i] = '.'; ++i; break;
								case K_COMMA: String[i] = ','; ++i; break;
								case K_BRACKET_LEFT: String[i] = '['; ++i; break;
								case K_BRACKET_RIGHT: String[i] = ']'; ++i; break;
								case K_A: String[i] = 'A'; ++i; break;
								case K_B: String[i] = 'B'; ++i; break;
								case K_C: String[i] = 'C'; ++i; break;
								case K_D: String[i] = 'D'; ++i; break;
								case K_E: String[i] = 'E'; ++i; break;
								case K_F: String[i] = 'F'; ++i; break;
								case K_G: String[i] = 'G'; ++i; break;
								case K_H: String[i] = 'H'; ++i; break;
								case K_I: String[i] = 'I'; ++i; break;
								case K_J: String[i] = 'J'; ++i; break;
								case K_K: String[i] = 'K'; ++i; break;
								case K_L: String[i] = 'L'; ++i; break;
								case K_M: String[i] = 'M'; ++i; break;
								case K_N: String[i] = 'N'; ++i; break;
								case K_O: String[i] = 'O'; ++i; break;
								case K_P: String[i] = 'P'; ++i; break;
								case K_Q: String[i] = 'Q'; ++i; break;
								case K_R: String[i] = 'R'; ++i; break;
								case K_S: String[i] = 'S'; ++i; break;
								case K_T: String[i] = 'T'; ++i; break;
								case K_U: String[i] = 'U'; ++i; break;
								case K_V: String[i] = 'V'; ++i; break;
								case K_W: String[i] = 'W'; ++i; break;
								case K_X: String[i] = 'X'; ++i; break;
								case K_Y: String[i] = 'Y'; ++i; break;
								case K_Z: String[i] = 'Z'; ++i; break;
								}
							}
							else
							{
								switch (keynum)
								{
								case K_0: String[i] = '0'; ++i; break;
								case K_1: String[i] = '1'; ++i; break;
								case K_2: String[i] = '2'; ++i; break;
								case K_3: String[i] = '3'; ++i; break;
								case K_4: String[i] = '4'; ++i; break;
								case K_5: String[i] = '5'; ++i; break;
								case K_6: String[i] = '6'; ++i; break;
								case K_7: String[i] = '7'; ++i; break;
								case K_8: String[i] = '8'; ++i; break;
								case K_9: String[i] = '9'; ++i; break;
								case K_POINT: String[i] = '.'; ++i; break;
								}
							}
						}

						if (!InputString)
						{
							if (keynum == K_UPARROW)
							{
								if (SS_EntryPos > 0)
									--SS_EntryPos;
								else
									SubSubMenu = false;
							}
							else if (keynum == K_DOWNARROW)
							{
								if (SS_EntryPos < (SS_EntrySize - 1))
									++SS_EntryPos;
							}
							else if (keynum == K_LEFTARROW)
							{
								if (SubSubmEntry[SS_EntryPos].Float)
								{
									*SubSubmEntry[SS_EntryPos].flValue -= SubSubmEntry[SS_EntryPos].flStep;

									if (*SubSubmEntry[SS_EntryPos].flValue < SubSubmEntry[SS_EntryPos].flMin)
										*SubSubmEntry[SS_EntryPos].flValue = SubSubmEntry[SS_EntryPos].flMin;
								}
								else
								{
									if (!SubSubmEntry[SS_EntryPos].Switch)
									{
										*SubSubmEntry[SS_EntryPos].iValue -= SubSubmEntry[SS_EntryPos].iStep;

										if (*SubSubmEntry[SS_EntryPos].iValue < SubSubmEntry[SS_EntryPos].iMin)
											*SubSubmEntry[SS_EntryPos].iValue = SubSubmEntry[SS_EntryPos].iMin;
									}
									else
										*SubSubmEntry[SS_EntryPos].bValue = false;
								}
							}
							else if (keynum == K_RIGHTARROW)
							{
								if (SubSubmEntry[SS_EntryPos].Float)
								{
									*SubSubmEntry[SS_EntryPos].flValue += SubSubmEntry[SS_EntryPos].flStep;

									if (*SubSubmEntry[SS_EntryPos].flValue > SubSubmEntry[SS_EntryPos].flMax)
										*SubSubmEntry[SS_EntryPos].flValue = SubSubmEntry[SS_EntryPos].flMax;
								}
								else
								{
									if (!SubSubmEntry[SS_EntryPos].Switch)
									{
										*SubSubmEntry[SS_EntryPos].iValue += SubSubmEntry[SS_EntryPos].iStep;

										if (*SubSubmEntry[SS_EntryPos].iValue > SubSubmEntry[SS_EntryPos].iMax)
											*SubSubmEntry[SS_EntryPos].iValue = SubSubmEntry[SS_EntryPos].iMax;
									}
									else
										*SubSubmEntry[SS_EntryPos].bValue = true;
								}
							}
							else if (keynum == K_BACKSPACE)
							{
								SubSubMenu = false;
							}

							if (M_EntryPos == AIMBOT)
							{
								if (S_EntryPos == SUBMENU_ENTRY_AIMBOT::PISTOLS && (keynum == K_LEFTARROW || keynum == K_RIGHTARROW))
									SetAimBotPistolsSettings();

								if (S_EntryPos == SUBMENU_ENTRY_AIMBOT::RIFLES && (keynum == K_LEFTARROW || keynum == K_RIGHTARROW))
									SetAimBotRiflesSettings();

								if (S_EntryPos == SUBMENU_ENTRY_AIMBOT::SNIPERS && (keynum == K_LEFTARROW || keynum == K_RIGHTARROW))
									SetAimBotSnipersSettings();
							}
							if (M_EntryPos == TRIGGERBOT)
							{
								if (S_EntryPos == SUBMENU_ENTRY_TRIGGERBOT::TPISTOLS && (keynum == K_LEFTARROW || keynum == K_RIGHTARROW))
									SetTriggerBotPistolsSettings();

								if (S_EntryPos == SUBMENU_ENTRY_TRIGGERBOT::TRIFLES && (keynum == K_LEFTARROW || keynum == K_RIGHTARROW))
									SetTriggerBotRiflesSettings();

								if (S_EntryPos == SUBMENU_ENTRY_TRIGGERBOT::TSNIPERS && (keynum == K_LEFTARROW || keynum == K_RIGHTARROW))
									SetTriggerBotSnipersSettings();
							}
						}
					}
				}

				RetFlag = true;
			}
		}
	}
}