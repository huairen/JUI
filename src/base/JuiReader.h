#ifndef JUI_CREATER_H_
#define JUI_CREATER_H_

class JuiContainer;
class JuiControl;

class JuiReader
{
public:
	bool LoadScript(JuiContainer *root, const char* filename);

protected:
	char* Squish( char* src );
	void ParseName(JuiControl *com, char* line);
	void ForwardSlash(char *str);
	void CatPath(char *dst, const char *src, int len);
	char* MakeFullPath( const char *file, char *buffer, int size );

private:
	char m_szScriptPath[256];
};

#endif