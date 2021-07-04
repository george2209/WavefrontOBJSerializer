#pragma once
#include <fstream>
#include "abstractobj.h"
#include "../linkedlist.h"

namespace my_utils {

	class obj_vertex_element;
	class obj_face_element;

	class obj_root_element : public abstractobj {
	public:
		obj_root_element();
		virtual ~obj_root_element();
		void persist(std::ofstream* pOutputStream);
		bool parse(const char* pLine, int startIndex, int end = -1);
		bool parseVertexArray(const char* pLine, int startIndex);
		bool parseVertexTexture(const char* pLine, int startIndex);
		bool parseVertexNormal(const char* pLine, int startIndex);
		bool parseFace(const char* pLine, int startIndex);

	private:
		template <class T> bool parseFloatArray(linkedlist<T> * pList, const char* pLine, int startIndex);
		void parseVertexFace(const char* pLine, int startIndex, int index);
		

	private:
		char* i_pObjName;
		linkedlist<obj_vertex_element>* lstVertices;
		linkedlist<obj_vertex_element>* lstTextures;
		linkedlist<obj_vertex_element>* lstNormals;
		linkedlist< obj_face_element>* lstFaces;

	};

}
