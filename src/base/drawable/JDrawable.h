#ifndef JDRAWABLE_H_
#define JDRAWABLE_H_

#include "JGlobalDefine.h"
#include "Math/JRect.h"

class JDrawable
{
public:
	JDrawable();
	virtual ~JDrawable();

	virtual uint32_t GetWidth() { return 0; }
	virtual uint32_t GetHeight() { return 0; }
	virtual void Draw(const JRectI& rcOrigin, const JRectI& rcPaint) = 0;

	virtual void SetState(int nState) {}


	static JDrawable* Create(const char* pString);

};

#endif // !JDRAWABLE_H_
