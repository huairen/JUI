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

void JuiCheckButton::OnRender( JPoint2I offset, const JRectI& rcPaint )
{
	JTexture2D *pImg = m_pNormalImage;

	if(!IsEnable())
		pImg = m_pDisabledImage;
	else if(m_bDepressed || m_bStateOn)
		pImg = m_pPressImage;
	else if(m_bMouseOver)
		pImg = m_pHoverImage;
}
