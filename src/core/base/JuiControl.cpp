#include "JuiControl.h"
#include "core/container/JuiContainer.h"


JRender* JuiControl::sm_pRender = NULL;

JuiControl::JuiControl() : m_nFlags(CTRL_FLAG_ENABLE | CTRL_FLAG_VISIBLE | CTRL_FLAG_MOUSE_ENABLE),
	m_HorizAlign(CTRL_HORIZ_ALIGN_LEFT), m_VerzAlign(CTRL_VERT_ALIGN_TOP), m_ScaleMode(CTRL_SCALE_CENTER),
	m_pParent(0), m_rcBounds(0,0,100,100), m_ptMinSize(8,2), m_ptMaxSize(-1,-1)
{
	m_szName[0] = 0;
}

JuiControl::~JuiControl()
{

}

JuiControl* JuiControl::GetRoot()
{
	JuiControl *root = NULL;
	JuiControl *parent = GetParent();

	while (parent)
	{
		root = parent;
		parent = parent->GetParent();
	}

	return root;
}

void JuiControl::SetUpdateRegion( const JPoint2I& pos, const JPoint2I& size )
{
	JuiControl *root = GetRoot();
	if(root != NULL)
		root->AddUpdateRegion(LocalToRoot(pos), size);
}

void JuiControl::SetUpdate()
{
	SetUpdateRegion(JPoint2I(0,0), GetExtent());
}

void JuiControl::MouseLock()
{
	JuiControl *root = GetRoot();
	if(!root)
		return;

	JuiInputManager *input = root->GetInputGenerator();
	if(input)
		input->MouseLock(this);
}

void JuiControl::MouseUnlock()
{
	JuiControl *root = GetRoot();
	if(!root)
		return;

	JuiInputManager *input = root->GetInputGenerator();
	if(input)
		input->MouseUnlock(this);
}

bool JuiControl::IsMouseLocked()
{
	JuiControl *root = GetRoot();
	if(!root)
		return false;

	JuiInputManager *input = root->GetInputGenerator();
	if(input)
		return input->GetMouseCaptureControl() == this;
	return false;
}

void JuiControl::SetBounds(const JPoint2I& position, const JPoint2I& extent)
{
	m_rcBounds.extent = extent;
	m_rcBounds.position = position;
}

bool JuiControl::IsPointIn( const JPoint2I& pt )
{
	return m_rcBounds.IsPointIn(pt);
}

JPoint2I JuiControl::LocalToRoot( const JPoint2I &pos )
{
	JPoint2I ret = pos;
	ret += GetPosition();

	JuiControl* ptr = m_pParent;
	while(ptr)
	{
		ret += ptr->GetPosition();
		ptr = ptr->m_pParent;
	}

	return ret;
}

void JuiControl::SetVisible(bool value)
{
	if(value)
		AddFlag(CTRL_FLAG_VISIBLE);
	else
		RemoveFlag(CTRL_FLAG_VISIBLE);
}

void JuiControl::OnParentResized( const JRectI &oldRect, const JRectI &newRect )
{
	JPoint2I newPosition = GetPosition();
	JPoint2I newSize = GetExtent();

	int deltaX = newRect.extent.x - oldRect.extent.x;
	int deltaY = newRect.extent.y - oldRect.extent.y;

	switch (m_HorizAlign)
	{
	case CTRL_HORIZ_ALIGN_CENTER:
		newPosition.x = (newRect.extent.x - GetWidth()) >> 1;
		break;
	case CTRL_HORIZ_ALIGN_RIGHT:
		newPosition.x += deltaX;
		break;
	case CTRL_HORIZ_ALIGN_WIDTH:
		newSize.x += deltaX;
		break;
	}

	switch (m_VerzAlign)
	{
	case CTRL_VERT_ALIGN_CENTER:
		newPosition.y = (newRect.extent.y - GetHeight()) >> 1;
		break;
	case CTRL_VERT_ALIGN_BOTTOM:
		newPosition.y += deltaY;
		break;
	case CTRL_VERT_ALIGN_HEIGHT:
		newSize.y += deltaY;
		break;
	}

	SetBounds(newPosition, newSize);
}

void JuiControl::NotifySiblings( int message, int param )
{
	JuiContainer *parent = GetParent();
	if(parent == NULL)
		return;

	JuiControl *ctrl = parent->FirstChild();
	while(ctrl)
	{
		if(ctrl != this)
			ctrl->OnControlEvent(this, message, param);
		ctrl = parent->NextChild();
	}
}


void JuiControl::DrawImage( JImage* img, const JPoint2I &offset, const JRectI &rcPaint,
						   const JRectI *srcRect, const JRectI *destRect )
{
	if(img == NULL)
		return;

	JRectI rcSrc(0,0,img->GetWidth(),img->GetHeight());
	JRectI rcDest = m_rcBounds;

	if(srcRect != NULL)
		rcSrc = *srcRect;

	if(destRect != NULL)
		rcDest = *destRect;

	//Í¼Æ¬²»Ëõ·Å
	if(rcSrc.extent == rcDest.extent)
	{
		JRectI imgRect = rcPaint;
		imgRect.position -= offset;

		sm_pRender->DrawImageStretchSR(img, rcPaint, imgRect);
		return;
	}

	switch(m_ScaleMode)
	{
	case CTRL_SCALE_ALL:
		{
			float xScale = (float)rcSrc.extent.x / rcDest.extent.x;
			float yScale = (float)rcSrc.extent.y / rcDest.extent.y;

			JRectI imgRect;
			imgRect.position.x = (int)((rcPaint.position.x - offset.x) * xScale);
			imgRect.position.y = (int)((rcPaint.position.y - offset.y) * yScale);
			imgRect.extent.x = (int)(rcPaint.extent.x * xScale);
			imgRect.extent.y = (int)(rcPaint.extent.y * yScale);

			sm_pRender->DrawImageStretchSR(img, rcPaint, imgRect);
		}
		break;
	case CTRL_SCALE_CENTER:
		{
			JRectI currRect = rcPaint;
			JRectI nextRect = rcPaint;

			for (int y = 0; y < 3; y++)
			{
				currRect.position.x = nextRect.position.x;
				currRect.extent.x = nextRect.extent.x;
				nextRect.position.y = currRect.position.y;
				nextRect.extent.y = currRect.extent.y;

				for (int x = 0; x < 3; x++)
				{
					currRect.position.y = nextRect.position.y;
					currRect.extent.y = nextRect.extent.y;

					DrawImageScaleCenter(img, offset, currRect, rcSrc, rcDest);

					if(currRect.extent.x == 0)
						break;
				}

				if(currRect.extent.y == 0)
					break;
			}
		}
		break;
	case CTRL_SCALE_SIDE:
		{
		}
		break;
	}
}

void JuiControl::DrawImageScaleCenter( JImage* img, const JPoint2I &offset, JRectI &rcPaint,
									  const JRectI &srcRect, const JRectI &destRect )
{
	JRectI imgRect;
	JRectI paintRect;
	JPoint2I startPos;

	bool xScale = (srcRect.extent.x != destRect.extent.x);
	bool yScale = (srcRect.extent.y != destRect.extent.y);

	int imgHalfWidth = srcRect.extent.x >> 1;
	int imgHalfHeight = srcRect.extent.y >> 1;

	int rightStart = destRect.extent.x - imgHalfWidth;
	int bottomStart = destRect.extent.y - imgHalfHeight;

	paintRect.position.x = rcPaint.position.x;
	paintRect.position.y = rcPaint.position.y;
	startPos = paintRect.position - offset;

	if(!xScale)
	{
		paintRect.extent.x = rcPaint.extent.x;
		imgRect.position.x = 0;
		imgRect.extent.x = paintRect.extent.x;
	}
	else if(startPos.x < imgHalfWidth)
	{
		paintRect.extent.x = GetMin(rcPaint.extent.x, imgHalfWidth - startPos.x);
		imgRect.position.x = (paintRect.position.x - offset.x);
		imgRect.extent.x = paintRect.extent.x;
	}
	else if(startPos.x < rightStart)
	{
		paintRect.extent.x = GetMin(rcPaint.extent.x, rightStart - startPos.x);
		imgRect.position.x = imgHalfWidth;
		imgRect.extent.x = 1;
	}
	else
	{
		paintRect.extent.x = rcPaint.extent.x;
		imgRect.position.x = startPos.x - (destRect.extent.x - srcRect.extent.x);
		imgRect.extent.x = paintRect.extent.x;
	}

	if(!yScale)
	{
		paintRect.extent.y = rcPaint.extent.y;
		imgRect.position.y = 0;
		imgRect.extent.y = paintRect.extent.y;
	}
	else if(startPos.y < imgHalfHeight)
	{
		paintRect.extent.y = GetMin(rcPaint.extent.y, imgHalfHeight - startPos.y);
		imgRect.position.y = (paintRect.position.y - offset.y);
		imgRect.extent.y = paintRect.extent.y;
	}
	else if(startPos.y < bottomStart)
	{
		paintRect.extent.y = GetMin(rcPaint.extent.y, bottomStart - startPos.y);
		imgRect.position.y = imgHalfHeight;
		imgRect.extent.y = 1;
	}
	else
	{
		paintRect.extent.y = rcPaint.extent.y;
		imgRect.position.y = startPos.y - (destRect.extent.y - srcRect.extent.y);
		imgRect.extent.y = paintRect.extent.y;
	}

	sm_pRender->DrawImageStretchSR(img, paintRect, imgRect);

	rcPaint.position.x += paintRect.extent.x;
	rcPaint.position.y += paintRect.extent.y;
	rcPaint.extent.x -= paintRect.extent.x;
	rcPaint.extent.y -= paintRect.extent.y;
}

