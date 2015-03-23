#include "ImplicitSystem.hpp"
#include "vecHelp.hpp"

#include "Image.hpp"
#include <glm/glm.hpp>
int main()
{
	Implicit::Primitive p(geoffFunction, 0.5, 1);
	Implicit::Translate t(&p, 10, 1, 0);
	std::cout << p.GetStartVertex() << '\n';
	std::cout << p.GetCenterVertex() << '\n';
	std::cout << t.GetStartVertex() << '\n';
	std::cout << t.GetCenterVertex() << '\n';
	std::cout << t.Normal(t.GetStartVertex()) << '\n';
	float k1, k2;
	t.Curvature(t.GetStartVertex(), k1, k2);
	std::cout << "Curvatures: " << k1 << ", " << k2 << '\n';

	Image image(100, 100);

	for (unsigned int x = 0; x < 100; x++)
	{
		for (unsigned int y = 0; y < 100; y++)
		{
			image.set(x, y, glm::vec3(0.5, 0.2, 0.1));
		}
	}

	image.save("output.ppm");
	return 0;
}
