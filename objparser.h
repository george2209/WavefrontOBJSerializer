#pragma once
#include "linkedlist.h"
#include <fstream>

namespace my_utils {

	class obj_vertex_element;
	class obj_container;
	class ternary_search;

	

	class obj_parser
	{
	public:
		obj_parser(const std::ofstream * pOutputStream);
		virtual ~obj_parser();
		void processLine(const char* line);
		void close();
	private:
		void buildOBJTagsArray();
	private:
		obj_container* iCurrentObjContainer;
		linkedlist< obj_vertex_element> * lstVertices;
		const std::ofstream* iOutputStream;
		ternary_search* iTagSearchEngine;
	};
}

