#ifndef JUI_CREATER_H_
#define JUI_CREATER_H_

class JuiContainer;
class JuiControl;

class JuiReader
{
public:
	static bool LoadScript(JuiContainer *root, const char* filename);
};

#endif