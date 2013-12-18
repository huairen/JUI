#ifndef JUI_CHECK_BUTTON_H_
#define JUI_CHECK_BUTTON_H_

#include "JuiButton.h"

class JuiCheckButton : public JuiButton
{
	typedef JuiButton Parent;
public:
	JuiCheckButton();
	~JuiCheckButton();

	void SetStateOn(bool on);
	bool GetStateOn();

	virtual void OnClick();
	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);

protected:
	bool m_bStateOn;
};

#endif