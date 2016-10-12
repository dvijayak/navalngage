#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "global.hpp"

#include "Color.hpp"
// #include "MatrixF.hpp"

class Polygon3F;
class LineSegment3F;

class WindowManager;

class RenderManager
{
public:
	RenderManager () {};
	RenderManager (const WindowManager& pWindowManager, Uint32 flags=0);
	~RenderManager ();

	SDL_Renderer* GetRenderer () const;
	SDL_Texture* GetTexture () const;

	void SetPixel (int index, Uint32 color=Color::Black);
	void SetPixel (int x, int y, Uint32 color=Color::Black);

	void Render () const;
	void FillScreenBackground (Uint32 color=Color::Black);
	void DrawLine (float, float, float, float, Uint32 color=Color::White);
	void DrawLine (const LineSegment3F& seg, Uint32 color=Color::White);
	void DrawPolygon (const Polygon3F& poly, Uint32 color=Color::White);

	// static Matrix3F s_TransformScreenSpace;

private:
	int m_WIDTH;
	int m_HEIGHT;

	// We possess ownership of screen pixels, screen texture and screen renderer
	Uint32* m_pPixels;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;
};

inline void RenderManager::SetPixel (int index, Uint32 color)
{
	m_pPixels[ index % (m_WIDTH*m_HEIGHT) ] = color;
}

inline void RenderManager::SetPixel (int x, int y, Uint32 color)
{
	m_pPixels[ (y%m_HEIGHT)*m_WIDTH + (x%m_WIDTH) ] = color;
}

#endif