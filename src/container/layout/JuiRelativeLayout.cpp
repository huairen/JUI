#include "JuiRelativeLayout.h"

JIMPLEMENT_DYNAMIC_CLASS(JuiRelativeLayoutParameter, JuiLayoutParameter)

JIMPLEMENT_FORCE_LINK_OBJ(JuiRelativeLayout)
JIMPLEMENT_DYNAMIC_CLASS(JuiRelativeLayout, JuiContainer)

void JuiRelativeLayout::UpdateLayout( const JRectI& newRect )
{
	Parent::UpdateLayout(newRect);
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
