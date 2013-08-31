#include "JImage.hxx"                                                  

JImage::JImage() : m_pFilename(0), m_nWidth(0), m_nHeight(0), m_bAlphaChannel(false)
{

}

JImage::~JImage()
{

}

int JImage::GetWidth()
{
	return m_nWidth;
}

int JImage::GetHeight()
{
	return m_nHeight;
}

bool JImage::HasAlphaChannel()
{
	return m_bAlphaChannel;
}
