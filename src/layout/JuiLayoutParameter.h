#ifndef JUI_LAYOUT_PARAMETER_H_
#define JUI_LAYOUT_PARAMETER_H_

#include "Object/JObject.h"
#include "Math/JPoint.h"

class JuiLayoutParameter : public JObject
{
	JDECLARE_ABSTRACT_CLASS(JuiLayoutParameter)
public:
	virtual void UpdatePos(JuiContainer* pParent, JRectI& bound) = 0;
};

#endif