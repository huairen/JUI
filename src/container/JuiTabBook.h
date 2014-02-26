#ifndef JUI_TABBOOK_H_
#define JUI_TABBOOK_H_

#include "JuiContainer.h"
#include "graphics/JTexture2D.h"

class JuiTabPage : public JuiContainer
{
	typedef JuiContainer Parent;
public:
	JuiTabPage();
	~JuiTabPage();

private:
	const char* m_pTitle;
	const char* m_pIconFile;
	JRectI m_rcTab;
};

class JuiTabBook : public JuiContainer
{
	typedef JuiContainer Parent;
public:
	JuiTabBook();
	~JuiTabBook();

	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);
	virtual void OnChildAdded(JuiControl *child);
	virtual void OnChildRemoved(JuiControl *child);

	virtual void OnMouseLeave();
	virtual void OnMouseDown(const MouseEventInfo& event);
	virtual void OnMouseMove(const MouseEventInfo& event);

protected:
	void RenderTab(const JRectI& tabRect, JuiTabPage *tab);
	JuiTabPage *FindHitTab(const JPoint2I &pt);

protected:
	JList m_lsPages;
	JuiTabPage *m_pHoverTab;
	JuiTabPage *m_pActivePage;

	int m_nTabHeight;
	
	JTexture2D *m_pNormalImage;
	JTexture2D *m_pHighlightImage;
	JTexture2D *m_pPressImage;
};

#endif