#ifndef JUI_SCROLL_H_
#define JUI_SCROLL_H_

#include "JuiContainer.hxx"
#include "graphics/JImage.hxx"

class JuiScroll : public JuiContainer
{
	typedef JuiContainer Parent;
public:
	JuiScroll();
	~JuiScroll();

	void LoadImage(const char* filename);

	virtual void OnMouseDown(const MouseEventInfo& event);
	virtual void OnMouseUp(const MouseEventInfo& event);
	virtual void OnMouseMove(const MouseEventInfo& event);

	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);
	virtual void UpdateLayout(const JRectI& newRect);

	virtual void DrawVertBar(const JPoint2I &offset);
	virtual void DrawHorizBar(const JPoint2I &offset);

protected:
	bool CalcChildExtent();

protected:
	JPoint2I m_ptChildPos;
	JPoint2I m_ptChildExtent;

	JPoint2I m_ptContentExtent;

	bool m_bAutoHide;
	bool m_bVertBar;
	bool m_bHorizBar;

	JImage *m_pImage;
};

#endif