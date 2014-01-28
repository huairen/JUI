#include "JuiButton.h"

JIMPLEMENT_DYNAMIC_CLASS(JuiButton, JuiControl)

JuiButton::JuiButton()
{
	m_bDepressed = false;
	m_bMouseOver = false;

	m_pNormalImage = NULL;
	m_pHighlightImage = NULL;
	m_pPressImage = NULL;
	m_pDisabledImage = NULL;
}

JuiButton::~JuiButton()
{

}

bool JuiButton::LoadImage( const char* filename, int state )
{
	switch (state)
	{
	case 1:
		m_pNormalImage = sm_pRender->CreateImage(filename);
		return (m_pNormalImage != NULL);
		break;
	case 2:
		m_pHighlightImage = sm_pRender->CreateImage(filename);
		return (m_pHighlightImage != NULL);
		break;
	case 3:
		m_pHighlightImage = sm_pRender->CreateImage(filename);
		return (m_pHighlightImage != NULL);
		break;
	case 4:
		m_pPressImage = sm_pRender->CreateImage(filename);
		return (m_pPressImage != NULL);
		break;
	}

	return false;
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
	JImage *pImg = m_pNormalImage;

	if(!IsEnable())
		pImg = m_pDisabledImage;
	else if(m_bDepressed)
		pImg = m_pPressImage;
	else if(m_bMouseOver)
		pImg = m_pHighlightImage;

	if(pImg != NULL)
		DrawImage(pImg, offset, rcPaint);
}