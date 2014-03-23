#include "JDrawable.h"
#include "JBitmapDrawable.h"
#include "JNinePatchDrawable.h"
#include "JStateListDrawable.h"
#include "FileSystem/JFileSystem.h"

JDrawable* CreateDrawableWithFile(const char* pString)
{
	char szFullPath[256];
	JFileSystem::GetInstance().MakeFullPath(pString, szFullPath, sizeof(szFullPath));

	if(JFileSystem::GetInstance().IsFileExist(szFullPath))
	{
		const char* ptr = strrchr(szFullPath, '.');
		if(ptr && (ptr - szFullPath > 2) && (*--ptr == '9') && (*--ptr == '.'))
		{
			JNinePatchDrawable* pBmp = new JNinePatchDrawable;
			if(pBmp == 0)
				return NULL;

			if(!pBmp->Load(szFullPath))
				delete pBmp;

			return pBmp;
		}
		else
		{
			JBitmapDrawable* pBmp = new JBitmapDrawable;
			if(pBmp == 0)
				return NULL;

			if(!pBmp->Load(szFullPath))
				delete pBmp;

			return pBmp;
		}
	}

	int pathLen = strlen(szFullPath);
	strcat(szFullPath, ".9.png");
	if(JFileSystem::GetInstance().IsFileExist(szFullPath))
	{
		JNinePatchDrawable* pBmp = new JNinePatchDrawable;
		if(pBmp == 0)
			return NULL;

		if(!pBmp->Load(szFullPath))
			delete pBmp;

		return pBmp;
	}

	strcpy(szFullPath + pathLen, ".png");
	if(JFileSystem::GetInstance().IsFileExist(szFullPath))
	{
		JBitmapDrawable* pBmp = new JBitmapDrawable;
		if(pBmp == 0)
			return NULL;

		if(!pBmp->Load(szFullPath))
			delete pBmp;

		return pBmp;
	}

	return NULL;
}

JDrawable::JDrawable()
{

}

JDrawable::~JDrawable()
{

}

JDrawable* JDrawable::Create(const char* pString)
{
	JDrawable* pDrawable = CreateDrawableWithFile(pString);
	if(pDrawable != NULL)
		return pDrawable;

	if(*pString == '{')
	{
		int nLen = strlen(pString);
		if(pString[nLen - 1] == '}')
		{
			JStateListDrawable* pList = new JStateListDrawable;
			if(pList == 0)
				return NULL;

			char temp[256];
			const char* ptr = pString+1;
			
			while(ptr && *ptr)
			{
				const char* endptr = strpbrk(ptr, ",}");
				if(endptr == NULL)
					break;

				nLen = endptr - ptr;
				strncpy(temp, ptr, nLen);
				temp[nLen] = 0;

				pDrawable = Create(temp);
				if(pDrawable == NULL)
				{
					delete pList;
					return NULL;
				}

				pList->Add(pDrawable, 0);
				ptr = endptr+1;
			}

			return pList;
		}
	}

	return 0;
}
