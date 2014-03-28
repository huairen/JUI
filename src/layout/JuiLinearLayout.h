#ifndef JUI_LINEARLAYOUT_H_
#define JUI_LINEARLAYOUT_H_

#include "JuiFrameLayout.h"

class JuiLinearLayoutParameter
{
protected:
	int m_Orientaion;
	int m_FillMode;
	int m_Weight;
};

class JuiLinearLayout : public JuiFrameLayout
{
	JDECLARE_DYNAMIC_CLASS(JuiLinearLayout)
	typedef JuiFrameLayout Parent;
public:
	virtual void UpdateLayout(const JRectI& newRect);
};

#endif