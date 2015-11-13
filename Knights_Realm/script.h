#ifndef _SCRIPT_H
#define _SCRIPT_H

#include <iostream>
#include <fstream>
#include <boost/python.hpp>
#include "entity.h"

using namespace std;
using namespace boost::python;

class Script : Entity {
private:
	/** the string containing the python script text.
	* this is the file contents of the .py script.
	*/
	string script;
	object result, global;

public:
	Script(std::string scriptFile);
	void Run();
	void Stop();
	void CallFunction(const std::string& f, object arg);
	void print() {cout<<script<<endl<<endl<<endl<<endl;}
};

#endif