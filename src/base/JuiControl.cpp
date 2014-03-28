#include "JuiControl.h"
#include "JuiContainer.h"
#include "drawable/JDrawable.h"
#include "layout/JuiLayoutParameter.h"

JIMPLEMENT_CLASS_COMMON(JuiControl, JObject, NULL)
	JCLASS_PROPERTY(JuiControl, position, JPoint2I, SetPosition, GetPosition)
	JCLASS_PROPERTY(JuiControl, size, JPoint2I, SetExtent, GetExtent)
	JCLASS_WRITEONLY_PROPERTY(JuiControl, minSize, JPoint2I, SetMinSize)
	JCLASS_WRITEONLY_PROPERTY(JuiControl, maxSize, JPoint2I, SetMaxSize)
	JCLASS_PROPERTY(JuiControl, visible, bool, SetVisible, IsVisible)
	JCLASS_PROPERTY(JuiControl, enable, bool, SetEnable, IsEnable)
	JCLASS_PROPERTY(JuiControl, mouseEnable, bool, SetMouseEnable, IsMouseEnable)
	JCLASS_WRITEONLY_PROPERTY(JuiControl, background, std::string, SetBackground)

JuiControl::JuiControl()
	: m_nState(STATE_ENABLE | STATE_VISIBLE | STATE_MOUSE_ENABLE)
	, m_pParent(0)
	, m_rcBounds(0,0,100,100)
	, m_ptMinSize(8,2)
	, m_ptMaxSize(-1,-1)
	, m_pBackground(0)
	, m_pLayoutParam(0)
{
}

JuiControl::~JuiControl()
{
	if(m_pBackground != NULL)
		delete m_pBackground;
}

JuiControl* JuiControl::Clone()
{
	return static_cast<JuiControl*>(JObject::Clone());
}

JuiControl* JuiControl::GetRoot()
{
	JuiControl *root = NULL;
	JuiControl *parent = GetParent();

	while (parent)
	{
		root = parent;
		parent = parent->GetParent();
	}

	return root;
}

void JuiControl::SetUpdateRegion( const JPoint2I& pos, const JPoint2I& size )
{
	JuiControl *root = GetRoot();
	if(root != NULL)
		root->AddUpdateRegion(LocalToRoot(pos), size);
}

void JuiControl::SetUpdate()
{
	SetUpdateRegion(JPoint2I(0,0), GetExtent());
}

void JuiControl::MouseLock()
{
	JuiControl *root = GetRoot();
	if(!root)
		return;

	JuiEventManager *input = root->GetInputGenerator();
	if(input)
		input->MouseLock(this);
}

void JuiControl::MouseUnlock()
{
	JuiControl *root = GetRoot();
	if(!root)
		return;

	JuiEventManager *input = root->GetInputGenerator();
	if(input)
		input->MouseUnlock(this);
}

bool JuiControl::IsMouseLocked()
{
	JuiControl *root = GetRoot();
	if(!root)
		return false;

	JuiEventManager *input = root->GetInputGenerator();
	if(input)
		return input->GetMouseCaptureControl() == this;
	return false;
}

void JuiControl::SetBackground(const std::string& drawable)
{
	m_pBackground = JDrawable::Create(drawable.c_str());
}

void JuiControl::SetPosition(const JPoint2I& point)
{
	m_rcBounds.position = point;
	if(m_pLayoutParam != NULL)
		m_pLayoutParam->UpdatePos(m_pParent, m_rcBounds);
}

void JuiControl::SetPosition( int x, int y )
{
	m_rcBounds.position.x = x;
	m_rcBounds.position.y = y;
	if(m_pLayoutParam != NULL)
		m_pLayoutParam->UpdatePos(m_pParent, m_rcBounds);
}

void JuiControl::SetPosX(int x)
{
	m_rcBounds.position.x = x;
	if(m_pLayoutParam != NULL)
		m_pLayoutParam->UpdatePos(m_pParent, m_rcBounds);
}

void JuiControl::SetPosY(int y)
{
	m_rcBounds.position.y = y;
	if(m_pLayoutParam != NULL)
		m_pLayoutParam->UpdatePos(m_pParent, m_rcBounds);
}

bool JuiControl::IsPointIn( const JPoint2I& pt )
{
	return m_rcBounds.IsPointIn(pt);
}

JPoint2I JuiControl::LocalToRoot( const JPoint2I &pos )
{
	JPoint2I ret = pos;
	ret += GetPosition();

	JuiControl* ptr = m_pParent;
	while(ptr)
	{
		ret += ptr->GetPosition();
		ptr = ptr->m_pParent;
	}

	return ret;
}

void JuiControl::SetVisible(bool value)
{
	if(value)
		AddState(STATE_VISIBLE);
	else
		RemoveState(STATE_VISIBLE);
}

void JuiControl::SetEnable(bool value)
{
	if(value)
		AddState(STATE_ENABLE);
	else
		RemoveState(STATE_ENABLE);
}

void JuiControl::SetMouseEnable(bool value)
{
	if(value)
		AddState(STATE_MOUSE_ENABLE);
	else
		RemoveState(STATE_MOUSE_ENABLE);
}

void JuiControl::NotifySiblings( int message, int param )
{
	JuiContainer *parent = GetParent();
	if(parent == NULL)
		return;

	JuiControl *ctrl = parent->FirstChild();
	while(ctrl)
	{
		if(ctrl != this)
			ctrl->OnControlEvent(this, message, param);
		ctrl = parent->NextChild();
	}
}

void JuiControl::OnRender(JPoint2I offset, const JRectI& rcPaint)
{
	if(m_pBackground != NULL)
		m_pBackground->Draw(JRectI(offset, m_rcBounds.extent), rcPaint);
}