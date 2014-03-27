#ifndef JUI_RELATIVELAYOUT_H_
#define JUI_RELATIVELAYOUT_H_

#include "JuiFrameLayout.h"

class JuiRelativeLayoutParameter : public JuiFrameLayoutParameter
{
	JDECLARE_DYNAMIC_CLASS(JuiRelativeLayoutParameter)
public:
	enum Align
	{
		ALIGN_TOP,
	};
};

class JuiRelativeLayout : public JuiFrameLayout
{
	JDECLARE_DYNAMIC_CLASS(JuiRelativeLayout)
	typedef JuiFrameLayout Parent;
public:
	virtual JuiFrameLayoutParameter* CreateParameter();
	virtual void UpdateLayout(const JRectI& newRect);
};

JFORCE_LINK_OBJ(JuiRelativeLayout)

#endif