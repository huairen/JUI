#ifndef JUI_BUTTON_H_
#define JUI_BUTTON_H_

#include "core/base/JuiControl.h"
#include "graphics/JImage.h"

class JuiButton : public JuiControl
{
	typedef JuiControl Parent;
public:
	JuiButton();
	~JuiButton();

	bool LoadNormalImage(const char* filename);
	bool LoadHighlightImage(const char* filename);
	bool LoadPressImage(const char* filename);
	bool LoadDisabledImage(const char* filename);

	virtual void OnClick();

	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
	virtual void OnMouseDown(const MouseEventInfo& event);
	virtual void OnMouseUp(const MouseEventInfo& event);

	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);

protected:
	bool m_bDepressed;
	bool m_bMouseOver;

	JImage *m_pNormalImage;
	JImage *m_pHighlightImage;
	JImage *m_pPressImage;
	JImage *m_pDisabledImage;
};

#endif