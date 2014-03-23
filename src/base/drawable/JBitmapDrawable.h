#ifndef JBITMAP_DRAWABLE_H_
#define JBITMAP_DRAWABLE_H_

#include "JDrawable.h"

class JTexture2D;

class JBitmapDrawable : public JDrawable
{
public:
	JBitmapDrawable();
	virtual ~JBitmapDrawable();

	bool Load(const char* filename);

	virtual uint32_t GetWidth();
	virtual uint32_t GetHeight();
	virtual void Draw(const JRectI& rcOrigin, const JRectI& rcPaint);

protected:
	JTexture2D* m_pBitmap;
};
#endif //JBITMAP_DRAWABLE_H_