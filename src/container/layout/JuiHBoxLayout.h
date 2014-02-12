#ifndef JUI_HBOXLAYOUT_H_
#define JUI_HBOXLAYOUT_H_

#include "container/JuiContainer.h"

class JuiHBoxLayout : public JuiContainer
{
	typedef JuiContainer Parent;
public:
	JuiHBoxLayout();
	~JuiHBoxLayout();

	virtual void UpdateLayout(const JRectI& newRect);

protected:
};

#endif