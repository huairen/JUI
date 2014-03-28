#ifndef JUI_CONTAINER_H_
#define JUI_CONTAINER_H_

#include "base/JuiControl.h"
#include "DataType/JList.h"


class JuiContainer : public JuiControl
{
	JDECLARE_DYNAMIC_CLASS(JuiContainer)
	typedef JuiControl Parent;

public:
	JuiContainer();
	virtual ~JuiContainer();

	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);

	virtual void OnChildAdded(JuiControl *child){};
	virtual void OnChildRemoved(JuiControl *child){};
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