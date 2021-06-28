#pragma once
#include <fstream>
#include "abstractobj.h"
#include "linkedlist.h"

namespace my_utils {

	class obj_vertex_element;

	class obj_container : abstractobj {
	public:
		obj_container();
		virtual ~obj_container();
		void persist(std::ofstream* pOutputStream);
		bool parse(const char* pLine, int startIndex);
		bool parseVertexArray(const char* pLine, int startIndex);
		bool parseVertexTexture(const char* pLine, int startIndex);
		bool parseVertexNormal(const char* pLine, int startIndex);

	private:
		template <class T> bool parseFloatArray(linkedlist<T> * pList, const char* pLine, int startIndex);

	private:
		char* i_pObjName;
		linkedlist<obj_vertex_element>* lstVertices;
		linkedlist<obj_vertex_element>* lstTextures;
		linkedlist<obj_vertex_element>* lstNormals;
	};

}
