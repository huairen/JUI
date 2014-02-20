#include "JuiWindow.h"

JuiWindow::JuiWindow()
{
	m_hWnd = NULL;
	m_pOldWndProc = NULL;
	m_pParent = NULL;
	m_bMouseTrack = true;
}

JuiWindow::~JuiWindow()
{

}

bool JuiWindow::Create(const char* title, int windowType, JuiWindow* parent)
{
	if(!RegisterWindowClass())
		return false;

	m_hWnd = ::CreateWindow(GetWindowClassName(), title, windowType,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		parent ? parent->m_hWnd : NULL,NULL,NULL,this);

	if(m_hWnd == NULL)
		return false;

	m_pParent = parent;
	return true;
}

void JuiWindow::Close(int nRet)
{
	assert(::IsWindow(m_hWnd));
	if( !::IsWindow(m_hWnd) ) return;
	PostMessage(m_hWnd, WM_CLOSE, (WPARAM)nRet, 0L);
}

void JuiWindow::SetPosition( int x, int y )
{
	assert(::IsWindow(m_hWnd));
	if( !::IsWindow(m_hWnd) ) return;
	::SetWindowPos(m_hWnd,NULL,x,y,0,0,SWP_NOZORDER|SWP_NOSIZE);
}

void JuiWindow::SetSize( int width, int height )
{
	assert(::IsWindow(m_hWnd));
	if( !::IsWindow(m_hWnd) ) return;
	::SetWindowPos(m_hWnd,NULL,0,0,width,height,SWP_NOZORDER|SWP_NOMOVE);
}

void JuiWindow::Show( int mode, bool bUpdate )
{
	assert(::IsWindow(m_hWnd));
	if( !::IsWindow(m_hWnd) ) return;
	::ShowWindow(m_hWnd, mode);
	if(bUpdate)
		::UpdateWindow(m_hWnd);
}

void JuiWindow::SetIcon( UINT nRes )
{
	HICON hIcon = (HICON)::LoadImage(::GetModuleHandle(NULL), MAKEINTRESOURCE(nRes), IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	assert(hIcon);
	::SendMessage(m_hWnd, WM_SETICON, (WPARAM) TRUE, (LPARAM) hIcon);
	hIcon = (HICON)::LoadImage(::GetModuleHandle(NULL), MAKEINTRESOURCE(nRes), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	assert(hIcon);
	::SendMessage(m_hWnd, WM_SETICON, (WPARAM) FALSE, (LPARAM) hIcon);

}

void JuiWindow::MoveToCenter()
{
	assert(::IsWindow(m_hWnd));
	assert((GetWindowStyle(m_hWnd)&WS_CHILD)==0);
	RECT rcDlg = { 0 };
	::GetWindowRect(m_hWnd, &rcDlg);
	RECT rcArea = { 0 };
	RECT rcCenter = { 0 };
	HWND hWnd = m_hWnd;
	HWND hWndParent = ::GetParent(m_hWnd);
	HWND hWndCenter = ::GetWindowOwner(m_hWnd);
	if (hWndCenter!=NULL)
		hWnd=hWndCenter;

	// 处理多显示器模式下屏幕居中
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &oMonitor);
	rcArea = oMonitor.rcWork;

	if( hWndCenter == NULL )
		rcCenter = rcArea;
	else
		::GetWindowRect(hWndCenter, &rcCenter);

	int DlgWidth = rcDlg.right - rcDlg.left;
	int DlgHeight = rcDlg.bottom - rcDlg.top;

	// Find dialog's upper left based on rcCenter
	int xLeft = (rcCenter.left + rcCenter.right) / 2 - DlgWidth / 2;
	int yTop = (rcCenter.top + rcCenter.bottom) / 2 - DlgHeight / 2;

	// The dialog is outside the screen, move it inside
	if( xLeft < rcArea.left ) xLeft = rcArea.left;
	else if( xLeft + DlgWidth > rcArea.right ) xLeft = rcArea.right - DlgWidth;
	if( yTop < rcArea.top ) yTop = rcArea.top;
	else if( yTop + DlgHeight > rcArea.bottom ) yTop = rcArea.bottom - DlgHeight;
	::SetWindowPos(m_hWnd, NULL, xLeft, yTop, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

int JuiWindow::MessageLoop()
{
	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}


//-------------------------------------------------------------------------------
LPCTSTR JuiWindow::GetWindowClassName() const
{
	return _T("DefaultClass");
}

LRESULT JuiWindow::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	bool done = false;
	LRESULT result = 0;

	switch(uMsg)
	{
	case WM_CREATE:
		done = HandleCreate((LPCREATESTRUCT)lParam);
		break;
	case WM_CLOSE:
		done = HandleClose();
		break;
	case WM_DESTROY:
		done = HandleDestroy();
		break;
	case WM_SYSCOMMAND:
		done = HandleSysCommand((UINT)wParam, MAKEPOINTS(lParam));
		break;
	case WM_NCHITTEST:
		{
			POINT pt;
			POINTSTOPOINT(pt, lParam);
			::ScreenToClient(m_hWnd, &pt);

			LONG pts = POINTTOPOINTS(pt);
			done = HandleHitTest(MAKEPOINTS(pts), &result);
		}
		break;
	case WM_NCMOUSEMOVE:
		{
			POINT pt;
			POINTSTOPOINT(pt, lParam);
			::ScreenToClient(m_hWnd, &pt);

			LONG pts = POINTTOPOINTS(pt);
			done = HandleMouseMove((UINT)wParam, MAKEPOINTS(pts));
		}
		break;
	case WM_MOUSEMOVE:
		{
			if(m_bMouseTrack)
			{
				TRACKMOUSEEVENT tme = {0};
				tme.cbSize = sizeof(tme);
				tme.dwFlags = TME_LEAVE;
				tme.hwndTrack = m_hWnd;
				tme.dwHoverTime = HOVER_DEFAULT;
				::TrackMouseEvent(&tme);
				m_bMouseTrack = false;
			}

			done = HandleMouseMove((UINT)wParam, MAKEPOINTS(lParam));
		}
		break;
	case WM_MOUSELEAVE:
		{
			LPARAM pos = -1;
			done = HandleMouseMove((UINT)wParam, MAKEPOINTS(pos));
			m_bMouseTrack = true;
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
	case WM_NCLBUTTONDOWN:
	case WM_NCLBUTTONUP:
	case WM_NCLBUTTONDBLCLK:
	case WM_NCRBUTTONDOWN:
	case WM_NCRBUTTONUP:
	case WM_NCRBUTTONDBLCLK:
	case WM_NCMBUTTONDOWN:
	case WM_NCMBUTTONUP:
	case WM_NCMBUTTONDBLCLK:
		done = HandleMouseButton(uMsg, (int)wParam, MAKEPOINTS(lParam));
		break;
	case WM_SIZE:
		done = HandleSize((UINT)wParam,GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_PAINT:
		done = HandlePaint();
		break;
	case WM_GETMINMAXINFO:
		done = HandleMinMaxInfo((LPMINMAXINFO) lParam);
		break;
	case WM_KILLFOCUS:
		done = 0;
		break;
	}

	return done ? result : DefaultWndProc(uMsg, wParam, lParam);
}

bool JuiWindow::HandleCreate( LPCREATESTRUCT lpCS )
{
	return false;
}

bool JuiWindow::HandleClose()
{
	return false;
}

bool JuiWindow::HandleDestroy()
{
	PostQuitMessage(0);
	return true;
}


bool JuiWindow::HandleSysCommand( UINT uCmdType, POINTS pt )
{
	return false;
}

bool JuiWindow::HandleHitTest( POINTS pt, LRESULT* result )
{
	return false;
}

bool JuiWindow::HandleMouseMove( UINT fwKeys, POINTS pt)
{
	return false;
}

bool JuiWindow::HandleMouseButton( UINT uMsg, UINT fwKeys, POINTS pt)
{
	return false;
}

bool JuiWindow::HandleSize(UINT nSizeType, WORD nWidht, WORD nHeight)
{
	return false;
}

bool JuiWindow::HandlePaint()
{
	return false;
}

bool JuiWindow::HandleMinMaxInfo( LPMINMAXINFO lpMMI )
{
	return false;
}

bool JuiWindow::RegisterWindowClass()
{
	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));

	wc.style = CS_BYTEALIGNCLIENT | CS_BYTEALIGNWINDOW | CS_DBLCLKS;
	wc.lpfnWndProc = JuiWindow::WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME;
	wc.lpszMenuName = 0;
	wc.lpszClassName = GetWindowClassName();

	if(!::RegisterClass(&wc))
		return false;

	return true;
}

LRESULT JuiWindow::DefaultWndProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if(m_pOldWndProc != NULL)
		return ::CallWindowProc(m_pOldWndProc, m_hWnd, uMsg, wParam, lParam);
	else
		return ::DefWindowProc(m_hWnd,uMsg,wParam,lParam);
}

LRESULT CALLBACK JuiWindow::WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	JuiWindow* pThis = NULL;
	if(uMsg == WM_NCCREATE)
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		pThis = static_cast<JuiWindow*>(lpcs->lpCreateParams);
		pThis->m_hWnd = hWnd;
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(pThis));
	}
	else
	{
		pThis = reinterpret_cast<JuiWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		if(uMsg == WM_NCDESTROY && pThis != NULL)
		{
			LRESULT lRes = pThis->DefaultWndProc(uMsg,wParam,lParam);
			::SetWindowLongPtr(pThis->m_hWnd, GWLP_USERDATA, 0);
			pThis->m_hWnd = NULL;
			return lRes;
		}
	}

	if(pThis != NULL)
		return pThis->HandleMessage(uMsg, wParam, lParam);

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
