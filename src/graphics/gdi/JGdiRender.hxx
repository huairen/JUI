#ifndef JGDIRENDER_H_
#define JGDIRENDER_H_

#include <windows.h>
#include "../JRender.hxx"

#pragma comment(lib,"msimg32.lib")

class JGdiRender : public JRender
{
public:
	JGdiRender();

	void SetWindowHandler(HWND hWnd);

	virtual JImage *CreateImage(const char* filename);

	virtual bool BeginPaint();
	virtual bool EndPaint();
	virtual bool GetUpdateRect(JRectI& rect);

	virtual void DrawRect(const JRectI& rect, uint32_t color);
	virtual void DrawRectFill(const JRectI& rect, uint32_t color);

	virtual void DrawLine(const JPoint2I& startPt, const JPoint2I& endPt, uint32_t color);
	virtual void DrawLine(int x1, int y1, int x2, int y2, uint32_t color);

	virtual void DrawImage(JImage* img, const JPoint2I& pos);
	virtual void DrawImageSR(JImage* img, const JPoint2I& pos, const JRectI& srcRect);
	virtual void DrawImageStretch(JImage* img, const JRectI& destRect);
	virtual void DrawImageStretchSR(JImage* img, const JRectI& destRect, const JRectI& srcRect);

private:
	HWND m_hWnd;
	PAINTSTRUCT m_PaintInfo;
	bool m_bBeginPaint;
	JRectI m_rcUpdateRect;
	HDC m_hBackDC;
	HBITMAP m_hBackBMP;
	HBITMAP m_hOldBMP;
};

#endif