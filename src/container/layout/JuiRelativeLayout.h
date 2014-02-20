#ifndef JUI_RELATIVELAYOUT_H_
#define JUI_RELATIVELAYOUT_H_

#include "container/JuiContainer.h"

class JuiRelativeLayout : public JuiContainer
{
	typedef JuiContainer Parent;
public:
	JuiRelativeLayout();
	~JuiRelativeLayout();

	virtual void UpdateLayout(const JRectI& newRect);

protected:

};

#endif