#include "JuiRadioButton.h"

JIMPLEMENT_FORCE_LINK_OBJ(JuiRadioButton)
JIMPLEMENT_DYNAMIC_CLASS(JuiRadioButton, JuiCheckButton)
	JCLASS_PROPERTY(JuiRadioButton, radioGroup, int, SetRadioGroup, GetRadioGroup)

JuiRadioButton::JuiRadioButton()
{
	m_nRadioGroup = 0;
}

JuiRadioButton::~JuiRadioButton()
{

}

void JuiRadioButton::SetRadioGroup(int nGroup)
{
	m_nRadioGroup = nGroup;
}

int JuiRadioButton::GetRadioGroup() const
{
	return m_nRadioGroup;
}

void JuiRadioButton::SetStateOn()
{
	m_bStateOn = true;
	NotifySiblings(MSG_RADIO_CLICK,m_nRadioGroup);
}

void JuiRadioButton::OnClick()
{
	SetStateOn();
	JuiButton::OnClick();
}

void JuiRadioButton::OnControlEvent( JuiControl* sender, int message, int param )
{
	if(message != MSG_RADIO_CLICK)
		return;

	if(m_bStateOn && m_nRadioGroup == param)
	{
		SetUpdate();
		m_bStateOn = false;
	}
}