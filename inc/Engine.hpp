#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Image.hpp"
#include "implicit/ImplicitSystem.hpp"
#include "floatlibs.hpp"
#include "vecHelp.hpp"

#include <list>
#include <mutex>
#include <future>
#include <thread>
#include <iostream>
#include <iomanip>

#define MIN_THREADS 1

class Ray
{
public:
	Ray(const glm::vec3& origin, const glm::vec3& direction) :
		m_origin(origin),
		m_direction(glm::normalize(direction))
	{}

	glm::vec3 m_origin;
	glm::vec3 m_direction;
};

class RayTracer
{
public:
	RayTracer(Implicit::Object* object, Image* i);
	RayTracer(Implicit::Object* object, Image* i, unsigned int threads);
	void Trace(unsigned int x0, unsigned int x1, unsigned int y0, unsigned int y1);

private:
	void trace(Implicit::Object* obj,
			unsigned int x0, unsigned int x1,
			unsigned int y0, unsigned int y1);

	bool SampleObject(const Ray& R, Implicit::Object* o, glm::vec3& color, float& distance);

	Ray ComputeEyeRay(double x, double y, unsigned int width,
			unsigned int height);

	glm::vec3 ProjectRay(const Ray& R, Implicit::Object* O, float& distance);

	static inline void progressBar(unsigned int x, unsigned int n,
		       	unsigned int r, unsigned int w = 50)
	{
		if ( (x != n) && (x % (n/100+1) != 0) ) return;
		float ratio = x /(float)n;
		unsigned int c = ratio *w;
		std::cout << std::setw(3) << (int)(ratio * 100) << "% [";
		for (unsigned int x = 0; x < c; x++) std::cout << "=";
		for (unsigned int x = c; x < w; x++) std::cout << " ";
		std::cout << "]\r" << std::flush;
	}

	//void Shade(const Implicit::Object* o, 

	unsigned int m_threads;
	Implicit::Object* m_obj;
	Image* m_image;
	std::mutex m_x_mux;
	std::mutex m_y_mux;
	unsigned int m_current_x;
	unsigned int m_current_y;
};



#endif//ENGINE_HPP
