#pragma once
#include<glm/glm.hpp>
#include <vector>
#include<GLAD/glad.h>
#include <gl/GL.h>
class LBM
{
private:
	struct Cell
	{
		glm::vec2 position, velocity, momentum_density;
		float mass_density;
		float Fequilibrium_old[9];
		float Fequilibrium[9];
		float BGK[9];
		glm::vec3 color;
	};
	float weights[9]{ 4.f / 9.f,1.f / 9.f,1.f / 9.f,1.f / 9.f,1.f / 9.f,1.f / 36.f,1.f / 36.f,1.f / 36.f,1.f / 36.f };
	glm::vec2 c[9]{ glm::vec2(0,0),glm::vec2(1,0), glm::vec2(0,1), glm::vec2(-1,0),glm::vec2(0,-1),glm::vec2(1,1),glm::vec2(-1,1),glm::vec2(-1,-1),glm::vec2(1,-1) };
	std::vector<std::vector<Cell>> grids;
	const float speeofsound = 1.f / 3.f;
	const float relaxtion = 0.500045;
	int M, N;
	float k = 0.01;
public:
	void init(int v,int b)
	{
		M = v;
		N = b;
		float q = 0.001;
		float vc = 0.001;
		float vcv = 1.0;
		grids.resize(N, std::vector<Cell>(M));
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				grids[i][j].position = glm::vec2(i*k, j * k);
				grids[i][j].velocity = glm::vec2(0, 0);
				grids[i][j].momentum_density = glm::vec2(0, 0);
				grids[i][j].mass_density = 1.f;
				grids[i][j].color = glm::vec3(vc, q, vcv);
				q += 0.00001;
				vc += 0.00001;
				vcv -= 0.00001;
				
			}
		}
	}
	void ComputeEquilibrium()
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				glm::vec2 u = grids[i][j].momentum_density / grids[i][j].mass_density;
				for (int k = 0; k < 9; k++)
				{
					grids[i][j].Fequilibrium[k] = weights[k] * grids[i][j].mass_density * (1 + (glm::dot(u, c[k]) / speeofsound) + (pow((glm::dot(u, c[k])), 2) / 2 * pow(speeofsound, 2)) - (glm::dot(u, u) / 2 * speeofsound));
			    }
			}
		}
	}
	void ComputeColisionAStream(float delat_time)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				for (int k = 0; k < 9; k++)
				{
					grids[i][j].BGK[k] = grids[i][j].Fequilibrium_old[k] * (1 - delat_time / relaxtion) * (grids[i][j].Fequilibrium[k]-grids[i][j].Fequilibrium_old[k]) * (delat_time / relaxtion);
					grids[i][j].Fequilibrium_old[k] = grids[i][j].Fequilibrium[k];
					grids[i][j].Fequilibrium[k] = grids[i][j].BGK[k];
				}
			}
		}
	}
	void ComputeDensity()
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
			grids[i][j].mass_density = 0.0001;
			grids[i][j].mass_density += grids[i][j].Fequilibrium_old[0] + grids[i][j].Fequilibrium_old[1]+ grids[i][j].Fequilibrium_old[2]+ grids[i][j].Fequilibrium_old[3]+ grids[i][j].Fequilibrium_old[4]+ grids[i][j].Fequilibrium_old[5]+ grids[i][j].Fequilibrium_old[6]+ grids[i][j].Fequilibrium_old[7]+ grids[i][j].Fequilibrium_old[8];
			}
		}
	}
	void ComputeMomentumDensity()
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				grids[i][j].momentum_density = glm::vec2(0, 0);
				grids[i][j].momentum_density.x += ((grids[i][j].Fequilibrium_old[1] + grids[i][j].Fequilibrium_old[5] + grids[i][j].Fequilibrium_old[8]) - (grids[i][j].Fequilibrium_old[3] + grids[i][j].Fequilibrium_old[6] + grids[i][j].Fequilibrium_old[7])) / grids[i][j].mass_density;
				grids[i][j].momentum_density.y += ((grids[i][j].Fequilibrium_old[2] + grids[i][j].Fequilibrium_old[5] + grids[i][j].Fequilibrium_old[6]) - (grids[i][j].Fequilibrium_old[4] + grids[i][j].Fequilibrium_old[7] + grids[i][j].Fequilibrium_old[8])) / grids[i][j].mass_density;
			}
		}
	}
	void UpdateColor(std::vector<float>& colors)
	{
		colors.clear();

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (grids[i][j].mass_density > 1.f)
				{
					grids[i][j].color = glm::vec3(1.f);//white (це значить що там рідини або газу максимум)
				}
				if (grids[i][j].mass_density <= 0.0001)
				{
					grids[i][j].color = glm::vec3(0,0,1.f);//black(це значить що там рідини або газу майже нема)
				}
				else
				{
					grids[i][j].color = glm::vec3(grids[i][j].mass_density);
				}
				colors.push_back(grids[i][j].color.x);
				colors.push_back(grids[i][j].color.y);
				colors.push_back(grids[i][j].color.z);
			}
		}
	}
	void VisData(std::vector<float>& vertics, std::vector<int>& ebo_int, std::vector<float>& colors)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
			vertics.push_back(grids[i][j].position.x + k);
			vertics.push_back(grids[i][j].position.y + k);
			//1 
			colors.push_back(grids[i][j].color.x);
			colors.push_back(grids[i][j].color.y);
			colors.push_back(grids[i][j].color.z);
			//1 color
			vertics.push_back(grids[i][j].position.x + k);
			vertics.push_back(grids[i][j].position.y - k);
			//2
			colors.push_back(grids[i][j].color.x);
			colors.push_back(grids[i][j].color.y);
			colors.push_back(grids[i][j].color.z);
			//2 color
			vertics.push_back(grids[i][j].position.x - k);
			vertics.push_back(grids[i][j].position.y - k);
			//3
			colors.push_back(grids[i][j].color.x);
			colors.push_back(grids[i][j].color.y);
			colors.push_back(grids[i][j].color.z);
			//3 color
			vertics.push_back(grids[i][j].position.x - k);
			vertics.push_back(grids[i][j].position.y + k);
			//4
			colors.push_back(grids[i][j].color.x);
			colors.push_back(grids[i][j].color.y);
			colors.push_back(grids[i][j].color.z);
			//4 color
			}
		}
		int vertexOffset = 0;
		for (int i = 0; i < M * N; i++)
		{
			///Треугольник 1//// +4 це stride до наступного треугольника
			ebo_int.push_back(vertexOffset + 0);
			ebo_int.push_back(vertexOffset + 1);
			ebo_int.push_back(vertexOffset + 3);
			///Треугольник 2
			ebo_int.push_back(vertexOffset + 1);
			ebo_int.push_back(vertexOffset + 2);
			ebo_int.push_back(vertexOffset + 3);
			vertexOffset += 4;
		}
	}
};

