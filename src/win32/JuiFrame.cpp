#include "JuiFrame.h"

JIMPLEMENT_DYNAMIC_CLASS(JuiFrame, JuiContainer)
	JCLASS_WRITEONLY_PROPERTY(JuiFrame, image, std::string, SetBackground)

JuiFrame::JuiFrame()
{
	m_InputMgr.SetController(this);
	m_bMouseTrack = true;
}

JuiFrame::~JuiFrame()
{

}

void JuiFrame::AddUpdateRegion( const JPoint2I& pos, const JPoint2I& extent )
{
	if(m_pBackground->HasAlphaChannel())
	{
		::InvalidateRect(m_hWnd, NULL, FALSE);
		return;
	}

	RECT rcUpdate;
	rcUpdate.left = pos.x;
	rcUpdate.top = pos.y;
	rcUpdate.right = pos.x + extent.x;
	rcUpdate.bottom = pos.y + extent.y;

	::InvalidateRect(m_hWnd, &rcUpdate, FALSE);
}

JuiInputManager * JuiFrame::GetInputGenerator()
{
	return &m_InputMgr;
}

void JuiFrame::SetBounds( const JPoint2I& position, const JPoint2I& extent )
{
	Parent::SetBounds(position, extent);
	JuiWindow::SetSize(extent.x,extent.y);
}

void JuiFrame::OnRender( JPoint2I offset, const JRectI& rcPaint )
{
	if(m_pBackground != NULL)
		DrawImage(m_pBackground, offset, rcPaint);

	Parent::OnRender(offset, rcPaint);
}

bool JuiFrame::SetBackground( const char* filename )
{
	m_pBackground = sm_pRender->CreateImage(filename);
	return m_pBackground != NULL;
}

bool JuiFrame::SetBackground(const std::string& filename)
{
	m_pBackground = sm_pRender->CreateImage(filename.c_str());
	return m_pBackground != NULL;
}

LRESULT JuiFrame::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
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

bool JuiFrame::HandleCreate( LPCREATESTRUCT lpCS )
{
	return false;
}

bool JuiFrame::HandleClose()
{
	return false;
}

bool JuiFrame::HandleDestroy()
{
	PostQuitMessage(0);
	return true;
}


bool JuiFrame::HandleSysCommand( UINT uCmdType, POINTS pt )
{
	return false;
}

bool JuiFrame::HandleHitTest( POINTS pt, LRESULT* result )
{
	int boardSize = 4;

	if(m_InputMgr.GetMouseControl() != NULL)
	{
		*result = HTCLIENT;
		return true;
	}

	if( m_ptMinSize.y != m_ptMaxSize.y )
	{
		if( pt.y < GetPosY() + boardSize)
		{
			if( pt.x < GetPosX() + boardSize )
				*result = HTTOPLEFT;
			else if( pt.x > GetRight() - boardSize )
				*result = HTTOPRIGHT;
			else *result = HTTOP;
			return true;
		}
		else if( pt.y > GetBottom() - boardSize )
		{
			if( pt.x < GetPosX() + boardSize )
				*result = HTBOTTOMLEFT;
			else if( pt.x > GetRight() - boardSize )
				*result = HTBOTTOMRIGHT;
			else
				*result = HTBOTTOM;
			return true;
		}
	}

	if( m_ptMinSize.x != m_ptMaxSize.x )
	{
		if( pt.x < GetPosX() + boardSize )
			*result = HTLEFT;
		else if( pt.x > GetRight() - boardSize )
			*result = HTRIGHT;
		else
			*result =  HTCAPTION;

		return true;
	}

	*result =  HTCAPTION;
	return true;
}

bool JuiFrame::HandleMouseMove( UINT fwKeys, POINTS pt)
{
	InputEventInfo event;
	event.deviceType = INPUT_DEVICE_MOUSE;
	event.action = INPUT_ACTION_MOVE;
	event.objInst = KEY_NONE;
	event.pos.x = pt.x;
	event.pos.y = pt.y;

	m_InputMgr.ProcessInputEvent(event);
	return true;
}

bool JuiFrame::HandleMouseButton( UINT uMsg, UINT fwKeys, POINTS pt)
{
	int index = 0;

	InputEventInfo event;

	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		index = (uMsg - WM_LBUTTONDOWN) / 3;
		event.action = INPUT_ACTION_PRESS;
		::SetCapture(m_hWnd);
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
		index = (uMsg - WM_LBUTTONUP) / 3;
		event.action = INPUT_ACTION_RELEASE;
		::ReleaseCapture();
		break;
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
		index = (uMsg - WM_LBUTTONDBLCLK) / 3;
		event.action = INPUT_ACTION_DBCLICK;
		break;
	case WM_NCLBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
	case WM_NCMBUTTONDOWN:
		index = (uMsg - WM_NCLBUTTONDOWN) / 3;
		event.action = INPUT_ACTION_PRESS;
		break;
	case WM_NCLBUTTONUP:
	case WM_NCRBUTTONUP:
	case WM_NCMBUTTONUP:
		index = (uMsg - WM_NCLBUTTONUP) / 3;
		event.action = INPUT_ACTION_RELEASE;
		break;
	case WM_NCLBUTTONDBLCLK:
	case WM_NCRBUTTONDBLCLK:
	case WM_NCMBUTTONDBLCLK:
		index = (uMsg - WM_NCLBUTTONDBLCLK) / 3;
		event.action = INPUT_ACTION_DBCLICK;
		break;
	}

	event.deviceType = INPUT_DEVICE_MOUSE;
	event.objInst = (InputObjectInstances)(KEY_BUTTON0 + index);
	event.pos.x = pt.x;
	event.pos.y = pt.y;

	return m_InputMgr.ProcessInputEvent(event);
}

bool JuiFrame::HandleSize(UINT nSizeType, WORD nWidht, WORD nHeight)
{
	if(GetWidth() != nWidht || GetHeight() != nHeight)
	{
		JuiContainer::SetExtent(nWidht, nHeight);
		::InvalidateRect(m_hWnd, NULL, FALSE);
		return true;
	}

	return false;
}

bool JuiFrame::HandlePaint()
{
	JRectI rcPaint;
	if(sm_pRender == NULL)
		return false;

	if(sm_pRender->BeginPaint())
	{
		sm_pRender->GetUpdateRect(rcPaint);
		OnRender(JPoint2I(0,0), rcPaint);

		sm_pRender->EndPaint();
	}
	return true;
}

bool JuiFrame::HandleMinMaxInfo( LPMINMAXINFO lpMMI )
{
	MONITORINFO monitor;
	monitor.cbSize = sizeof(monitor);
	::GetMonitorInfo(::MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST), &monitor);

	RECT rcWork = monitor.rcWork;
	rcWork.left -= monitor.rcMonitor.left;
	rcWork.top -= monitor.rcMonitor.top;

	// 计算最大化时，正确的原点坐标
	lpMMI->ptMaxPosition.x	= rcWork.left;
	lpMMI->ptMaxPosition.y	= rcWork.top;

	lpMMI->ptMaxTrackSize.x = (m_ptMaxSize.x >= m_ptMinSize.x) ? m_ptMaxSize.x : (rcWork.right - rcWork.left);
	lpMMI->ptMaxTrackSize.y = (m_ptMaxSize.y >= m_ptMinSize.y) ? m_ptMaxSize.y : (rcWork.bottom - rcWork.top);

	lpMMI->ptMinTrackSize.x = m_ptMinSize.x;
	lpMMI->ptMinTrackSize.y = m_ptMinSize.y;

	return true;
}