#ifndef JPOINT_H_
#define JPOINT_H_

class JPoint2I
{
public:
	int x;
	int y;

public:
	JPoint2I() {};
	JPoint2I(int _x, int _y) { x = _x; y = _y; }

	bool operator==(const JPoint2I&) const;
	bool operator!=(const JPoint2I&) const;

	JPoint2I operator+(const JPoint2I&) const;
	JPoint2I operator-(const JPoint2I&) const;
	JPoint2I& operator+=(const JPoint2I&);
	JPoint2I& operator-=(const JPoint2I&);
};

inline bool JPoint2I::operator==(const JPoint2I& _test) const
{
	return ((x == _test.x) && (y == _test.y));
}

inline bool JPoint2I::operator!=(const JPoint2I& _test) const
{
	return (operator==(_test) == false);
}

inline JPoint2I JPoint2I::operator+( const JPoint2I& add ) const
{
	return JPoint2I(x + add.x, y + add.y);
}

inline JPoint2I JPoint2I::operator-( const JPoint2I& sub ) const
{
	return JPoint2I(x - sub.x, y - sub.y);
}

inline JPoint2I& JPoint2I::operator+=(const JPoint2I& add)
{
	x += add.x;
	y += add.y;

	return *this;
}

inline JPoint2I& JPoint2I::operator-=(const JPoint2I& sub)
{
	x -= sub.x;
	y -= sub.y;

	return *this;
}

#endif                                                  