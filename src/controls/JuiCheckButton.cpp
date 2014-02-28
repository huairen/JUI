#include "JuiCheckButton.h"

JIMPLEMENT_DYNAMIC_CLASS(JuiCheckButton, JuiButton)

JuiCheckButton::JuiCheckButton()
{
	m_bStateOn = false;
}

JuiCheckButton::~JuiCheckButton()
{

}

void JuiCheckButton::SetStateOn( bool on )
{
	m_bStateOn = on;
}

bool JuiCheckButton::GetStateOn()
{
	return m_bStateOn;
}

void JuiCheckButton::OnClick()
{
	m_bStateOn = !m_bStateOn;
	Parent::OnClick();
}