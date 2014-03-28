#include "JuiFrameLayout.h"
#include "base/drawable/JDrawable.h"

JIMPLEMENT_CLASS_COMMON(JuiLayoutParameter, JObject, NULL)

JBEGIN_CLASS_ENUM(JuiFrameLayoutParameter,LayoutSizeType)
	JENUM_NAME_MEMBER(fill_parent,JuiFrameLayoutParameter::SIZE_FILL_PARENT)
	JENUM_NAME_MEMBER(wrap_content,JuiFrameLayoutParameter::SIZE_WRAP_CONTENT)
JEND_CLASS_ENUM(JuiFrameLayoutParameter,LayoutSizeType)

JBEGIN_CLASS_ENUM(JuiFrameLayoutParameter,LayoutGravityType)
	JENUM_NAME_MEMBER(top,JuiFrameLayoutParameter::GRAVITY_TOP)
	JENUM_NAME_MEMBER(left,JuiFrameLayoutParameter::GRAVITY_LEFT)
	JENUM_NAME_MEMBER(right,JuiFrameLayoutParameter::GRAVITY_RIGHT)
	JENUM_NAME_MEMBER(bottm,JuiFrameLayoutParameter::GRAVITY_BOTTOM)
JEND_CLASS_ENUM(JuiFrameLayoutParameter,LayoutGravityType)


JIMPLEMENT_DYNAMIC_CLASS(JuiFrameLayoutParameter, JObject)
JCLASS_WRITEONLY_PROPERTY(JuiFrameLayoutParameter, layout_width, JuiFrameLayoutParameter::LayoutSizeType, SetLayoutWidth)
JCLASS_WRITEONLY_PROPERTY(JuiFrameLayoutParameter, layout_height, JuiFrameLayoutParameter::LayoutSizeType, SetLayoutHeight)
JCLASS_WRITEONLY_PROPERTY(JuiFrameLayoutParameter, layout_gravity, JuiFrameLayoutParameter::LayoutGravityType, SetLayoutGravity)

JuiFrameLayoutParameter::JuiFrameLayoutParameter()
	: m_LayoutWidth(SIZE_CUSTOM)
	, m_LayoutHeight(SIZE_CUSTOM)
	, m_ptOrigPos(0,0)
{

}

void JuiFrameLayoutParameter::SetLayoutWidth(const LayoutSizeType& type)
{
	m_LayoutWidth = type;
}

void JuiFrameLayoutParameter::SetLayoutHeight(const LayoutSizeType& type)
{
	m_LayoutHeight = type;
}

void JuiFrameLayoutParameter::SetLayoutGravity(const LayoutGravityType& type)
{
	m_Gravity = type;
}

void JuiFrameLayoutParameter::UpdateControl( JuiControl *pCtrl, const JPoint2I &parentSize )
{
	if(m_LayoutWidth == SIZE_FILL_PARENT)
	{
		pCtrl->SetWidth(parentSize.x);
	}
	else if(m_LayoutWidth == SIZE_WRAP_CONTENT)
	{
		JDrawable *pDraw = pCtrl->GetDrawable();
		if(pDraw != NULL)
			pCtrl->SetWidth(pDraw->GetWidth());
	}

	if(m_LayoutHeight == SIZE_FILL_PARENT)
	{
		pCtrl->SetHeight(parentSize.y);
	}
	else if(m_LayoutWidth == SIZE_WRAP_CONTENT)
	{
		JDrawable *pDraw = pCtrl->GetDrawable();
		if(pDraw != NULL)
			pCtrl->SetHeight(pDraw->GetHeight());
	}

	pCtrl->SetPosition(m_ptOrigPos);
}

void JuiFrameLayoutParameter::UpdatePos(JuiContainer* pParent, JRectI& bound)
{
	if(pParent == NULL)
		return;

	JPoint2I parentSize = pParent->GetExtent();
	m_ptOrigPos = bound.position;

	if(m_Gravity == GRAVITY_RIGHT)
	{
		bound.position.x = parentSize.x - bound.extent.x - m_ptOrigPos.x;
	}
	else if (m_Gravity == GRAVITY_BOTTOM)
	{
		bound.position.y = parentSize.y - bound.extent.y - m_ptOrigPos.y;
	}
}



JIMPLEMENT_DYNAMIC_CLASS(JuiFrameLayout, JuiContainer)

JuiFrameLayoutParameter* JuiFrameLayout::CreateParameter()
{
	return new JuiFrameLayoutParameter;
}

void JuiFrameLayout::OnSizeChanged(const JPoint2I& newSize)
{
	JuiControl* pCtrl = (JuiControl*)m_lsChilds.First();
	while(pCtrl)
	{
		JuiFrameLayoutParameter *pParam = static_cast<JuiFrameLayoutParameter*>(pCtrl->GetLayoutParameter());
		if(pParam != NULL)
		{
			pParam->UpdateControl(pCtrl, newSize);
		}

		pCtrl = (JuiControl*)m_lsChilds.Next();
	}
}

void JuiFrameLayout::OnChildAdded( JuiControl *child )
{
	JuiFrameLayoutParameter *pParam = CreateParameter();
	if(child->IsContainer())
	{
		pParam->SetLayoutWidth(JuiFrameLayoutParameter::SIZE_FILL_PARENT);
		pParam->SetLayoutHeight(JuiFrameLayoutParameter::SIZE_FILL_PARENT);
	}
	else
	{
		pParam->SetLayoutWidth(JuiFrameLayoutParameter::SIZE_WRAP_CONTENT);
		pParam->SetLayoutHeight(JuiFrameLayoutParameter::SIZE_WRAP_CONTENT);
	}

	child->SetLayoutParameter(pParam);
	child->AddComponent("LayoutParamer",pParam);
}

void JuiFrameLayout::OnChildRemoved( JuiControl *child )
{
	child->SetLayoutParameter(NULL);
	child->RemoveComponent("LayoutParamer");
}
