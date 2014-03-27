#ifndef JUI_FRAMELAYOUT_H_
#define JUI_FRAMELAYOUT_H_

#include "container/JuiContainer.h"

struct Bound
{
	int left;
	int top;
	int right;
	int bottom;
};


class JuiFrameLayoutParameter : public JObject
{
	JDECLARE_DYNAMIC_CLASS(JuiFrameLayoutParameter)
public:
	enum LayoutSizeType
	{
		SIZE_CUSTOM,
		SIZE_FILL_PARENT,
		SIZE_WRAP_CONTENT,
	};

	JuiFrameLayoutParameter();
	void SetLayoutWidth(const LayoutSizeType& type);
	void SetLayoutHeight(const LayoutSizeType& type);

	void UpdateExtent(JuiControl *pCtrl, const JRectI &parentRect);

private:
	LayoutSizeType m_LayoutWidth;
	LayoutSizeType m_LayoutHeight;
	//	Bound m_Margin;
};

class JuiFrameLayout : public JuiContainer
{
	JDECLARE_DYNAMIC_CLASS(JuiRelativeLayout)
public:
	virtual JuiFrameLayoutParameter* CreateParameter();
	virtual void UpdateLayout(const JRectI& newRect);
	virtual void OnChildAdded(JuiControl *child);
	virtual void OnChildRemoved(JuiControl *child);
};

#endif