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

	virtual void UpdateLayout(const JRectI& newRect);

	void AddControl(JuiControl *obj);
	JuiControl *FindControl(const JPoint2I& pt);
	JuiControl *FileControl(const char* name);

	JuiControl *FirstChild();
	JuiControl *NextChild();
	
protected:
	JListPtr m_lsChilds;
};

#endif 