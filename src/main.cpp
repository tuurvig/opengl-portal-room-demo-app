//----------------------------------------------------------------------------------------
/**
 * \file       main.cpp
 * \author     Richard Kvasnica
 * \brief      main program execution
*/
//----------------------------------------------------------------------------------------

#include <stdexcept>

#include "GLUTWrapper.hpp"
#include "demo/HelloTriangle.hpp"
#include "demo/ModelLoad.hpp"
#include "demo/ShadersData.hpp"
#include "demo/TestScene.hpp"
#include "PortalTestRoom.hpp"

namespace kvasnric
{
	int main(int argc, char** argv)
	{
		//try
		//{
		//	GLUTWrapper::Init(argc, argv, new PortalTestRoom());
		//}
		//catch (const std::runtime_error& err)
		//{
		//	GLUTWrapper::TerminateWithError(err.what());
		//}
		GLUTWrapper::Init(argc, argv, new PortalTestRoom());
		GLUTWrapper::Run();

		return 0;
	}
}

int main(int argc, char ** argv)
{
	return kvasnric::main(argc, argv);
}