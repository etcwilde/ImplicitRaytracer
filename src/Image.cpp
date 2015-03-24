#include "Image.hpp"
#include <iostream>
#include "vecHelp.hpp"

Image::Image(unsigned int width, unsigned int height)
	:m_width(width)
	 , m_height(height)
	 , m_data(width * height)
{}

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
	m_data[x + y * m_width] = value;
}

const glm::vec3& Image::get(unsigned int x, unsigned int y) const
{
	return m_data[x + y * m_width];
}

void Image::blur()
{
	for (unsigned int y = 1; y < (m_height - 1); ++y)
	{
		for (unsigned int x = 1; x < (m_width - 1); ++x)
		{
			const glm::vec3 c1 = get(x - 1, y -1); // corner
			const glm::vec3 c2 = get(x, y - 1);
			const glm::vec3 c3 = get(x + 1, y - 1); // corner
			const glm::vec3 c4 = get(x - 1, y);
			const glm::vec3 c5 = get(x, y);
			const glm::vec3 c6 = get(x + 1, y);
			const glm::vec3 c7 = get(x - 1, y + 1); // corner
			const glm::vec3 c8 = get(x , y + 1);
			const glm::vec3 c9 = get(x + 1, y + 1); // corner
			glm::vec3 c = glm::abs((
						(c1 + c3 + c7 + c9) * 0.15f +
						(c2 + c4 + c6 + c8) * 0.25f +
						c5) * 1.5f);
			if (glm::length(c) > 1) c = glm::normalize(c);
			set(x-1, y-1, c);
		}
	}
}






void Image::save(const std::string& filename) const
{
	FILE* file = fopen(filename.c_str(), "wt");
	fprintf(file, "P3 %d %d 255\n", m_width, m_height);
	for (unsigned int y = 0; y < m_height; ++y)
	{
		fprintf(file, "\n# y = %d\n", y);
		for (unsigned int x = 0; x < m_width; ++x)
		{
			glm::vec3 a = get(x, y);
			fprintf(file, "%d %d %d\n",
					int(a.r * 255) ,
					int(a.g * 255) ,
					int(a.b * 255) );

		}
	}
	fclose(file);
}
