#include "JuiReader.h"
#include "container/JuiContainer.h"
#include "controls/JuiListBox.h"
#include "controls/JuiRadioButton.h"

#include "JGlobalDefine.h"


bool JuiReader::LoadScript( JuiContainer *root, const char* filename )
{
	char buffer[1024];
	char *line, *find, *name, *value;
	JuiControl *objStack[32] = {0};
	JuiControl *currObject = NULL;
	int stackIndex = -1;

	FILE *pf = fopen(filename, "rb");

	if(pf == NULL)
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

		if(strnicmp(line, "new", 3) == 0)
		{
			if(currObject != NULL)
			{
				objStack[++stackIndex]  = currObject;
				currObject = NULL;
			}

			line += 4;
			size_t len = strcspn(line, " (");
			char tmp = line[len];
			line[len] = 0;
			line = Squish(line);
			currObject = dynamic_cast<JuiControl*>(JCreateDynamicObject(line));
			line += len;
			*line = tmp;

			if(currObject != NULL)
				ParseName(currObject, line);
		}
		else if(strnicmp(line, "end", 3) == 0)
		{
			if(stackIndex < 0)
				break;

			JuiContainer *parent = dynamic_cast<JuiContainer*>(objStack[stackIndex]);
			if(parent != NULL)
				parent->AddControl(currObject);

			currObject = parent;
			stackIndex--;
		}
		else if(strnicmp(line, "root", 4) == 0)
		{
			currObject = root;
			ParseName(currObject, line);
		}
		else if(find = strchr(line, '='))
		{
			*find = 0;
			find++;

			name = Squish(line);
			value = Squish(find);

			if(currObject != NULL)
 				currObject->SetProperty(name, value);
		}
	}

	fclose(pf);
	return true;
}


char* JuiReader::Squish( char* src )
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

void JuiReader::ParseName(JuiControl *com, char* line)
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

void JuiReader::ForwardSlash(char *str)
{
	while(*str)
	{
		if(*str == '\\')
			*str = '/';
		str++;
	}
}

void JuiReader::CatPath(char *dst, const char *src, int len)
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

char* JuiReader::MakeFullPath( const char *file, char *buffer, int size )
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