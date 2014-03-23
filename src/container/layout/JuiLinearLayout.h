#ifndef JUI_LINEARLAYOUT_H_
#define JUI_LINEARLAYOUT_H_

#include "container/JuiContainer.h"

class JuiLinearLayoutParameter
{
protected:
	int m_Orientaion;
	int m_FillMode;
	int m_Weight;
};

class JuiLinearLayout : public JuiContainer
{
	JDECLARE_DYNAMIC_CLASS(JuiLinearLayout)
	typedef JuiContainer Parent;
public:
	virtual void UpdateLayout(const JRectI& newRect);
};

#endif