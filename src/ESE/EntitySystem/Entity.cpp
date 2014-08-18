#include <ESE/EntitySystem/Entity.hpp>

namespace ESE{
	Entity::Entity(){
		setId(ESE::EntityGenerator::registerId());
	}
	Entity::Entity(int id){
		setId(id);
	}
	void Entity::setId(int id){
		this->id = id;
	}
	int Entity::getId(){
		return id;
	}
	int Entity::getAmountOfComponents(){
		return systemsId.size();
	}
	void Entity::addSystem(int systemId){
		systemsId.push_back(systemId);
	}
	void Entity::removeSystem(int systemId){
		for (unsigned int i=0; i<systemsId.size(); i++){
			if (systemsId[i]==systemId){
				systemsId.erase(systemsId.begin()+i);
				return;
			}
		}
	}
	bool Entity::is(int systemId){
		for (unsigned int i=0; i<systemsId.size(); i++){
			if (systemsId[i]==systemId){
				return true;
			}
		}
		return false;
	}


	namespace EntityGenerator{
		int lastId = 0;
		
		int registerId(){
			return ++lastId;
		}
	}

}