#ifndef JRECT_H_
#define JRECT_H_

#include "JPoint.h"
#include "JMath.h"

class JRectI
{
public:
	JPoint2I position;
	JPoint2I extent;

public:
	JRectI() {};
	JRectI(const JPoint2I& _point, const JPoint2I& _size);
	JRectI(int _x, int _y, int _wigth, int _height);

	bool isValidRect() const;
	bool Intersect(const JRectI& clipRect);
	bool IsPointIn(const JPoint2I& pt);
	bool Overlaps(JRectI R) const;
	bool Contains(const JRectI& R) const;

	bool operator==(const JRectI&) const;
	bool operator!=(const JRectI&) const;
};

inline JRectI::JRectI(const JPoint2I& _position, const JPoint2I& _extent)
{
	position = _position;
	extent = _extent;
}

inline JRectI::JRectI(int _x, int _y, int _wigth, int _height)
{
	position.x = _x; position.y = _y; extent.x = _wigth; extent.y = _height;
}

inline bool JRectI::isValidRect() const
{
	return (extent.x > 0 && extent.y > 0);
}

inline bool JRectI::Intersect(const JRectI& clipRect)
{
	JPoint2I bottomL;
	bottomL.x = GetMin(position.x + extent.x, clipRect.position.x + clipRect.extent.x);
	bottomL.y = GetMin(position.y + extent.y, clipRect.position.y + clipRect.extent.y);
	
	position.x = GetMax(position.x, clipRect.position.x);
	position.y = GetMax(position.y, clipRect.position.y);

	extent.x = bottomL.x - position.x;
	extent.y = bottomL.y - position.y;

	return isValidRect();
}

inline bool JRectI::IsPointIn(const JPoint2I& pt)
{
	return (pt.x >= position.x && pt.x < position.x + extent.x && pt.y >= position.y && pt.y < position.y + extent.y);
}

inline bool JRectI::Overlaps( JRectI R ) const
{
	return R.Intersect(*this);
}

inline bool JRectI::Contains( const JRectI& R ) const
{
	if (position.x <= R.position.x && position.y <= R.position.y)
		if (R.position.x + R.extent.x <= position.x + extent.x)
			if (R.position.y + R.extent.y <= position.y + extent.y)
				return true;
	return false;
}

inline bool JRectI::operator==( const JRectI& cmp) const
{
	return (position == cmp.position) && (extent == cmp.extent);
}

inline bool JRectI::operator!=( const JRectI& cmp) const
{
	return (operator==(cmp) == false);
}

#endif                                                  