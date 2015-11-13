#include "script.h"

using namespace std;
using namespace boost::python;

Script::Script(std::string scriptFile) : Entity() 
{
	string temp;
	ifstream in;
	in.open(scriptFile);
	getline(in, temp);
	while(in) {
		script += temp;
		script += '\n';
		getline(in, temp);
	}
	Py_Initialize();
	object main = import("__main__");
	global = main.attr("__dict__");
	result = exec(script.c_str(), global, global);
}

void Script::CallFunction(const std::string& f, object arg)
{
	// create a reference to the function
	object function = global[f];

	// call it
	function(arg);
}