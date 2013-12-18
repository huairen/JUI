#include "JuiCreater.h"
#include <stdio.h>
#include <string.h>
#include "core/button/JuiRadioButton.h"
#include "core/container/JuiScroll.h"
#include "core/container/JuiTabBook.h"



bool JuiCreater::LoadScript( JuiContainer *root, const char* filename )
{
	char buffer[1024];
	char *line, *find, *name, *value;
	JuiControl *objStack[32] = {0};
	JuiControl *currObject = root;
	int classStack[32] = {0};
	int currObjectClass;
	int stackIndex = -1;

	FILE *pf;

	if(fopen_s(&pf, filename, "rb"))
		return false;

	strcpy_s(m_szScriptPath, sizeof(m_szScriptPath), filename);
	ForwardSlash(m_szScriptPath);

	name = strrchr(m_szScriptPath, '/');
	if(name != NULL)
		*name = 0;
	else
		m_szScriptPath[0] = 0;

	while(fgets(buffer, sizeof(buffer), pf))
	{
		line = Squish(buffer);
		if(line[0] == ';' || line[0] == '#' || line[0] == '\0')
			continue;

		if(_strnicmp(line, "new", 3) == 0)
		{
			if(currObject != NULL)
			{
				objStack[++stackIndex]  = currObject;
				currObject = NULL;

				classStack[stackIndex] = currObjectClass;
				currObjectClass = CTRL_CLASS_NONE;
			}

			line = Squish(line + 3);
			currObjectClass = GetControlClass(line);
			if(currObjectClass == CTRL_CLASS_NONE)
				break;

			currObject = CreateControl(currObjectClass);
			if(currObject == NULL)
				break;

			ParseName(currObject, line);
		}
		else if(_strnicmp(line, "end", 3) == 0)
		{
			if(stackIndex < 0)
				break;

			JuiContainer *parent = dynamic_cast<JuiContainer*>(objStack[stackIndex]);
			if(parent != NULL)
				parent->AddControl(currObject);

			currObjectClass = classStack[stackIndex];
			currObject = parent;
			stackIndex--;
		}
		else if(find = strchr(line, '='))
		{
			*find = 0;
			find++;

			name = Squish(line);
			value = Squish(find);

			if(currObject != NULL)
 				SetAttribute(currObject, currObjectClass, name, value);
		}
		else
		{
			int objClass = GetControlClass(line);
			if(objClass != CTRL_CLASS_NONE)
				currObjectClass = objClass;

			ParseName(currObject, line);
		}
	}

	fclose(pf);
	return true;
}


char* JuiCreater::Squish( char* src )
{
	char* cp = 0;

	if(src[0] == 0)
		return src;

	if(src == 0)
		return 0;

	for (cp = src + strlen(src) - 1; cp != src; --cp)
		if(!isspace(*(unsigned char*)cp))
			break;
	cp[1] = '\0';

	for (cp = src; isspace(*(unsigned char*)cp); ++cp)
		continue;

	return cp;
}

void JuiCreater::ParseName(JuiControl *com, char* line)
{
	char *find = strchr(line, '(');
	if(find == NULL)
		return;

	*find = 0;
	line = find+1;

	find = strrchr(line, ')');
	if(find == NULL)
		return;

	*find = 0;

	if(com != NULL)
		com->SetName(Squish(line));
}

void JuiCreater::ForwardSlash(char *str)
{
	while(*str)
	{
		if(*str == '\\')
			*str = '/';
		str++;
	}
}

void JuiCreater::CatPath(char *dst, const char *src, int len)
{
	if(*dst != 0)
	{
		if(*dst != '/')
		{
			++dst; --len;
			*dst = '/';
		}

		++dst; --len;
	}

	strcpy_s(dst, len, src);
	dst[len - 1] = 0;
}

char* JuiCreater::MakeFullPath( const char *file, char *buffer, int size )
{
	char bspath[256];
	strcpy_s(bspath, sizeof(bspath), file);
	bspath[sizeof(bspath)-1] = 0;

	ForwardSlash(bspath);

	if(bspath[0] == '/' || bspath[1] == ':')
	{
		strcpy_s(buffer, size, bspath);
		buffer[size - 1] = 0;
		return buffer;
	}

	strcpy_s(buffer, size, m_szScriptPath);


	char *ptr = bspath;
	char *slash = NULL;
	char *endptr = buffer + strlen(buffer) - 1;

	do 
	{
		slash = strchr(ptr, '/');
		if(slash)
		{
			*slash = 0;
			if(strcmp(ptr, "..") == 0)
			{
				if(buffer[0] == 0)
				{
					*slash = '/';
					strcpy_s(buffer, size, ptr);
					return buffer;
				}

				endptr = strrchr(buffer, '/');
				if(endptr == 0)
				{
					endptr = buffer;
					*endptr = 0;
				}
				else
				{
					*endptr-- = 0;
				}
			}
			else if(strcmp(ptr, ".") == 0)
			{
				//current dir
			}
			else if(endptr)
			{
				CatPath(endptr, ptr, size - (endptr - buffer));
				endptr += strlen(endptr) - 1;
			}

			ptr = slash + 1;
		}
		else if(endptr)
		{
			CatPath(endptr, ptr, size - (endptr - buffer));
			endptr += strlen(endptr) - 1;
		}

	} while (slash);

	return buffer;
}

int JuiCreater::GetControlClass(char *line)
{
	if(_strnicmp(line, "button", 6) == 0)
		return CTRL_CLASS_BUTTON;
	else if(_strnicmp(line, "checkbutton", 11) == 0)
		return CTRL_CLASS_CHECK_BUTTON;
	else if(_strnicmp(line, "radiobutton", 11) == 0)
		return CTRL_CLASS_RADIO_BUTTON;
	else if(_strnicmp(line, "frame", 5) == 0)
		return CTRL_CLASS_FRAME;
	else if(_strnicmp(line, "scroll", 6) == 0)
		return CTRL_CLASS_SCROLL;
	else if(_strnicmp(line, "tabBook", 7) == 0)
		return CTRL_CLASS_TABBOOK;
	else if(_strnicmp(line, "tabPage", 7) == 0)
		return CTRL_CLASS_TABPAGE;

	return CTRL_CLASS_NONE;
}

JuiControl *JuiCreater::CreateControl( int ctrlClass )
{
	switch (ctrlClass)
	{
	case CTRL_CLASS_BUTTON:
		return new JuiButton;
	case CTRL_CLASS_CHECK_BUTTON:
		return new JuiCheckButton;
	case CTRL_CLASS_RADIO_BUTTON:
		return new JuiRadioButton;
	case CTRL_CLASS_SCROLL:
		return new JuiScroll;
	case CTRL_CLASS_TABBOOK:
		return new JuiTabBook;
	case CTRL_CLASS_TABPAGE:
		return new JuiTabPage;
	}

	return NULL;
}