#pragma once

#include "Main.h"

#include "Info.h"

namespace Renderer
{
	class Drawing
	{
	public:
		void FillArea ( int x, int y, int w, int h, BYTE R, BYTE G, BYTE B, BYTE A );

		Vector vBone[52];

		inline void Box(int x, int y, int w, int h, int lw, BYTE R, BYTE G, BYTE B, BYTE A)
		{
			FillArea(x, y, w, lw, R, G, B, A);
			FillArea(x + w - lw, y + lw, lw, h - lw, R, G, B, A);
			FillArea(x, y + lw, lw, h - lw, R, G, B, A);
			FillArea(x + lw, y + h - lw, w - lw * 2, lw, R, G, B, A);
		}

		inline void BoxRainbow(int x, int y, int w, int h, int lw, BYTE R, BYTE G, BYTE B, BYTE A )
		{
			FillArea(x, y, w, lw, R, G, B, A);
			FillArea(x + w - lw, y + lw, lw, h - lw, R, G, B, A);
			FillArea(x, y + lw, lw, h - lw, R, G, B, A);
			FillArea(x + lw, y + h - lw, w - lw * 2, lw, R, G, B, A);
		}

		inline void BoxOutline ( int x, int y, int w, int h, int lw, BYTE R, BYTE G, BYTE B, BYTE A )
		{
			Box ( x - 1, y - 1, w + 2, h + 2, lw + 2, 0, 0, 0, A );
			Box ( x, y, w, h, lw, R, G, B, A );
		}

		inline void BoxCorner ( int x, int y, int w, int h, int lw, BYTE R, BYTE G, BYTE B, BYTE A )
		{
			FillArea ( x, y, w / 4, lw, R, G, B, A );
			FillArea ( x + w - w / 4, y, w / 4, lw, R, G, B, A );
			FillArea ( x, y + lw, lw, h / 4 - lw, R, G, B, A );
			FillArea ( x, y + h - h / 4, lw, h / 4, R, G, B, A );
			FillArea ( x + w - lw, y + lw, lw, h / 4 - lw, R, G, B, A );
			FillArea ( x + w - lw, y + h - h / 4, lw, h / 4, R, G, B, A );
			FillArea ( x + lw, y + h - lw, w / 4 - lw, lw, R, G, B, A );
			FillArea ( x + w - w / 4, y + h - lw, w / 4 - lw, lw, R, G, B, A );
		}

		inline void BoxCornerOutline ( int x, int y, int w, int h, int lw, BYTE R, BYTE G, BYTE B, BYTE A )
		{
			BoxCorner ( x - 1, y + 1, w, h, lw, 0, 0, 0, A );
			BoxCorner ( x - 1, y - 1, w, h, lw, 0, 0, 0, A );
			BoxCorner ( x + 1, y + 1, w, h, lw, 0, 0, 0, A );
			BoxCorner ( x + 1, y - 1, w, h, lw, 0, 0, 0, A );

			BoxCorner ( x, y, w, h, lw, R, G, B, A );
		}

		inline void Circle ( int x, int y, int rad, int amount, int lw, BYTE R, BYTE G, BYTE B, BYTE A )
		{
			glDisable ( GL_TEXTURE_2D );
			glEnable ( GL_BLEND );
			glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glColor4ub ( R, G, B, A );
			glLineWidth ( GLfloat ( lw ) );
			glBegin ( GL_LINE_LOOP );

			for ( int i = 0; i < amount; ++i )
			{
				double Angle = 2.0 * M_PI * i / amount;
				double X = rad * cos ( Angle );
				double Y = rad * sin ( Angle );

				glVertex2d ( x + X, y + Y );
			}

			glEnd ( );
			glEnable ( GL_TEXTURE_2D );
			glDisable ( GL_BLEND );
		}

		inline void DrawLine(int x0, int y0, int x1, int y1, int r, int g, int b, int a)
		{
			glPushMatrix();
			glLoadIdentity();
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4ub(r, g, b, 255);
			glLineWidth(1.0);
			glBegin(GL_LINES);
			glVertex2i(x1, y1);
			glVertex2i(x0, y0);
			glEnd();
			glColor3f(1.0f, 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			glPopMatrix();
		}

		inline void DrawCoalBox(int x, int y, int w, int h, BYTE Red, BYTE Green, BYTE Blue, BYTE Alpha)
		{
			int iw = w / 4;
			int ih = h / 1;

			DrawLine(x, y, x + iw, y, Red, Green, Blue, Alpha);
			DrawLine(x + w - iw, y, x + w, y, Red, Green, Blue, Alpha);
			DrawLine(x, y, x, y + ih, Red, Green, Blue, Alpha);
			DrawLine(x + w, y, x + w, y + ih, Red, Green, Blue, Alpha);
			DrawLine(x, y + h, x + iw, y + h, Red, Green, Blue, Alpha);
			DrawLine(x + w - iw, y + h, x + w, y + h, Red, Green, Blue, Alpha);
			DrawLine(x, y + h - ih, x, y + h, Red, Green, Blue, Alpha);
			DrawLine(x + w, y + h - ih, x + w, y + h, Red, Green, Blue, Alpha);

		}

	};

	extern Drawing *g_Drawing;
}