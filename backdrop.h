#pragma once



#include <vector>
#include "ValveSDK/util_vector.h"
#include "Color.hpp"
#include "eSurface.hpp"

class Dot;

extern std::vector<Dot*> Dots;

class Dot
{
public:
	Dot(Vector2D p, Vector2D v)
	{
		RelativePosition = p;
		Velocity = v;

	}
	virtual void Draw()
	{
		g_Surface->DrawSetColor(Color(255, 255, 255, 255));
		g_Surface->DrawFilledRect(RelativePosition.x - 2, RelativePosition.y - 2, RelativePosition.x + 2, RelativePosition.y + 2);
		auto t = std::find(Dots.begin(), Dots.end(), this);
		if (t == Dots.end()) return;
		for (auto i = t; i != Dots.end(); i++)
		{
			if ((*i) == this) continue;
			Vector2D Pos = RelativePosition;
			float Dist = Pos.DistTo((*i)->RelativePosition);
			if (Dist < 128)
			{
				Vector2D Dir = ((*i)->RelativePosition - RelativePosition).Normalize();
				g_Surface->DrawSetColor(Color(69, 140, 230, 255));
				g_Surface->DrawLine(Pos.x, Pos.y, (Pos + Dir * Dist).x, (Pos + Dir * Dist).y);
				//g_csgo.m_surface()->Line(Pos.x, Pos.y, (Pos + Dir * Dist).x, (Pos + Dir * Dist).y, Color(255, 111, 15, 255));

			}
		}
	}

	Vector2D RelativePosition = Vector2D(0, 0);
	Vector2D Velocity;
};

namespace draw
{
	void backdrop();
}