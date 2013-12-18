#ifndef JRENDER_H_
#define JRENDER_H_
#include <stdint.h>
#include "JImage.h"
#include "math/JRect.h"

class JRender
{
public:
	virtual JImage *CreateImage(const char* filename) = 0;

	virtual bool BeginPaint() = 0;
	virtual bool EndPaint() = 0;
	virtual bool GetUpdateRect(JRectI& rect) { return false; }

	virtual void DrawRect(const JRectI& rect, uint32_t color) = 0;
	virtual void DrawRectFill(const JRectI& rect, uint32_t color) = 0;

	virtual void DrawLine(const JPoint2I& startPt, const JPoint2I& endPt, uint32_t color) = 0;
	virtual void DrawLine(int x1, int y1, int x2, int y2, uint32_t color) = 0;

	virtual void DrawImage(JImage* img, const JPoint2I& pos) = 0;
	virtual void DrawImageSR(JImage* img, const JPoint2I& pos, const JRectI& srcRect) = 0;
	virtual void DrawImageStretch(JImage* img, const JRectI& destRect) = 0;
	virtual void DrawImageStretchSR(JImage* img, const JRectI& destRect, const JRectI& srcRect) = 0;
};

#endif
