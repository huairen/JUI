#include "JuiContainer.h"

JBEGIN_CLASS_ENUM(JuiLayoutParameter,LayoutSizeType)
	JENUM_NAME_MEMBER(fill_parent,JuiLayoutParameter::SIZE_FILL_PARENT)
	JENUM_NAME_MEMBER(wrap_content,JuiLayoutParameter::SIZE_WRAP_CONTENT)
JEND_CLASS_ENUM(JuiLayoutParameter,LayoutSizeType)

JIMPLEMENT_DYNAMIC_CLASS(JuiLayoutParameter, JObject)
JCLASS_WRITEONLY_PROPERTY(JuiLayoutParameter, layout_width, JuiLayoutParameter::LayoutSizeType, SetLayoutWidth)
JCLASS_WRITEONLY_PROPERTY(JuiLayoutParameter, layout_height, JuiLayoutParameter::LayoutSizeType, SetLayoutHeight)

JuiLayoutParameter::JuiLayoutParameter()
	: m_LayoutWidth(SIZE_CUSTOM)
	, m_LayoutHeight(SIZE_CUSTOM)
{

}

void JuiLayoutParameter::SetLayoutWidth(const LayoutSizeType& type)
{
	m_LayoutWidth = type;
}

void JuiLayoutParameter::SetLayoutHeight(const LayoutSizeType& type)
{
	m_LayoutHeight = type;
}



JIMPLEMENT_DYNAMIC_CLASS(JuiContainer, JuiControl)

JuiContainer::JuiContainer()
{
	AddState(STATE_CONTAINER);
	RemoveState(STATE_MOUSE_ENABLE);
}

JuiContainer::~JuiContainer()
{

}

void JuiContainer::SetBounds( const JPoint2I& point, const JPoint2I& size )
{
	if(size != m_rcBounds.extent)
		UpdateLayout(JRectI(point, size));

	JuiControl::SetBounds(point,size);
}

void JuiContainer::OnRender(JPoint2I offset,  const JRectI& rcPaint )
{
	Parent::OnRender(offset, rcPaint);

	JuiControl* pControl = (JuiControl*)m_lsChilds.First();
	while(pControl)
	{
		if(pControl->IsVisible())
		{
			JPoint2I childPos = offset + pControl->GetPosition();
			JRectI childClip(childPos, pControl->GetExtent());

			if(childClip.Intersect(rcPaint))
				pControl->OnRender(childPos, childClip);
		}

		pControl = (JuiControl*)m_lsChilds.Next();
	}
}

JuiControl* JuiContainer::Clone()
{
	JuiContainer* pClone = dynamic_cast<JuiContainer*>(Parent::Clone());
	if(pClone == NULL)
		return NULL;

	JuiControl* pSubCtrl = FirstChild();
	while(pSubCtrl)
	{
		JuiControl* pSubClone = pSubCtrl->Clone();
		if(pSubClone != NULL)
			pClone->AddControl(pSubClone);
		pSubCtrl = NextChild();
	}

	return pClone;
}

void JuiContainer::AddControl( JuiControl *obj )
{
	if(obj == this || obj == NULL)
		return;

	if(obj->GetParent() == this)
		return;

	if(obj->GetParent() != NULL)
		obj->GetParent()->RemoveControl(obj);

	m_lsChilds.PushBack(obj);
	obj->SetParent(this);

	OnChildAdded(obj);

	UpdateLayout(m_rcBounds);
}

void JuiContainer::RemoveControl( JuiControl* obj )
{
	OnChildRemoved(obj);

	m_lsChilds.Remove(obj);
	obj->SetParent(NULL);

	UpdateLayout(m_rcBounds);
}

void JuiContainer::OnChildAdded(JuiControl *child)
{
	JuiLayoutParameter *pParam = new JuiLayoutParameter;
	child->AddComponent("LayoutParameter",pParam);
}

void JuiContainer::OnChildRemoved(JuiControl *child)
{
	child->RemoveComponent("LayoutParameter");
}

void JuiContainer::UpdateLayout(const JRectI& newRect)
{
	JuiControl* pCtrl = (JuiControl*)m_lsChilds.First();
	while(pCtrl)
	{
		pCtrl = (JuiControl*)m_lsChilds.Next();
	}
}

JuiControl * JuiContainer::FindHitControl( const JPoint2I& pt )
{
	JuiControl* pCtrl = (JuiControl*)m_lsChilds.First();
	while(pCtrl)
	{
		if(pCtrl->IsVisible() && pCtrl->IsPointIn(pt))
		{
			if(pCtrl->IsContainer())
			{
				JuiContainer* pContainer = dynamic_cast<JuiContainer*>(pCtrl);
				if(pContainer != NULL)
				{
					JPoint2I tmpPoint = pt - pCtrl->GetPosition();
					JuiControl *pSub = pContainer->FindHitControl(tmpPoint);
					if(pSub != NULL)
						return pSub;
				}
			}

			return pCtrl->IsMouseEnable() ? pCtrl : NULL;
		}

		pCtrl = (JuiControl*)m_lsChilds.Next();
	}

	return NULL;
}

JuiControl * JuiContainer::FindControl( const char* name )
{
	JuiControl* pCtrl = (JuiControl*)m_lsChilds.First();
	while(pCtrl)
	{
		const char *ctrlName = pCtrl->GetName();
		if(*ctrlName && _stricmp(name, ctrlName) == 0)
			return pCtrl;

		if(pCtrl->IsContainer())
		{
			JuiContainer* pContainer = dynamic_cast<JuiContainer*>(pCtrl);
			if(pContainer != NULL)
			{
				JuiControl *pSubCtrl = pContainer->FindControl(name);
				if(pSubCtrl != NULL)
					return pSubCtrl;
			}
		}

		pCtrl = (JuiControl*)m_lsChilds.Next();
	}

	return NULL;
}

JuiControl * JuiContainer::FirstChild()
{
	return (JuiControl*)m_lsChilds.First();
}

JuiControl * JuiContainer::NextChild()
{
	return (JuiControl*)m_lsChilds.Next();
}
