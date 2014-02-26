#include "JuiButton.h"

JIMPLEMENT_DYNAMIC_CLASS(JuiButton, JuiControl)

JuiButton::JuiButton()
{
	m_bDepressed = false;
	m_bMouseOver = false;

	m_pNormalImage = NULL;
	m_pHoverImage = NULL;
	m_pPressImage = NULL;
	m_pDisabledImage = NULL;
}

JuiButton::~JuiButton()
{

}

void JuiButton::OnClick()
{
	JuiControl *root = GetRoot();
	if(root)
		root->OnControlEvent(this, MSG_CLICK,0);
}

void JuiButton::OnMouseEnter()
{
	SetUpdate();

	if(IsMouseLocked())
		m_bDepressed = true;

	m_bMouseOver = true;
}

void JuiButton::OnMouseLeave()
{
	SetUpdate();

	if(IsMouseLocked())
		m_bDepressed = false;

	m_bMouseOver = false;
}

void JuiButton::OnMouseDown( const MouseEventInfo& event )
{
	if(event.button != KEY_BUTTON0)
		return;

	MouseLock();
	m_bDepressed = true;

	SetUpdate();
}

void JuiButton::OnMouseUp( const MouseEventInfo& event )
{
	if(event.button != KEY_BUTTON0)
		return;

	MouseUnlock();
	SetUpdate();

	if(m_bDepressed)
		OnClick();

	m_bDepressed = false;
}

void JuiButton::OnRender( JPoint2I offset, const JRectI& rcPaint )
{
	JTexture2D *pImg = m_pNormalImage;

	if(!IsEnable())
		pImg = m_pDisabledImage;
	else if(m_bDepressed)
		pImg = m_pPressImage;
	else if(m_bMouseOver)
		pImg = m_pHoverImage;
}