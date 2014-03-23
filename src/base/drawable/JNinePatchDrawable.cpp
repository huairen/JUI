#include "JNinePatchDrawable.h"
#include "Graphics/JRenderSystem.h"
#include "Graphics/JImage.h"

JNinePatchDrawable::JNinePatchDrawable()
	: m_pBitmap(0)
{

}

JNinePatchDrawable::~JNinePatchDrawable()
{
	if(m_pBitmap != 0)
		delete m_pBitmap;
}

bool JNinePatchDrawable::Load(const char* filename)
{
	JImage img;
	if(!img.LoadFromFile(filename))
		return false;

	FindArea(&img);
	m_pBitmap = JRenderSystem::GetInstance().CreateTexture(&img);
	return (m_pBitmap != NULL);
}


void JNinePatchDrawable::Draw(const JRectI &rcOrigin, const JRectI &rcPaint)
{
	JRenderer* pRenderer = JRenderSystem::GetInstance().GetRenderer();
	if(pRenderer == NULL)
		return;

	JRectI destRect,srcRect;
	int paintPosY, imagePosY;

	for (int i=0; i<m_FixedAreaList.GetCount(); i++)
	{
		const JRectI& patchRect = m_FixedAreaList.At(i);
		JPoint2I pos = DrawFixedPatch(patchRect, rcOrigin, rcPaint);

		if(patchRect.position.x > 1)
		{
			destRect.position.y = pos.y;
			destRect.extent.x = pos.x - destRect.position.x;
			destRect.extent.y = patchRect.extent.y;

			srcRect.position.y = patchRect.position.y;
			srcRect.extent.x = patchRect.position.x - srcRect.position.x;
			srcRect.extent.y = patchRect.extent.y;

			int ySave = destRect.position.y;
			if(destRect.Intersect(rcPaint))
			{
				srcRect.position.y += (destRect.position.y - ySave);
				srcRect.extent.y = destRect.extent.y;
				pRenderer->DrawImageStretchSR(m_pBitmap, destRect, srcRect);
			}

			if(patchRect.position.y > 1)
			{
				destRect.extent.y = destRect.position.y - paintPosY;
				destRect.position.y -= destRect.extent.y;

				srcRect.extent.y = srcRect.position.y - imagePosY;
				srcRect.position.y -= srcRect.extent.y;
				
				if(destRect.Intersect(rcPaint))
					pRenderer->DrawImageStretchSR(m_pBitmap, destRect, srcRect);
			}

		}

		if(patchRect.position.y > 1)
		{
			destRect.position.x = pos.x;
			destRect.position.y = paintPosY;
			destRect.extent.x = patchRect.extent.x;
			destRect.extent.y = pos.y - paintPosY;

			srcRect.position.x = patchRect.position.x;
			srcRect.position.y = imagePosY;
			srcRect.extent.x = patchRect.extent.x;
			srcRect.extent.y = patchRect.position.y - imagePosY;

			int xSave = destRect.position.x;
			if(destRect.Intersect(rcPaint))
			{
				srcRect.position.x += (destRect.position.x - xSave);
				srcRect.extent.x = destRect.extent.x;
				pRenderer->DrawImageStretchSR(m_pBitmap, destRect, srcRect);
			}
		}

		destRect.position.x = pos.x + patchRect.extent.x;
		srcRect.position.x = patchRect.position.x + patchRect.extent.x;

		if((uint32_t)(patchRect.position.x + patchRect.extent.x + 1) >= m_pBitmap->GetWidth())
		{
			paintPosY = pos.y + patchRect.extent.y;
			imagePosY = patchRect.position.y + patchRect.extent.y;
		}
	}
}

void JNinePatchDrawable::FindArea(const JImage *img)
{
	JArray<JPoint2I> fixedX,fixedY;

	uint32_t lastPixel;
	for (uint32_t i=1; i<img->GetWidth(); ++i)
	{
		uint32_t pixel = img->GetPixel(i, 0);

		if(i == 1 || i+1 == img->GetWidth() || lastPixel != pixel)
		{
			if(!fixedX.IsEmpty() && ((lastPixel&0xff000000) == 0 || (lastPixel&0x00ffffff) != 0))
			{
				fixedX.Last().y = i - fixedX.Last().x;
			}

			//透明 或者 不是黑色，则为不缩放区域
			if((i+1 != img->GetWidth()) && ((pixel&0xff000000) == 0 || (pixel&0x00ffffff) != 0))
			{
				fixedX.Increment();
				fixedX.Last().x  = i;
			}
		}

		lastPixel = pixel;
	}


	for (uint32_t i=1; i<img->GetHeight(); ++i)
	{
		uint32_t pixel = img->GetPixel(0, i);

		if(i == 1 || i+1 == img->GetHeight() || lastPixel != pixel)
		{
			if(!fixedY.IsEmpty() && ((lastPixel&0xff000000) == 0 || (lastPixel&0x00ffffff) != 0))
			{
				fixedY.Last().y = i - fixedY.Last().x;
			}

			//透明 或者 不是黑色，则为不缩放区域
			if((i+1 != img->GetHeight()) && ((pixel&0xff000000) == 0 || (pixel&0x00ffffff) != 0))
			{
				fixedY.Increment();
				fixedY.Last().x  = i;
			}
		}

		lastPixel = pixel;
	}

	for (int y=0; y<fixedY.GetCount(); y++)
	{
		for (int x=0; x<fixedX.GetCount(); x++)
		{
			m_FixedAreaList.Increment();
			m_FixedAreaList.Last().position.x = fixedX.At(x).x;
			m_FixedAreaList.Last().position.y = fixedY.At(y).x;
			m_FixedAreaList.Last().extent.x = fixedX.At(x).y;
			m_FixedAreaList.Last().extent.y = fixedY.At(y).y;
		}
	}
}

JPoint2I JNinePatchDrawable::DrawFixedPatch( const JRectI &rcPatch, const JRectI &rcOrigin, const JRectI &rcPaint )
{
	JPoint2I pos;

	if(rcPatch.position.x <= 1)
		pos.x = rcOrigin.position.x;
	else if((uint32_t)(rcPatch.position.x + rcPatch.extent.x + 1) >= m_pBitmap->GetWidth())
		pos.x = rcOrigin.extent.x - rcPatch.extent.x;
	else
	{
		float scale = (float)(rcPatch.position.x + (rcPatch.extent.x>>1)) / m_pBitmap->GetWidth();
		int center = (int)(rcOrigin.extent.x * scale);
		pos.x = center - (rcPatch.extent.x>>1);
	}

	if(rcPatch.position.y <= 1)
		pos.y = rcOrigin.position.y;
	else if((uint32_t)(rcPatch.position.y + rcPatch.extent.y + 1) >= m_pBitmap->GetHeight())
		pos.y = rcOrigin.extent.y - rcPatch.extent.y;
	else
	{
		float scale = (float)(rcPatch.position.y + (rcPatch.extent.y>>1)) / m_pBitmap->GetHeight();
		int center = (int)(rcOrigin.extent.y * scale);
		pos.y = center - (rcPatch.extent.y>>1);
	}

	JRectI imgRect(pos, rcPatch.extent);
	if(imgRect.Intersect(rcPaint))
	{
		JPoint2I clipPos = imgRect.position;
		imgRect.position = clipPos - pos + rcPatch.position;
		JRenderSystem::GetInstance().DrawImageSR(m_pBitmap, clipPos, imgRect);
	}

	return pos;
}