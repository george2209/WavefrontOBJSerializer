#pragma once

#include <fstream>

namespace my_utils {

	
	class obj_container;
	class ternary_search;

	

	class obj_parser
	{
	public:
		obj_parser(std::ofstream * pOutputStream);
		virtual ~obj_parser();
		void processLine(const char* line);
		void close();
	private:
		void buildOBJTagsArray();
	private:
		obj_container* iCurrentObjContainer;
		std::ofstream* iOutputStream;
		ternary_search* iTagSearchEngine;
	};
}

