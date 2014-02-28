#ifndef JUI_INPUTEVENT_H_
#define JUI_INPUTEVENT_H_

#include "math/JPoint.h"

enum InputObjectInstances
{
	KEY_NONE          = 0,
	KEY_BUTTON0       = 0x0100,
	KEY_BUTTON1       = 0x0101,
	KEY_BUTTON2       = 0x0102,
	KEY_BUTTON3       = 0x0103,
	KEY_BUTTON4       = 0x0104,
};

enum InputDeviceType
{
	INPUT_DEVICE_UNKNOWN,
	INPUT_DEVICE_MOUSE,
	INPUT_DEVICE_KEYBOARD,
	NUM_INPUT_DEVICE_TYPES,
};

enum InputActionType
{
	INPUT_ACTION_DBCLICK,
	INPUT_ACTION_PRESS,
	INPUT_ACTION_RELEASE,
	INPUT_ACTION_MOVE,
};

enum InputModifiers
{
	IM_LSHIFT = 0x0001,
	IM_RSHIFT = 0x0002,
	IM_SHIFT = (IM_LSHIFT | IM_RSHIFT),

	IM_LCTRL = 0x0004,
	IM_RCTRL = 0x0008,
	IM_CTRL = (IM_LCTRL | IM_RCTRL),

	IM_LALT = 0x0010,
	IM_RALT = 0x0020,
	IM_ALT = (IM_LALT | IM_RALT),
};


enum ControlMessage
{
	MSG_CLICK,
	MSG_RADIO_CLICK,
};


struct InputEventInfo
{
	InputDeviceType deviceType;
	InputActionType action;
	InputObjectInstances objInst;
	JPoint2I pos;
	JPoint2I gap;
};

struct MouseEventInfo
{
	InputObjectInstances button;
	JPoint2I pos;
	int clickCount;
};

#endif                                                  