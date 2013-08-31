#ifndef JRECT_H_
#define JRECT_H_

#include "JPoint.hxx"
#include "JMath.hxx"

class JRectI
{
public:
	JPoint2I point;
	JPoint2I size;

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

inline JRectI::JRectI(const JPoint2I& _point, const JPoint2I& _size)
{
	point = _point;
	size = _size;
}

inline JRectI::JRectI(int _x, int _y, int _wigth, int _height)
{
	point.x = _x; point.y = _y; size.x = _wigth; size.y = _height;
}

inline bool JRectI::isValidRect() const
{
	return (size.x > 0 && size.y > 0);
}

inline bool JRectI::Intersect(const JRectI& clipRect)
{
	JPoint2I bottomL;
	bottomL.x = GetMin(point.x + size.x, clipRect.point.x + clipRect.size.x);
	bottomL.y = GetMin(point.y + size.y, clipRect.point.y + clipRect.size.y);
	
	point.x = GetMax(point.x, clipRect.point.x);
	point.y = GetMax(point.y, clipRect.point.y);

	size.x = bottomL.x - point.x;
	size.y = bottomL.y - point.y;

	return isValidRect();
}

inline bool JRectI::IsPointIn(const JPoint2I& pt)
{
	return (pt.x >= point.x && pt.x < point.x + size.x && pt.y >= point.y && pt.y < point.y + size.y);
}

inline bool JRectI::Overlaps( JRectI R ) const
{
	return R.Intersect(*this);
}

inline bool JRectI::Contains( const JRectI& R ) const
{
	if (point.x <= R.point.x && point.y <= R.point.y)
		if (R.point.x + R.size.x <= point.x + size.x)
			if (R.point.y + R.size.y <= point.y + size.y)
				return true;
	return false;
}

inline bool JRectI::operator==( const JRectI& cmp) const
{
	return (point == cmp.point) && (size == cmp.size);
}

inline bool JRectI::operator!=( const JRectI& cmp) const
{
	return (operator==(cmp) == false);
}

#endif                                                  