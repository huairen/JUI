#ifndef JUI_VERTICALLAYOUT_H_
#define JUI_VERTICALLAYOUT_H_

#include "core/container/JuiContainer.hxx"

class JuiVerticalLayout : public JuiContainer
{
	typedef JuiContainer Parent;
public:
	JuiVerticalLayout();
	~JuiVerticalLayout();

	virtual void UpdateLayout(const JRectI& newRect);

protected:

};

#endif