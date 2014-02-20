#include "JuiButton.h"

JIMPLEMENT_DYNAMIC_CLASS(JuiButton, JuiControl)
	JCLASS_WRITEONLY_PROPERTY(JuiButton, NormalImage, std::string, LoadNormalImage)
	JCLASS_WRITEONLY_PROPERTY(JuiButton, HoverImage, std::string, LoadHoverImage)
	JCLASS_WRITEONLY_PROPERTY(JuiButton, PressImage, std::string, LoadPressImage)
	JCLASS_WRITEONLY_PROPERTY(JuiButton, DisableImage, std::string, LoadDisableImage)

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

bool JuiButton::LoadNormalImage(const std::string& filename)
{
	m_pNormalImage = sm_pRender->CreateTexture(filename.c_str());
	return (m_pNormalImage != NULL);
}

bool JuiButton::LoadHoverImage(const std::string& filename)
{
	m_pHoverImage = sm_pRender->CreateTexture(filename.c_str());
	return (m_pHoverImage != NULL);
}

bool JuiButton::LoadPressImage(const std::string& filename)
{
	m_pPressImage = sm_pRender->CreateTexture(filename.c_str());
	return (m_pPressImage != NULL);
}

bool JuiButton::LoadDisableImage(const std::string& filename)
{
	m_pDisabledImage = sm_pRender->CreateTexture(filename.c_str());
	return (m_pDisabledImage != NULL);
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

	if(pImg != NULL)
		DrawImage(pImg, offset, rcPaint);
}