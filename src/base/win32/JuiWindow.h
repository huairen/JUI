#ifndef JUI_WINDOW_H_
#define JUI_WINDOW_H_

#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <assert.h>

class JuiWindow
{
public:
	JuiWindow();
	virtual ~JuiWindow();

	HWND GetHander();

	bool Create(const char* title, int windowType, JuiWindow* parent = NULL);
	void Close(int nRet);

	void SetPosition(int x, int y);
	void SetSize(int width, int height);
	void Show(int mode, bool bUpdate = false);
	void SetIcon(UINT nRes);

	void MoveToCenter();

	static int MessageLoop();

protected:
	virtual LPCTSTR GetWindowClassName() const;

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);	virtual bool HandleCreate(LPCREATESTRUCT lpCS);
	virtual bool HandleClose();
	virtual bool HandleDestroy();
	virtual bool HandleSysCommand(UINT uCmdType, POINTS pt);
	virtual bool HandleHitTest(POINTS pt, LRESULT* result);
	virtual bool HandleMouseMove(UINT fwKeys, POINTS pt);
	virtual bool HandleMouseButton(UINT uMsg, UINT fwKeys, POINTS pt);
	virtual bool HandleSize(UINT nSizeType, WORD nWidht, WORD nHeight);
	virtual bool HandlePaint();
	virtual bool HandleMinMaxInfo(LPMINMAXINFO lpMMI);

	bool RegisterWindowClass();
	LRESULT DefaultWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
protected:
	HWND m_hWnd;
	WNDPROC m_pOldWndProc;
	JuiWindow *m_pParent;
	bool m_bMouseTrack;
};

inline HWND JuiWindow::GetHander()
{
	return m_hWnd;
}

#endif 