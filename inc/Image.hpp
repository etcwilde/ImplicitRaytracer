#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <string>

#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include <glm/glm.hpp>

class Image
{
public:
	Image(unsigned int width, unsigned int height);
	unsigned int width() const;
	unsigned int height() const;

	void set(unsigned int x, unsigned int y, const glm::vec3& value);
	const glm::vec3& get(unsigned int x, unsigned int y) const;

	void blur();

	void save(const std::string& filename) const;
private:
	unsigned int m_width;
	unsigned int m_height;
	std::vector<glm::vec3> m_data;
};


#endif//IMAGE_HPP
