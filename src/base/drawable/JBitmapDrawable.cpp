#include "JBitmapDrawable.h"
#include "Graphics/JRenderSystem.h"

JBitmapDrawable::JBitmapDrawable()
	: m_pBitmap(0)
{

}

JBitmapDrawable::~JBitmapDrawable()
{
	if(m_pBitmap != 0)
		delete m_pBitmap;
}

bool JBitmapDrawable::Load(const char* filename)
{
	m_pBitmap = JRenderSystem::GetInstance().CreateTexture(filename);
	return (m_pBitmap != NULL);
}

uint32_t JBitmapDrawable::GetWidth()
{
	if(m_pBitmap != 0)
		return m_pBitmap->GetWidth();
	return 0;
}

uint32_t JBitmapDrawable::GetHeight()
{
	if(m_pBitmap != 0)
		return m_pBitmap->GetHeight();
	return 0;
}

void JBitmapDrawable::Draw(const JRectI& rcOrigin, const JRectI& rcPaint)
{
	JRenderer* pRenderer = JRenderSystem::GetInstance().GetRenderer();
	if(pRenderer == NULL)
		return;

	float xScale = (float)m_pBitmap->GetWidth() / rcOrigin.extent.x;
	float yScale = (float)m_pBitmap->GetHeight() / rcOrigin.extent.y;

	JRectI imgRect;
	imgRect.position.x = (int)((rcPaint.position.x - rcOrigin.position.x) * xScale);
	imgRect.position.y = (int)((rcPaint.position.y - rcOrigin.position.y) * yScale);
	imgRect.extent.x = (int)(rcPaint.extent.x * xScale);
	imgRect.extent.y = (int)(rcPaint.extent.y * yScale);

	pRenderer->DrawImageStretchSR(m_pBitmap, rcPaint, imgRect);
}