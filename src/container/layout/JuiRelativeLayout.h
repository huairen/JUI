#ifndef JUI_RELATIVELAYOUT_H_
#define JUI_RELATIVELAYOUT_H_

#include "container/JuiContainer.h"

class JuiRelativeLayoutParameter : public JuiLayoutParameter
{
	JDECLARE_DYNAMIC_CLASS(JuiRelativeLayoutParameter)
public:
	enum Align
	{
		ALIGN_TOP,
	};
};

class JuiRelativeLayout : public JuiContainer
{
	JDECLARE_DYNAMIC_CLASS(JuiRelativeLayout)
	typedef JuiContainer Parent;
public:
	virtual void UpdateLayout(const JRectI& newRect);
	virtual void OnChildAdded(JuiControl *child);
	virtual void OnChildRemoved(JuiControl *child);
};

JFORCE_LINK_OBJ(JuiRelativeLayout)

#endif