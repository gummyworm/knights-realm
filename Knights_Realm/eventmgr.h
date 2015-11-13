#ifndef _TASKMGR
#define _TASKMGR

#include <boost\python.hpp>
#include <map>
#include <string>
#include "entity.h"
#include "fastdelegate/FastDelegate.h"

using namespace fastdelegate;

typedef FastDelegate1<Entity*, void> EvtFunc;
typedef struct {
	EvtFunc func;
	PyObject* pyOverride;
	Entity* sender;
}EvtMapElement;

class EvtMgr {
public:
	/** Bind a function to the given event message.
	* the given EvtFunc is executed once the string "name" message is sent.  The given entity is used as a parameter so that the receiver knows what 
	* entity should be considered as the originator of the event.  There is no true originator as the evtmgr is implemented as a top level instance
	* of this object (entities cannot add to the evtmgr themselves).
	*/
	void Bind(std::string name, Entity* e, EvtFunc func);

	/** Bind a python function to the given event message.
	* this is used for python callbacks.
	*/
	void BindPy(std::string name, Entity*e, PyObject* func);

	void Update();
	void Receive(std::string evtName);
	void Send(std::string evtName);
private:
	// map for the event delegates
	std::map<std::string, EvtMapElement> events;
};

#endif

