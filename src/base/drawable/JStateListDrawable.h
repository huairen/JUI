#ifndef JSTATELIST_DRAWABLE_H_
#define JSTATELIST_DRAWABLE_H_

#include "JDrawable.h"
#include "DataType/JArray.h"

class JTexture2D;

class JStateListDrawable : public JDrawable
{
public:
	JStateListDrawable();
	virtual ~JStateListDrawable();

	virtual uint32_t GetWidth();
	virtual uint32_t GetHeight();
	virtual void Draw(const JRectI& rcOrigin, const JRectI& rcPaint);
	virtual void SetState(int nState);

	void Add(JDrawable* pDrawable, int nState);

protected:
	JArray<JDrawable*> m_DrawableList;
	JDrawable* m_pCurrDrawable;
};
#endif //JBITMAP_DRAWABLE_H_