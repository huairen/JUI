#ifndef JUI_LINEARLAYOUT_H_
#define JUI_LINEARLAYOUT_H_

#include "container/JuiContainer.h"

class JuiLinearLayout : public JuiContainer
{
	typedef JuiContainer Parent;
public:
	JuiLinearLayout();
	~JuiLinearLayout();

	virtual void UpdateLayout(const JRectI& newRect);

protected:
};

#endif