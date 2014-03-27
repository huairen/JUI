#include "JuiRelativeLayout.h"

JIMPLEMENT_DYNAMIC_CLASS(JuiRelativeLayoutParameter, JuiFrameLayoutParameter)

JIMPLEMENT_FORCE_LINK_OBJ(JuiRelativeLayout)
JIMPLEMENT_DYNAMIC_CLASS(JuiRelativeLayout, JuiFrameLayout)

JuiFrameLayoutParameter* JuiRelativeLayout::CreateParameter()
{
	return new JuiRelativeLayoutParameter;
}

void JuiRelativeLayout::UpdateLayout( const JRectI& newRect )
{
	Parent::UpdateLayout(newRect);
}
