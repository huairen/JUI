#ifndef JUI_FRAME_H_
#define JUI_FRAME_H_

#include "JuiWindow.hxx"
#include "core/container/JuiContainer.hxx"
#include "core/base/JuiInputManager.hxx"

class JuiFrame : public JuiContainer, public JuiWindow
{
	typedef JuiContainer Parent;

public:
	JuiFrame();
	virtual ~JuiFrame();

	virtual void SetUpdateRegion( JPoint2I pos, JPoint2I size );
	virtual JuiInputManager *GetInputGenerator();
	virtual void SetBounds(const JPoint2I& point, const JPoint2I& size);
	virtual void OnRender(JPoint2I offset, const JRectI& rcPaint);

	bool SetBackground(const char* filename);

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