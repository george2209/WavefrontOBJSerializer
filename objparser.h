#pragma once

#include <fstream>
#include "../linkedlist.h"

namespace my_utils {

	enum class E_OBJ_TAGS_t;
	class obj_root_element;
	class obj_vertex_element;
	class mtl_parser;
	template <class T> class ternary_search;
	template <class T> class linkedlist;
	
	
	class obj_parser
	{
	public:
		obj_parser(const char * pClassPath);
		virtual ~obj_parser();
		void processLine(const char* line);
		void saveAllData(std::ofstream & outputStream);
	private:
		void buildOBJTagsArray();
	private:
		linkedlist<obj_root_element> * i_pListObj;
		ternary_search<E_OBJ_TAGS_t>* i_pTagSearchEngine;
		mtl_parser* i_pMTLParser;
		const char* i_pClassPath;

		linkedlist<obj_vertex_element>* lstVertices;
		linkedlist<obj_vertex_element>* lstTextures;
		linkedlist<obj_vertex_element>* lstNormals;
	};
}

