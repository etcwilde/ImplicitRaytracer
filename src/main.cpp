#include "implicit/ImplicitSystem.hpp"
#include "vecHelp.hpp"

#include "Engine.hpp"

#include "Image.hpp"
#include <glm/glm.hpp>
int main()
{
	Implicit::Primitive p(geoffFunction, 0.5, 1);
	Implicit::Translate t1(&p, 0, -0.2, 0);
	Implicit::Translate t2(&p, 0, 0.2, 0);
	Implicit::Blend b(&t1, &t2, 0.5);
	Implicit::Translate t(&b ,0, 0 , -3);
	Image image(960, 480);
	RayTracer R(&t, &image, 8);
	R.Trace(0, image.width(), 0, image.height());
	image.blur();
	image.save("output.ppm");
	return 0;
}
