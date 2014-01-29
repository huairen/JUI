#ifndef JUI_BUTTON_H_
#define JUI_BUTTON_H_

#include "base/JuiControl.h"
#include "graphics/JImage.h"

class JuiButton : public JuiControl
{
	JDECLARE_DYNAMIC_CLASS(JuiButton)
	typedef JuiControl Parent;
public:
	JuiButton();
	~JuiButton();

	bool LoadNormalImage(const std::string& filename);
	bool LoadHoverImage(const std::string& filename);
	bool LoadPressImage(const std::string& filename);
	bool LoadDisableImage(const std::string& filename);

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
	JImage *m_pHoverImage;
	JImage *m_pPressImage;
	JImage *m_pDisabledImage;
};

#endif