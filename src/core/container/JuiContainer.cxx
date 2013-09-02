#include "JuiContainer.hxx"

JuiContainer::JuiContainer()
{
	m_nFlags |= CTRL_FLAG_CONTAINER;
}

JuiContainer::~JuiContainer()
{

}

void JuiContainer::SetBounds( const JPoint2I& point, const JPoint2I& size )
{
	UpdateLayout(JRectI(point, size));
	JuiControl::SetBounds(point,size);
}

void JuiContainer::OnRender(JPoint2I offset,  const JRectI& rcPaint )
{
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

void JuiContainer::UpdateLayout(const JRectI& newRect)
{
	if(newRect.extent == m_rcBounds.extent)
		return;

	JuiControl* pCom = (JuiControl*)m_lsChilds.First();
	while(pCom)
	{
		pCom->OnParentResized(m_rcBounds, newRect);
		pCom = (JuiControl*)m_lsChilds.Next();
	}
}

void JuiContainer::AddControl( JuiControl *obj )
{
	m_lsChilds.PushBack(obj);
	obj->SetParent(this);
	UpdateLayout(m_rcBounds);
}

JuiControl * JuiContainer::FindControl( const JPoint2I& pt )
{
	JuiControl* pCom = (JuiControl*)m_lsChilds.First();
	while(pCom)
	{
		if(pCom->IsVisible() && pCom->IsMouseEnable() && pCom->IsPointIn(pt))
		{
			if(pCom->IsContainer())
			{
				JuiContainer* pContainer = dynamic_cast<JuiContainer*>(pCom);
				if(pContainer != NULL)
				{
					JPoint2I tmpPoint = pt - pCom->GetPosition();
					return pContainer->FindControl(tmpPoint);
				}
			}

			return pCom;
		}

		pCom = (JuiControl*)m_lsChilds.Next();
	}

	return NULL;
}

JuiControl * JuiContainer::FileControl( const char* name )
{
	JuiControl* pCom = (JuiControl*)m_lsChilds.First();
	while(pCom)
	{
		if(_stricmp(name, pCom->GetName()) == 0)
			return pCom;

		if(pCom->IsContainer())
		{
			JuiContainer* pContainer = dynamic_cast<JuiContainer*>(pCom);
			if(pContainer != NULL)
				return pContainer->FileControl(name);
		}

		pCom = (JuiControl*)m_lsChilds.Next();
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
