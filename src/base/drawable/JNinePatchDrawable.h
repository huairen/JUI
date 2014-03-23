#ifndef JNINEPATCH_DRAWABLE_H_
#define JNINEPATCH_DRAWABLE_H_

#include "JDrawable.h"
#include "DataType/JArray.h"

class JTexture2D;
class JImage;

class JNinePatchDrawable : public JDrawable
{
public:
	JNinePatchDrawable();
	virtual ~JNinePatchDrawable();

	bool Load(const char* filename);

	virtual void Draw(const JRectI &rcOrigin, const JRectI &rcPaint);

private:
	void FindArea(const JImage* img);
	JPoint2I DrawFixedPatch(const JRectI &rcPatch, const JRectI &rcOrigin, const JRectI &rcPaint);

protected:
	JTexture2D* m_pBitmap;
	JArray<JRectI> m_FixedAreaList;
};

#endif //JBITMAP_DRAWABLE_H_