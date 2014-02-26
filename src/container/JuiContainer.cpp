#include "JuiContainer.h"

JIMPLEMENT_DYNAMIC_CLASS(JuiContainer, JuiControl)

JuiContainer::JuiContainer()
{
	m_nFlags |= FLAG_CONTAINER;
}

JuiContainer::~JuiContainer()
{

}

void JuiContainer::SetBounds( const JPoint2I& point, const JPoint2I& size )
{
	if(size != m_rcBounds.extent)
	{
		JRectI newRect(point, size);

		JuiControl* pCom = (JuiControl*)m_lsChilds.First();
		while(pCom)
		{
			pCom->OnParentResized(m_rcBounds, newRect);
			pCom = (JuiControl*)m_lsChilds.Next();
		}
	}

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
}

void JuiContainer::RemoveControl( JuiControl* obj )
{
	OnChildRemoved(obj);

	m_lsChilds.Remove(obj);
	obj->SetParent(NULL);
}

JuiControl * JuiContainer::FindHitControl( const JPoint2I& pt )
{
	JuiControl* pCtrl = (JuiControl*)m_lsChilds.First();
	while(pCtrl)
	{
		if(pCtrl->IsVisible() && pCtrl->IsMouseEnable() && pCtrl->IsPointIn(pt))
		{
			if(pCtrl->IsContainer())
			{
				JuiContainer* pContainer = dynamic_cast<JuiContainer*>(pCtrl);
				if(pContainer != NULL)
				{
					JPoint2I tmpPoint = pt - pCtrl->GetPosition();
					JuiControl *pHit = pContainer->FindHitControl(tmpPoint);
					return pHit ? pHit : pContainer;
				}
			}

			return pCtrl;
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