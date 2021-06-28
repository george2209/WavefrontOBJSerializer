#include "obj_container.h"

namespace my_utils {

	/// <summary>
	/// initialize an "o" object tag
	/// </summary>
	/// <param name="line">a NULL ending line</param>
	/// <param name="start">the position inside the "line" where to start the parsing from</param>
	/// <returns></returns>
	obj_container::obj_container(const char* line, unsigned int start): i_pLine(line), pivotStart(start)
	{

	}

	obj_container::~obj_container()
	{

	}

	void obj_container::persist(const std::ofstream* pOutputStream)
	{
		
	}
}