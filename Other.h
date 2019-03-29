#pragma once

#include "Main.h"

namespace Client
{
	namespace Functions
	{
		namespace Visuals
		{

			struct PlayerStruct
			{
				int iIndex;
				bool isAlive;
			};

			class Other
			{
			public:
				
				static void HUD_Redraw();

			private:
				static PlayerStruct Player[33];

				static void DrawAimSpot();
				static void DrawAimFOV();
				static void DrawPunch();
				static void DrawSpread();
				static void NameStealer();
				static void StatusAimBot();
				static void StatusTriggerBot();
			};
		}
	}
}