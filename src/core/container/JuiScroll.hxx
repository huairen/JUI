#ifndef JUI_SCROLL_H_
#define JUI_SCROLL_H_

#include "JuiContainer.hxx"
#include "graphics/JImage.hxx"

class JuiScroll : public JuiContainer
{
	typedef JuiContainer Parent;
public:
	JuiScroll();
	~JuiScroll();

	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);
};

#endif