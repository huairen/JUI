#ifndef JUI_FRAMELAYOUT_H_
#define JUI_FRAMELAYOUT_H_

#include "JuiContainer.h"
#include "JuiLayoutParameter.h"

struct Bound
{
	int left;
	int top;
	int right;
	int bottom;
};


class JuiFrameLayoutParameter : public JuiLayoutParameter
{
	JDECLARE_DYNAMIC_CLASS(JuiFrameLayoutParameter)
public:
	enum LayoutSizeType
	{
		SIZE_CUSTOM,
		SIZE_FILL_PARENT,
		SIZE_WRAP_CONTENT,
	};

	enum LayoutGravityType
	{
		GRAVITY_TOP,
		GRAVITY_LEFT,
		GRAVITY_RIGHT,
		GRAVITY_BOTTOM,
	};

	JuiFrameLayoutParameter();
	void SetLayoutWidth(const LayoutSizeType& type);
	void SetLayoutHeight(const LayoutSizeType& type);
	void SetLayoutGravity(const LayoutGravityType& type);

	void UpdateControl(JuiControl *pCtrl, const JPoint2I &parentSize);

	virtual void UpdatePos(JuiContainer* pParent, JRectI& bound);

private:
	LayoutSizeType m_LayoutWidth;
	LayoutSizeType m_LayoutHeight;
	LayoutGravityType m_Gravity;
	JPoint2I m_ptOrigPos;
	//	Bound m_Margin;
};

class JuiFrameLayout : public JuiContainer
{
	JDECLARE_DYNAMIC_CLASS(JuiRelativeLayout)
public:
	virtual JuiFrameLayoutParameter* CreateParameter();
	virtual void OnSizeChanged(const JPoint2I& newSize);
	virtual void OnChildAdded(JuiControl *child);
	virtual void OnChildRemoved(JuiControl *child);
};

#endif