#ifndef PROPERTY_LIST_HPP
#define PROPERTY_LIST_HPP

#include <vector>

class PropertyList{
private:
	std::vector<int>properties;
public:
	void addProperty(int id);
	bool is(int id);
};


#endif