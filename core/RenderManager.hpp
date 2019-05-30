#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "global.hpp"

#include "Color.hpp"
#include "Geometry.hpp"

class WindowManager;

class RenderManager
{
public:
	RenderManager () {};
	RenderManager (const WindowManager& pWindowManager, Uint32 flags=0);
	~RenderManager ();

	SDL_Renderer* GetRenderer () const;
	SDL_Texture* GetTexture () const;

	void SetPixel (size_t index, Uint32 color=Color::Black);
	void SetPixel (size_t x, size_t y, Uint32 color=Color::Black);

	void Render () const;
	void FillScreenBackground (Uint32 color=Color::Black);

	/// All draw functions expect normalized device coordinates of range [0, 1]
	void DrawPoint (PointF const&, Uint32 color=Color::White);
	void DrawLine (float, float, float, float, Uint32 color=Color::White); 
	void DrawLine (const LineSegmentF& seg, Uint32 color=Color::White);
	void DrawPolygon (const PolygonF& poly, Uint32 color=Color::White);

private:
	size_t m_WIDTH;
	size_t m_HEIGHT;

	// We possess ownership of screen pixels, screen texture and screen renderer
	Uint32* m_pPixels;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;
};

inline void RenderManager::SetPixel (size_t index, Uint32 color)
{
	m_pPixels[index] = color;
}

inline void RenderManager::SetPixel (size_t x, size_t y, Uint32 color)
{
	SetPixel(y*m_WIDTH + x, color);
}

#endif
