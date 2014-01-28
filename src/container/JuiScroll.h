#ifndef JUI_SCROLL_H_
#define JUI_SCROLL_H_

#include "JuiContainer.h"

class JuiScroll : public JuiContainer
{
	typedef JuiContainer Parent;
public:
	JuiScroll();
	~JuiScroll();

	void JuiScroll::LoadBarImage(const char* filename);
	void JuiScroll::LoadArrowImage(const char* filename);

	virtual void JuiScroll::OnMouseDown(const MouseEventInfo& event);
	virtual void JuiScroll::OnMouseUp(const MouseEventInfo& event);
	virtual void JuiScroll::OnMouseMove(const MouseEventInfo& event);
	virtual void JuiScroll::OnRender(JPoint2I offset, const JRectI& rcPaint);

	virtual void UpdateLayout(const JRectI& newRect);

	virtual void DrawVScrollBar(const JPoint2I &offset, const JRectI& rcPaint);
	virtual void DrawHScrollBar(const JPoint2I &offset, const JRectI& rcPaint);

protected:
	bool CalcChildExtent();

protected:
	JPoint2I m_ptChildPos;
	JPoint2I m_ptChildExtent;

	JPoint2I m_ptContentExtent;

	bool m_bAutoHide;
	bool m_bVertBar;
	bool m_bHorizBar;

	JImage *m_pBarImg;
	JImage *m_pArrowImg;
};

#endif