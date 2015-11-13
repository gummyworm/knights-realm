#ifndef _ENTITY_H
#define _ENTITY_H

#include <string>
#include <set>
#include <algorithm>

class Entity {
protected:
	/** the string that refers to this entity.
	* this is used to generate event messages in the format.  For example: collision events are sent in the form "name-into-name_of_into_object"
	* where id is the entity's name and name_of_into_object is the entity that the entity is 
	*/
	std::string name;

	/** a set of tags that allow the user to sort the properties of the entity.
	* this set can be searched for specific tags to determine what action to take when an event is triggered affecting this entity.
	* The engine also uses it to determine basic actions. For instance, if the tag "collidable" is set, then action will be taken when the entity is collided into.  
	* Assumptions may be made based upon this tag.  For instance, if the "damage" tag is set, then it is assumed that the entity has a damage variable.
	*/
	std::set<std::string> *tags;
public:
	Entity() {name=""; tags=new std::set<std::string>;}
	virtual void Update() {}
	virtual void Draw() {}

	bool HasTag(std::string s) {if(std::find(tags->begin(), tags->end(), s) != tags->end()) return true; return false;}
	void SetTag(std::string s) {tags->insert(s);}
	void SetName(std::string s) {name=s;}
	std::string GetName() {return name;}
};


typedef std::set<Entity*> GameEntity;

#endif