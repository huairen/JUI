#include "JGdiImage.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
	extern uint8_t *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
	extern void stbi_image_free(void *retval_from_stbi_load);
#ifdef __cplusplus
}
#endif

JGdiImage::JGdiImage()
{

}

JGdiImage::~JGdiImage()
{

}

bool JGdiImage::Load( const char* filename )
{
	int x,y,n;
	uint8_t *pPixel = NULL;

	pPixel = stbi_load(filename, &x, &y, &n, 4);
	if(pPixel == NULL)
		return false;

	BITMAPINFO bmi;
	::ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = x;
	bmi.bmiHeader.biHeight = -y;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = x * y * 4;

	bool bAlphaChannel = false;
	LPBYTE pDest = NULL;
	HBITMAP hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pDest, NULL, 0);
	if( !hBitmap ) {
		stbi_image_free(pPixel);
		return false;
	}

	for( int i = 0; i < x * y; i++ ) 
	{
		pDest[i*4 + 3] = pPixel[i*4 + 3];
		if( pDest[i*4 + 3] < 255 )
		{
			pDest[i*4] = (BYTE)(DWORD(pPixel[i*4 + 2])*pPixel[i*4 + 3]/255);
			pDest[i*4 + 1] = (BYTE)(DWORD(pPixel[i*4 + 1])*pPixel[i*4 + 3]/255);
			pDest[i*4 + 2] = (BYTE)(DWORD(pPixel[i*4])*pPixel[i*4 + 3]/255); 
			bAlphaChannel = true;
		}
		else
		{
			pDest[i*4] = pPixel[i*4 + 2];
			pDest[i*4 + 1] = pPixel[i*4 + 1];
			pDest[i*4 + 2] = pPixel[i*4]; 
		}

		if( *(DWORD*)(&pDest[i*4]) == 0 ) {
			pDest[i*4] = (BYTE)0;
			pDest[i*4 + 1] = (BYTE)0;
			pDest[i*4 + 2] = (BYTE)0; 
			pDest[i*4 + 3] = (BYTE)0;
			bAlphaChannel = true;
		}
	}

	stbi_image_free(pPixel);

	m_hBitmap = hBitmap;
	m_nWidth = x;
	m_nHeight = y;
	m_bAlphaChannel = bAlphaChannel;
	return true;
}

int JGdiImage::GetHandler()
{
	return (int)m_hBitmap;
}
