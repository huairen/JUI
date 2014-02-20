#ifndef JUI_ROLLOUT_H_
#define JUI_ROLLOUT_H_

#include "JuiContainer.h"
#include "graphics/JTexture2D.h"

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

	JTexture2D *m_pBarImg;
	JTexture2D *m_pPanel;
};

#endif