#include "SDL_opengl.h"
#include "entity.h"
#include "eventmgr.h"
#include "node.h"
#include "game.h"
#include "texture.h"
#include <boost/python.hpp>
#include <boost/python/class.hpp>

using namespace boost::python;

BOOST_PYTHON_FUNCTION_OVERLOADS(bind_overloads, EvtMgr::Bind, 3, 3);

BOOST_PYTHON_MODULE(engine) {
	def("LoadTexture", LoadTexture);
	//def("GetGame", GetGame, return_value_policy<reference_existing_object>());

	class_<EvtMgr>("EvtMgr")
		.def("BindPy", &EvtMgr::BindPy)
	;
	class_<Entity>("Entity")
	;
	class_<Sprite, bases<Entity> >("Sprite", 
		init<std::string>(args("filename")))
		.def("HasTag", &Entity::HasTag)
		.def("SetTag", &Entity::SetTag)
		.def("SetName", &Entity::SetName)
		.def("GetName", &Entity::GetName)
	;
	class_<Node, bases<Entity> >("Node", 
		init<float, float, float, float>(args("x", "y", "z", "rot")))
		.def("AddChild", &Node::AddChild)
		.def("GetX", &Node::GetX)
		.def("GetY", &Node::GetY)
		.def("GetZ", &Node::GetZ)
		.def("GetRot", &Node::GetRot)
		.def("GetTurnSpeed", &Node::GetTurnSpeed)
		.def("GetTurnDst", &Node::GetTurnDst)
		.def("GetCenter", &Node::GetCenter)
		.def("SetX", &Node::SetX)
		.def("SetY", &Node::SetY)
		.def("SetZ", &Node::SetZ)
		.def("SetRot", &Node::SetRot)
		.def("SetTurnSpeed", &Node::SetTurnSpeed)
		.def("SetTurnDst", &Node::SetTurnDst)
		.def("SetCenter", &Node::SetCenter)
	;
	class_<Game>("Game")
		.def("Run", &Game::Run)
		.def("AddEntity", &Game::AddEntity)
		.def("Accept", &Game::Accept)
		.def("Setup", &Game::Setup)
	;
}