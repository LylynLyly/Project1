#include <iostream>
#include<vector>
#include<list>
#include<set>
#include"Particle.h"
class SpatialHash
{
private:
	const float cellSize;
	std::vector<std::list<Particle*>> grid;
	int count_neighboors = 0;
public:
	SpatialHash(const float c = 0.1f) : cellSize(c) {}
	void Reload(int a)
	{
		count_neighboors = 0;
	}
	int AVG(int size)
	{
		return count_neighboors / size;
	}
	void SetSize(int xs = 20, int ys = 20, int zs = 20)
	{
		grid.resize(xs * ys * zs);
	}

	size_t Hash(float xi, float yi, float zi)
	{///(0.2 / cellSize)
		int x = static_cast<int>(std::floor(xi/cellSize));
		int y = static_cast<int>(std::floor(yi/cellSize));
		int z = static_cast<int>(std::floor(zi/cellSize));

		return (std::abs((x * 73856093)) ^ std::abs((y * 19349663)) ^ std::abs((z * 83492791))) % grid.size();
	}

	void StoreGrid(std::vector<Particle*> allparticles)
	{
		for (int i = 0; i < allparticles.size(); ++i)
		{
			grid[Hash(allparticles[i]->GetPos().x, allparticles[i]->GetPos().y, allparticles[i]->GetPos().z)].push_back(allparticles[i]);
		}
	}
	void found_neighbor(Particle* P,float smradius = 0.2)
	{

		std::set<Particle*> newN;
		

		for (float cellz = -smradius; cellz < smradius; cellz += cellSize)///Z ////ZAXODIM
		{
			for (float celly = -smradius; celly < smradius; celly += cellSize)///Y ///// OTSASIVAEM
			{
				for (float cellx = -smradius; cellx < smradius; cellx += cellSize)///X //// VIXODIM
				{
					for (std::list<Particle*>::iterator a = grid[Hash(P->GetPos().x + cellx, P->GetPos().y + celly, P->GetPos().z + cellz)].begin(); a != grid[Hash(P->GetPos().x + cellx, P->GetPos().y + celly, P->GetPos().z + cellz)].end(); ++a)
					{
						
						if (P != *a && glm::length(P->GetPos() - (*a)->GetPos()) <= smradius)
						{
							std::cout << "R" << glm::length(P->GetPos() - (*a)->GetPos()) << " " << smradius << '\n';
							newN.insert(*a);
						}
					}
				}
			}
			P->SetNeighboors(newN);
		}
		for (std::set<Particle*>::iterator i = newN.begin(); i != newN.end(); ++i)
		{
			//std::cout << " T " << (*i)->GetPos().x << " " << (*i)->GetPos().y << " " << (*i)->GetPos().z << '\n';
		}
	}
};


