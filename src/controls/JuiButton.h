#ifndef JUI_BUTTON_H_
#define JUI_BUTTON_H_

#include "base/JuiControl.h"
#include "graphics/JTexture2D.h"

class JuiButton : public JuiControl
{
	JDECLARE_DYNAMIC_CLASS(JuiButton)
	typedef JuiControl Parent;
public:
	JuiButton();
	~JuiButton();

	virtual void OnClick();

	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
	virtual void OnMouseDown(const MouseEventInfo& event);
	virtual void OnMouseUp(const MouseEventInfo& event);

protected:
	bool m_bDepressed;
	bool m_bMouseOver;
};

#endif