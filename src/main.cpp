#include "implicit/ImplicitSystem.hpp"
#include "vecHelp.hpp"

#include <iostream>
#include <chrono>

#include "Engine.hpp"

#include "Image.hpp"
#include <glm/glm.hpp>
int main()
{
	Implicit::Sphere s(geoffFunction, 0.5, 1);
	Implicit::Translate t1(&s, 0, -0.2, 0);
	Implicit::Translate t2(&s, 0, 0.2, 0);
	Implicit::Translate t3(&s, -0.8, 0, 0);
	Implicit::Translate t4(&s, 0.8, 0, 0);

	Implicit::Union u1(&t3, &t4);

	Implicit::Intersect i1(&t1, &t2);

	Implicit::Intersect u2(&i1, &u1);


	Implicit::Translate t(&u2 ,0, 0 , -3);
	Image image(960, 480);
	RayTracer R(&t, &image, 8);
	auto begin = std::chrono::high_resolution_clock::now();
	R.Trace(0, image.width(), 0, image.height());
	auto end = std::chrono::high_resolution_clock::now();
	std::cout <<  '\n' <<
		std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
		<< " ms" << '\n';
	image.blur();
	image.save("output.ppm");
	return 0;
}
