#pragma once
#include <fstream>
#include "../linkedlist.h"
#include "abstractserializer.h"

namespace my_utils {

	class obj_vertex_element;
	class obj_face_element;

	class obj_root_element : protected abstractserializer {
	public:
		obj_root_element();
		virtual ~obj_root_element();
		void persist(std::ofstream* pOutputStream, obj_vertex_element* pArrVertices, obj_vertex_element* pArrTextures, obj_vertex_element* pArrNormals);
		bool parse(const char* pLine, int startIndex, int end = -1);
		bool parseVertexArray(const char* pLine, int startIndex, linkedlist<obj_vertex_element>* lstVertices);
		bool parseVertexTexture(const char* pLine, int startIndex, linkedlist<obj_vertex_element>* lstTextures);
		bool parseVertexNormal(const char* pLine, int startIndex, linkedlist<obj_vertex_element>* lstNormals);
		bool parseFace(const char* pLine, int startIndex);
		bool getParseMaterialName(const char* pLine, int startIndex, char ** i_arrOut);
		inline void setMTLID(short id)
		{
			this->i_mtlID = id;
		};

	private:
		template <class T> bool parseFloatArray(linkedlist<T> * pList, const char* pLine, int startIndex);
		void parseVertexFace(const char* pLine, int startIndex, int index);
		

	private:
		char* i_pObjName;
		short i_mtlID;
		linkedlist<obj_face_element>* lstFaces;
	};

}
