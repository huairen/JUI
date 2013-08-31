#ifndef JGDIIMAGE_H_
#define JGDIIMAGE_H_

#include <windows.h>
#include "../JImage.hxx"

class JGdiImage : public JImage
{
public:
	JGdiImage();
	virtual ~JGdiImage();

	virtual bool Load(const char* filename);
	virtual int GetHandler();

private:
	HBITMAP m_hBitmap;
};

#endif