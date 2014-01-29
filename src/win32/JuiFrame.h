#ifndef JUI_FRAME_H_
#define JUI_FRAME_H_

#include "JuiWindow.h"
#include "container/JuiContainer.h"
#include "base/JuiInputManager.h"

class JuiFrame : public JuiContainer, public JuiWindow
{
	JDECLARE_DYNAMIC_CLASS(JuiFrame)
	typedef JuiContainer Parent;

public:
	JuiFrame();
	virtual ~JuiFrame();

	virtual void AddUpdateRegion( const JPoint2I& pos, const JPoint2I& extent );
	virtual JuiInputManager *GetInputGenerator();
	virtual void SetBounds(const JPoint2I& position, const JPoint2I& extent);
	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);

	bool SetBackground(const char* filename);
	bool SetBackground(const std::string& filename);

protected:
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual bool HandleCreate(LPCREATESTRUCT lpCS);
	virtual bool HandleClose();
	virtual bool HandleDestroy();
	virtual bool HandleSysCommand(UINT uCmdType, POINTS pt);
	virtual bool HandleHitTest(POINTS pt, LRESULT* result);
	virtual bool HandleMouseMove(UINT fwKeys, POINTS pt);
	virtual bool HandleMouseButton(UINT uMsg, UINT fwKeys, POINTS pt);
	virtual bool HandleSize(UINT nSizeType, WORD nWidht, WORD nHeight);
	virtual bool HandlePaint();
	virtual bool HandleMinMaxInfo(LPMINMAXINFO lpMMI);


private:
	JImage *m_pBackground;
	JuiInputManager m_InputMgr;
	bool m_bMouseTrack;
};

#endif 