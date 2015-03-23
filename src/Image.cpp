#include "Image.hpp"

Image::Image(unsigned int width, unsigned int height) :
	m_width(width),
	m_height(height),
	m_data(width * height)
{ }

unsigned int Image::width() const
{
	return m_width;
}

unsigned int Image::height() const
{
	return m_height;
}

void Image::set(unsigned int x, unsigned int y, const glm::vec3& value)
{
	x = x % m_height;
	m_data[x + y * m_width] = value;
}

const glm::vec3& Image::get(unsigned int x, unsigned int y) const
{
	return m_data[(x % m_height) + y * m_width];
}


