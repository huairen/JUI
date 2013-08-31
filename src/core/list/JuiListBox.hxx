#ifndef JUI_LIST_H_
#define JUI_LIST_H_

#include "core/container/JuiContainer.hxx"
#include "graphics/JImage.hxx"

class JuiListBox : public JuiContainer
{
	typedef JuiContainer Parent;
public:
	JuiListBox();
	~JuiListBox();

	virtual void OnMouseDown(const MouseEventInfo& event);
	virtual void OnMouseUp(const MouseEventInfo& event);
	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);

private:
};

#endif