#include "implicit/ImplicitSystem.hpp"
#include "vecHelp.hpp"

#include <iostream>
#include <chrono>

#include "Engine.hpp"

#include "Image.hpp"
#include <glm/glm.hpp>
int main()
{
	Implicit::Primitive p(geoffFunction, 0.5, 1);
	Implicit::Translate t1(&p, 0, -0.2, 0);
	Implicit::Translate t2(&p, 0, 0.2, 0);
	Implicit::Blend b(&t1, &t2, 0.5);
	//Implicit::Rotate r(&b, glm::vec3(0, 0, 1), M_PI /2.f);
	Implicit::Scale s(&b, 0.24, 0.25, 1);
	Implicit::Rotate r(&s, 0, M_PI / 3.f , 0);
	Implicit::Translate t(&r ,0, 0 , -3);
	Image image(960, 480);
	RayTracer R(&t, &image, 1);
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
