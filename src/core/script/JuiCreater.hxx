#ifndef JUI_CREATER_H_
#define JUI_CREATER_H_

#include "core/container/JuiContainer.hxx"

enum ControlClass
{
	CTRL_CLASS_NONE,
	CTRL_CLASS_BASE			= 0x0001,
	CTRL_CLASS_CONTAINER	= (0x0002 | CTRL_CLASS_BASE),
	CTRL_CLASS_BUTTON		= (0x0004 | CTRL_CLASS_BASE),
	CTRL_CLASS_FRAME		= (0x0008 | CTRL_CLASS_CONTAINER),
	CTRL_CLASS_SCROLL		= (0x0010 | CTRL_CLASS_CONTAINER),
	CTRL_CLASS_HORIZLAYOUT	= (0x0020 | CTRL_CLASS_CONTAINER),
	CTRL_CLASS_CHECK_BUTTON	= (0x0040 | CTRL_CLASS_BUTTON),
	CTRL_CLASS_RADIO_BUTTON	= (0x0080 | CTRL_CLASS_CHECK_BUTTON),
};

enum ImageEffect
{
	IMG_EFFECT_BACKGROUND,
	IMG_EFFECT_NORMAL,
	IMG_EFFECT_PRESS,
	IMG_EFFECT_HIGHLIGHT,
	IMG_EFFECT_BAR,
	IMG_EFFECT_ARROW,
};

enum PointEffect
{
	PT_EFFECT_POSITION,
	PT_EFFECT_SIZE,
	PT_EFFECT_MINSIZE,
	PT_EFFECT_MAXSIZE,
};

class JuiCreater
{
public:
	static bool LoadScript(JuiContainer *root, const char* filename);
	static bool SetAttribute(JuiControl *control, int ctrlClass, const char *name, char *value);
};

#endif