#ifndef JUI_RADIO_BUTTON_H_
#define JUI_RADIO_BUTTON_H_

#include "JuiCheckButton.hxx"

class JuiRadioButton : public JuiCheckButton
{
	typedef JuiCheckButton Parent;
public:
	JuiRadioButton();
	~JuiRadioButton();

	void SetStateOn();
	int GetRadioGroup();

	virtual void OnClick();
	virtual void OnControlEvent(JuiControl* sender, int message, int param);

private:
	int m_nRadioGroup;
};

#endif