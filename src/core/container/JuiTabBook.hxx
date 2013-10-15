#ifndef JUI_TABBOOK_H_
#define JUI_TABBOOK_H_

#include "JuiContainer.hxx"
#include "graphics/JImage.hxx"

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
	
	bool LoadNormalImage(const char* filename);
	bool LoadHighlightImage(const char* filename);
	bool LoadPressImage(const char* filename);

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
	JPtrList m_lsPages;
	JuiTabPage *m_pHoverTab;
	JuiTabPage *m_pActivePage;

	int m_nTabHeight;
	
	JImage *m_pNormalImage;
	JImage *m_pHighlightImage;
	JImage *m_pPressImage;
};

#endif