#include "JuiCreater.hxx"
#include <stdio.h>
#include <string.h>
#include "core/button/JuiRadioButton.hxx"
#include "core/layout/JuiHorizontalLayout.hxx"

static char* Squish( char* src )
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

static void ParseName(JuiControl *com, char* line)
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

static bool IsFilePath(const char *str)
{
	while(*str)
	{
		if(*str == '\\' || *str == '/')
			return true;
		str++;
	}
	return false;
}

static void ForwardSlash(char *str)
{
	while(*str)
	{
		if(*str == '\\')
			*str = '/';
		str++;
	}
}

static void CatPath(char *dst, const char *src, int len)
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

static char* MakeFullPath( const char *file, char *buffer, int size )
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

	char *endptr = strrchr(buffer, '/');
	if(endptr == NULL)
	{
		endptr = buffer;
		*endptr = 0;
	}
	else
	{
		*endptr-- = 0;
	}


	char *ptr = bspath;
	char *slash = NULL;

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

static int GetControlClass(char *line)
{
	if(_strnicmp(line, "button", 6) == 0)
		return CTRL_CLASS_BUTTON;
	else if(_strnicmp(line, "checkbutton", 11) == 0)
		return CTRL_CLASS_CHECK_BUTTON;
	else if(_strnicmp(line, "radiobutton", 11) == 0)
		return CTRL_CLASS_RADIO_BUTTON;
	else if(_strnicmp(line, "frame", 5) == 0)
		return CTRL_CLASS_FRAME;
	else if(_strnicmp(line, "horizontalLayout", 16) == 0)
		return CTRL_CLASS_HORIZLAYOUT;

	return CTRL_CLASS_NONE;
}

static JuiControl *CreateControl( int ctrlClass )
{
	switch (ctrlClass)
	{
	case CTRL_CLASS_BUTTON:
		return new JuiButton;
	case CTRL_CLASS_CHECK_BUTTON:
		return new JuiCheckButton;
	case CTRL_CLASS_RADIO_BUTTON:
		return new JuiRadioButton;
	case CTRL_CLASS_HORIZLAYOUT:
		return new JuiHorizontalLayout;
	}

	return NULL;
}


bool JuiCreater::LoadScript( JuiContainer *root, const char* filename )
{
	char filePath[1024];
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

			if(IsFilePath(value))
			{
				strcpy_s(filePath, sizeof(filePath), filename);
				value = MakeFullPath(value, filePath, sizeof(filePath));
			}

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