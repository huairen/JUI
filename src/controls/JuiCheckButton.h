#ifndef JUI_CHECK_BUTTON_H_
#define JUI_CHECK_BUTTON_H_

#include "JuiButton.h"

class JuiCheckButton : public JuiButton
{
	JDECLARE_DYNAMIC_CLASS(JuiCheckButton)
	typedef JuiButton Parent;
public:
	JuiCheckButton();
	~JuiCheckButton();

	void SetStateOn(bool on);
	bool GetStateOn();

	virtual void OnClick();

protected:
	bool m_bStateOn;
};

#endif