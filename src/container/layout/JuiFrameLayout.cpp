#include "JuiFrameLayout.h"
#include "base/drawable/JDrawable.h"

JBEGIN_CLASS_ENUM(JuiFrameLayoutParameter,LayoutSizeType)
	JENUM_NAME_MEMBER(fill_parent,JuiFrameLayoutParameter::SIZE_FILL_PARENT)
	JENUM_NAME_MEMBER(wrap_content,JuiFrameLayoutParameter::SIZE_WRAP_CONTENT)
JEND_CLASS_ENUM(JuiFrameLayoutParameter,LayoutSizeType)

JIMPLEMENT_DYNAMIC_CLASS(JuiFrameLayoutParameter, JObject)
JCLASS_WRITEONLY_PROPERTY(JuiFrameLayoutParameter, layout_width, JuiFrameLayoutParameter::LayoutSizeType, SetLayoutWidth)
JCLASS_WRITEONLY_PROPERTY(JuiFrameLayoutParameter, layout_height, JuiFrameLayoutParameter::LayoutSizeType, SetLayoutHeight)

JuiFrameLayoutParameter::JuiFrameLayoutParameter()
	: m_LayoutWidth(SIZE_CUSTOM)
	, m_LayoutHeight(SIZE_CUSTOM)
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

void JuiFrameLayoutParameter::UpdateExtent( JuiControl *pCtrl )
{
	if(m_LayoutWidth == SIZE_FILL_PARENT)
	{
		JuiContainer *pParent = pCtrl->GetParent();
		if(pParent != NULL)
			pCtrl->SetWidth(pParent->GetWidth());
	}
	else if(m_LayoutWidth == SIZE_WRAP_CONTENT)
	{
		JDrawable *pDraw = pCtrl->GetDrawable();
		if(pDraw != NULL)
			pCtrl->SetWidth(pDraw->GetWidth());
	}

	if(m_LayoutHeight == SIZE_FILL_PARENT)
	{
		JuiContainer *pParent = pCtrl->GetParent();
		if(pParent != NULL)
			pCtrl->SetHeight(pParent->GetHeight());
	}
	else if(m_LayoutWidth == SIZE_WRAP_CONTENT)
	{
		JDrawable *pDraw = pCtrl->GetDrawable();
		if(pDraw != NULL)
			pCtrl->SetHeight(pDraw->GetHeight());
	}
}



JIMPLEMENT_DYNAMIC_CLASS(JuiFrameLayout, JuiContainer)

void JuiFrameLayout::UpdateLayout( const JRectI& newRect )
{
	JuiControl* pCtrl = (JuiControl*)m_lsChilds.First();
	while(pCtrl)
	{
		JuiFrameLayoutParameter *pParam = static_cast<JuiFrameLayoutParameter*>(pCtrl->GetComponent("FrameLayout"));
		if(pParam != NULL)
		{
			pParam->UpdateExtent(pCtrl);
		}

		pCtrl = (JuiControl*)m_lsChilds.Next();
	}
}

void JuiFrameLayout::OnChildAdded( JuiControl *child )
{
	JuiFrameLayoutParameter *pParam = new JuiFrameLayoutParameter;
	child->AddComponent("FrameLayout",pParam);
}

void JuiFrameLayout::OnChildRemoved( JuiControl *child )
{
	child->RemoveComponent("FrameLayout");
}
