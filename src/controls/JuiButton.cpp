#include "JuiButton.h"
#include "Graphics/Drawable/JDrawable.h"

JIMPLEMENT_DYNAMIC_CLASS(JuiButton, JuiControl)

JuiButton::JuiButton()
{
	m_bDepressed = false;
	m_bMouseOver = false;
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
	if(m_pBackground)
		m_pBackground->SetState(m_bDepressed ? 2 : 1);
}

void JuiButton::OnMouseLeave()
{
	SetUpdate();

	if(IsMouseLocked())
		m_bDepressed = false;

	m_bMouseOver = false;
	if(m_pBackground && !m_bDepressed)
		m_pBackground->SetState(0);
}

void JuiButton::OnMouseDown( const MouseEventInfo& event )
{
	if(event.button != KEY_BUTTON0)
		return;

	MouseLock();
	m_bDepressed = true;
	if(m_pBackground)
		m_pBackground->SetState(2);

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
	if(m_pBackground)
		m_pBackground->SetState(m_bMouseOver ? 1 : 0);
}