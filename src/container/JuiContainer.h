#ifndef JUI_CONTAINER_H_
#define JUI_CONTAINER_H_

#include "base/JuiControl.h"
#include "DataType/JList.h"

class JuiLayoutParameter : public JObject
{
	JDECLARE_DYNAMIC_CLASS(JuiLayoutParameter)
public:
	enum LayoutSizeType
	{
		SIZE_CUSTOM,
		SIZE_FILL_PARENT,
		SIZE_WRAP_CONTENT,
	};

	JuiLayoutParameter();
	void SetLayoutWidth(const LayoutSizeType& type);
	void SetLayoutHeight(const LayoutSizeType& type);

private:
	LayoutSizeType m_LayoutWidth;
	LayoutSizeType m_LayoutHeight;
//	Bound m_Margin;
};

class JuiContainer : public JuiControl
{
	JDECLARE_DYNAMIC_CLASS(JuiContainer)
	typedef JuiControl Parent;

public:
	JuiContainer();
	virtual ~JuiContainer();

	virtual void SetBounds(const JPoint2I& point, const JPoint2I& size);
	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);
	virtual void OnChildAdded(JuiControl *child);
	virtual void OnChildRemoved(JuiControl *child);
	virtual void UpdateLayout(const JRectI& newRect);
	virtual JuiControl* Clone();

	JuiControl *FindHitControl(const JPoint2I& pt);
	JuiControl *FindControl(const char* name);

	void AddControl(JuiControl *obj);
	void RemoveControl(JuiControl* obj);

	JuiControl *FirstChild();
	JuiControl *NextChild();
	
protected:
	JList m_lsChilds;
};

#endif 