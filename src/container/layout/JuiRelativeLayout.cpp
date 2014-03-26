#include "JuiRelativeLayout.h"

JIMPLEMENT_DYNAMIC_CLASS(JuiRelativeLayoutParameter, JuiFrameLayoutParameter)

JIMPLEMENT_FORCE_LINK_OBJ(JuiRelativeLayout)
JIMPLEMENT_DYNAMIC_CLASS(JuiRelativeLayout, JuiFrameLayout)

void JuiRelativeLayout::UpdateLayout( const JRectI& newRect )
{
	JuiControl* pCtrl = (JuiControl*)m_lsChilds.First();
	while(pCtrl)
	{
		JuiRelativeLayoutParameter *pParam = static_cast<JuiRelativeLayoutParameter*>(pCtrl->GetComponent("RelativeLayout"));
		if(pParam != NULL)
		{
			pParam->UpdateExtent(pCtrl);
		}

		pCtrl = (JuiControl*)m_lsChilds.Next();
	}
}

void JuiRelativeLayout::OnChildAdded(JuiControl *child)
{
	JuiRelativeLayoutParameter *pParam = new JuiRelativeLayoutParameter;
	child->AddComponent("RelativeLayout",pParam);
}

void JuiRelativeLayout::OnChildRemoved(JuiControl *child)
{
	child->RemoveComponent("RelativeLayout");
}
