#pragma once
#include "abstractobj.h"

namespace my_utils {
	class obj_vertex_element : abstractobj
	{
	public:
		obj_vertex_element();
		bool parse(const char* pLine, int startIndex, int endIndex = -1);
	public:
		float x;
		float y;
		float z;
	};
}

