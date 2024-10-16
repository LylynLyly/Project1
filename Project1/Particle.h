#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<math.h>
#include"PI.h"
#include <set>
class Particle
{
private:
	
	const float radius, smoothingradius, coeficient, coeficient_kernel_fucction, mass,start_density=1000;
	float density, vic;
	glm::vec3 pos, velocity , vicosity, acceleration, intermediate_density, intermediate_velocity, Fviscosiy, Fpressure, pressure, gradient_pressure,laplace_viscosiy,c_f;
	std::vector<Particle*> allneigboors;
public:
	Particle(glm::vec3 p, glm::vec3 start_velocity, glm::vec3 start_pressure, const float r, const float sr, const float m, const float coef, const float coef_k_f, double start_density = 1000, double v = 1e-6) : pos(p), velocity(start_velocity), pressure(start_pressure), radius(r), smoothingradius(sr), density(start_density), mass(m), coeficient(coef), coeficient_kernel_fucction(coef_k_f), vic(v) {}
	glm::vec3 GetPos()
	{return pos;}
	float GetMass()
	{return mass;}
	float GetDensity()
	{return density;}
	glm::vec3 GetVelocity()
	{return velocity;}
	void SetVelocity(glm::vec3 a)
	{velocity = a;}
	int C()
	{
		return allneigboors.size();
	}
	void SetNeighboors(std::set<Particle*> a)
	{
		allneigboors.assign(a.begin(), a.end());
	}
	float kernel_cubic(glm::vec3 pos_k,glm::vec3 n_pos)
	{
		float q = glm::normalize(glm::length(pos_k - n_pos)) / smoothingradius;
		//std::cout << q << '\n';
		if (0.0 <= q && q <= 0.5)
		{
		return (8.0 / (3.14 * pow(q, 3))) * 6.0 * (pow(q, 3) - pow(q, 2) - 1.0);
		}
		if (0.5 < q && q <= 1.0)
		{
		return (8.0 / (3.14 * pow(q, 3))) * 2.0 * pow((1.0 - q), 3);
		}
		else
		{
		return 0.0;
		}
	}
	float Test(int i)
	{
		return kernel_cubic(pos,allneigboors[i]->GetPos());
	}
	void ComputeDensity()
	{
		for (int i = 0; i < allneigboors.size(); i++)
		{
			//density += allneigboors[i]->GetMass() * kernel_cubic(allneigboors[i]->GetPos());
		}
	}
	void ComputeFVicosiy()
	{
		glm::vec3 value = glm::vec3(0,0,0);
		for (int i = 0; i < allneigboors.size(); i++)
		{
			//value += (allneigboors[i]->GetMass() / allneigboors[i]->GetDensity()) * (allneigboors[i]->GetVelocity() - velocity) * 2 * glm::normalize()
		}
	}
	void IntoToOGL(std::vector<float>& vertices)
	{
		vertices.push_back(pos.x);
		vertices.push_back(pos.y);
		vertices.push_back(pos.z);
	}
	
};

