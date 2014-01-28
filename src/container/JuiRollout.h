#ifndef JUI_ROLLOUT_H_
#define JUI_ROLLOUT_H_

#include "JuiContainer.h"
#include "graphics/JImage.h"

class JuiRollout : public JuiContainer
{
	typedef JuiContainer Parent;
public:
	JuiRollout();
	~JuiRollout();

	void Collapse();
	void Expand();

	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);


protected:
	bool m_bExtanded;
	int m_nBarHeight;

	JImage *m_pBarImg;
	JImage *m_pPanel;
};

#endif