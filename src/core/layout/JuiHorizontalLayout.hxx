#ifndef JUI_HORIZONTALLAYOUT_H_
#define JUI_HORIZONTALLAYOUT_H_

#include "core/container/JuiContainer.hxx"

class JuiHorizontalLayout : public JuiContainer
{
	typedef JuiContainer Parent;
public:
	JuiHorizontalLayout();
	~JuiHorizontalLayout();

	virtual void UpdateLayout(const JRectI& newRect);

protected:
};

#endif