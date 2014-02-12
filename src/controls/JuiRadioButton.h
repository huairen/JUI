#ifndef JUI_RADIO_BUTTON_H_
#define JUI_RADIO_BUTTON_H_

#include "JuiCheckButton.h"

class JuiRadioButton : public JuiCheckButton
{
	JDECLARE_DYNAMIC_CLASS(JuiRadioButton)
	typedef JuiCheckButton Parent;
public:
	JuiRadioButton();
	~JuiRadioButton();

	void SetStateOn();
	void SetRadioGroup(int nGroup);
	int GetRadioGroup()  const;

	virtual void OnClick();
	virtual void OnControlEvent(JuiControl* sender, int message, int param);

private:
	int m_nRadioGroup;
};

JFORCE_LINK_OBJ(JuiRadioButton)

#endif