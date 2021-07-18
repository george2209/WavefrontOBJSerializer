#pragma once

#include <fstream>

namespace my_utils {

	enum class E_OBJ_TAGS_t;
	class obj_root_element;
	class mtl_parser;
	template <class T> class ternary_search;
	
	
	class obj_parser
	{
	public:
		obj_parser(std::ofstream * pOpOutputStream, const char * pClassPath);
		virtual ~obj_parser();
		void processLine(const char* line);
		void close();
	private:
		void buildOBJTagsArray();
	private:
		obj_root_element* i_pCurrentObjContainer;
		std::ofstream* i_pOutputStream;
		ternary_search<E_OBJ_TAGS_t>* i_pTagSearchEngine;
		mtl_parser* i_pMTLParser;
		const char* i_pClassPath;
	};
}

