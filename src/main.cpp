#include "ImplicitSystem.hpp"
#include "vecHelp.hpp"
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

	return 0;
}
