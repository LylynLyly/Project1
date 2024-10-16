#pragma once
#include<math.h>
#include<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Time
{
private:
	float time_s;
	float time_d;
public:
	Time(float s = 1,float d = 0.0) : time_s(s), time_d(d) {}
	void ComputeCFL(float smoothingradius,glm::vec3 max_velocity)
	{
		time_d = 0.4 * (smoothingradius / glm::length(max_velocity));
	}
	float Gettime_s()
	{
		return time_s;
	}
	float Gettime_d()
	{
		return time_d;
	}
	void Incrementtime_s(float t)
	{
		time_s+= t;
	}
};

