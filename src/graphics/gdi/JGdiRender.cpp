#include "JGdiRender.h"
#include "JGdiImage.h"

JGdiRender::JGdiRender()
{
	m_hWnd = NULL;
	m_hBackDC = NULL;
	m_hBackBMP = NULL;
	m_hOldBMP = NULL;
	m_bBeginPaint = false;
}

void JGdiRender::SetWindowHandler( HWND hWnd )
{
	m_hWnd = hWnd;
}

JImage * JGdiRender::CreateImage( const char* filename )
{
	JGdiImage *img = new JGdiImage;
	if(img->Load(filename))
		return img;

	delete img;
	return NULL;
}

bool JGdiRender::BeginPaint()
{
	RECT rcPaint;
	if(!::GetUpdateRect(m_hWnd, &rcPaint, FALSE))
		return false;

	m_rcUpdateRect.position.x = rcPaint.left;
	m_rcUpdateRect.position.y = rcPaint.top;
	m_rcUpdateRect.extent.x = rcPaint.right - rcPaint.left;
	m_rcUpdateRect.extent.y = rcPaint.bottom - rcPaint.top;

	::BeginPaint(m_hWnd, &m_PaintInfo);

	m_hBackDC = ::CreateCompatibleDC(m_PaintInfo.hdc);
	m_hBackBMP = ::CreateCompatibleBitmap(m_PaintInfo.hdc, m_rcUpdateRect.extent.x, m_rcUpdateRect.extent.y); 
	m_hOldBMP =  (HBITMAP)::SelectObject(m_hBackDC, m_hBackBMP);

	m_bBeginPaint = true;
	return true;
}

bool JGdiRender::EndPaint()
{
	//»æÖÆ°ëÍ¸Ã÷µ×Í¼
/*	{
		static BLENDFUNCTION blendFunc = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};

		DWORD dwExStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
		if((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
			SetWindowLong(m_hWnd, GWL_EXSTYLE, (dwExStyle | WS_EX_LAYERED));

		RECT rcWindow;
		::GetWindowRect(m_hWnd, &rcWindow);

		POINT dstPos = {rcWindow.left, rcWindow.top};
		SIZE dstSize = {rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top};
		POINT srcPos = {0, 0};

		HDC hdcTemp = ::GetWindowDC(m_hWnd);

		UpdateLayeredWindow(m_hWnd, hdcTemp, &dstPos, &dstSize, m_hBackDC, &srcPos, 0, &blendFunc, ULW_ALPHA);
		::ReleaseDC(m_hWnd, hdcTemp);
	}*/

	::BitBlt(m_PaintInfo.hdc, m_rcUpdateRect.position.x, m_rcUpdateRect.position.y,
		m_rcUpdateRect.extent.x, m_rcUpdateRect.extent.y, m_hBackDC, 0, 0, SRCCOPY);

	::SelectObject(m_hBackDC, m_hOldBMP);
	::DeleteObject(m_hBackBMP);
	::DeleteObject(m_hBackDC);

	m_bBeginPaint = false;
	::EndPaint(m_hWnd, &m_PaintInfo);
	return true;
}

bool JGdiRender::GetUpdateRect( JRectI& rect )
{
	if(!m_bBeginPaint)
		return false;

	rect = m_rcUpdateRect;
	return true;
}


void JGdiRender::DrawRect( const JRectI& rect, uint32_t color )
{

}

void JGdiRender::DrawRectFill( const JRectI& rect, uint32_t color )
{

}

void JGdiRender::DrawLine( const JPoint2I& startPt, const JPoint2I& endPt, uint32_t color )
{

}

void JGdiRender::DrawLine( int x1, int y1, int x2, int y2, uint32_t color )
{

}

void JGdiRender::DrawImage( JImage* img, const JPoint2I& pos )
{
	HBITMAP hBmp = (HBITMAP)img->GetHandler();

	HDC hSrcDc = ::CreateCompatibleDC(NULL);
	HBITMAP	hOldBmp = (HBITMAP)::SelectObject(hSrcDc, hBmp);

	::BitBlt(m_hBackDC, pos.x - m_rcUpdateRect.position.x,
		pos.y - m_rcUpdateRect.position.x, img->GetWidth(),
		img->GetHeight(), hSrcDc, 0, 0, SRCCOPY);

	::SelectObject(hSrcDc, hOldBmp);
	::DeleteObject(hSrcDc);
}

void JGdiRender::DrawImageSR( JImage* img, const JPoint2I& pos, const JRectI& srcRect )
{
	HBITMAP hBmp = (HBITMAP)img->GetHandler();

	HDC hSrcDc = ::CreateCompatibleDC(NULL);
	HBITMAP	hOldBmp = (HBITMAP)::SelectObject(hSrcDc, hBmp);

	::StretchBlt(m_hBackDC, pos.x - m_rcUpdateRect.position.x,
		pos.y - m_rcUpdateRect.position.x, img->GetWidth(), img->GetHeight(), 
		hSrcDc, srcRect.position.x, srcRect.position.y, srcRect.extent.x, srcRect.extent.y, SRCCOPY);

	::SelectObject(hSrcDc, hOldBmp);
	::DeleteObject(hSrcDc);
}

void JGdiRender::DrawImageStretch( JImage* img, const JRectI& destRect )
{
	HBITMAP hBmp = (HBITMAP)img->GetHandler();

	HDC hSrcDc = ::CreateCompatibleDC(NULL);
	HBITMAP	hOldBmp = (HBITMAP)::SelectObject(hSrcDc, hBmp);

	::BitBlt(m_hBackDC, destRect.position.x - m_rcUpdateRect.position.x,
		destRect.position.y - m_rcUpdateRect.position.y, destRect.extent.x,
		destRect.extent.y, hSrcDc, 0, 0, SRCCOPY);

	::SelectObject(hSrcDc, hOldBmp);
	::DeleteObject(hSrcDc);
}

void JGdiRender::DrawImageStretchSR( JImage* img, const JRectI& destRect, const JRectI& srcRect )
{
	HBITMAP hBmp = (HBITMAP)img->GetHandler();

	HDC hSrcDc = ::CreateCompatibleDC(NULL);
	HBITMAP	hOldBmp = (HBITMAP)::SelectObject(hSrcDc, hBmp);

	if(img->HasAlphaChannel())
	{
		BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
		::AlphaBlend(m_hBackDC, destRect.position.x - m_rcUpdateRect.position.x,
			destRect.position.y - m_rcUpdateRect.position.y, destRect.extent.x, destRect.extent.y,
			hSrcDc, srcRect.position.x, srcRect.position.y, srcRect.extent.x, srcRect.extent.y, bf);
	}
	else
	{
		::StretchBlt(m_hBackDC, destRect.position.x - m_rcUpdateRect.position.x,
			destRect.position.y - m_rcUpdateRect.position.y, destRect.extent.x, destRect.extent.y, 
			hSrcDc, srcRect.position.x, srcRect.position.y, srcRect.extent.x, srcRect.extent.y, SRCCOPY);
	}

	::SelectObject(hSrcDc, hOldBmp);
	::DeleteObject(hSrcDc);
}