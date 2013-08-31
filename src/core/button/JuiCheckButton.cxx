#include "JuiCheckButton.hxx"

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
	JImage *pImg = m_pNormalImage;

	if(!IsEnable())
		pImg = m_pDisabledImage;
	else if(m_bDepressed || m_bStateOn)
		pImg = m_pPressImage;
	else if(m_bMouseOver)
		pImg = m_pHighlightImage;

	if(pImg != NULL)
		DrawImage(pImg, offset, rcPaint);
}
