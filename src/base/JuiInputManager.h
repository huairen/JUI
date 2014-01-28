#ifndef JUI_INPUTMANAGER_H_
#define JUI_INPUTMANAGER_H_

#include "JuiInputEvent.h"

class JuiContainer;
class JuiControl;

class JuiInputManager
{
public:
	JuiInputManager();
	~JuiInputManager();

	bool ProcessInputEvent(InputEventInfo &inputEvent);

	void SetController(JuiContainer* controller);
	void MouseLock(JuiControl *control);
	void MouseUnlock(JuiControl *control);

	JuiControl* GetMouseControl();
	JuiControl* GetMouseCaptureControl();

protected:
	bool ProcessKeyboardEvent(InputEventInfo &inputEvent);
	bool ProcessMouseEvent(InputEventInfo &inputEvent);

	//mouse
	bool OnMouseDown(const MouseEventInfo &event);
	bool OnMouseUp(const MouseEventInfo &event);
	bool OnMouseMove(const MouseEventInfo &event);
	void FindMouseControl(const MouseEventInfo &event);
	void CheckLockMouseMove(const MouseEventInfo &event);

private:
	JuiContainer *m_pInputController;
	JuiControl *m_pMouseControl;
	JuiControl *m_pMouseCapturedControl;
	MouseEventInfo m_LastEvent;
};

#endif