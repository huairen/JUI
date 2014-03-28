#include "JuiEventManager.h"
#include "JuiContainer.h"

JuiEventManager::JuiEventManager()
{
	m_pInputController = NULL;
	m_pMouseControl = NULL;
	m_pMouseCapturedControl = NULL;
	memset(&m_LastEvent, 0, sizeof(m_LastEvent));
}

JuiEventManager::~JuiEventManager()
{

}

void JuiEventManager::SetController( JuiContainer* controller )
{
	m_pInputController = controller;
}

void JuiEventManager::MouseLock( JuiControl *control )
{
	if(m_pMouseCapturedControl != NULL)
		return;

	m_pMouseCapturedControl = control;

	if(m_pMouseControl && m_pMouseControl != m_pMouseCapturedControl)
		m_pMouseControl->OnMouseLeave();
}

void JuiEventManager::MouseUnlock( JuiControl *control )
{
	if(m_pMouseCapturedControl != control)
		return;

	m_pMouseCapturedControl = NULL;
}

JuiControl* JuiEventManager::GetMouseControl()
{
	return m_pMouseControl;
}

JuiControl* JuiEventManager::GetMouseCaptureControl()
{
	return m_pMouseCapturedControl;
}

bool JuiEventManager::ProcessInputEvent( InputEventInfo &inputEvent )
{
	if(!m_pInputController)
		return false;

	switch (inputEvent.deviceType)
	{
	case INPUT_DEVICE_KEYBOARD:
		return ProcessKeyboardEvent(inputEvent);
	case INPUT_DEVICE_MOUSE:
		return ProcessMouseEvent(inputEvent);
	}

	return false;
}

bool JuiEventManager::ProcessKeyboardEvent( InputEventInfo &inputEvent )
{
	return false;
}

bool JuiEventManager::ProcessMouseEvent( InputEventInfo &inputEvent )
{
	m_LastEvent.button = inputEvent.objInst;
	m_LastEvent.pos = inputEvent.pos;

	switch (inputEvent.action)
	{
	case INPUT_ACTION_DBCLICK:
		m_LastEvent.clickCount = 2;
		return OnMouseDown(m_LastEvent);

	case INPUT_ACTION_PRESS:
		m_LastEvent.clickCount = 1;
		return OnMouseDown(m_LastEvent);

	case INPUT_ACTION_RELEASE:
		return OnMouseUp(m_LastEvent);

	case INPUT_ACTION_MOVE:
		return OnMouseMove(m_LastEvent);
	}

	return false;
}


bool JuiEventManager::OnMouseDown( const MouseEventInfo &event )
{
	if(m_pMouseCapturedControl != NULL)
	{
		m_pMouseCapturedControl->OnMouseDown(event);
		return true;
	}

	JuiControl *controlHit = m_pInputController->FindHitControl(event.pos);
	if(controlHit != NULL && controlHit->IsEnable())
	{
		controlHit->OnMouseDown(event);
		return true;
	}

	return false;
}

bool JuiEventManager::OnMouseUp( const MouseEventInfo &event )
{
	if(m_pMouseCapturedControl != NULL)
	{
		m_pMouseCapturedControl->OnMouseUp(event);
		return true;
	}

	JuiControl *controlHit = m_pInputController->FindHitControl(event.pos);
	if(controlHit != NULL && controlHit->IsEnable())
	{
		controlHit->OnMouseUp(event);
		return true;
	}

	return false;
}

bool JuiEventManager::OnMouseMove( const MouseEventInfo &event )
{
	if(m_pMouseCapturedControl != NULL)
	{
		CheckLockMouseMove(event);
		m_pMouseCapturedControl->OnMouseMove(event);
		return true;
	}

	FindMouseControl(event);
	if(m_pMouseControl != NULL)
	{
		m_pMouseControl->OnMouseMove(event);
		return true;
	}

	return false;
}

void JuiEventManager::FindMouseControl( const MouseEventInfo &event )
{
	JuiControl *controlHit = m_pInputController->FindHitControl(event.pos);
	if(controlHit != m_pMouseControl)
	{
		if(m_pMouseControl != NULL)
			m_pMouseControl->OnMouseLeave();

		m_pMouseControl = controlHit;

		if(m_pMouseControl != NULL)
			m_pMouseControl->OnMouseEnter();
	}
}

void JuiEventManager::CheckLockMouseMove( const MouseEventInfo &event )
{
	JuiControl *controlHit = m_pInputController->FindHitControl(event.pos);
	if(controlHit != m_pMouseControl)
	{
		if(m_pMouseControl == m_pMouseCapturedControl)
			m_pMouseCapturedControl->OnMouseLeave();
		else if(controlHit == m_pMouseCapturedControl)
			m_pMouseCapturedControl->OnMouseEnter();

		m_pMouseControl = controlHit;
	}
}
