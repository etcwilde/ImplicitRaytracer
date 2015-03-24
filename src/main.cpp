#include "ImplicitSystem.hpp"
#include "vecHelp.hpp"

#include "Engine.hpp"

#include "Image.hpp"
#include <glm/glm.hpp>
int main()
{
	Implicit::Primitive p(geoffFunction, 0.5, 1);
	Implicit::Translate t1(&p, 1.5, 0, 0);
	Implicit::Translate t2(&p, -1.5, 0, 0);
	Implicit::Translate t3(&p, 0, 1, 0);
	Implicit::Blend b(&t1, &p, 0.5f);
	//Implicit::Blend b2(&b, &t2, 0.5f);
	Implicit::Blend b3(&b, &t3, 0.5f);


	Implicit::Translate t(&b3, 0, 0, -3);


	/*std::cout << p.GetStartVertex() << '\n';
	std::cout << p.GetCenterVertex() << '\n';
	std::cout << t.GetStartVertex() << '\n';
	std::cout << t.GetCenterVertex() << '\n';
	std::cout << t.Normal(t.GetStartVertex()) << '\n';
	float k1, k2;
	t.Curvature(t.GetStartVertex(), k1, k2);
	std::cout << "Curvatures: " << k1 << ", " << k2 << '\n'; */

	Image image(960, 480);
	RayTracer R(&t, &image, 8);
	R.Trace(0, image.width(), 0, image.height());
	image.save("output.ppm");
	return 0;
}
