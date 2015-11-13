#include "eventmgr.h"
#include <iostream>

using namespace boost::python;
using namespace std;

// bind a given entity member function to the given string
void EvtMgr::Bind(std::string name, Entity* e, EvtFunc func)
{
    EvtMapElement evtElement = {func, NULL, e};
    events.insert(std::pair<std::string, EvtMapElement>(name, evtElement));
}

void EvtMgr::BindPy(std::string name, Entity* e, PyObject* func)
{
	EvtMapElement evtElement = {NULL, func, e};
	events.insert(std::pair<std::string, EvtMapElement>(name, evtElement));
}

void EvtMgr::Update()
{

}

void EvtMgr::Send(std::string evtName)
{
	// TODO: delete!  print # of events
	std::cout <<std::endl << events.size() << std::endl;
	for(std::map<std::string, EvtMapElement>::iterator it=events.begin(); it != events.end(); it++) {
		std::cout << (*it).first << std::endl;
	}
	// TODO: delete
    std::cout<<"event "<<evtName<<" sent" <<std::endl;

	//if(events[evtName].sender->HasTag("collidable")) {
	//	std::cout << " collidable! " << std::endl;
	//}

	// if the event sent includes a wildcard, call a matching event
	if(evtName.find('*') != evtName.npos) {
		string substring = evtName.substr(evtName.find('*'));
		for(map<string, EvtMapElement>::iterator it=events.begin(); it != events.end(); it++) {
			if((*it).first.find(substring)) {
				call<void>(events[(*it).first].pyOverride, boost::ref(events[evtName].sender));
			}
		}
	}

	// is there a python function associated with this event?  If so, use it
	if(events[evtName].pyOverride != NULL) {
		call<void>(events[evtName].pyOverride, boost::ref(events[evtName].sender));
	}

	// if there is no python function, check if there is a C++ function associated with the event.  If so, call it.  If not, there is no function 
	// associated with this event.
	else if(events[evtName].func != NULL) {	
		events[evtName].func(events[evtName].sender);
	}
}