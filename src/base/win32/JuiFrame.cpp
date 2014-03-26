#include "JuiFrame.h"
#include "Graphics/JRenderSystem.h"

JIMPLEMENT_DYNAMIC_CLASS(JuiFrame, JuiFrameLayout)
	JCLASS_WRITEONLY_PROPERTY(JuiFrame, image, std::string, SetBackground)

JuiFrame::JuiFrame()
{
	m_InputMgr.SetController(this);
}

JuiFrame::~JuiFrame()
{

}

void JuiFrame::AddUpdateRegion( const JPoint2I& pos, const JPoint2I& extent )
{
// 	if(m_pBackground->HasAlphaChannel())
// 	{
// 		::InvalidateRect(m_hWnd, NULL, FALSE);
// 		return;
// 	}

	RECT rcUpdate;
	rcUpdate.left = pos.x;
	rcUpdate.top = pos.y;
	rcUpdate.right = pos.x + extent.x;
	rcUpdate.bottom = pos.y + extent.y;

	::InvalidateRect(m_hWnd, &rcUpdate, FALSE);
}

JuiEventManager * JuiFrame::GetInputGenerator()
{
	return &m_InputMgr;
}

void JuiFrame::SetBounds( const JPoint2I& position, const JPoint2I& extent )
{
	Parent::SetBounds(position, extent);
	JuiWindow::SetSize(extent.x,extent.y);
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
	JRenderer* pRenderer = JRenderSystem::GetInstance().GetRenderer();
	if(pRenderer == NULL)
		return false;

	if(pRenderer->BeginPaint())
	{
		pRenderer->GetUpdateRect(rcPaint);
		OnRender(JPoint2I(0,0), rcPaint);

		pRenderer->EndPaint();
	}
	return true;
}

bool JuiFrame::HandleMinMaxInfo( LPMINMAXINFO lpMMI )
{
	MONITORINFO monitor;
	monitor.cbSize = sizeof(monitor);
	::GetMonitorInfo(::MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST), &monitor);

	POINT rcWorkPos;
	rcWorkPos.x = monitor.rcWork.left - monitor.rcMonitor.left;
	rcWorkPos.y = monitor.rcWork.top - monitor.rcMonitor.top;

	POINT rcWorkSize;
	rcWorkSize.x = monitor.rcWork.right - monitor.rcWork.left;
	rcWorkSize.y = monitor.rcWork.bottom - monitor.rcWork.top;
	
	POINT ptMax;
	ptMax.x = (m_ptMaxSize.x >= m_ptMinSize.x) ? m_ptMaxSize.x : rcWorkSize.x;
	ptMax.y = (m_ptMaxSize.y >= m_ptMinSize.y) ? m_ptMaxSize.y : rcWorkSize.y;

	// 计算最大化时，正确的原点坐标
	lpMMI->ptMaxPosition.x	= rcWorkPos.x + ((rcWorkSize.x - ptMax.x)>>1);
	lpMMI->ptMaxPosition.y	= rcWorkPos.y + ((rcWorkSize.y - ptMax.y)>>1);

	lpMMI->ptMaxSize.x = ptMax.x;
	lpMMI->ptMaxSize.y = ptMax.y;

	lpMMI->ptMaxTrackSize.x = ptMax.x;
	lpMMI->ptMaxTrackSize.y = ptMax.y;

	lpMMI->ptMinTrackSize.x = m_ptMinSize.x;
	lpMMI->ptMinTrackSize.y = m_ptMinSize.y;

	return true;
}