#include "JuiRadioButton.h"

JuiRadioButton::JuiRadioButton()
{
	m_nRadioGroup = 0;
}

JuiRadioButton::~JuiRadioButton()
{

}

int JuiRadioButton::GetRadioGroup()
{
	return m_nRadioGroup;
}

void JuiRadioButton::SetStateOn()
{
	m_bStateOn = true;
	NotifySiblings(CTRL_MSG_RADIO_CLICK,m_nRadioGroup);
}

void JuiRadioButton::OnClick()
{
	SetStateOn();
	JuiButton::OnClick();
}

void JuiRadioButton::OnControlEvent( JuiControl* sender, int message, int param )
{
	if(message != CTRL_MSG_RADIO_CLICK)
		return;

	if(m_bStateOn && m_nRadioGroup == param)
	{
		SetUpdate();
		m_bStateOn = false;
	}
}
