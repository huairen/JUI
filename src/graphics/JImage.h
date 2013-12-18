#ifndef JIMAGE_H_
#define JIMAGE_H_

enum ImageType
{
	IMAGE_JPEG,
	IMAGE_PNG,
	IMAGE_BMP,
	IMAGE_GIF,
};

enum ImageFormat
{
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_L8,

	IMAGE_FORMAT_R8G8B8,
	IMAGE_FORMAT_R8G8B8A8,
};

class JImage
{
public:
	JImage();
	virtual ~JImage();

	int GetWidth();
	int GetHeight();
	bool HasAlphaChannel();

	virtual bool Load(const char* filename) = 0;
	virtual int GetHandler() = 0;

protected:
	const char* m_pFilename;
	int m_nWidth;
	int m_nHeight;
	bool m_bAlphaChannel;
	ImageType m_Type;
	ImageFormat m_Format;
};


#endif
                                                  