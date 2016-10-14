#include "RenderManager.hpp"

#include <cmath>

#include "WindowManager.hpp"

// Static definitions
// Matrix3F RenderManager::s_TransformScreenSpace = Matrix3F();

RenderManager::RenderManager (const WindowManager& windowManager, Uint32 flags)
{
	trclog("Initializing render manager");

	m_WIDTH = windowManager.GetWidth();
	m_HEIGHT = windowManager.GetHeight();
		
	// Renderer
	m_pRenderer = SDL_CreateRenderer(windowManager.GetWindow(), -1, flags);

	// Main Texture
	m_pTexture = SDL_CreateTexture(m_pRenderer, 
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STATIC,
		m_WIDTH, m_HEIGHT
		);

	// Raw buffer
	m_pPixels = new Uint32[m_WIDTH * m_HEIGHT];

	// Transforms
	// Matrix3F::values_type values = {

	// };

	trclog("Render manager initialized.");
}

RenderManager::~RenderManager ()
{
	trclog("Destroying render manager...");
	
	delete[] m_pPixels;
	SDL_DestroyTexture(m_pTexture);
	SDL_DestroyRenderer(m_pRenderer);

	trclog("Render manager destroyed.");  
}

SDL_Renderer* RenderManager::GetRenderer () const
{
	return m_pRenderer;
}

SDL_Texture* RenderManager::GetTexture () const
{
	return m_pTexture;
}

void RenderManager::Render () const
{
	SDL_UpdateTexture(m_pTexture, 0, m_pPixels, m_WIDTH * sizeof(Uint32));

	SDL_RenderClear(m_pRenderer);
	SDL_RenderCopy(m_pRenderer, m_pTexture, 0, 0);
	SDL_RenderPresent(m_pRenderer);
}

void RenderManager::FillScreenBackground (Uint32 color)
{
	for (int w = 0; w < m_WIDTH; ++w)
	{
		for (int h = 0; h < m_HEIGHT; ++h)
		{
			SetPixel(w, h, color);
		}
	}
}

void RenderManager::DrawLine (float x_s, float y_s, float x_e, float y_e, Uint32 color)
{
	// Transform to screen space
	// PointF P_s = s_TransformScreenSpace * line.start;  
	// PointF P_e = s_TransformScreenSpace * line.end;
	//
	// For now, just multiply by width and height
	x_s *= m_WIDTH;
	y_s *= m_HEIGHT;
	x_e *= m_WIDTH;
	y_e *= m_HEIGHT;

	// console("Start = (" << x_s << ", " << y_s << ")" << "\t" << "End = (" << x_e << ", " << y_e << ") color = " << color);

	// If the start and end are the same, there's nothing else to be done
	if (x_s == x_e && y_s == y_e)
	{
		return;
	}

	// Approximate the line segment and render each discrete point on the line
	float dx = x_e - x_s;
	float dy = y_e - y_s;

	// console("dx = " << dx << "    " << "dy = " << dy);

	// Corner case 1: dy = 0, so dx/dy = n.d
	// Simply fill up every single pixel along the x-axis
	if (dy == 0.0)
	{
		int y = int(y_s);
		if (dx < 0.0)
		{
			for (int x = int(x_s); x > x_e; --x)
			{
				SetPixel(x, y, color);
			}
		}
		else
		{
			for (int x = int(x_s); x < x_e; ++x)
			{
				SetPixel(x, y, color);
			}
		}
	}
	// Corner case 2: dx = 0, so dy/dx = n.d
	// Simply fill up every single pixel along the y-axis
	else if (dx == 0.0)
	{
		int x = int(x_s);
		if (dy < 0.0)
		{
			for (int y = int(y_s); y > y_e; --y)
			{
				SetPixel(x, y, color);
			}
		}
		else
		{
			for (int y = int(y_s); y < y_e; ++y)
			{
				SetPixel(x, y, color);
			}
		}
	}
	// Corner case 3: dx = dy, so dy/dx = 1
	// Rarely occurs, but why not handle it?
	else if (std::abs(dx) == std::abs(dy))
	{
		int x = int(std::round(x_s));
		int y = int(std::round(y_s));

		if (dy > 0.0)
		{
			if (dx > 0.0)
			{
				for (; x < x_e && y < y_e; ++x, ++y)
				{
					SetPixel(x, y, color);
				}
			}
			else // dx < 0
			{
				for (; x > x_e && y < y_e; --x, ++y)
				{
					SetPixel(x, y, color);
				}
			}
		}
		else // dy < 0
		{
			if (dx > 0.0)
			{
				for (; x < x_e && y > y_e; ++x, --y)
				{
					SetPixel(x, y, color);
				}
			}
			else // dx < 0
			{
				for (; x > x_e && y > y_e; --x, --y)
				{
					SetPixel(x, y, color);
				}
			}
		}
	}
	else
	{
		// Now the real (no pun intended) work begins: deal with the octants

		float m = dy/dx;
		// console("m = " << m);

		if (m < -1.0) // |dy| > |dx|, so approximate x component
		{
			m = 1/m;

			if (dy < 0.0) // Octant 0
			{
				std::swap(x_s, x_e);
				std::swap(y_s, y_e);
			}
			// else, Octant 4

			float x = x_s;
			for (int y = int(y_s); y < y_e; ++y, x += m)
			{
				SetPixel(int(std::round(x)), y, color);
			}
		}
		else if (m > 1.0) // |dy| > |dx|, so approximate x component
		{
			m = 1/m;

			if (dy < 0.0) // Octant 7
			{
				std::swap(x_s, x_e);
				std::swap(y_s, y_e);
			}
			// else, Octant 3
			
			float x = x_s;
			for (int y = int(y_s); y < y_e; ++y, x += m)
			{
				SetPixel(int(std::round(x)), y, color);
			}
		}
		else if (m > -1.0 && m < 0.0) // |dy| < |dx|, so approximate y component
		{
			if (dy > 0.0) // Octant 5
			{
				std::swap(x_s, x_e);
				std::swap(y_s, y_e);
			}
			// else, Octant 1
			
			float y = y_s;
			for (int x = int(x_s); x < x_e; ++x, y += m)
			{
				SetPixel(x, int(std::round(y)), color);
			}
		}
		else if (m > 0.0 && m < 1.0) // |dy| < |dx|, so approximate y component
		{
			if (dy < 0.0) // Octant 6
			{
				std::swap(x_s, x_e);
				std::swap(y_s, y_e);
			}
			// else, Octant 2
			
			float y = y_s;
			for (int x = int(x_s); x < x_e; ++x, y += m)
			{
				SetPixel(x, int(std::round(y)), color);
			}
		}
		else
		{
			errlog("Should never reach here.");
			assert(false);
		}
	}

}

void RenderManager::DrawLine (const LineSegment2F& seg, Uint32 color)
{
	// Forget 3D for now

	DrawLine(seg.start.x, seg.start.y, seg.end.x, seg.end.y, color);
}

void RenderManager::DrawPolygon (const Polygon2F& poly, Uint32 color)
{
	// Render each edge of the polygon
	std::vector<LineSegment2F> edges;
	poly.ComputeEdges(edges);
	for (auto& edge : edges)
	{
		DrawLine(edge.start.x, edge.start.y, edge.end.x, edge.end.y, color);
	}
}
