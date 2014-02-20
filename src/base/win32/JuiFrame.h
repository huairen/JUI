#ifndef JUI_FRAME_H_
#define JUI_FRAME_H_

#include "JuiWindow.h"
#include "container/JuiContainer.h"
#include "base/JuiEventManager.h"

class JuiFrame : public JuiContainer, public JuiWindow
{
	JDECLARE_DYNAMIC_CLASS(JuiFrame)
	typedef JuiContainer Parent;

public:
	JuiFrame();
	virtual ~JuiFrame();

	virtual void AddUpdateRegion( const JPoint2I& pos, const JPoint2I& extent );
	virtual JuiEventManager *GetInputGenerator();
	virtual void SetBounds(const JPoint2I& position, const JPoint2I& extent);

protected:
	virtual bool HandleHitTest(POINTS pt, LRESULT* result);
	virtual bool HandleMouseMove(UINT fwKeys, POINTS pt);
	virtual bool HandleMouseButton(UINT uMsg, UINT fwKeys, POINTS pt);
	virtual bool HandleSize(UINT nSizeType, WORD nWidht, WORD nHeight);
	virtual bool HandlePaint();
	virtual bool HandleMinMaxInfo(LPMINMAXINFO lpMMI);


private:
	JuiEventManager m_InputMgr;
};

#endif 