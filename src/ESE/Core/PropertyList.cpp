#include <ESE/Core/PropertyList.hpp>

void PropertyList::addProperty(int id){
	properties.push_back(id);
}

bool PropertyList::is(int id){
	for (int i:properties){
		if (i==id){
			return true;
		}
	}
	return false;
}