#pragma once
class List
{
private:
	float position;
	List* nextl;
public:
	void AddList(List* l)
	{
		nextl = l;
	}
	float GetValue()
	{
		return position;
	}
};

