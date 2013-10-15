#include "JuiCreater.hxx"
#include "core/button/JuiRadioButton.hxx"
#include "core/container/JuiScroll.hxx"
#include "core/container/JuiTabBook.hxx"
#include "win32/JuiFrame.hxx"

void JuiCreater::AttriPoint(JuiControl *control, int ctrlClass, int param, char* value)
{
	char* tok;
	char* next;
	
	tok = strtok_s(value, " ,", &next);
	if(tok && next)
	{
		switch (param)
		{
		case PT_EFFECT_POSITION:
			control->SetPosition(atoi(tok), atoi(next));
			break;
		case PT_EFFECT_SIZE:
			control->SetExtent(atoi(tok), atoi(next));
			break;
		case PT_EFFECT_MINSIZE:
			control->SetMinSize(atoi(tok), atoi(next));
			break;
		case PT_EFFECT_MAXSIZE:
			control->SetMaxSize(atoi(tok), atoi(next));
			break;
		}
	}
}

void JuiCreater::AttriHorizAlign(JuiControl *control, int ctrlClass, int param, char* value)
{
	if(_strnicmp(value, "left", 4) == 0)
		control->SetHorizAlign(CTRL_HORIZ_ALIGN_LEFT);
	else if(_strnicmp(value, "right", 5) == 0)
		control->SetHorizAlign(CTRL_HORIZ_ALIGN_RIGHT);
	else if(_strnicmp(value, "center", 6) == 0)
		control->SetHorizAlign(CTRL_HORIZ_ALIGN_CENTER);
	else if(_strnicmp(value, "width", 5) == 0)
		control->SetHorizAlign(CTRL_HORIZ_ALIGN_WIDTH);
}

void JuiCreater::AttriVertAlign(JuiControl *control, int ctrlClass, int param, char* value)
{
	if(_strnicmp(value, "top", 3) == 0)
		control->SetVertAlign(CTRL_VERT_ALIGN_TOP);
	else if(_strnicmp(value, "bottom", 6) == 0)
		control->SetVertAlign(CTRL_VERT_ALIGN_BOTTOM);
	else if(_strnicmp(value, "center", 6) == 0)
		control->SetVertAlign(CTRL_VERT_ALIGN_CENTER);
	else if(_strnicmp(value, "height", 6) == 0)
		control->SetVertAlign(CTRL_VERT_ALIGN_HEIGHT);
}

void JuiCreater::AttriScaleMode(JuiControl *control, int ctrlClass, int param, char* value)
{
	if(_strnicmp(value, "all", 3) == 0)
		control->SetScaleMode(CTRL_SCALE_ALL);
	else if(_strnicmp(value, "center", 6) == 0)
		control->SetScaleMode(CTRL_SCALE_CENTER);
	else if(_strnicmp(value, "side", 4) == 0)
		control->SetScaleMode(CTRL_SCALE_SIDE);
}

void JuiCreater::AttriFlag(JuiControl *control, int ctrlClass, int param, char* value)
{
	if(!_strnicmp(value, "true", 4) || atoi(value))
		control->AddFlag(param);
	else
		control->RemoveFlag(param);
}

void JuiCreater::AttriImage(JuiControl *control, int ctrlClass, int param, char* value)
{
	char fullPath[256];
	MakeFullPath(value, fullPath, sizeof(fullPath));

	if(ctrlClass == CTRL_CLASS_FRAME)
	{
		static_cast<JuiFrame*>(control)->SetBackground(fullPath);
	}
	else if(ctrlClass == CTRL_CLASS_SCROLL)
	{
		if(param == IMG_EFFECT_BAR)
			static_cast<JuiScroll*>(control)->LoadBarImage(fullPath);
		else if(param == IMG_EFFECT_ARROW)
			static_cast<JuiScroll*>(control)->LoadArrowImage(fullPath);
	}
	else if (ctrlClass == CTRL_CLASS_TABBOOK)
	{
		switch (param)
		{
		case IMG_EFFECT_NORMAL:
			static_cast<JuiTabBook*>(control)->LoadNormalImage(fullPath);
			break;
		case IMG_EFFECT_HIGHLIGHT:
			static_cast<JuiTabBook*>(control)->LoadHighlightImage(fullPath);
			break;
		case IMG_EFFECT_PRESS:
			static_cast<JuiTabBook*>(control)->LoadPressImage(fullPath);
			break;
		}
	}
	else if (ctrlClass & CTRL_CLASS_BUTTON)
	{
		switch (param)
		{
		case IMG_EFFECT_NORMAL:
			static_cast<JuiButton*>(control)->LoadNormalImage(fullPath);
			break;
		case IMG_EFFECT_HIGHLIGHT:
			static_cast<JuiButton*>(control)->LoadHighlightImage(fullPath);
			break;
		case IMG_EFFECT_PRESS:
			static_cast<JuiButton*>(control)->LoadPressImage(fullPath);
			break;
		}
	}
	
}

void JuiCreater::AttriStateOn(JuiControl *control, int ctrlClass, int param, char* value)
{
	bool bStateOn = (!_strnicmp(value, "true", 4) || atoi(value));

	if(ctrlClass == CTRL_CLASS_CHECK_BUTTON)
		static_cast<JuiCheckButton*>(control)->SetStateOn(bStateOn);
	else if(ctrlClass == CTRL_CLASS_RADIO_BUTTON && bStateOn)
		static_cast<JuiRadioButton*>(control)->SetStateOn();
}

struct ControlAttribute
{
	char name[32];
	int nameLen;
	int objClass;
	void (JuiCreater::*attriFunc)(JuiControl*,int,int,char*);
	int param;
};

ControlAttribute attriTable[] = {
	{"position", 8, CTRL_CLASS_BASE, &JuiCreater::AttriPoint, PT_EFFECT_POSITION},
	{"size", 4, CTRL_CLASS_BASE, &JuiCreater::AttriPoint,PT_EFFECT_SIZE},
	{"minSize", 7, CTRL_CLASS_BASE, &JuiCreater::AttriPoint, PT_EFFECT_MINSIZE},
	{"maxSize", 7, CTRL_CLASS_BASE, &JuiCreater::AttriPoint, PT_EFFECT_MAXSIZE},
	{"horizAlign", 10, CTRL_CLASS_BASE, &JuiCreater::AttriHorizAlign, 0},
	{"vertAlign", 9, CTRL_CLASS_BASE, &JuiCreater::AttriVertAlign, 0},
	{"visible", 7, CTRL_CLASS_BASE, &JuiCreater::AttriFlag, CTRL_FLAG_VISIBLE},
	{"enable", 6, CTRL_CLASS_BASE, &JuiCreater::AttriFlag, CTRL_FLAG_ENABLE},
	{"readonly", 8, CTRL_CLASS_BASE, &JuiCreater::AttriFlag, CTRL_FLAG_READONLY},
	{"mouseEnable", 11, CTRL_CLASS_BASE, &JuiCreater::AttriFlag, CTRL_FLAG_MOUSE_ENABLE},
	{"keyboardEnable", 14, CTRL_CLASS_BASE, &JuiCreater::AttriFlag, CTRL_FLAG_KEYBOARD_ENABLE},
	{"scaleMode", 9, CTRL_CLASS_BASE, &JuiCreater::AttriScaleMode, 0},
	{"image", 5, CTRL_CLASS_FRAME, &JuiCreater::AttriImage, IMG_EFFECT_BACKGROUND},
	{"barImage", 5, CTRL_CLASS_SCROLL, &JuiCreater::AttriImage, IMG_EFFECT_BAR},
	{"arrowImage", 5, CTRL_CLASS_SCROLL, &JuiCreater::AttriImage, IMG_EFFECT_ARROW},
	{"normalImage", 11, CTRL_CLASS_BUTTON | CTRL_CLASS_TABBOOK, &JuiCreater::AttriImage, IMG_EFFECT_NORMAL},
	{"highlightImage", 14, CTRL_CLASS_BUTTON | CTRL_CLASS_TABBOOK, &JuiCreater::AttriImage, IMG_EFFECT_HIGHLIGHT},
	{"pressImage", 10, CTRL_CLASS_BUTTON | CTRL_CLASS_TABBOOK, &JuiCreater::AttriImage, IMG_EFFECT_PRESS},
	{"stateOn", 7, CTRL_CLASS_RADIO_BUTTON, &JuiCreater::AttriStateOn, 0},
};

const int attriNum = sizeof(attriTable) / sizeof(ControlAttribute);


bool JuiCreater::SetAttribute( JuiControl *control, int ctrlClass, const char *name, char *value )
{
	int nameLen = strlen(name);

	for (int i = 0; i < attriNum; i++)
	{
		ControlAttribute &attri = attriTable[i];

		if(attri.nameLen != nameLen || !(attri.objClass & ctrlClass))
			continue;

		if(_stricmp(attri.name, name) == 0)
		{
			(this->*attri.attriFunc)(control, ctrlClass, attri.param, value);
			break;
		}
	}

	return true;
}
