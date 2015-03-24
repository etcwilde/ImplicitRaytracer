#include "Engine.hpp"

RayTracer::RayTracer(Implicit::Object* o, Image* i) :
	m_threads(MIN_THREADS),
	m_obj(o),
	m_image(i)
{ }

RayTracer::RayTracer(Implicit::Object* o, Image* i, unsigned int t) :
	m_threads(t),
	m_obj(o),
	m_image(i)
{ }

void RayTracer::Trace(unsigned int x0, unsigned int x1, unsigned int y0,
		unsigned int y1)
{
	std::list<std::thread> thread_list;
	if(m_threads == 0) m_threads = 1;
	for (unsigned int i = 0; i < m_threads; i++)
	{
		thread_list.push_back(std::thread(&RayTracer::trace, this, m_obj, x0, x1, y0, y1));
	}

	for (std::list<std::thread>::iterator it = thread_list.begin();
			it != thread_list.end(); it++)
		it->join();


}

void RayTracer::trace(Implicit::Object* obj, unsigned int x0, unsigned int x1,
		unsigned int y0, unsigned int y1)
{

	m_y_mux.try_lock();
	m_current_y = y0;
	m_y_mux.unlock();
	unsigned int y;
	for(;;)
	{
		m_y_mux.lock();
		y = m_current_y;
		m_current_y += 1; // THIS MAY CAUSE A SEGFAULT -- CHECK IT
		if (m_current_y >= y1)
		{

			m_y_mux.unlock();

			break;
		}
		m_y_mux.unlock();


		progressBar(y, y1, 10, 50);

		for (unsigned int x = x0; x < x1; ++x)
		{
			float distance = INFINITY;
			const Ray& R = ComputeEyeRay(x, y, m_image->width(),
					m_image->height());
			glm::vec3 color;
			if (SampleObject(R, obj, color, distance))
				m_image->set(x, y, color);
		}

	}
}

Ray RayTracer::ComputeEyeRay(double x, double y, unsigned int width,
		unsigned int height)
{
	const float aspect = float(height)/width;
	const float s = -2.f * tan(45.0 * 0.5f);
	const glm::vec3 start = glm::vec3( (x / width - 0.5f) * s,
			-(y / height - 0.5f) * s * aspect,
			1.f) * 0.1f;
	return Ray(start , glm::normalize(start));
}

bool RayTracer::SampleObject(const Ray& R, Implicit::Object* O, glm::vec3& color, float& distance)
{

	const float eps = 0.00001;
	const float min_step = 0.00001;
	float d, dt;
	glm::vec3 proj = ProjectRay(R, O, d);
	if (!f_equ(O->Evaluate(proj), 0, eps))
	{
		dt = O->DistanceFromSurface(proj);
		if (dt > eps) return false;
	}
	color = glm::abs(O->Normal(proj));
	return true;
}

glm::vec3 RayTracer::ProjectRay(const Ray& R, Implicit::Object* O, float& d)
{
	register float xi;
	float xi1 = 0;
	float xi2 = 1;
	glm::vec3 start = R.m_origin;
	glm::vec3 direction = R.m_direction;

	for (unsigned int i = 0; i < 100; ++i)
	{
		float fxi1 = O->Evaluate( start + (direction * xi1));
		float fxi2 = O->Evaluate( start + (direction * xi2));
		xi = xi1 - fxi1 * ((xi1 - xi2)/(fxi1 - fxi2));
		if (fxi1 == fxi2)
		{
			d = xi1;
			break;
		}
		xi2 = xi1; xi1 = xi;
		if (i == 99)
		{
			d = INFINITY;
			return start;
		}
	}
	return start + direction * d;
}
