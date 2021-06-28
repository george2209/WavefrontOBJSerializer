#pragma once
#include <fstream>

namespace my_utils {

	class obj_container {
	public:
		void persist(const char * pLine, unsigned int startIndex, const std::ofstream* pOutputStream);

	};

}
