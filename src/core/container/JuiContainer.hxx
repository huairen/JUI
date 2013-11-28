#ifndef JUI_CONTAINER_H_
#define JUI_CONTAINER_H_

#include "core/base/JuiControl.hxx"
#include "math/JList.hxx"

class JuiContainer : public JuiControl
{
	typedef JuiControl Parent;
public:
	JuiContainer();
	virtual ~JuiContainer();

	virtual void SetBounds(const JPoint2I& point, const JPoint2I& size);
	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);
	virtual void OnChildAdded(JuiControl *child) {};
	virtual void OnChildRemoved(JuiControl *chile) {};

	JuiControl *FindHitControl(const JPoint2I& pt);
	JuiControl *FindControl(const char* name);

	void AddControl(JuiControl *obj);
	void RemoveControl(JuiControl* obj);

	JuiControl *FirstChild();
	JuiControl *NextChild();
	
protected:
	JPtrList m_lsChilds;
};

#endif 