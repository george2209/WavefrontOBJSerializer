#pragma once
#include <fstream>

namespace my_utils {

	class obj_container {
	public:
		obj_container(const char* line, unsigned int start);
		virtual ~obj_container();
		void persist(const std::ofstream* pOutputStream);

	private:
		const unsigned int pivotStart;
		const char* i_pLine;

	};

}
